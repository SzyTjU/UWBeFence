#include "E_Fence.h"


E_Fence::E_Fence(UWB* Fen, int s=8)//参数构造函数，默认基站个数为8
	: Fence(Fen),size(s)
{
	//cout << "电子围栏建立成功" << endl;
}


E_Fence::E_Fence(const E_Fence& fence)//拷贝构造函数
	: size(fence.size),Fence(fence.Fence)
{
	//cout << "电子围栏拷贝成功" << endl;
}


E_Fence::~E_Fence()//析构函数
{
	//cout << "电子围栏回收成功" << endl;
}


void E_Fence::setFence(UWB* Fen, int s=8)//更改器
{
	size = s;
	Fence = Fen;
}


int E_Fence::getFenceSize()const//查看围栏基站个数
{
	return size;
}


UWB* E_Fence::getFence()const//访问各基站，再通过ｇｅｔＵＷＢ函数即可得到各基站坐标
{
	UWB* res = new UWB[size];
	for (int i = 0; i < size; i++)
	{
	    res[i] = Fence[i];
	}
	return res;
}


E_Fence E_Fence::convex_hull(E_Fence fen1)//凸包算法
{
	//1、找出坐标y值最小的基站：
	int min_id = 0;
	double miny = 10000;
	double p;
	for (int i1 = 0; i1 < fen1.size; i1++) {
		p = fen1.Fence[i1].getUWB()[1];//读取电子围栏内序号i1的UWB基站的y坐标
		if (p < miny) {
			miny = p;
			min_id = i1;
		}
	}
	//min_id存储了坐标y值最小的基站的序号

	//2、计算其余基站与该基站的连线与x轴之间夹角的余弦值
	double coss;
	double* mcos;
	mcos = new double[fen1.size];
	for (int i2 = 0; i2 < fen1.size; i2++) {
		if (i2 == min_id) {
			mcos[i2] = 2;
		}
		else {
			coss = (fen1.Fence[i2].getUWB()[0] - fen1.Fence[min_id].getUWB()[0]) / sqrt((fen1.Fence[i2].getUWB()[0] - fen1.Fence[min_id].getUWB()[0]) * (fen1.Fence[i2].getUWB()[0] - fen1.Fence[min_id].getUWB()[0]) + (fen1.Fence[i2].getUWB()[1] - fen1.Fence[min_id].getUWB()[1]) * (fen1.Fence[i2].getUWB()[1] - fen1.Fence[min_id].getUWB()[1]));
			mcos[i2] = coss;//序号i2的UWB基站与序号min_id的基站的连线与x轴之间夹角的余弦值
		}
	}

	//3、按余弦值从大到小排序,bubble排序法，排序结果存储在电子围栏对象fen1中
	double temp_cos;
	for (int i3 = 0; i3 < size; i3++) {
		for (int j = 0; j < fen1.size - i3 - 1; j++) {      //bubble sorting
			if (mcos[j] < mcos[j + 1]) {
				temp_cos = mcos[j];
				mcos[j] = mcos[j + 1];
				mcos[j + 1] = temp_cos;

				UWB temp_UWB = fen1.Fence[j];
				fen1.Fence[j] = fen1.Fence[j + 1];
				fen1.Fence[j + 1] = temp_UWB;
			}
		}
	}

	//4、返回结果
	vector <UWB>outUWB;//模拟栈
	outUWB.push_back(fen1.Fence[0]);//将最低点压入栈中（y最小）
	outUWB.push_back(fen1.Fence[1]);//将余弦值最大的点压入栈中
	int i4 = 2;
	while (true) {
		if (i4 == fen1.size) {
			break;//遍历结束的终止条件
		}
		UWB a=outUWB[outUWB.size() - 2];//上上次压入栈的基站A
		UWB b=outUWB[outUWB.size() - 1];//上一次压入栈的基站B（栈顶元素）
		UWB c= fen1.Fence[i4];//待判定的基站C
		double area2 = (b.getUWB()[0] - a.getUWB()[0]) * (c.getUWB()[1] - a.getUWB()[1]) - (b.getUWB()[1] - a.getUWB()[1]) * (c.getUWB()[0] - a.getUWB()[0]);
		if (area2 > 0) {//栈顶两个点（AB）与该点（C)三点向量是逆时针转动
			outUWB.push_back(fen1.Fence[i4]);//压入C
			i4 = i4 + 1;//遍历下一个基站
		}
		else {//栈顶两个点（AB）与该点（C)三点向量是顺时针转动
			outUWB.pop_back();//将栈顶元素（B）推出
		}
	}

    //存储数据为一个新的电子围栏对象
	int k = outUWB.size();//基站个数
	UWB* f;
	f = new UWB[k];
	for (int i5 = 0; i5 < k; i5++) {
		f[i5] = outUWB[i5];//逐个写入UWB基站信息
	}
	E_Fence convex_fen(f, k);//将凸包写入电子围栏对象convex_fen
	return convex_fen;
}



