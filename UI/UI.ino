#include <Communicator.h>
#include <SoftwareSerial.h>

#define SetDisplay 0xFE
#define ClearDisplay 0x01
#define MoveCursorRightOne 0x14
#define MoveCursorLeftOne 0x10
#define ScrollRight 0x1C
#define ScrollLeft 0x18
#define BlinkingBoxCursorOn 0x0D
#define SetCursorPosition 0x80

// constants won't change. They're used here to
SoftwareSerial lcd(7, 6); // pin 7 = RX (unused), pin 6 = TX
const int buttonUpPin = 13;
const int buttonDownPin = 3;
const int buttonOkPin = 4;
const int buttonBackPin = 5;
Communicator comm = Communicator(0x7df);

// variables will change:
int Position = 0;
int buttonUpState = 0;
int buttonDownState = 0;
int buttonOkState = 0;
int buttonBackState = 0;
int choise = 0;
bool firsttime = true; 

//AutoFILL
char* alldrinks[] = {"Koffie", "Thee", "Chocomelk", "Soep", "IETS EXTRA'S"};
//char* availabledrinks[] = {};
//bool suiker = false;
//bool melk = false;

void setup()
{
  //debug
  Serial.begin(9600);
  pinMode(buttonUpPin, INPUT);
  pinMode(buttonDownPin, INPUT);
  pinMode(buttonOkPin, INPUT);
  pinMode(buttonBackPin, INPUT);
  lcd.begin(9600); // set up serial port for 9600 baud
  delay(1000); // wait for display to boot up
  lcd.write(SetDisplay);
  lcd.write(BlinkingBoxCursorOn);

  //Ask for availablemodules()
  //filldrinks(0b11111111);
}

void loop()
{
  if (firsttime)
  {
    firsttime = false;
    choise = 0;
    Page1();
  }
  
  buttonstates();
  if (buttonUpState == HIGH && Position != 0)
  {
    choise--;
    buttonUp();
  }
  else if (buttonDownState == HIGH & Position != 84)
  {
    choise++;
    buttonDown();
  }
  else if (buttonOkState == HIGH)
  {
    order(choise);
  }
  
}

//AutoFILL
//void filldrinks(byte modules)
//{
//  //Module = niks, niks, Chocomelk, Soep, melk, suiker, Koffie, Water
//  byte check = modules & 0b00000001;
//  int t = 0;
//  suiker = false;
//  melk = false;
//  byte Time[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000};
//  for (int i = 0; i < 6; i++)
//  {
//    Serial.println(check, BIN);
//    if (check == Time[i])
//    {
//      if (i == 2)
//      {
//        suiker = true;
//      }
//      else if (i == 3)
//      {
//        melk = true;
//      }
//      else
//      {
//        availabledrinks[t] = alldrinks[t];
//        t++;
//      }
//    }
//    check = check << 1;
//  }
//}

void order(int choise)
{
  int order = choise;
  int grootte = 1;
  int sterkte = 2;
  int suiker = 2;
  int melk = 2;

  Page1();
//  buttonstates();
//  while (buttonOkState == LOW)
//  {
//    buttonstates();
//    if (buttonUpState == HIGH && Position != 0)
//    {
//      order--;
//      buttonUp();
//    }
//    else if (buttonDownState == HIGH & Position != 84)
//    {
//      order++;
//      buttonDown();
//    }
//  }


  Kopgrootte(grootte);
  buttonstates();
  while (buttonOkState == LOW)
  {
    buttonstates();
    if ((buttonUpState == HIGH) && (grootte < 3))
    {
      grootte++;
      Kopgrootte(grootte);
    }
    else if ((buttonDownState == HIGH) && (grootte > 1))
    {
      grootte--;
      Kopgrootte(grootte);
    }
    else
    {
      //Nothing do to
    }
  }

  if (alldrinks[order] == "Koffie")
  {
    KoffieSterkte(sterkte);
    buttonstates();
    while (buttonOkState == LOW)
    {
      buttonstates();
      if (buttonUpState == HIGH && sterkte < 3)
      {
        sterkte++;
        KoffieSterkte(sterkte);
      }
      else if (buttonDownState == HIGH && sterkte > 1)
      {
        sterkte--;
        KoffieSterkte(sterkte);
      }
      else
      {
        //NOTHING DO TO
      }
    }

    Suiker(suiker);
    buttonstates();
    while (buttonOkState == LOW)
    {
      buttonstates();
      if (buttonUpState == HIGH && suiker < 3)
      {
        suiker++;
        Suiker(suiker);
      }
      else if (buttonDownState == HIGH && suiker > 0)
      {
        suiker--;
        Suiker(suiker);
      }
      else
      {
        //NOTHING DO TO
      }
    }

    Melk(melk);
    buttonstates();
    while (buttonOkState == LOW)
    {
      buttonstates();
      if (buttonUpState == HIGH && melk < 3)
      {
        melk++;
        Melk(melk);
      }
      else if (buttonDownState == HIGH && melk > 0)
      {
        melk--;
        Melk(melk);
      }
      else
      {
        //NOTHING DO TO
      }
    }
  }
  conformOrder(order, grootte, sterkte, melk, suiker);
  choise = 0;
}

