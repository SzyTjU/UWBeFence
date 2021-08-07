#include "UWB.h"


UWB::UWB(double x, double y, double z)//�������캯����
	:xx(x), yy(y), zz(z)
{
	//cout << "UWB��վ��ӳɹ�" << endl;
}


UWB::UWB()//Ĭ�Ϲ��캯��
	: UWB(0, 0, 0)
{
	//cout << "���Ĭ��UWB��վ" << endl;
}


UWB::UWB(const UWB& uwb)//�������캯��
	: xx(uwb.xx), yy(uwb.yy), zz(uwb.zz)
{
	//cout << "UWB��վ�滻�ɹ�" << endl;
}


UWB::~UWB()//��������
{
	//cout << "UWB��վ���ճɹ�" << endl;
}


void UWB::setUWB(double x, double y, double z)//������
{
	xx = x;
	yy = y;
	zz = z;
}


double* UWB::getUWB()const//������
{
	double* res = new double[3];
	res[0] = xx;
	res[1] = yy;
	res[2] = zz;
	return res;
}


double UWB::measureDistance(UWB uwb2)const//��ࣨʵ�ʲ���ʵ�����ݡ�ĿǰΪ�����㷨����ʱ��ŷʽ���룩
{
	double xx1 = uwb2.getUWB()[0]; 
	double yy1 = uwb2.getUWB()[1];
	double zz1 = uwb2.getUWB()[2];
	double a = (xx - xx1)*(xx-xx1);
	double b = (yy - yy1) * (yy - yy1);
	double c = (zz - zz1) * (zz - zz1);
	double dis = sqrt(a+b+c);
	return dis;
}