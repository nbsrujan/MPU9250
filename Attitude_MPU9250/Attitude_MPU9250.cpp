#include "Attitude_MPU9250.h"

#define ROWS 3
#define COLS 3


float** MatrixMult33(float **a, float  **b) {
	float** c = new float*[3];
	for (int i = 0; i < ROWS; i++) {
		c[i] = new float[3];
		for (int j = 0; j < COLS; j++) {
			c[i][j] = 0;
			for (int k = 0; k < ROWS; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

void MatrixMult31(float **a, float *b, float(&c)[ROWS]) {
	for (int i = 0; i < ROWS; i++) {
		c[i] = 0;
		for (int k = 0; k < ROWS; k++) {
			c[i] += a[i][k] * b[k];
		}
	}
	return;
}
float** getMatx(float angle) {
	float** M = new float*[3];
	M[0] = new float[3]{ 1.0f,  0.0f, 0.0f };
	M[1] = new float[3]{ 0,  (float)cos(angle), (float)sin(angle) };
	M[2] = new float[3]{ 0, -(float)sin(angle), (float)cos(angle) };
	return M;
}

float** getMaty(float angle) {
	float** M = new float*[3];
	M[0] = new float[3]{ (float)cos(angle),  0.0f, -(float)sin(angle) };
	M[1] = new float[3]{ 0.0f, 1.0f, 0.0f };
	M[2] = new float[3]{ (float)sin(angle), 0.0f, (float)cos(angle) };
	return M;
}


float** getMatz(float angle) {
	float** M = new float*[3];
	M[0] = new float[3]{ (float)cos(angle), (float)sin(angle), 0.0f };
	M[1] = new float[3]{ -(float)sin(angle), (float)cos(angle), 0.0f };
	M[2] = new float[3]{ 0.0f, 0.0f, 1.0f };
	return M;
}

/*
0 - x-direction
1 - y-direction
2 - z-direction
*/

float** getRotMat(float angle, int direction) {
	switch (direction) {
	case(0):
		return getMatx(angle);
		break;
	case(1):
		return getMaty(angle);
		break;
	case(2):
		return getMatz(angle);
		break;
	}
	return getMatx(0.0);
}


AttitudeBasic::AttitudeBasic(){
	for(int i=0;i<3;i++){
		acc[i]=0.0f;
		mag[i]=0.0f;
		gyro[i]=0.0f;
	}
}

void AttitudeBasic::getAttitude(float _acc[3], float _mag[3], float (& attitude)[3]){
	float roll, pitch, yaw;
	float resMag[3];
	float **resMat;

	for(int i=0;i<3;i++){
		acc[i]=_acc[i];
		mag[i]=_mag[i];
	}

	roll  = (float)atan2(-acc[0], acc[2]);
	pitch = (float) atan2(acc[1],(-acc[0]*sin(roll)+acc[2]*cos(roll)));
	resMat = MatrixMult33(getRotMat(-roll, 0), getRotMat(-pitch, 1));
	MatrixMult31(resMat, mag,resMag);
	yaw = (float)atan2(resMag[0], resMag[1]);

	attitude[0] = roll;
	attitude[1] = pitch;
	attitude[2] = yaw;
}
