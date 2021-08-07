#include "E_Fence.h"


E_Fence::E_Fence(UWB* Fen, int s=8)//�������캯����Ĭ�ϻ�վ����Ϊ8
	: Fence(Fen),size(s)
{
	//cout << "����Χ�������ɹ�" << endl;
}


E_Fence::E_Fence(const E_Fence& fence)//�������캯��
	: size(fence.size),Fence(fence.Fence)
{
	//cout << "����Χ�������ɹ�" << endl;
}


E_Fence::~E_Fence()//��������
{
	//cout << "����Χ�����ճɹ�" << endl;
}


void E_Fence::setFence(UWB* Fen, int s=8)//������
{
	size = s;
	Fence = Fen;
}


int E_Fence::getFenceSize()const//�鿴Χ����վ����
{
	return size;
}


UWB* E_Fence::getFence()const//���ʸ���վ����ͨ�������գףº������ɵõ�����վ����
{
	UWB* res = new UWB[size];
	for (int i = 0; i < size; i++)
	{
	    res[i] = Fence[i];
	}
	return res;
}


E_Fence E_Fence::convex_hull(E_Fence fen1)//͹���㷨
{
	//1���ҳ�����yֵ��С�Ļ�վ��
	int min_id = 0;
	double miny = 10000;
	double p;
	for (int i1 = 0; i1 < fen1.size; i1++) {
		p = fen1.Fence[i1].getUWB()[1];//��ȡ����Χ�������i1��UWB��վ��y����
		if (p < miny) {
			miny = p;
			min_id = i1;
		}
	}
	//min_id�洢������yֵ��С�Ļ�վ�����

	//2�����������վ��û�վ��������x��֮��нǵ�����ֵ
	double coss;
	double* mcos;
	mcos = new double[fen1.size];
	for (int i2 = 0; i2 < fen1.size; i2++) {
		if (i2 == min_id) {
			mcos[i2] = 2;
		}
		else {
			coss = (fen1.Fence[i2].getUWB()[0] - fen1.Fence[min_id].getUWB()[0]) / sqrt((fen1.Fence[i2].getUWB()[0] - fen1.Fence[min_id].getUWB()[0]) * (fen1.Fence[i2].getUWB()[0] - fen1.Fence[min_id].getUWB()[0]) + (fen1.Fence[i2].getUWB()[1] - fen1.Fence[min_id].getUWB()[1]) * (fen1.Fence[i2].getUWB()[1] - fen1.Fence[min_id].getUWB()[1]));
			mcos[i2] = coss;//���i2��UWB��վ�����min_id�Ļ�վ��������x��֮��нǵ�����ֵ
		}
	}

	//3��������ֵ�Ӵ�С����,bubble���򷨣��������洢�ڵ���Χ������fen1��
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

	//4�����ؽ��
	vector <UWB>outUWB;//ģ��ջ
	outUWB.push_back(fen1.Fence[0]);//����͵�ѹ��ջ�У�y��С��
	outUWB.push_back(fen1.Fence[1]);//������ֵ���ĵ�ѹ��ջ��
	int i4 = 2;
	while (true) {
		if (i4 == fen1.size) {
			break;//������������ֹ����
		}
		UWB a=outUWB[outUWB.size() - 2];//���ϴ�ѹ��ջ�Ļ�վA
		UWB b=outUWB[outUWB.size() - 1];//��һ��ѹ��ջ�Ļ�վB��ջ��Ԫ�أ�
		UWB c= fen1.Fence[i4];//���ж��Ļ�վC
		double area2 = (b.getUWB()[0] - a.getUWB()[0]) * (c.getUWB()[1] - a.getUWB()[1]) - (b.getUWB()[1] - a.getUWB()[1]) * (c.getUWB()[0] - a.getUWB()[0]);
		if (area2 > 0) {//ջ�������㣨AB����õ㣨C)������������ʱ��ת��
			outUWB.push_back(fen1.Fence[i4]);//ѹ��C
			i4 = i4 + 1;//������һ����վ
		}
		else {//ջ�������㣨AB����õ㣨C)����������˳ʱ��ת��
			outUWB.pop_back();//��ջ��Ԫ�أ�B���Ƴ�
		}
	}

    //�洢����Ϊһ���µĵ���Χ������
	int k = outUWB.size();//��վ����
	UWB* f;
	f = new UWB[k];
	for (int i5 = 0; i5 < k; i5++) {
		f[i5] = outUWB[i5];//���д��UWB��վ��Ϣ
	}
	E_Fence convex_fen(f, k);//��͹��д�����Χ������convex_fen
	return convex_fen;
}



bool E_Fence::in_out(E_Fence fen1, UWB u1, double e)const
{//�����б��㷨����������ΪΧ������͹���������б��UWB��ǩ���б𾫶ȣ�0.01/0.03/0.05��
//ʹ��˵�����㷨��������ƽ��������з�������Χ�������㡢���б��վ������ͬһƽ�棬���ǵ�
	//ʵ������´��ڸ߶Ȳ�ĸ�������������Ӱ�죬ͬʱΪ������һ���ĵ��Կռ䣬Ӧ�����б𾫶�
	//���ݲ��ԣ��߶Ȳ������Ӱ��ǳ�΢С����e=0.01�²�Ӱ���㷨�б���
	//��ˣ�������ݵ��Կռ�����������ȡe��ֵ
	//�������͹������������밴��˳�����кã�������ʱ�룩,
	//����͹���㷨convex_hull()�ķ���ֵ����
	//�����޷���֤�б�����ȷ��
	
	int n = fen1.size;//͹����������
	double S1 = 0, area, a, b, c, p;
	for (int j1 = 0; j1 < n - 2; j1++)//����͹n�������S1,���ں��׹�ʽ
	{
		a = fen1.Fence[0].measureDistance(fen1.Fence[j1+1]); 
		b = fen1.Fence[0].measureDistance(fen1.Fence[j1+2]);
		c = fen1.Fence[j1+1].measureDistance(fen1.Fence[j1+2]);
		p = 0.5 * (a + b + c);
		area = sqrt(p * (p - a) * (p - b) * (p - c));//���׹�ʽ
		S1 = S1 + area;
	}
	cout << "����Χ����Χ���S1Ϊ��" << S1 << endl;

	double S2 = 0, S, a1, b1, c1, p1;
	for (int j2 = 0; j2 < n; j2++)//����S2�����ں��׹�ʽ
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
		S = sqrt(p1 * (p1 - a1) * (p1 - b1) * (p1 - c1));//���׹�ʽ
		S2 = S2 + S;
	}
	cout << "S2Ϊ��" << S2 << endl;


	if ((1+e) * S1 > S2 && S2 > (1-e) * S1)//S1��S2�㹻�ӽ��������Ϊ���б��ǩ�ڵ���Χ����
	{
		cout << "���б����Χ����" << endl;
		return true;
	}
	else//S1��S2����ϴ�����Ϊ���б��ǩ�ڵ���Χ����
	{
		cout << "���б����Χ����" << endl;
		return false;
	}
}
