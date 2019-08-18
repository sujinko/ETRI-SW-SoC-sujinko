#ifndef CNNLAYER_HPP
#define CNNLAYER_HPP

#include "cnn1ch.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//-----------------------------다채널---------------------------//
class CNNLAYER{
public:
	CNN1CH *data; //채널까지 3차원을 구현하고싶음 , 단채널에서 2차원구현했으니 데이터형을 단채널클래스로 하고 한차원만 더 늘리면됨
	int H; 
	int W; 
    int ch;
	CNNLAYER();
	CNNLAYER(double***data,int H,int W, int ch);
    CNNLAYER(vector<Mat> img);
	~CNNLAYER();
	double** convolution(double***F, int F_row, int F_col, double bias, int stride, int padding);
    double*** convolution(double****F, int F_row, int F_col, double* bias, int F_ch, int stride, int padding);
	double*** maxpooling(int kernel ,int stride);
	double*** innerproduct(double**F, int F_row, int F_col);
	void activation();
    double*** softmax();
    void tempfunc();
};
//------------------------------3차원 입력 데이터---------------------/
CNNLAYER::CNNLAYER(double***data,int H,int W,int ch){
	this->H = H;
	this->W = W; 
    this->ch = ch;

	this->data = (CNN1CH*)malloc(ch * sizeof(CNN1CH));  //3차원 데이터 data 동적할당, 단채널클래스에서 이미 2차원 동적할당 ok

    for(int i=0; i<ch;i++){
        CNN1CH data2D(data[i],H,W); //CNNCH1의 생성자를 통해 2차원데이터 data2D 만들어줌
        this->data[i] = data2D;     // 만들어준 2차원 data2D를 ch만큼 돌려 3차원으로 만들어줌
    }  
}

//---------------------vector를 이용한 3차원 입력 데이터-----------------//
//vector는 사이즈를 확인해주는 함수가 있기 때문에 직접 사이즈를 몰라도 된다는 장점!
CNNLAYER::CNNLAYER(vector<Mat> img){
    this->ch = img.size();
    this->H = img[0].rows;  //무조건 이미지 한개는 들어오기 때문에 img[0]을 이용할수 있다!
    this->W = img[0].cols;
    this->data = (CNN1CH*)malloc(sizeof(CNN1CH)*this->ch);
    
    for(int i=0; i< this->ch; i++){
        CNN1CH data2D(img[i]);   //CNNCH1의 생성자를 통해 이미지인 2차원데이터 data2D 만들어줌
        this->data[i] = data2D;  //만들어준 2차원 data2D를 ch만큼 돌려 3차원으로 만들어줌
    }
}

CNNLAYER::~CNNLAYER(){
}

//-----------------------------2차원 convolution------------------------//
double**CNNLAYER::convolution(double***F, int F_row, int F_col, double bias, int stride, int padding){
    double ** data2D;
    double ** temp;
    
    int C_row = (this->H - F_row + 2*padding)/stride +1;
    int C_col = (this->W - F_col + 2*padding)/stride +1;

    data2D = (double**)malloc(C_row* sizeof(double*)); 
	for (int i = 0; i < C_row; i++){
		data2D[i] = (double*)malloc(C_col*sizeof(double));
        for(int j=0; j < C_col; j++){
            data2D[i][j] = 0;
        }
	}
	// ch만큼 2차원 conv 결과 더해서 하나의 2차원 데이터로 합쳐주기
    for(int i=0; i<this->ch; i++){
        temp = this->data[i].convolution(F[i], F_row, F_col, stride, padding);  // CNN1CH 클래스 내부의 conv 함수 호출

        for (int row=0; row<C_row; row++){
            for (int col=0; col<C_col; col++){
                data2D[row][col] += temp[row][col];
            }
        }
    }
    for (int row=0; row<C_row; row++){
            for (int col=0; col<C_col; col++){
                data2D[row][col] += bias;
            }
        }
    return data2D;
}

//-----------------------------3차원 convolution------------------------//
double*** CNNLAYER::convolution(double****F, int F_row, int F_col, double* bias, int F_ch, int stride, int padding){
    double*** data3D = (double***)malloc(sizeof(double**)*F_ch);
	// F_ch 즉 depth 만큼 3차원으로 할당
    for (int i=0; i<F_ch; i++){
        data3D[i] = this->convolution(F[i], F_row, F_col, bias[i], stride, padding); //다채널 클래스 내 즉 바로위의 conv함수 호출
    }
   
    return data3D;
}

//-----------------------------max pooling----------------------//
double*** CNNLAYER::maxpooling(int kernel,int stride){
    double*** data3D = (double***)malloc(sizeof(double**)*this->ch);
    for (int i=0; i<this->ch; i++)
       data3D[i] = this->data[i].maxpooling(kernel, stride);
    
    return data3D;
}

//-----------------------------inner product-----------------------------------//
double*** CNNLAYER::innerproduct(double**F, int F_row, int F_col){

	// ip 동적할당 (1x500)
    double*** data3D = (double***)malloc(sizeof(double**)*1);
    data3D[0] = (double**)malloc(sizeof(double*)*1);
    data3D[0][0] = (double*)malloc(sizeof(double)*F_row);
    for (int i=0; i<F_row; i++) data3D[0][0][i] = 0;
	
	// transfer filter 동적할당 (800x500)
    double** data2D;
    double** T_F = (double**)malloc(sizeof(double*)*F_col);
    for (int i=0; i<F_col; i++){
        T_F[i] = (double*)malloc(sizeof(double)*F_row);
        for (int j=0; j<F_row; j++){
            T_F[i][j] = F[j][i];
        }
    }

	// 입력사이즈 4x4에 맞게 transfer filter를 내적할수 있게 자르기
	// slice filter (16x500)
    double** slice_F = (double**)malloc(sizeof(double*)*this->H*this->W);
    for (int i=0; i<this->H*this->W; i++)
        slice_F[i] = (double*)malloc(sizeof(double)*F_row);
    
	
    for (int iter=0; iter<this->ch; iter++){
        for (int i=0; i<this->H*this->W; i++){
            for (int j=0; j<F_row; j++){
                slice_F[i][j] = T_F[iter*(this->H*this->W)+i][j]; // 16x500 짜리 ch(50)개 생성
            }
        }
        data2D = this->data[iter].innerproduct(slice_F,this->H*this->W,F_row); // 
        for (int i=0; i<F_row; i++){
             data3D[0][0][i] += data2D[0][i]; // 16x500 짜리를 1/+
        }
    }
    return data3D;
}

//---------------------------activation lelu---------------------------------//
void CNNLAYER::activation(){
    for (int i=0; i<this->ch; i++)
        this->data[i].activation();

    return;
}

//---------------------------확률 softmax---------------------------------//
double*** CNNLAYER::softmax(){
    double*** data3D = (double***)malloc(sizeof(double**)*this->ch);
    for (int i=0; i<this->ch; i++){
        data3D[i] = this->data[i].softmax();
    }

    return data3D;
}

//------------------이해못함????????????????--------------------------//
void CNNLAYER::tempfunc(){
    for (int i=0; i<this->ch; i++){
        for (int j=0; j<this->H; j++){
            for (int k=0; k<this->W; k++){
                if (this->data[i].data[j][k]<127)
                    this->data[i].data[j][k] = 1;
                else this->data[i].data[j][k] = 0;
            }
        }
    }
}


#endif