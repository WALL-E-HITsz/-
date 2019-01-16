#include <stdio.h>
#include <stdlib.h>

#define AFA 60 //���������ӵĽṹ�йصı�����120�й�
#define length 15//���������ĵ����Ӿ���


double v[3]={0,0,0};//�������ӵ��ٶ�
double theta;//��������ϵ�ͻ���������ϵ�нǣ���ʱ���ù�
double L;//���������ĵ����Ӿ���
double Vx, Vy;//Ŀ���ٶȷ���
double angle;//Ŀ���ٶ�������˵�x��
double V;//Ŀ���ٶ�
double angularVell;//��ת���ٶȣ���ʱ���ù�

void ThreeWheelVellControl2()
{
    Vx = V * cos(angle / 180.0f*3.1415926f);
    Vy = V * sin(angle / 180.0f*3.1415926f);
    theta = 0;
    L = length;//���������ĵ����Ӿ���
    angularVell = 0;
    v[0] = -((double)(-cos((AFA - theta) / 180.0f * 3.1415926f) * Vx + sin((AFA - theta) / 180.0f*3.1415926f) * Vy + L * angularVell));

    v[1] =-((double)(cos(theta / 180.0f*3.1415926f) * Vx + sin(theta / 180.0f*3.1415926f) * Vy + L * angularVell));

    v[2] = -((double)(-cos((AFA + theta) / 180.0f*3.1415926f) * Vx - sin((theta + AFA) / 180.0f*3.1415926f) * Vy + L * angularVell));
}


int main()
{
    printf("����Ŀ���ٶ�\n");
    scanf("%lf",&V);//����Ŀ��ǶȺ��ٶ�
    printf("����Ŀ��Ƕ�\n");
    scanf("%lf",&angle);
    ThreeWheelVellControl2();
    int i=0;
	for(i = 0; i < 3; i++)
	{
    printf("%lf\n",v[i]);
	}
	system("pause");

    return 0;
}
