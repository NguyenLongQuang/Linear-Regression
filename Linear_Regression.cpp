#include<iostream>
#include<math.h>
#include<fstream>
#define learningrate 0.001
using namespace std;
//m stands for number of features
//n stands for number of training example

struct trainset{
	double x[100]={1};
	double y;
	
};

double Hypothesis_H(trainset TS, double theta[], int m){           //Hypothesis H
	double ans=0;
	for(int i=0;i<m+1;i++){
		ans+=TS.x[i]*theta[i];
	}
	return ans;
}

double Square_Cost_function(trainset TS[], double theta[], int n, int m){
	double ans=0;
	for(int i=0;i<n;i++){
		ans+=pow(Hypothesis_H(TS[i], theta, m)-TS[i].y,2);
	}
	ans/=n*2;
	return ans;
}
// define J(theta) as Square Cost Function(theta)

double Derivate_J (trainset TS[], double theta[], int n, int m, int t){
	double ans=0;
	for(int i=0;i<n;i++){
		ans+=TS[i].x[t]*(Hypothesis_H(TS[i], theta, m)-TS[i].y);
	}
	ans/=n;
	return ans;
}

void Gradient_descent_runner(double *t, trainset TS[], int n, int m){
	double tmp[100];
	for(int i=0;i<300000;i++){
		for(int j=0;j<m+1;j++){
			tmp[j]=*(t+j)-learningrate*Derivate_J(TS, t, n, m, j);
		}
		for(int j=0;j<m+1;j++){
			*(t+j)=tmp[j];
		}
	}
}

void Normalize(trainset *p, double *mx, double *my, int n, int m){
	//Normalize Y
	double max_y=(*p).y;
	for(int i=0;i<n;i++){
		if(max_y<(*(p+i)).y) max_y=(*(p+i)).y;			//find max Y
	}
	for(int i=0;i<n;i++){
		(*(p+i)).y/=max_y;									
	} 
	*my=max_y;
	
	//Normalize X
	double max_x[100];
	for(int j=0;j<m;j++){
		max_x[j]=(*p).x[j+1];
	}
	for(int j=0;j<m;j++){
		for(int i=0;i<n;i++){
				if(max_x[j]<(*(p+i)).x[j+1]) max_x[j]=(*(p+i)).x[j+1];
		}
	}
	for(int j=0;j<m;j++){
		for(int i=0;i<n;i++){
				(*(p+i)).x[j+1]/=max_x[j];
		}
	}
	for(int j=0;j<m;j++){
		*(mx+j)=max_x[j];
	}
}

	

int main(){
	double theta[100]={}, X[100], Y, y;
	double *mx, *my=&Y, *t;
	mx=X;
	t=theta;
	int n,m;
	trainset TS[100];
	trainset ans;
	trainset *p;
	p=TS;
	
	cout<<"Input number of training examples: ";
	cin>>n;
	
	cout<<"Input number of features: ";
	cin>>m;
	
	cout<<"Input training set:\n";
	for(int i=0;i<n;i++){
		for(int j=1;j<m+1;j++){
			cin>>TS[i].x[j];
		}
		cin>>TS[i].y;
	}
	
	cout<<"Input X: ";
	for(int i=1;i<m+1;i++){
		cin>>ans.x[i];
	}

	Normalize(p,mx,my,n,m);
	
	Gradient_descent_runner(t,TS,n,m);
	
	for(int i=1;i<m+1;i++){
		ans.x[i]/=X[i-1];
	} //Normalize "input" X


	y=Y*Hypothesis_H(ans,theta,m);
	
	cout<<"Prediction of Y: "<<y;
}
	
