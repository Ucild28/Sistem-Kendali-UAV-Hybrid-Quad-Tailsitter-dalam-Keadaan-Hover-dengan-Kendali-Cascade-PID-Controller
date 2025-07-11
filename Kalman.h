#ifndef _Kalman_h
#define _Kalman_h

class Kalman {
public:
Kalman(){
  /* We will set the variables like so, these can also be tuned by the user */
  Q_angle = 0.001;
  Q_bias = 0.003;
  R_measure = 0.03;

  angle = 0; // Reset the angle
  bias = 0; // Reset bias

  P[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
  P[0][1] = 0;
  P[1][0] = 0;
  P[1][1] = 0;
  };
  
  // The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds

double getAngle(double newAngle, double newRate, double dt) {      
  // Discrete Kalman filter time update equations - Time Update ("Predict")
  // Update xhat - Project the state ahead
  /* Step 1 */
  rate = newRate - bias;
  angle += dt * rate;

  // Update estimation error covariance - Project the error covariance ahead
  /* Step 2 */
  P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt * P[1][1];
  P[1][0] -= dt * P[1][1];
  P[1][1] += Q_bias * dt;

  // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
  // Calculate Kalman gain - Compute the Kalman gain
  /* Step 4 */
  S = P[0][0] + R_measure;
  /* Step 5 */
  K[0] = P[0][0] / S;
  K[1] = P[1][0] / S;

  // Calculate angle and bias - Update estimate with measurement zk (newAngle)
  /* Step 3 */
  y = newAngle - angle;
  /* Step 6 */
  angle += K[0] * y;
  bias += K[1] * y;

  // Calculate estimation error covariance - Update the error covariance
  /* Step 7 */
  P[0][0] -= K[0] * P[0][0];
  P[0][1] -= K[0] * P[0][1];
  P[1][0] -= K[1] * P[0][0];
  P[1][1] -= K[1] * P[0][1];

  return angle;
  };
    
void setAngle(double newAngle) { angle = newAngle; }; // Used to set angle, this should be set as the starting angle
double getRate() { return rate; }; // Return the unbiased rate

/* These are used to tune the Kalman filter */
void setQangle(double newQ_angle) { Q_angle = newQ_angle; };
void setQbias(double newQ_bias) { Q_bias = newQ_bias; };
void setRmeasure(double newR_measure) { R_measure = newR_measure; };

double getQangle() { return Q_angle; };
double getQbias() { return Q_bias; };
double getRmeasure() { return R_measure; };

private:
/* Kalman filter variables */
double Q_angle; // Process noise variance for the accelerometer
double Q_bias; // Process noise variance for the gyro bias
double R_measure; // Measurement noise variance - this is actually the variance of the measurement noise

double angle; // The angle calculated by the Kalman filter - part of the 2x1 state vector
double bias; // The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
double rate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate

double P[2][2]; // Error covariance matrix - This is a 2x2 matrix
double K[2]; // Kalman gain - This is a 2x1 vector
double y; // Angle difference
double S; // Estimate error
};

#endif
