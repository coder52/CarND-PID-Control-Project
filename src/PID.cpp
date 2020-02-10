#include <uWS/uWS.h>
#include <vector>
#include "PID.h"

using std::vector;

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init() {
  // Twiddle parameters
  this -> slct = 0;
  this -> best_err = 0;
  this -> p = {-0.12, 0, -2.7};
  this -> dp = {1, 1, 1};
  // errors
  this -> p_error = 0;
  this -> i_error = 0;
  this -> d_error = 0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
   // p_error stores previous error(cte),
   //   before changing to p_error value with new error, we are using it in d_error
   d_error = cte - p_error;
   p_error = cte;
   i_error += cte;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return p[0]*p_error + p[1]*i_error + p[2]*d_error;  // TODO: Add your total error calc here!
}

void PID::Restart(uWS::WebSocket<uWS::SERVER> ws) {
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

void PID::Twiddle(){
  // print best parameters
  if(err<best_err){
  	std::cout << "parameters: [ "<<p[0]<<", "<<p[1]<<", "<< p[2]<<" ]\n";
  	std::cout << "dp: [ "<<dp[0]<<", "<<dp[1]<<", "<<dp[2]<<" ]\n";
  }

  if(this -> slct==0){
    best_err = err;
    p[0] += dp[0];
    this -> slct = 1;
    std::cout << " a " << "\n";
  } else if(this -> slct==1){///////0//////////////////
    if(err<best_err){
      best_err = err;
      dp[0] *= 1.1;

      p[2] += dp[2];
      this -> slct = 3;
      std::cout << "p-b1 " << "\n";
    } else {
      p[0] -= 2 * dp[0];
      this -> slct = 2;
      std::cout << "p-b2 " << "\n";
    }
  } else if (this -> slct==2){
    if(err<best_err){
      best_err = err;
      dp[0] *= 1.1;

      p[2] += dp[2];
      this -> slct = 3;
      std::cout << "p-c1 " << "\n";
    } else {
      p[0]+=dp[0];
      dp[0]*=0.9;

      p[2] += dp[2];
      this -> slct = 3;
      std::cout << "p-c2 " << "\n";
    }
  } else if(this -> slct==3){///////2////////////
    if(err<best_err){
      best_err = err;
      dp[2] *= 1.1;

      p[1] += dp[1];
      this -> slct = 5;
      std::cout << "d-b1 " << "\n";
    } else {
      p[2] -= 2 * dp[2];
      this -> slct = 4;
      std::cout << "d-b2 " << "\n";
    }
  } else if(this -> slct==4){
    if(err<best_err){
      best_err = err;
      dp[2] *= 1.1;

      p[1] += dp[1];
      this -> slct = 5;
      std::cout << "d-c1 " << "\n";
    } else {
      p[2]+=dp[2];
      dp[2]*=0.9;

      p[1] += dp[1];
      this -> slct = 5;
      std::cout << "d-c1 " << "\n";
    }
  } else if(this -> slct==5){///////1//////////////////////
    if(err<best_err){
      best_err = err;
      dp[1] *= 1.1;

      p[0] += dp[0];
      this -> slct = 1;
      std::cout << "i-b1 " << "\n";
    } else {
      p[1] -= 2 * dp[1];
      this -> slct = 6;
      std::cout << "i-b2 " << "\n";
    }
  } else if(this -> slct==6){
    if(err<best_err){
      best_err = err;
      dp[1] *= 1.1;

      p[0] += dp[0];
      this -> slct = 1;
      std::cout << "i-c1 " << "\n";
    } else {
      p[1]+=dp[1];
      dp[1]*=0.9;

      p[0] += dp[0];
      this -> slct = 1;
      std::cout << "i-c2 " << "\n";
    }
  }
}
