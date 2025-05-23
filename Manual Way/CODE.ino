#define lms 5
#define lmf 6
#define lmb 7
#define rmf 8
#define rmb 9
#define rms 10

int s[6], sum;
int base[6] = { 1, 2, 4, 8, 16, 32 };
int position[6] = { 1, 2, 3, 4, 5, 6 };
int threshold = 512, sensor;
int lsp = 25, rsp = 25;
int pos;

void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  // motor(10 * lsp, 10 * rsp);
  line_follow();
}

void loop() {

}

void line_follow() {
  while (1) {
    reading();
    if (sum == 0) {

    }

    else if (sum == 1 || sum == 2) {  //normal line
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * lsp, 10 * rsp) : motor(10 * lsp, -10 * rsp);
          delay(abs(pos) * 5);
        }
        motor(10 * lsp, 10 * rsp);
      }

      //for right side turn correction
      else if (sensor == 0b000100)
        motor(10 * lsp, 9 * rsp);

      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1;
        motor(10 * lsp, (9 - line_prop) * rsp);
      }

      else if (sensor == 0b000010) {
        if (pos < 2) pos = 2;
        motor(10 * lsp, (9 - 2 * line_prop) * rsp);
      }

      else if (sensor == 0b000011) {
        if (pos < 3) pos = 3;
        motor(10 * lsp, (9 - 3 * line_prop) * rsp);
      }

      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4;
        motor(10 * lsp, (9 - 4 * line_prop) * rsp);
      }

      //for left side turn detection
      else if (sensor == 0b001000)
        motor(9 * lsp, 10 * rsp);

      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1;
        motor((9 - line_prop) * lsp, 10 * rsp);
      }

      else if (sensor == 0b010000) {
        if (pos > -2) pos = -1;
        motor((9 - 2 * line_prop) * lsp, 10 * rsp);
      }

      else if (sensor == 0b110000) {
        if (pos > -3) pos = -3;
        motor((9 - 3 * line_prop) * lsp, 10 * rsp);
      }

      else if (sensor == 0b100000) {
        if (pos > -4) pos = -4;
        motor((9 - 4 * line_prop) * lsp, 10 * rsp);
      }
    }

    else if (sum >= 3 && sum <= 5) {  //sharp turn detection

    }

    else if (sum == 6) {
    }
  }
}


void reading() {
  sensor = 0;
  sum = 0;
  for (byte i = 0; i < 6; i++) {
    s[i] = analogRead(i);
    (s[i] > threshold) ? s[i] = 1 : s[i] = 0; //this line converts analog value into digital
    sensor += s[i] * base[i];
    sum += s[i];
  }
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
