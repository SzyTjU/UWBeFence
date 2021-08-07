#ifndef E_FENCE_H
#define E_FENCE_H
#include"UWB.h"
#include <math.h>
#include <stdio.h>
#include<stdlib.h>
#include<vector>

class E_Fence
{
private:
	UWB* Fence;                                    //属于围栏的各个UWB基站（UWB类）
	int size;                                      //属于围栏的UWB基站个数	                                
public:
	E_Fence(UWB* Fen, int s);                      //参数构造函数
	~E_Fence();                                    //析构函数
	E_Fence(const E_Fence& e_fence);               //拷贝构造函数
	void setFence(UWB* Fence,int size);            //更改器
	int getFenceSize()const;                       //查看围栏的UWB基站个数
	UWB* getFence()const;                          //访问器，访问各UWB基站
	E_Fence convex_hull(E_Fence Fen1);             //凸包算法
	bool in_out(E_Fence fen1,UWB u1,double e)const;//判断某个点是否在围栏内（是，返回1；否，返回0）
};
#endif 



