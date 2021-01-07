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
 program();
}

void loop()
{ 
}

void program(){
lcd.clear();
for(int i=0;i<2;i=1+1){
  start();
}
delay(500);
lcd.clear();
level1();
delay(600);
level2();
delay(600);
level3();
delay(600);
endGame();
lcd.clear();
}

void frame1(){
 for(int i=0;i<=18;i=i+1){
  lcd.setCursor(i,0);
  lcd.write(byte(3));
 } 
  for(int i=0;i<=18;i=i+1){
  lcd.setCursor(i,3);
  lcd.write(byte(3));
 }
 
 lcd.setCursor(0,1);
 lcd.write(byte(3));
 lcd.setCursor(0,2);
 lcd.write(byte(3));
  
 for(int i=1;i<=19;i=i+1){
  lcd.setCursor(i,1);
  lcd.write(byte(5));
  lcd.setCursor(i,2);
  lcd.write(byte(4));
 }
}
void frame2(){
for(int i=0;i<=9;i=i+1){
  lcd.setCursor(i,1);
  lcd.write(byte(5));
  lcd.setCursor(i,2);
  lcd.write(byte(4));
 }
 for(int i=12;i<=19;i=i+1){
  lcd.setCursor(i,1);
  lcd.write(byte(5));
  lcd.setCursor(i,2);
  lcd.write(byte(4));
 }
  lcd.setCursor(11,1);
  lcd.write(byte(2));
  lcd.setCursor(11,2);
  lcd.write(byte(2));
 
 for(int i=0;i<=19;i=i+1){
  lcd.setCursor(i,0);
  lcd.write(byte(3));
 }
 for(int i=1;i<=19;i=i+1){
  lcd.setCursor(i,3);
  lcd.write(byte(3));
 }
 lcd.setCursor(10,1);
  lcd.write(byte(3));
  lcd.setCursor(10,2);
  lcd.write(byte(3));
 
}

void frame3(){
 for(int i=1;i<=3;i=i+1){
  lcd.setCursor(1,i);
  lcd.write(byte(6));
 }
 for(int i=2;i<=17;i=i+1){
  lcd.setCursor(i,1);
  lcd.write(byte(4));
 }
 for(int i=0;i<=3;i=i+1){
  lcd.setCursor(0,i);
  lcd.write(byte(3));
 } 
  for(int i=0;i<=19;i=i+1){
  lcd.setCursor(i,0);
  lcd.write(byte(3));
 }
  lcd.setCursor(19,0);
  lcd.write(byte(2));
  lcd.setCursor(19,1);
  lcd.write(byte(2));
  
  lcd.setCursor(17,2);
  lcd.write(byte(2));
  lcd.setCursor(15,3);
  lcd.write(byte(2));
  lcd.setCursor(13,2);
  lcd.write(byte(2));
  lcd.setCursor(11,3);
  lcd.write(byte(2));
  lcd.setCursor(9,2);
  lcd.write(byte(2));
  lcd.setCursor(7,3);
  lcd.write(byte(2));
  lcd.setCursor(5,2);
  lcd.write(byte(2));
  lcd.setCursor(3,3);
  lcd.write(byte(2));
  
  lcd.setCursor(17,3);
  lcd.write(byte(3));
  lcd.setCursor(15,2);
  lcd.write(byte(3));
  lcd.setCursor(13,3);
  lcd.write(byte(3));
  lcd.setCursor(11,2);
  lcd.write(byte(3));
  lcd.setCursor(9,3);
  lcd.write(byte(3));
  lcd.setCursor(7,2);
  lcd.write(byte(3));
  lcd.setCursor(5,3);
  lcd.write(byte(3));
  lcd.setCursor(3,2);
  lcd.write(byte(3));
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
nrLevel=0;
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
int c1=0;
int c2=0;
int c3=0;
lcd.setCursor(xPac,yPac);
lcd.write(byte(0));
while(final2 == 0){
  int state=readBtn();
  move_Pac(state);
  if(xPac == 0 && yPac == 0){
    c1=1;
  }
  if(xPac == 19 && yPac == 0){
    c2=1;
  }
  if(xPac == 19 && yPac == 3){
    c3=1;
  }
  if(c1 == 1 && c2 == 1 && c3 == 1){
    lcd.clear();
    you_won();
    final2=1;
  }
  if(xPac == 11 && yPac == 1){
    lcd.clear();
    you_lose();
    final2=1;
  } 
  if(xPac == 11 && yPac == 2){
    lcd.clear();
    you_lose();
    final2=1;
  }
}
nrLevel=0;
}

