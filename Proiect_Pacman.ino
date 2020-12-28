#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte pacman1[8] = {
B00000,
B00000,
B01110,
B11011,
B11100,
B11111,
B01110,
};

byte pacman2[8] = {
B00000,
B00000,
B01110,
B11011,
B11111,
B11111,
B01110,
};

byte ghost[8] = {
B00000,
B00000,
B01110,
B10101,
B11111,
B11111,
B10101,
};

byte food[8] = {
B00000,
B00000,
B00000,
B00110,
B00110,
B00000,
B00000,
};

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buzzer = 11;

//butonale
#define rightBtn     A2
#define upBtn        A1
#define downBtn      A3
#define leftBtn      A0

int xPac=4; // pozitia initiala pe linie 
int yPac=0; // pozitia initiala pe coloana

int v=0;
int pacState=0;

void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  lcd.begin();
  lcd.createChar(0, pacman1);
  lcd.createChar(1, pacman2);
  lcd.createChar(2, ghost);
  lcd.createChar(3, food);
  
  //lcd.setCursor(xPac,yPac);
 // lcd.write(byte(0));
}

void loop()
{ 
  int state=readBtn();
  start();
}

void start(){ 
   lcd.setCursor(0, 1);
   lcd.print("       Pacman"); 
   lcd.setCursor(0, 1);  
  for(int i=0;i<20;i++){
    if(i>0){
      delay(200);
      lcd.setCursor(i-1,2);
      lcd.print(" ");
    }
    if(i == 0){
      delay(200);
      lcd.setCursor(19,2);
      lcd.print(" ");
    }
    if(i % 2 == 0){
    delay(200);
    lcd.setCursor(i, 2);
    lcd.write(byte(0));
    }else{
    delay(200);
    lcd.setCursor(i, 2);
    lcd.write(byte(1));
    }
  }
}

void move_Pac(int state){
 switch (state) {
  case rightBtn:
    v=verify(xPac+1,yPac);
    if(v == 1){
    xPac=xPac+1;
    move_rigth(xPac,yPac,pacState);
    pacState=~pacState;
    v=0;
    delay(300);
    }
    break;
  case upBtn:
    v=verify(xPac,yPac-1);
    if(v == 1){
    yPac=yPac-1;
    move_up(xPac,yPac,pacState);
    pacState=~pacState;
    v=0;
    delay(300);
    }
    break;
  case downBtn:
    v=verify(xPac,yPac+1);
    if(v == 1){
    yPac=yPac+1;
    move_down(xPac,yPac,pacState);
    pacState=~pacState;
    v=0;
    delay(300);
    }
    break;
  case leftBtn:
    v=verify(xPac-1,yPac);
    if(v == 1){
    xPac=xPac-1;  
    move_left(xPac,yPac,pacState);
    pacState=~pacState;
    v=0;
    delay(300);
    }
    break;
  default:
    // statements
    break;
 }
}

void move_down(int x,int y,int s){
  if(s == 0){
    delay(200);
    lcd.setCursor(x,y-1);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(1));
  }else{
    delay(200);
    lcd.setCursor(x,y-1);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(0));
  }
}

void move_up(int x,int y,int s){
  if(s == 0){
    delay(200);
    lcd.setCursor(x,y+1);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(1));
  }else{
    delay(200);
    lcd.setCursor(x,y+1);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(0));
  }
}

void move_left(int x,int y,int s){
  if(s == 0){
    delay(200);
    lcd.setCursor(x+1,y);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(1));
  }else{
    delay(200);
    lcd.setCursor(x+1,y);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(0));
  }
}

void move_rigth(int x,int y,int s){
  if(s == 0){
    delay(200);
    lcd.setCursor(x-1,y);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(1));
  }else{
    delay(200);
    lcd.setCursor(x-1,y);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(x,y);
    lcd.write(byte(0));
  }
}

void you_won(){ 
lcd.setCursor(0,0);
lcd.print("       YOU");
lcd.setCursor(0,1); 
  lcd.print("       WON");
win_song();  
}

void level1(){
lcd.setCursor(0,0);
lcd.print("       LEVEL");
lcd.setCursor(0,1); 
  lcd.print("         1");
}

int verify(int x,int y){
  if((x<=19 && x>=0) && (y<=3 && y>=0)){
  return 1;
  }
  else{
  return 0;
  }
}

int readBtn(){
buttonState1=digitalRead(leftBtn);
buttonState2=digitalRead(upBtn);
buttonState3=digitalRead(rightBtn);
buttonState4=digitalRead(downBtn);
  
  if(buttonState1 == LOW){
    return leftBtn;
  }
  if(buttonState2 == LOW){
    return upBtn;
  }
  if(buttonState3 == LOW){
    return rightBtn;
  }
  if(buttonState4 == LOW){
    return downBtn;
  }
}

void you_lose(){
lcd.setCursor(0,0);
lcd.print("       YOU");
lcd.setCursor(0,1); 
  lcd.print("      LOSE");
lose_song();
}

void win_song(){
      tone(buzzer,420,200);
      delay(500);
      tone(buzzer,440,200);
      delay(500);
      tone(buzzer,490,270);
      delay(300);
      tone(buzzer,520,200);
      delay(300);
}

void lose_song(){
      tone(buzzer,190,230);
      delay(500);
      tone(buzzer,100,230);
      delay(500);
      tone(buzzer,50,270);
      delay(300);
}
