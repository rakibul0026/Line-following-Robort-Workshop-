#define lms 5
#define lmf 6
#define lmb 7
#define rmf 8
#define rmb 9
#define rms 10

int s[6], sum;
int position[6] = { 1, 2, 3, 4, 5, 6 };
int threshold = 512, sensor;
int lbase = 200, rbase = 200;
int lmotor, rmotor;
float avg, line_prop = 3;
int kp = 50, kd = 1000;
int PID;
float error, last_error;
int pos;

void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  // motor(10 * lsp, 10 * rsp);
  PID_follow();
}

void loop(){
}

void PID_reading() {
  sensor = 0;
  sum = 0;
  for (byte i = 0; i < 6; i++) {
    s[i] = analogRead(i);
    (s[i] > threshold) ? s[i] = 1 : s[i] = 0; //this line converts analog value into digital
    sensor += s[i] * position[i];
    sum += s[i];
  }
  if(sum) avg = sensor / sum; //average value
}

void motor(int a, int b) {
  if (a > 0) {
    digitalWrite(lmf, 1);
    digitalWrite(lmb, 0);
  } 
  
  else {
    a = -(a);
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 1);
  }

  if (b > 0) {
    digitalWrite(rmf, 1);
    digitalWrite(rmb, 0);
  } 
  
  else {
    b = -b;
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 1);
  }

  if (a > 250) a = 250;
  if (b > 250) b = 250;

  analogWrite(lms, a);
  analogWrite(rms, b);
}
