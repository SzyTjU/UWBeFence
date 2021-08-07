#ifndef UWB_H
#define UWB_H
#include<iostream>
using namespace std;

class UWB
{
private:
	//UWB��վ��ƽ������ϵ�µ����꣨xx,yy,zz)
	double xx; //��λm
	double yy;
	double zz;
public:
	UWB(double xx, double yy, double zz);        //�������캯��
	UWB();                                       //Ĭ�Ϲ��캯��
	~UWB();                                      //��������
	UWB(const UWB& uwb);                         //�������캯��
	void setUWB(double xx, double yy, double zz);//������
	double* getUWB()const;                       //������
	double measureDistance(UWB uwb)const;        //��������վ����һ��վ�ľ��루m��
};
#endif

