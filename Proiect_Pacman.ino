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

byte zid1[8] = {
B11111,
B11111,
B00000,
B00000,
B00000,
B00000,
B00000,
};

byte zid2[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B11111,
B11111,
};

byte zid3[8] = {
B00011,
B00011,
B00011,
B00011,
B00011,
B00011,
B00011,
B00011,
};

byte sad[8] = {
B00000,
B11011,
B11011,
B00000,
B00000,
B01110,
B10001,
};

byte happy[8] = {
B00000,
B11011,
B11011,
B00000,
B00000,
B10001,
B01110,
};

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buzzer = 11;

int nrLevel=0;

//butonale
#define rightBtn     A2
#define upBtn        A1
#define downBtn      A3
#define leftBtn      A0

int xPac=19; // pozitia initiala pe linie 
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
  lcd.createChar(4, zid1);
  lcd.createChar(5, zid2);
  lcd.createChar(6, zid3);
  //lcd.createChar(7, happy);
  //lcd.createChar(8, sad);
  //lcd.setCursor(xPac,yPac);
 // lcd.write(byte(0));
 program();
}

void loop()
{ 
  int state=readBtn();
 // program();
 //frame1();
}

void program(){
lcd.clear();
for(int i=0;i<2;i=1+1){
  start();
}
delay(5000);
//lcd.clear();
//level1();
//delay(600);
level2();
delay(600);
}

void frame1(){
 for(int i=6;i<=19;i=i+1){
  lcd.setCursor(i,1);
  lcd.write(byte(5));
  lcd.setCursor(i,2);
  lcd.write(byte(4));
 }
}

void frame2(){
 for(int i=10;i<=19;i=i+1){
  lcd.setCursor(i,1);
  lcd.write(byte(5));
  lcd.setCursor(i,2);
  lcd.write(byte(4));
 }
 
 lcd.setCursor(4,3);
 lcd.write(byte(6));
 lcd.setCursor(4,2);
 lcd.write(byte(6)); 
 
 lcd.setCursor(19,3);
 lcd.write(byte(3));
 
 lcd.setCursor(19,0);
 lcd.write(byte(2));
}

void level1(){
nrLevel=1;  
  
lcd.clear();
lcd.setCursor(0,1);
lcd.print("        LEVEL");
lcd.setCursor(0,2); 
lcd.print("         1");
delay(1000);
lcd.clear();
lcd.setCursor(19,3);
lcd.write(byte(3));
lcd.setCursor(xPac,yPac);
lcd.write(byte(0));
frame1();
int final=0;
while(final == 0){
  int state=readBtn();
  move_Pac(state);
  if(xPac == 19 && yPac == 3){
    lcd.clear();
    you_won();
    final=1;
  } 
}
}


void level2(){
nrLevel=2;  
  
int final2=0;
lcd.clear();
lcd.setCursor(0,1);
lcd.print("        LEVEL");
lcd.setCursor(0,2); 
lcd.print("         2");
delay(1000);
lcd.clear();
frame2();
xPac=0;
yPac=3;
lcd.setCursor(xPac,yPac);
lcd.write(byte(0));
while(final2 == 0){
  int state=readBtn();
  move_Pac(state);
  if(xPac == 19 && yPac == 3){
    lcd.clear();
    you_won();
    final2=1;
  }
  if(xPac == 19 && yPac == 0){
    lcd.clear();
    you_lose();
    final2=1;
  } 
}
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
lcd.setCursor(0,1);
lcd.print("       YOU");
lcd.setCursor(0,2); 
  lcd.print("       WON");
win_song();  
}

int verify(int x,int y){
  if((x<=19 && x>=0) && (y<=3 && y>=0)){
  int ver;  
  if(nrLevel == 1){  
  ver=verifyFrame1(x,y);
  }
  if(nrLevel == 2){  
  ver=verifyFrame2(x,y);
  }
  if(ver == 1){
  return 1;
  }
  }
  else{
  return 0;
  }
}

int verifyFrame1(int x, int y){
for(int i=6;i<=19;i=i+1){
 if(x == i && y == 1){
   return 0;
}
}
for(int i=6;i<=19;i=i+1){
 if(x == i && y == 2){
   return 0;
}
}

 return 1;
}

int verifyFrame2(int x, int y){
for(int i=10;i<=19;i=i+1){
 if(x == i && y == 1){
   return 0;
}
}
for(int i=10;i<=19;i=i+1){
 if(x == i && y == 2){
   return 0;
}
}

 if(x == 4 && y == 3){
   return 0;
}

 if(x == 4 && y == 2){
   return 0;
}

 return 1;
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
lcd.setCursor(0,1);
lcd.print("         YOU");
lcd.setCursor(0,2); 
  lcd.print("         LOSE");
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
