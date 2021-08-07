#ifndef UWB_H
#define UWB_H
#include<iostream>
using namespace std;

class UWB
{
private:
	//UWB基站在平面坐标系下的坐标（xx,yy,zz)
	double xx; //单位m
	double yy;
	double zz;
public:
	UWB(double xx, double yy, double zz);        //参数构造函数
	UWB();                                       //默认构造函数
	~UWB();                                      //析构函数
	UWB(const UWB& uwb);                         //拷贝构造函数
	void setUWB(double xx, double yy, double zz);//更改器
	double* getUWB()const;                       //访问器
	double measureDistance(UWB uwb)const;        //测量本基站和另一基站的距离（m）
};
#endif