bool E_Fence::in_out(E_Fence fen1, UWB u1, double e)const
{//内外判别算法，输入依次为围栏对象（凸包）、待判别的UWB标签、判别精度（0.01/0.03/0.05）
//使用说明：算法按照理想平面问题进行分析，即围栏各顶点、待判别基站均处于同一平面，考虑到
	//实际情况下存在高度差的给面积计算带来的影响，同时为了设置一定的弹性空间，应设置判别精度
	//根据测试，高度差带来的影响非常微小，在e=0.01下不影响算法判别结果
	//因此，建议根据弹性空间的设置情况，取e的值
	//另：输入的凸包顶点坐标必须按照顺序排列好（建议逆时针）,
	//采用凸包算法convex_hull()的返回值即可
	//否则无法保证判别结果正确性
	
	int n = fen1.size;//凸包顶点数量
	double S1 = 0, area, a, b, c, p;
	for (int j1 = 0; j1 < n - 2; j1++)//计算凸n边形面积S1,基于海伦公式
	{
		a = fen1.Fence[0].measureDistance(fen1.Fence[j1+1]); 
		b = fen1.Fence[0].measureDistance(fen1.Fence[j1+2]);
		c = fen1.Fence[j1+1].measureDistance(fen1.Fence[j1+2]);
		p = 0.5 * (a + b + c);
		area = sqrt(p * (p - a) * (p - b) * (p - c));//海伦公式
		S1 = S1 + area;
	}
	cout << "电子围栏所围面积S1为：" << S1 << endl;

	double S2 = 0, S, a1, b1, c1, p1;
	for (int j2 = 0; j2 < n; j2++)//计算S2，基于海伦公式
	{
		if (j2 != n - 1)
		{
			a1 = u1.measureDistance(fen1.Fence[j2]);  
			b1 = u1.measureDistance(fen1.Fence[j2+1]); 
			c1 = fen1.Fence[j2].measureDistance(fen1.Fence[j2+1]);
		}
		else
		{
			a1 = u1.measureDistance(fen1.Fence[j2]);
			b1 = u1.measureDistance(fen1.Fence[0]);
			c1 =fen1.Fence[0].measureDistance(fen1.Fence[j2]);
		}
		p1 = 0.5 * (a1 + b1 + c1);
		S = sqrt(p1 * (p1 - a1) * (p1 - b1) * (p1 - c1));//海伦公式
		S2 = S2 + S;
	}
	cout << "S2为：" << S2 << endl;


	if ((1+e) * S1 > S2 && S2 > (1-e) * S1)//S1与S2足够接近，则可认为待判别标签在电子围栏内
	{
		cout << "待判别点在围栏内" << endl;
		return true;
	}
	else//S1与S2差异较大，则认为待判别标签在电子围栏外
	{
		cout << "待判别点在围栏外" << endl;
		return false;
	}
}
