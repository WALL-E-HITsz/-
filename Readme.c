#include <stdio.h>
#include <stdlib.h>

#define AFA 60 //与三角轮子的结构有关的变量与120有关
#define length 15//机器人中心到轮子距离


double v[3]={0,0,0};//三个轮子的速度
double theta;//场地坐标系和机器人坐标系夹角，暂时不用管
double L;//机器人中心到轮子距离
double Vx, Vy;//目标速度分量
double angle;//目标速度与机器人的x轴
double V;//目标速度
double angularVell;//自转角速度，暂时不用管

void ThreeWheelVellControl2()
{
    Vx = V * cos(angle / 180.0f*3.1415926f);
    Vy = V * sin(angle / 180.0f*3.1415926f);
    theta = 0;
    L = length;//机器人中心到轮子距离
    angularVell = 0;
    v[0] = -((double)(-cos((AFA - theta) / 180.0f * 3.1415926f) * Vx + sin((AFA - theta) / 180.0f*3.1415926f) * Vy + L * angularVell));

    v[1] =-((double)(cos(theta / 180.0f*3.1415926f) * Vx + sin(theta / 180.0f*3.1415926f) * Vy + L * angularVell));

    v[2] = -((double)(-cos((AFA + theta) / 180.0f*3.1415926f) * Vx - sin((theta + AFA) / 180.0f*3.1415926f) * Vy + L * angularVell));
}


int main()
{
    printf("输入目标速度\n");
    scanf("%lf",&V);//输入目标角度和速度
    printf("输入目标角度\n");
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