void Page1()
{
  clearDisplay();
  //AUTOFILL
  //  if (availabledrinks[0] != NULL)
  //  {
  //    writeOnDisplay(1, availabledrinks[0]);
  //    writeOnDisplay(65, availabledrinks[1]);
  //    writeOnDisplay(21, availabledrinks[2]);
  //    writeOnDisplay(85, availabledrinks[3]);
  //    writeOnDisplay(0, "");
  //  }
  //  else
  //  {
  //    writeOnDisplay(1, "NIKS AANWEZIG");
  //  }
  writeOnDisplay(1, alldrinks[0]);
  writeOnDisplay(65, alldrinks[1]);
  writeOnDisplay(21, alldrinks[2]);
  writeOnDisplay(85, alldrinks[3]);
  writeOnDisplay((Position = 0), "");
}

void Kopgrootte(int grootte)
{
  clearDisplay();
  writeOnDisplay(5, "Kopgrootte");
  writeOnDisplay(85, "Klein");
  writeOnDisplay(92, "Gem");
  writeOnDisplay(97, "Groot");

  if (grootte >= 1)
  {
    writeOnDisplay(21, "-----");
  }
  if (grootte >= 2)
  {
    writeOnDisplay(27, "-----");
  }
  if (grootte >= 3)
  {
    writeOnDisplay(33, "-----");
  }
}

void KoffieSterkte(int sterkte)
{
  clearDisplay();
  writeOnDisplay(3, "Koffie Sterkte");
  writeOnDisplay(86, "Mild");
  writeOnDisplay(92, "Gem");
  writeOnDisplay(97, "Sterk");

  if (sterkte >= 1)
  {
    writeOnDisplay(21, "-----");
  }
  if (sterkte >= 2)
  {
    writeOnDisplay(27, "-----");
  }
  if (sterkte >= 3)
  {
    writeOnDisplay(33, "-----");
  }
}

void Suiker(int suiker)
{
  clearDisplay();
  writeOnDisplay(7, "Suiker");

  if (suiker >= 0)
  {
    writeOnDisplay(85, "     ");
  }
  if (suiker >= 1)
  {
    writeOnDisplay(65, "-----");
  }
  if (suiker >= 2)
  {
    writeOnDisplay(71, "-----");
  }
  if (suiker >= 3)
  {
    writeOnDisplay(77, "-----");
  }
}

void Melk(int melk)
{
  writeOnDisplay(28, "Melk");

  if (melk >= 0)
  {
    writeOnDisplay(85, "     ");
  }
  if (melk >= 1)
  {
    writeOnDisplay(91, "     ");
    writeOnDisplay(85, "-----");
  }
  if (melk >= 2)
  {
    writeOnDisplay(97, "     ");
    writeOnDisplay(91, "-----");
  }
  if (melk >= 3)
  {
    writeOnDisplay(97, "-----");
  }
}

void conformOrder(int order, int grootte, int sterkte, int suiker, int melk)
{
  bool iets = true;
  clearDisplay();
  writeOnDisplay(0, "Drank:");
  writeOnDisplay(6, alldrinks[order]);
  writeOnDisplay(64, "Grootte:");
  writeOnDisplay(72, (String)grootte);

  if (alldrinks[order] == "Koffie")
  {
    writeOnDisplay(20, "Sterkte:");
    writeOnDisplay(28, (String)sterkte);
    writeOnDisplay(84, "Melk:");
    writeOnDisplay(89, (String)melk);
    writeOnDisplay(94, "Suiker:");
    writeOnDisplay(101, (String)suiker);
  }
  buttonstates();
  while (iets)
  {
    buttonstates();
    if (buttonOkState == HIGH)
    {
//      , (byte)suiker
      Serial.println("Sended");
      while(true)
      {
        comm.SendCommand(1,1);
        delay(2000);
      }
//      comm.SendCommand(0x0a, (byte)order, ((byte)grootte - 1), ((byte)sterkte - 1), (byte)melk);
      firsttime = true;
      iets = false;
    }
    else if (buttonBackState == HIGH)
    {
      firsttime = true;
      iets = false;
    }
  }

}

void errorscreem(int errorPosition)
{
  clearDisplay();
  writeOnDisplay(errorPosition, "Somting went wrong!");
}

void buttonUp()
{
  if (Position == 64)
  {
    lcd.write(SetDisplay);
    lcd.write(SetCursorPosition + 0);
    Position = 0;
  }
  else if (Position == 20)
  {
    lcd.write(SetDisplay);
    lcd.write(SetCursorPosition + 64);
    Position = 64;
  }
  else if (Position == 84)
  {
    lcd.write(SetDisplay);
    lcd.write(SetCursorPosition + 20);
    Position = 20;
  }
  else
  {
    //Nothing to do here
  }
}

void buttonDown()
{
  if (Position == 0)
  {
    lcd.write(SetDisplay);
    lcd.write(SetCursorPosition + (Position = 64));
  }
  else if (Position == 64)
  {
    lcd.write(SetDisplay);
    lcd.write(SetCursorPosition + (Position = 20));
  }
  else if (Position == 20)
  {
    lcd.write(SetDisplay);
    lcd.write(SetCursorPosition + (Position = 84));
  }
  else
  {
    //Nothing to do here
  }
}

void writeOnDisplay(int position, String text)
{
  lcd.write(SetDisplay);
  lcd.write(SetCursorPosition + position);
  lcd.print(text);
}

void clearDisplay()
{
  lcd.write(SetDisplay);
  lcd.write(ClearDisplay);
}

void buttonstates()
{
  buttonUpState = digitalRead(buttonUpPin);
  buttonDownState = digitalRead(buttonDownPin);
  buttonOkState = digitalRead(buttonOkPin);
  buttonBackState = digitalRead(buttonBackPin);
  delay(200);
}

