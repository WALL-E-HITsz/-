#include <windows.h>
#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <gl/glut.h>
using namespace Eigen;
using namespace std;

void Display();
void Caculate_R(int i);
Vector3d Caculate_Curve(int i, double u);
//double delta_u(int i, double u_j);
double position[15][2];
//MatrixXd P(10, 3); //10����ֵ�㣬n+1=10
MatrixXd B(12, 3); //12�����Ƶ㣬10+2=12
Vector3d R3, R2, R1, R0; //B�������ߵĲ�������Pi = R0 + R1*u + R2*u*u + R3*u*u*u
int main(int argc, char *argv[])
{

	B << 0.075, -0.275, 0.0,
		0.075, -0.15, 0.0,
		-0.075, -0.15, 0.0,
		-0.075, -0.075, 0.0,
		-0.075, 0.0, 0.0,
		0.0,    0.0, 0.0,
		0.075,  0.0, 0.0,
		0.075, 0.075, 0.0,
		0.075, 0.15, 0.0,
		-0.075, 0.15, 0.0,
		-0.075, 0.225, 0.0,
		-0.075, 0.3, 0.0;
    B=B*2;
	cout << "���Ƶ�" << endl;
	cout << B << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("B��������");
	glutDisplayFunc(&Display);
	glutMainLoop();

	return 0;
}
void Caculate_R(int i)
{
	R3 = (-B.row(i) + 3 * B.row(i + 1) - 3 * B.row(i + 2) + B.row(i + 3)) / 6;
	R2 = (3 * B.row(i) - 6 * B.row(i + 1) + 3 * B.row(i + 2)) / 6;
	R1 = (-3 * B.row(i) + 3 * B.row(i + 2)) / 6;
	R0 = (B.row(i) + 4 * B.row(i + 1) + B.row(i + 2)) / 6;
}
Vector3d Caculate_Curve(int i,double u)
{
	Caculate_R(i);
	return (R0 + R1*u + R2*u*u + R3*u*u*u);
}
//double delta_u(int i, double u_j)
//{
//	Caculate_R(i);
//	double a4, a3, a2, a1, a0;
//	a4 = 9 * R3.transpose()*R3;
//	a3 = 12 * R3.transpose()*R2;
//	a2 = 4 * R2.transpose()*R2;
//	a2= a2 + (6 * R3.transpose()*R1);
//	a1 = 4 * R2.transpose()*R1;
//	a0 = R1.transpose()*R1;
//	double delta;
//	delta = sqrt(a4*pow(u_j,4)+a3*pow(u_j,3)+a2*pow(u_j,2)+a1*u_j+a0);
//	return delta;
//}

void Display(void)//OpenGL����������
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	float g_CP[24];
	int k = 0;
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 2; j++){
			g_CP[k] = B(i, j);
			cout << g_CP[k] << endl;
			k++;
		}
	}
	glPointSize(10);
	glColor3d(255, 0, 0);
	glBegin(GL_POINTS);
	k = 0;
	while (k < 22){
		glVertex2f(g_CP[k], g_CP[k + 1]);
		k = k + 2;
	}
	glEnd();

	glVertexPointer(2, GL_FLOAT, 0, g_CP);
	glPointSize(2);
	glColor3d(255, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 0, 12); //���պ����߻���

	float u;
	Vector3d point_3d;
	GLfloat point[2];
	glColor3d(0, 255, 0);
	glBegin(GL_LINE_STRIP);
	glPointSize(4);
	for (int i = 0; i < 9; i++) {
		u = 0;
		Caculate_R(i);
		for (int j = 0; j < 20; j++){

			//u = u + delta_u(i, u);
			point_3d = Caculate_Curve(i,u);

			u = u + 0.05;
			point[0] = point_3d(0), point[1] = point_3d(1);
			glVertex2f(point[0], point[1]);
            position[i][0]= (point[0]-0.075*2)*500;position[i][1]= (point[1]+0.275*2)*500;
		}


	}
	for(int i=0;i<15;i++) cout<<position[i][0]<<" "<<position[i][1]<<endl;

	glEnd();
	glPointSize(10);
	glBegin(GL_POINTS);
//	for (int i = 0; i<10; i++){
//		glVertex2f(P(i, 0), P(i, 1));
//	}
	glEnd();
	glFlush();
}
