#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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

int buttonState = 0;
int buttonState2 = 0;
int buzzer = 8;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.createChar(0, pacman1);
  lcd.createChar(1, pacman2);
  lcd.createChar(2, ghost);
}

void loop() {
  buttonState=digitalRead(A1);
  buttonState2=digitalRead(A2);
  if(buttonState == LOW){
    you_lose();
  }
  if(buttonState2 == LOW){
    //you_won();
    level1();
  }
}

void start(){
 //for(int i=0;i<16;i++){ 
   lcd.setCursor(0, 0);
   lcd.print("     Pacman"); 
   lcd.setCursor(0, 1);  
  for(int i=0;i<16;i++){
    if(i>0){
      delay(200);
      lcd.setCursor(i-1,1);
      lcd.print(" ");
    }
    if(i == 0){
      delay(200);
      lcd.setCursor(15,1);
      lcd.print(" ");
    }
    if(i % 2 == 0){
    delay(200);
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    }else{
    delay(200);
    lcd.setCursor(i, 1);
    lcd.write(byte(1));
    }
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
lcd.print("      LEVEL");
lcd.setCursor(0,1); 
  lcd.print("        1");
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
 
