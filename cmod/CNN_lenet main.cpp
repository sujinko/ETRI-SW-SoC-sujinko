#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <string>
#include "cnnlayer.hpp"
#include "file_manager.hpp"
#include <algorithm>

using namespace cv;
using namespace std;



bool cmp(double a, double b){
    return a > b;
}

int main(){	

	//////////////////////////////////////////////////////////////////////////
    //                              READ IMG                                //
    //////////////////////////////////////////////////////////////////////////
    string img_name = read_image("lenet/image/");                           //
    Mat img = imread(img_name,IMREAD_GRAYSCALE);                            //
    vector<Mat> split_img;                                                  //
    split(img,split_img);                                                   //
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //                          CHECK VALID IMAGE                           //
    //                          28 x 28 IMAGE INPUT                         //
    //////////////////////////////////////////////////////////////////////////
    if (img.rows != 28 || img.cols != 28){                                  //
        cout << "image size wrong!!\nNEED 28 x 28 image\n";                 //
        return -1;                                                          //
    }                                                                       //
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //                          GET FILTER AND BIAS                         //
    //////////////////////////////////////////////////////////////////////////
    double***** filter_conv = read_filter3D_mult_all("lenet/filter_conv/");    
    double*** filter_ip = read_filter2D_all("lenet/filter_ip/");             
    double** bias = read_bias_all("lenet/bias/");   
    int kkk;
    
	double**** F_conv1  = filter_conv[0];
	double**** F_conv2  = filter_conv[1];
	double** F_ip1      = filter_ip[0];
	double** F_ip2      = filter_ip[1];
	double* B_conv1     = bias[0];
	double* B_conv2     = bias[1];
	double* B_ip1       = bias[2];
	double* B_ip2       = bias[3];

	CNNLAYER data(split_img);                                                   // input image
    data.tempfunc();															
    CNNLAYER conv1(data.convolution(F_conv1,5,5,B_conv1,20,1,0),24,24,20);		// CNNLAYER의 3차원 conv함수 
	CNNLAYER pool1(conv1.maxpooling(2,2),12,12,20);
	CNNLAYER conv2(pool1.convolution(F_conv2,5,5,B_conv2,50,1,0),8,8,50);
	CNNLAYER pool2(conv2.maxpooling(2,2),4,4,50);  
	CNNLAYER ip1(pool2.innerproduct(F_ip1,500,800),1,500,1);
	CNNLAYER ip2(ip1.innerproduct(F_ip2,10,500),1,10,1);
	CNNLAYER prob(ip2.softmax(),1,10,1);

    double top[10];
    for (int i=0; i<10; i++){
        top[i] = prob.data[0].data[0][i]; 
    }
    
	sort(top,top+10,cmp);
 
    for (int i=0; i<10; i++){
        if (prob.data[0].data[0][i] == top[0]){
            cout << i << endl;
            break;
        }
    }

    imshow("image",img);
    waitKey(0);
    
	return 0;
}