#ifndef PID_H
#define PID_H

#include <vector>

using std::vector;

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init();

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  /**
   * reset the simulator and car.
   */
  void Restart(uWS::WebSocket<uWS::SERVER> ws);

  /**
   * run twiddle.
   */
  void Twiddle();

  /**
   * Twiddle parameters
   */
  int slct;
  double best_err;
  vector <double> p;
  vector <double> dp;
  double err;

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;
};

#endif  // PID_H