void level3(){
nrLevel=3;  
int final3=0;  
lcd.clear();
lcd.setCursor(0,1);
lcd.print("        LEVEL");
lcd.setCursor(0,2); 
lcd.print("         3");
delay(1000);
lcd.clear();
frame3();
xPac=0;
yPac=3;
lcd.setCursor(xPac,yPac);
lcd.write(byte(0));
while(final3 == 0){
  int state=readBtn();
  move_Pac(state);
 if(xPac == 3 && yPac == 2){
    lcd.clear();
    you_won();
    final3=1;
  }
  if(xPac == 19 && yPac == 0){
    lcd.clear();
    you_lose();
    final3=1;
  } 
   if(xPac == 19 && yPac == 1){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 17 && yPac == 2){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 15 && yPac == 3){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 13 && yPac == 2){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 11 && yPac == 3){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 9 && yPac == 2){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 7 && yPac == 3){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 5 && yPac == 2){
    lcd.clear();
    you_lose();
    final3=1;
  }
   if(xPac == 3 && yPac == 3){
    lcd.clear();
    you_lose();
    final3=1;
  }
  
}
nrLevel=0;
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

void endGame(){ 
   lcd.setCursor(0, 1);
   lcd.print("         END"); 
   lcd.setCursor(0, 2);
   lcd.print("        GAME");
   lcd.setCursor(0, 3);  
  for(int i=0;i<20;i++){
    if(i>0){
      delay(200);
      lcd.setCursor(i-1,3);
      lcd.print(" ");
      lcd.setCursor(i-1,0);
      lcd.print(" ");
    }
    if(i == 0){
      delay(200);
      lcd.setCursor(19,3);
      lcd.print(" ");
      lcd.setCursor(19,0);
      lcd.print(" ");
    }
    if(i % 2 == 0){
    delay(200);
    lcd.setCursor(i, 3);
    lcd.write(byte(0));
    lcd.setCursor(i, 0);
    lcd.write(byte(2));
    }else{
    delay(200);
    lcd.setCursor(i, 3);
    lcd.write(byte(1));
     lcd.setCursor(i, 0);
    lcd.write(byte(2));
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

int verify(int x,int y){
  if((x<=19 && x>=0) && (y<=3 && y>=0)){
  int ver;  
  if(nrLevel == 1){  
  ver=verifyFrame1(x,y);
  }
  if(nrLevel == 2){  
  ver=verifyFrame2(x,y);
  }
  if(nrLevel == 3){  
  ver=verifyFrame3(x,y);
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
for(int i=0;i<=9;i=i+1){
 if(x == i && y == 1){
   return 0;
}
}
for(int i=0;i<=9;i=i+1){
 if(x == i && y == 2){
   return 0;
}
}
for(int i=12;i<=19;i=i+1){
 if(x == i && y == 1){
   return 0;
}
}
for(int i=12;i<=19;i=i+1){
 if(x == i && y == 2){
   return 0;
}
}


 return 1;
}

int verifyFrame3(int x, int y){
for(int i=1;i<=3;i=i+1){
 if(x == 1 && y == i){
   return 0;
}
}
for(int i=2;i<=17;i=i+1){
 if(x == i && y == 1){
   return 0;
}
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

void you_won(){    
lcd.setCursor(0,1);
lcd.print("         YOU");
lcd.setCursor(0,2); 
  lcd.print("         WON");
win_song();  
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
