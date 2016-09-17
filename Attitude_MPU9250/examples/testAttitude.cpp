#include "../Attitude_MPU9250.h"

int main() {
	AttitudeBasic attitude;
	float acc[3] = { 0,0,0 };
	float mag[3] = { 0,0,0 };
	float att[3] = { 0,0,0 };
	attitude.getAttitude(acc, mag, att);
}