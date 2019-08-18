#ifndef CNN1CH_HPP
#define CNN1CH_HPP

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//---------------------------단채널---------------------------------//
class CNN1CH{
public:
	double **data;
	int H;
	int W;

	CNN1CH();
	CNN1CH(double**data,int H,int W);
	CNN1CH(Mat img);
	~CNN1CH();
	double** convolution(double**F, int F_row, int F_col, int stride, int padding);
	double** maxpooling(int kernel ,int stride);
	double** innerproduct(double**F, int F_row, int F_col);
	void activation();
	double** softmax();
};
//-------------------------2차원 입력 데이터 -------------------------------//
CNN1CH::CNN1CH(double**data,int H,int W){
	this->H = H;              //this 바로뒤 H가 클래스내, =H 가 함수내 
	this->W = W; 

	this->data = (double**)malloc(H * sizeof(double*));  
	for(int i=0 ; i<H; i++){
		this->data[i] = (double*)malloc( W * sizeof(double));
		for(int j=0; j<W; j++){
			this->data[i][j] = data[i][j];
		}
	}
}
//------------------------초기 이미지 데이터 입력---------------------------// 
CNN1CH::CNN1CH(Mat img){
	this->H = img.rows;
	this->W = img.cols;
	this->data = (double**)malloc(sizeof(double*)*this->H);
	for (int i=0; i<this->H; i++){
		this->data[i] = (double*)malloc(sizeof(double)*this->W);
		for (int j=0; j<this->W; j++){
			this->data[i][j] = img.at<uchar>(i,j);  //IMREAD_GRAYSCALE
		}
	}
}

CNN1CH::~CNN1CH()
{
}
//----------------------------padding 함수(메인에서 함수 호출X  -> 클래스 함수로 굳이 만들필요 X)----------------------------//
double** padding(double **data, int H, int W,int padding_size){
	
	double **padding;
	int padding_row = H+2*padding_size;
	int padding_col = W+2*padding_size;
	
    padding = (double**)malloc(padding_row * sizeof(double*));  
	for (int i = 0; i < padding_row; i++)
	{
		padding[i] = (double*)malloc(padding_col * sizeof(double));
	}
	
	for(int i=0; i<padding_row; i++){
			for(int j=0; j<padding_col; j++)
			{
				padding[i][j] = 0;
			}	
	}
	
	for(int i=0; i<padding_row; i++){
			for(int j=0; j<padding_col; j++){
				if(i<padding_size|| j<padding_size || 
				i>=padding_row-padding_size || j>=padding_col-padding_size) padding[i][j] = 0;
				else padding[i][j] = data[i-padding_size][j-padding_size];
			}
	}
	
	return padding;
}
//-----------------------------convolution------------------------//
double** CNN1CH::convolution(double**F, int F_row, int F_col, int stride, int padding_size){

	double **C;
	int C_row = (this->H - F_row+ 2*padding_size)/stride + 1;
    int C_col = (this->W - F_col+ 2*padding_size)/stride + 1;

    double ** pad = padding(this->data,this->H,this->W,padding_size);

	C = (double**)malloc(C_row* sizeof(double*));  
	for (int i = 0; i < C_row; i++){
		C[i] = (double*)malloc( C_col * sizeof(double));
	}
	
	for(int i=0; i<C_row; i++){
		for(int j=0; j<C_col; j++){
			C[i][j] = 0;
		}
	}

	for(int i=0; i<C_row; i++){  
     	for(int j=0; j<C_col; j++){
			double temp = 0;
         	for(int k=0; k<F_row;k++){
             	for(int l=0; l<F_col; l++)
					temp += double(pad[k+i*stride][l+j*stride] * F[k][l]); 
            }
			C[i][j] = temp;		
        }    
    }
	
    return C;
}
//-----------------------------max pooling----------------------//	
double** CNN1CH::maxpooling(int kernel, int stride){
	double max = 0;
	double **pooling;
	int pooling_row = (this->H-kernel)/stride +1;
	int pooling_col = (this->W-kernel)/stride +1;
	
    pooling = (double**)malloc(pooling_row* sizeof(double*));  
	for (int i = 0; i < pooling_row; i++){
		pooling[i] = (double*)malloc(pooling_col * sizeof(double));
		
	}
	
	for(int i=0; i<pooling_row; i++){
		for(int j=0; j<pooling_col; j++){
			pooling[i][j] = 0;
		}
	}
	
	for(int i=0; i<pooling_row; i++){  
		for(int j=0; j<pooling_col; j++){
			max=this->data[i*stride][j*stride];    //max = INT_MIN;
			for(int k=0; k<kernel;k++){
				for( int l=0; l<kernel; l++){
					if(max<this->data[i*stride+k][j*stride+l]) max = this->data[i*stride+k][j*stride+l];
				}
			} 
			pooling[i][j] = max;
		}
	}
	return pooling;
}
//-----------------------------inner product-----------------------------------//
double** CNN1CH::innerproduct(double**F, int F_row, int F_col){
	double**ip = (double**)malloc(1* sizeof(double*)); 
	ip[0] = (double*)malloc(F_col * sizeof(double));
	
	for (int i = 0; i < F_col; i++){
		for (int j = 0; j < this->H*this->W; j++){
			ip[0][i] += this->data[j/this->W][j%this->W] * F[j][i];
		}		
	}
	return ip;
}
//---------------------------activation lelu---------------------------------//
void CNN1CH::activation(){
	double sigma;
	for(int i=0; i<this->H; i++){
		for(int j=0; j<this->W; j++){
			sigma = this->data[i][j];
			if(sigma < 0){
				sigma = 0;
			}
			this->data[i][j] = sigma;  // 자기자신에게 쏘기
		}
	}
	return;
}


double** CNN1CH::softmax(){
	double** data2D = (double**)malloc(sizeof(double*)*this->H);
	for (int i=0; i<this->H; i++)
		data2D[i] = (double*)malloc(sizeof(double)*this->W);
	
	double sum = 0;
	for (int i=0; i<this->H; i++){
		for (int j=0; j<this->W; j++){
			sum += exp(this->data[i][j]);
		}
	}

	for (int i=0; i<this->H; i++){
		for (int j=0; j<this->W; j++){
			data2D[i][j] = exp(this->data[i][j])/sum;
		}
	}
	return data2D;
}

#endif