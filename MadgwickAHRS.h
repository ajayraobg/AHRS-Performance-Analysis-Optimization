//=====================================================================================================
// MadgwickAHRS.h
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=====================================================================================================
#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h

//----------------------------------------------------------------------------------------------------
// Variable declaration

extern volatile float beta;				// algorithm gain

#if 1									//Set this to 0 while doing the step 5 of the optimization and beyond
extern volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame
#endif

#if 0									//Set this to 1 while doing the step 5 of the optimization and beyond							
extern float q0, q1, q2, q3;
#endif
//---------------------------------------------------------------------------------------------------
// Function declarations

void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz,int flag_a,int flag_m);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az,int flag_a);
#endif
//=====================================================================================================
// End of file
//=====================================================================================================
