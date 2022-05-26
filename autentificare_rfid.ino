//__________________________________________________________________________________________________________________________________________
//                                                                                                                                          |
//--------------------AUTENTIFICARE CONTURI LOCALE PC CU CARTELA RFID,FIECARE CARTELA FIIND SPECIFICA UNUI CONT LOCAL-----------------------|
//   
// Apropiati cartela aproximativ 15 secunde pentru a executa corect programul.
//_____---ANCHIDIN GABRIEL ALEXANDRU--_________  !
//__________________________________________________________________________________________________________________________________________|

//Acestui cod ii sunt asociate 4 cartele din care doua suntasociate conturilor de user din PC iar celelalte nu sunt asociate nici unui cont pentru a verifica si conditia Else din void loop 

#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

constexpr uint8_t RST_PIN = 9;  
constexpr uint8_t SS_PIN = 10;  

MFRC522 mfrc522(SS_PIN, RST_PIN);

int RXLED = 17;

void setup() {
  pinMode(RXLED, OUTPUT); 
  Serial.begin(9600);
  SPI.begin();    
  mfrc522.PCD_Init();   
  mfrc522.PCD_DumpVersionToSerial();
  Keyboard.begin();
}

void readHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void loop() {
  // Cauta cartela
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    digitalWrite(RXLED, HIGH); 
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  digitalWrite(RXLED, LOW);
  Serial.print("serie cartela: ");// Afiseaza in consola cuvintele serie cartela urmate de seria UID a cartelei 
  readHex(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();


  //Conditie pentru a valida prima cartela rfid si daca este valida conditia se executa codul de mai jos
  if (mfrc522.uid.uidByte[0] == 0x03 &&       //0x03=the first 2 digits of the uid series are specific to your card
      mfrc522.uid.uidByte[1] == 0x82 &&        //0x82= the second group of numbers in the uid series
      mfrc522.uid.uidByte[2] == 0x3E &&       //0x3E=the third group in the uid series
      mfrc522.uid.uidByte[3] == 0x19) {       //0x19=the last group in the uid series of the card 
           Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_DELETE);
     
      Keyboard.releaseAll();
       Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('s');
      Keyboard.releaseAll();
   
      Keyboard.print("alex");//one of the computer accounts
      Keyboard.press(KEY_TAB);
      Keyboard.print("alex");//Password
      Keyboard.write(10);
               Keyboard.press('Enter');
                   Keyboard.release('Enter');
                     Keyboard.releaseAll();
                    
       
                                                  
    Serial.println("Cartela asociata");//printeaza in consola mesajul Cartela Asociata
    delay(5000);
    return;
  }
     
        else if(mfrc522.uid.uidByte[0] == 0xC3 &&     //Conditie pentru a valida a doua cartela diferita de prima si executa secventa de cod specifica cartelei care este validata
          mfrc522.uid.uidByte[1] == 0xD4 &&
          mfrc522.uid.uidByte[2] == 0x6A &&
          mfrc522.uid.uidByte[3] == 0x11){
                        Keyboard.press(KEY_LEFT_CTRL);
                            Keyboard.press(KEY_LEFT_ALT);
                               Keyboard.press(KEY_DELETE);
                              Keyboard.releaseAll();
       Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('s');
      Keyboard.releaseAll();
   
      Keyboard.print("alex2");//  computer accounts
      Keyboard.press(KEY_TAB);
      Keyboard.print("!@#$%^&*()asdfghjkl;ZXCVBN");//Password
      Keyboard.write(10);
               Keyboard.press('Enter');
                   Keyboard.release('Enter');
                     Keyboard.releaseAll();
                    
       
                                                  
    Serial.println("Cartela asociata");//printeaza in consola mesajul Cartela Asociata
    delay(5000);
    return;
          }
          else if(mfrc522.uid.uidByte[0] == 0xA4 &&   ////Conditie pentru a valida a doua cartela diferita de prima si executa secventa de cod specifica cartelei care este validata
          mfrc522.uid.uidByte[1] == 0xA5 &&
          mfrc522.uid.uidByte[2] == 0xF2 &&
          mfrc522.uid.uidByte[3] == 0xD2){
    Serial.println("Cartela asociata");
    //aici nu avem niciun cont asociat cartelei de mai sus ,doar ne va printa in consola ca este asociata cartela fara a executa nimic
    delay(5000);
    return;
          }
          else {
            Serial.println("Cartela nu este asociata");//aici ne v a afisa in consola mesajul ca nu este asociata cartela pe care am scanat-o. 
            delay(5000);
    return;
  }
                                           
}
