
int rm1 = A0;
int rm2 = A1;
int lm1 = A2;
int lm2 = A3;
int tc = 2;
int ec = 3;
int tl = 4;
int el = 5;
int tr = 6;
int er = 7;

float o;
float l;
float duration1, duration2, duration3, dl, dc, dr;

int tdelay = 530;
int fdelay = 700;
int udelay = 1000;

void Stop()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}

void forward()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

void smallright()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}

void smallleft()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

void right()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}

void left()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

/*int eosens()
  {
  readsens();
  if(((c1+c2+c3)==1) || ((c1+c2+c3)==2))
  return 1;
  else
  return 0;
  }*/

void readsens()
{

  digitalWrite(tl, LOW);
  delayMicroseconds(2);
  digitalWrite(tl, HIGH);
  delayMicroseconds(6);
  duration2 = pulseIn(el, HIGH);
  dl = duration2 * (0.034 / 2);

  digitalWrite(tc, LOW);
  delayMicroseconds(2);
  digitalWrite(tc, HIGH);
  delayMicroseconds(6);
  duration1 = pulseIn(ec, HIGH);
  dc = duration1 * (0.034 / 2);

  digitalWrite(tr, LOW);
  delayMicroseconds(2);
  digitalWrite(tr, HIGH);
  delayMicroseconds(6);
  duration3 = pulseIn(er, HIGH);
  dr = duration3 * (0.034 / 2);
}

void inch()
{

  Stop();
  delay(100);
  forward();
  delay(fdelay);
  Stop();
  delay(100);
  readsens();
}

/*void align()
  {
  Stop();
  delay(100);
  forward();
  delay(70);
  Stop();
  delay(100);
  readsens();
  }*/


void setup()
{
  Serial.begin(9600);
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(tl, OUTPUT);
  pinMode(tc, OUTPUT);
  pinMode(tr, OUTPUT);
  pinMode(el, INPUT);
  pinMode(ec, INPUT);
  pinMode(er, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  analogWrite(10, 100);
  analogWrite(11, 100);

  o = 8;
  l = 6;

}

void loop()
{
  readsens();                                              //  READING SENSOR

  Serial.println();
  Serial.print(dl);
  Serial.print('/');
  Serial.print(dc);
  Serial.print('/');
  Serial.print(dr);

  if ((dl <= o && dl >= l) && (dc > 8) &&  (dr <= o && dr >= l))              // FORWARD
  {
    forward();
  }

  else if (dl < l)
  { // SMALL LEFT
    smallleft();
  }

  else if (dr < l)
  { // SMALL RIGHT
    smallright();
  }



  //   Right and Straight   /   Right only   //



  else if ((dl <= o && dl >= l) && (dc > 8) &&  (dr > 20))
  {
    inch();

    if ((dl <= o && dl >= l) && (dc > 8) &&  (dr > 20))                        // RIGHT  AND STRAIGHT
    {
      forward();
      delay(fdelay);
    }

    else if ((dl <= o && dl >= l) && (dc <= 8) && (dr > 20))                  // Right only
    {
      right();
      delay(tdelay);
      forward();
      delay(fdelay);
    }
  }



  //  Left and Straight / Left only  //



  else if ((dl > 20) && (dc > 8) && (dr <= o && dr >= l))
  {
    inch();

    if ((dl > 20) && (dc > 8) && (dr <= o && dr >= l))  // LEFT  AND STRAIGHT
    {
      left();
      delay(tdelay);
      forward();
      delay(fdelay);
    }

    else if ((dl > 20) && (dc < 8) && (dr <= o && dr >= l)) // LEFT ONLY
    {
      left();
      delay(tdelay);
      forward();
      delay(fdelay);
    }
  }



  //4-Way-intersection  /  T-intersection



  else if ((dl > 20) && (dc > 8) && (dr > 20))
  {
    inch();

    if ((dl > 20) && (dc > 8) && (dr > 20))                    // 4 WAY INTERSECTION
    {
      left();
      delay(tdelay);
      forward();
      delay(fdelay);
    }

    else if ((dl > 20) && (dc <= 8) && (dr > 20))               // T-intersection
    {
      left();
      delay(tdelay);
      forward();
      delay(fdelay);
    }
  }



  else if ((dl <= o && dl >= l) && (dc <= 8) && (dr <= o && dr >= l))            // U-TURN
  {
    left();
    delay(udelay);
  }

  else
  {
    Stop();
  }
}
