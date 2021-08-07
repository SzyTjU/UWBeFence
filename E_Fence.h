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
	UWB* Fence;                                    //����Χ���ĸ���UWB��վ��UWB�ࣩ
	int size;                                      //����Χ����UWB��վ����	                                
public:
	E_Fence(UWB* Fen, int s);                      //�������캯��
	~E_Fence();                                    //��������
	E_Fence(const E_Fence& e_fence);               //�������캯��
	void setFence(UWB* Fence,int size);            //������
	int getFenceSize()const;                       //�鿴Χ����UWB��վ����
	UWB* getFence()const;                          //�����������ʸ�UWB��վ
	E_Fence convex_hull(E_Fence Fen1);             //͹���㷨
	bool in_out(E_Fence fen1,UWB u1,double e)const;//�ж�ĳ�����Ƿ���Χ���ڣ��ǣ�����1���񣬷���0��
};
#endif 



