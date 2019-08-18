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

//-----------------------------��ä��---------------------------//
class CNNLAYER{
public:
	CNN1CH *data; //ä�α��� 3������ �����ϰ���� , ��ä�ο��� 2�������������� ���������� ��ä��Ŭ������ �ϰ� �������� �� �ø����
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
//------------------------------3���� �Է� ������---------------------/
CNNLAYER::CNNLAYER(double***data,int H,int W,int ch){
	this->H = H;
	this->W = W; 
    this->ch = ch;

	this->data = (CNN1CH*)malloc(ch * sizeof(CNN1CH));  //3���� ������ data �����Ҵ�, ��ä��Ŭ�������� �̹� 2���� �����Ҵ� ok

    for(int i=0; i<ch;i++){
        CNN1CH data2D(data[i],H,W); //CNNCH1�� �����ڸ� ���� 2���������� data2D �������
        this->data[i] = data2D;     // ������� 2���� data2D�� ch��ŭ ���� 3�������� �������
    }  
}

//---------------------vector�� �̿��� 3���� �Է� ������-----------------//
//vector�� ����� Ȯ�����ִ� �Լ��� �ֱ� ������ ���� ����� ���� �ȴٴ� ����!
CNNLAYER::CNNLAYER(vector<Mat> img){
    this->ch = img.size();
    this->H = img[0].rows;  //������ �̹��� �Ѱ��� ������ ������ img[0]�� �̿��Ҽ� �ִ�!
    this->W = img[0].cols;
    this->data = (CNN1CH*)malloc(sizeof(CNN1CH)*this->ch);
    
    for(int i=0; i< this->ch; i++){
        CNN1CH data2D(img[i]);   //CNNCH1�� �����ڸ� ���� �̹����� 2���������� data2D �������
        this->data[i] = data2D;  //������� 2���� data2D�� ch��ŭ ���� 3�������� �������
    }
}

CNNLAYER::~CNNLAYER(){
}

//-----------------------------2���� convolution------------------------//
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
	// ch��ŭ 2���� conv ��� ���ؼ� �ϳ��� 2���� �����ͷ� �����ֱ�
    for(int i=0; i<this->ch; i++){
        temp = this->data[i].convolution(F[i], F_row, F_col, stride, padding);  // CNN1CH Ŭ���� ������ conv �Լ� ȣ��

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

//-----------------------------3���� convolution------------------------//
double*** CNNLAYER::convolution(double****F, int F_row, int F_col, double* bias, int F_ch, int stride, int padding){
    double*** data3D = (double***)malloc(sizeof(double**)*F_ch);
	// F_ch �� depth ��ŭ 3�������� �Ҵ�
    for (int i=0; i<F_ch; i++){
        data3D[i] = this->convolution(F[i], F_row, F_col, bias[i], stride, padding); //��ä�� Ŭ���� �� �� �ٷ����� conv�Լ� ȣ��
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

	// ip �����Ҵ� (1x500)
    double*** data3D = (double***)malloc(sizeof(double**)*1);
    data3D[0] = (double**)malloc(sizeof(double*)*1);
    data3D[0][0] = (double*)malloc(sizeof(double)*F_row);
    for (int i=0; i<F_row; i++) data3D[0][0][i] = 0;
	
	// transfer filter �����Ҵ� (800x500)
    double** data2D;
    double** T_F = (double**)malloc(sizeof(double*)*F_col);
    for (int i=0; i<F_col; i++){
        T_F[i] = (double*)malloc(sizeof(double)*F_row);
        for (int j=0; j<F_row; j++){
            T_F[i][j] = F[j][i];
        }
    }

	// �Է»����� 4x4�� �°� transfer filter�� �����Ҽ� �ְ� �ڸ���
	// slice filter (16x500)
    double** slice_F = (double**)malloc(sizeof(double*)*this->H*this->W);
    for (int i=0; i<this->H*this->W; i++)
        slice_F[i] = (double*)malloc(sizeof(double)*F_row);
    
	
    for (int iter=0; iter<this->ch; iter++){
        for (int i=0; i<this->H*this->W; i++){
            for (int j=0; j<F_row; j++){
                slice_F[i][j] = T_F[iter*(this->H*this->W)+i][j]; // 16x500 ¥�� ch(50)�� ����
            }
        }
        data2D = this->data[iter].innerproduct(slice_F,this->H*this->W,F_row); // 
        for (int i=0; i<F_row; i++){
             data3D[0][0][i] += data2D[0][i]; // 16x500 ¥���� 1/+
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

//---------------------------Ȯ�� softmax---------------------------------//
double*** CNNLAYER::softmax(){
    double*** data3D = (double***)malloc(sizeof(double**)*this->ch);
    for (int i=0; i<this->ch; i++){
        data3D[i] = this->data[i].softmax();
    }

    return data3D;
}

//------------------���ظ���????????????????--------------------------//
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