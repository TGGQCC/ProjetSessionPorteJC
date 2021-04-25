/**
    Class MyOled : Gestion d'un écran Oled Utilisant un GPIO d'un contrôleur ESP32
    @file MyOled.h (Héritage : Adafruit_SSD1306)
    @author Alain Dubé
    @version 1.0 17/03/21  

    Historique des modifications
                                      Date      Auteur      Description
                                     18/04/21   JC           Ajout et modification de fonctionnalités
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      17/03/21   Ald          Première version de la classe
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        adafruit/Adafruit GFX Library @ ^1.10.1
        adafruit/Adafruit SSD1306 @ ^2.4.0
        adafruit/Adafruit NeoPixel @ ^1.7.0
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    Résolution 128 x 64
            Protocole I2C, Adresse : 0x3C (défaut)
            GPIO21 : SDA
            GPIO22 : SCL
    Exemple d'utilisation (ainsi que toutes les commandes héritées de la Librarie Adafruit)
        #include "MyOled.h"
        MyOled *myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
        myOled->init(OLED_I2C_ADDRESS);
        myOled->veilleDelay(30); //En secondes
        myOled->DisplayInitialisationSystem("My Oled");
        myOled->DisplayWorkingScreen("Ecole du WEB", "Bienvenue");
        if (myOled->veilleCheck()) cout << "\nEst en veille";

        loop:
            myOled->veilleCheck();

**/


#ifndef MY_OLED_H
#define MY_OLED_H

#include <string>


//Pour la gestion du Oled
//lib_deps = adafruit / Adafruit SSD1306 @^2.4.0
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

class MyOled : public Adafruit_SSD1306 {
public:
    int init(uint8_t addrI2C = 0x3C);   //Parfois 0x3D
    MyOled(TwoWire *twi, uint8_t RST = 4, uint8_t rawHeight = 64, uint8_t rawWidth = 128) : Adafruit_SSD1306(rawWidth, rawHeight, twi, RST){ };
    void printSpecialChar(std::string spacialCaractere, int makeDelaySecondes = 0); //Caractères qui ont des accents
    void printIt(std::string toDisplay, bool displayAfter, int makeDelaySecondes = 0); //makeDelaySecondes: Attends avant de poursuivre
    void printIt(int posx, int posy, std::string toDisplay, bool displayAfter, int makeDelaySecondes = 0); //makeDelaySecondes: Attends avant de poursuivre
    
    void DisplayWorkingScreen(std::string nomDuSysteme, std::string message);
    void DisplayInitialisationSystem(std::string nomDuSysteme);
    void DisplayPassword(std::string nomDuSysteme, int i);
   
    
private:


    //Pour les fonctionnalités de veille
    static void vATaskSecondCount(void *pvParameters);


    String lastError; //Garde la dernière erreur connue
    
};
#endif
