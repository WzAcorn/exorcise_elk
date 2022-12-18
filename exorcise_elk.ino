//#define DIST_S 200*58.2 // 200cm로 제한


int trig[3]={38,40,42};
int echo[3]={39,41,43};
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

int cds = A0;
int piezo = A1;
int LaserPin = A2;
int button = A3;

void setup() {
  Serial.begin (9600);
  for (int i=0; i<=2; i++){
    pinMode(trig[i],OUTPUT);
    pinMode(echo[i],INPUT);
  }
   pinMode(piezo, OUTPUT);
   pinMode(LaserPin, OUTPUT);
   digitalWrite(LaserPin, HIGH);
   pinMode(button, INPUT_PULLUP);
}
 

int cases;
int sonic_distance = 15;

void loop() {
  cases = 0;
  int cdsValue = analogRead(cds);
  long dist[3];
  for(int i=0; i<=2; i++){
      dist[i] = trig_ultra(trig[i],echo[i]);
  }
  if (digitalRead(button) == LOW) {
    cases = 1;
  }
  if(dist[0] <= sonic_distance  and cdsValue >= 200){   //다람쥐일때
    cases = 1;
    if(dist[0] <= sonic_distance  and dist[1] <= sonic_distance){   //고라니일때
      cases = 2;
      if(dist[0] <= sonic_distance  and dist[1] <= sonic_distance and dist[2] <= sonic_distance){    //사람일때
        cases = 3;
      }
    }
  }
  button_low();

  /*
  if (cases >= 1){
    tone(piezo, tones[cases]);
    delay(50);
    noTone(piezo);
    delay(500);
  }

  */
  delay(200);
  Serial.println(cases);

}

int button_low(){
  if (digitalRead(button) == LOW) {
    cases = 4;
  }
  return cases;
}

long trig_ultra(int TRIG,int ECHO)
{
  long dist;
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  dist = pulseIn(ECHO, HIGH)/58.2;  
  return(dist);
}
