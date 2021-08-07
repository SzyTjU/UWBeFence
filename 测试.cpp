#include"E_Fence.h"
//测试代码
int main()
{
	int s = 6;
	UWB* f;
	f = new UWB[s];
	f[0].setUWB(162.9447, 55.6996, 0);
	f[1].setUWB(181.1584,109.3763,0 );
	f[2].setUWB(25.3974,191.5014,0 );
	f[3].setUWB(182.6752,192.9777,0 );
	f[4].setUWB(126.4718,31.5226,0 );
	f[5].setUWB(19.5081,194.1186,0 );

	E_Fence a(f, s);
    UWB* m=a.getFence();
	cout << "所有点坐标为：" << endl;
	for (int i = 0; i < s; i++) {
		cout << i + 1 << "、x:" << m[i].getUWB()[0] << ",y:" << m[i].getUWB()[1] << ",z:" << m[i].getUWB()[2] << endl;
	}
    cout << endl;//输出所有点坐标

	E_Fence b=a.convex_hull(a);//凸包算法
	int s1 = b.getFenceSize();
	UWB* n=b.getFence();
	for (int i = 0; i < s1; i++) {//按逆时针顺序依次输出凸包顶点坐标
		cout << i + 1 << "、x:" << n[i].getUWB()[0] << ",y:" << n[i].getUWB()[1] << ",z:" << n[i].getUWB()[2] << endl;
	}

	double e = 0.01;//精度标准
	UWB u(75.2, 105.0, 1.8);//待判别UWB标签
	bool Bool=b.in_out(b, u, e);//内外判别算法
	cout << Bool << endl;
		

}