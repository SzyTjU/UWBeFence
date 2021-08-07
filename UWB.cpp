#include "UWB.h"


UWB::UWB(double x, double y, double z)//参数构造函数：
	:xx(x), yy(y), zz(z)
{
	//cout << "UWB基站添加成功" << endl;
}


UWB::UWB()//默认构造函数
	: UWB(0, 0, 0)
{
	//cout << "添加默认UWB基站" << endl;
}


UWB::UWB(const UWB& uwb)//拷贝构造函数
	: xx(uwb.xx), yy(uwb.yy), zz(uwb.zz)
{
	//cout << "UWB基站替换成功" << endl;
}


UWB::~UWB()//析构函数
{
	//cout << "UWB基站回收成功" << endl;
}


void UWB::setUWB(double x, double y, double z)//更改器
{
	xx = x;
	yy = y;
	zz = z;
}


double* UWB::getUWB()const//访问器
{
	double* res = new double[3];
	res[0] = xx;
	res[1] = yy;
	res[2] = zz;
	return res;
}


double UWB::measureDistance(UWB uwb2)const//测距（实际采用实测数据。目前为测试算法，暂时算欧式距离）
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