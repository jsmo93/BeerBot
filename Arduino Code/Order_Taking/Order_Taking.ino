#include <LiquidCrystal.h>

const int cancelButtonPin = 2;
const int downButtonPin = 3;
const int upButtonPin =  4;
const int acceptButtonPin = 5;
const int sendOrderPin = 6;
const int d7Pin = 7;
const int d6Pin = 8;
const int d5Pin = 9;
const int d4Pin = 10;
const int enablePin = 11;
const int rsPin = 12;

bool welcomeState = true;
int orderState = 0;

int cancelButtonState = 0;
int downButtonState = 0;
int upButtonState = 0;
int acceptButtonState = 0;

typedef struct welcomeLCD{
  char welcomeLine1[16] = "Hi, I'm BeerBot";
  char welcomeLine3[16] = "Can I take your";
  char welcomeLine4[16] = "beer order?";
  } Welcome;
  
Welcome defaultWelcome;
  
typedef struct orderLCD{
  char orderLine1[16] = "Sierra Nevada";
  char orderLine2[16] = "Shocktop";

  } Order;

Order defaultOrder;

LiquidCrystal lcd(rsPin, enablePin, d4Pin, d5Pin, d6Pin, d7Pin);

void drawOrderState(int state)
{
  lcd.clear();
  if(state == 0)
  {
    lcd.print(">");
    lcd.setCursor(1, 0);
    lcd.print(defaultOrder.orderLine1);
    lcd.setCursor(0, 1);
    lcd.print(defaultOrder.orderLine2);
  }
  else if(state == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print(">");
    lcd.setCursor(0, 0);
    lcd.print(defaultOrder.orderLine1);
    lcd.setCursor(1, 1);
    lcd.print(defaultOrder.orderLine2);
  }
}

void sendOrder(int state)
{
  lcd.clear();
  lcd.print("No problem,");
  lcd.setCursor(0, 1);
  lcd.print("be right back!");
  
  digitalWrite(sendOrderPin, LOW);
  delay(1000);
  if(orderState == 0)
  {
    digitalWrite(sendOrderPin, HIGH);
  }
  delay(3000);
  lcd.noDisplay();
}

void setup() {
  pinMode(cancelButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(acceptButtonPin, INPUT);
  pinMode(sendOrderPin, OUTPUT);
  lcd.begin(16, 2); 
  lcd.noBlink();
  lcd.print(defaultWelcome.welcomeLine1);
  delay(3000);
  lcd.clear();
  lcd.print(defaultWelcome.welcomeLine3);
  lcd.setCursor(0, 1);
  lcd.print(defaultWelcome.welcomeLine4);
  digitalWrite(sendOrderPin, HIGH);
}

void loop(){
  if (welcomeState)
  {
      acceptButtonState = digitalRead(acceptButtonPin);
      if(acceptButtonState == HIGH)
      {
          welcomeState = false;
          orderState = 0;
          drawOrderState(orderState);
      }
      delay(200);
  }
  else
  {
      cancelButtonState = digitalRead(cancelButtonPin);
      downButtonState = digitalRead(downButtonPin);
      upButtonState = digitalRead(upButtonPin);
      acceptButtonState = digitalRead(acceptButtonPin);

    if (cancelButtonState == HIGH) {
      welcomeState = true;
      lcd.clear();
      lcd.print(defaultWelcome.welcomeLine1);
      delay(3000);
      lcd.clear();
      lcd.print(defaultWelcome.welcomeLine3);
      lcd.setCursor(0, 1);
      lcd.print(defaultWelcome.welcomeLine4);
    }
  
    if (downButtonState == HIGH) {
       if (orderState == 0)
       {
         orderState = 1;
         drawOrderState(orderState);
       }
    }
  
    if (upButtonState == HIGH) {
       if (orderState == 1)
       {
         orderState = 0;
         drawOrderState(orderState);
       }    
    }
  
    if (acceptButtonState == HIGH) {
      sendOrder(orderState);
    }
    
    delay(200);
  }
}
