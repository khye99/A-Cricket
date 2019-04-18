/* cricket
 *  tempF = (tempC*(9.00/5.00))+32.00;
 *  CSE 132 - Assignment 3
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Karen Ye
 *  WUSTL Key: khye
 *  
 *  and if two are partnered together
 *  
 *  Name:
 *  WUSTL Key:
 */

double tempC;
long flash;
boolean ledState = LOW;

int temp = A1;
const int cricket = 3;


#define FILTER_COUNTS 7
double temperatures[FILTER_COUNTS];
long delta = 100;
long count = 0;
long count1 = 0;
long count2 = 0;
void setup() {
  analogReference(INTERNAL);
  pinMode(cricket, OUTPUT);
  Serial.begin(9600);
  Serial.println(FILTER_COUNTS);
}

void loop() {
  unsigned long time = millis();
  double sum = 0;
  double average = 0;
  if(time - count1 > delta) {
    readTemp();
    count1 += delta;
    for (int i = 0; i < FILTER_COUNTS; i++) {
      sum = sum + temperatures[i];
    }
    average = sum / FILTER_COUNTS;
    Serial.print("tempC: ");
    Serial.print(tempC);
    Serial.print("     average: ");
    Serial.println(average);
  }
      period();
   if (time - count2 > flash) {
      count2 += flash;
     if (ledState == LOW) {
        ledState = HIGH;
        digitalWrite(cricket, ledState);
      }
      else {
        ledState = LOW;
        digitalWrite(cricket, ledState);
    }
  }
}

void readTemp() {
  int out = analogRead(temp);
  float voltage = (out / 1024.00) * (1.10);
  tempC = (voltage - 0.5) / 0.01;
  temperatures[count % FILTER_COUNTS] = tempC;
  count +=1;
}

void period() {
  flash = 60000.00 / ((7.00 * tempC) - 30.00);
}



