/**
    ProjetSessionJC
    Programme de gestion d'une porte avec un code d'accès
    @file main.cpp
    @author Jérémie Cyr
    @version 1.0 18/04/21  
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      18/04/21   JC          Première version qui n'est pas parfaite mais fonctionnelle
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Mark Stanley Keypad @ ^3.1.1
        adafruit/Adafruit NeoPixel @ ^1.7.0
        adafruit/Adafruit GFX Library @ ^1.10.1
        adafruit/Adafruit SSD1306 @ ^2.4.0
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    Classes du système
        MyKeypad    V1.0    Pour la gestion du clavier
            GPIO13 : Row 1
            GPIO12 : Row 2
            GPIO14 : Row 3
            GPIO27 : Row 4
            GPIO26 : Column 1
            GPIO25 : Column 2
            GPIO33 : Column 3
            GPIO32 : Column 4

        MyLeds      V1.0    Pour controller le ring de leds
            Nombre de leds : 8
            GPIO2 : Controlle des 8 leds

        MyOled      V1.0    Pour interfacer le Oled
            Résolution 128 x 64
            Protocole I2C, Adresse : 0x3C 
            GPIO21 : SDA
            GPIO22 : SCL
**/
#include <string>
#include <iostream>

//Classe MyKeypad
#include <MyKeypad.h>
MyKeypad *myKeypad = NULL;
char enter = 35; //Indicate wich caracter is the enter button on the keypad

//Classe MyLeds
#include <MyLeds.h> 
#define NOMBRE_LEDS 8 //Number of leds
#define PIN 2  //Pin used for led ring
#define TYPE NEO_GRB + NEO_KHZ800 //Neopixel Type
MyLeds *myLeds = NULL;

//Classe MyOled 
#include <wire.h>
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define OLED_RESET 4            // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C   // Adresse I2C de l'écran Oled
#include "MyOled.h"
MyOled *myOled = NULL;

//Constant used for the code needed to change the password
const int passChangeCode = 42;

//Variables used to controll the password
char passBuffer[4] = {67, 48, 56, 57}; //Default Password (C089)
char inputBuffer[4];  //Buffer for the user input
int i = 0;  //Counts how many times the user clicked on a button
bool changePassword = false;  //Activates or deactivates the possibility to change the password (True = On, False = Off)

/**
 * ouverturePorteReussi 
 * 
 * Affiche l'ouverture de la porte et allume la séquence de leds
 *
 * @param int delais :  Délais entre le changement de couleur des leds
 * @param int delaisFinal :  Délais pendant lequel les leds restent allumées avant de s'éteindre
 * @param int luminosite :  Luminosité des leds
 */
void ouverturePorteReussi(int delais, int delaisFinal, int luminosite){
        myOled->DisplayWorkingScreen("Porte", "Code correct");
        delay(1000);
        myOled->DisplayWorkingScreen("Porte", "Ouverture en cours...");
        myLeds->afficherLedsAccepte(delais, delaisFinal, luminosite); //Démarre une séquence de couleurs de leds
        myLeds->black(); //Éteint les leds
        myOled->clearDisplay(); //Vide le contenu de l'écran
        myOled->DisplayInitialisationSystem("Porte Verrouillee");
}

/**
 * passCheck 
 * 
 * Vérifie si le mot de passe entré est bon
 *
 */
void passCheck(){
  if(passBuffer[0] == inputBuffer[0] && passBuffer[1] == inputBuffer[1] && passBuffer[2] == inputBuffer[2] && passBuffer[3] == inputBuffer[3]){
    ouverturePorteReussi(600, 1600, 10); 
    myKeypad->resetInputBuffer(inputBuffer); //Sers à modifier le contenu du input buffer pour ne pas pouvoir simplement cliquer sur enter pour déverrouiler la porte sans rerentrer le mot de passe
    changePassword = true; //Rend le changement de mot de passe possible
    i=0;  //Remet le compteur à 0
  }
  else{
    myLeds->afficherLedsRefuse(600, 1600, 10);
    myKeypad->resetInputBuffer(inputBuffer); //Sers à modifier le contenu du input buffer pour ne pas pouvoir simplement cliquer sur enter pour déverrouiler la porte sans rerentrer le mot de passe
    changePassword = false; //Rend le changement de mot de passe impossible
    myOled->DisplayInitialisationSystem("Porte Verrouillee");
    i=0;  //Remet le compteur à 0
  }
}

/**
 * passChange 
 * 
 * Change le mot de passe pour ce que l'utilisateur a entré
 *
 */
void passChange(){
  myOled->DisplayWorkingScreen("Mot de passe", "Changement du mot de passe en cours...");
  delay(1000); //En ms
  myKeypad->changePassword(passBuffer, inputBuffer); //Modifie le mot de passe
  changePassword = false; //Désactive la possibilité de changer le mot de passe
  i=0; //Remet le compteur à 0
  myOled->clearDisplay(); //Vide l'écran
  myOled->DisplayInitialisationSystem("Porte Verrouillee");
}

void setup(){
  myKeypad = new MyKeypad();
  myLeds = new MyLeds(NOMBRE_LEDS, PIN, TYPE);
  myLeds->begin();
  myLeds->black(); //Éteint les leds
  myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
  myOled->init(OLED_I2C_ADDRESS);
  myOled->DisplayInitialisationSystem("Porte Verrouillee");
}
 
void loop(){
  char customKey = myKeypad->getKey(); //Prend la touche qui a été appuyée et la stocke dedans
  //En appuyant sur la touche enter, on vérifie si le mot de passe entré est bon
  if(enter == customKey && inputBuffer[0] != _NULL){
    passCheck(); //Appelle la fonction qui vérifie si le mot de passe est bon
  }
  //Enregistre les caractères entrés par l'utilisateur dans le inputBuffer chaque fois qu'une touce est enfoncée
  if(customKey != enter && customKey != '\0' && i < 4){
    myOled->DisplayPassword("Porte Verrouillee", i);
    inputBuffer[i] = customKey;
    i++;
  }
  //En ayant changePassword a true (Activé) et si le bouton qui a été appuyé est celui choisis pour changer le mot de passe  (*), le mot de passe sera changé par celui entré avant d'appuyer sur *
  if(changePassword && customKey == passChangeCode){          
        passChange(); //Appelle la fonction qui change le mot de passe
  }
}