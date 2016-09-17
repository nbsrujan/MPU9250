#ifndef ATTITUDE_MPU9250_HEADER

#define ATTITUDE_MPU9250_HEADER

#include <Arduino.h>
#include <math.h>

class AttitudeBasic
{
public:
	AttitudeBasic();
	void getAttitude(float _acc[3], float _mag[3], float(&attitude)[3]);
	~AttitudeBasic() {};
private:
	float acc[3];
	float mag[3];
	float gyro[3];
};

#endif // !
