void semi_pid() {
  reading();
  if (sum == 0) {
    if (turn != 's') {
      delay(10);
      (turn == 'r') ? motor(tsp, -tsp) : motor(-tsp, tsp);
      while (!s[2] && !s[3]) reading();
      turn = 's';
    }
  }
  
  PID_reading();
  error = 3.5 - avg;
  PID = error * kp + kd * (error - last_error);
  last_error = error;
  rmotor = rbase - PID;
  lmotor = lbase + PID;
  motor(lmotor, rmotor);

  if (s[0] && !s[5]) turn = 'r';
  if (s[5] && !s[0]) turn = 'l';

  else if (sum == 6) {
    delay(200);
    reading();
    if (sum == 6) {
      motor(0, 0);
      while (sum == 6) reading();
    }
    else if (sum == 0) turn = 'r';
  }
}
