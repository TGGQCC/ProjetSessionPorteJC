/**
    Class MyLeds : Gestion d'un keypad Utilisant un GPIO d'un contrôleur ESP32
    @file MyKeypad.h (Héritage : Adafruit_NeoPixel)
    @author Jérémie Cyr
    @version 1.0 18/04/21  
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      18/04/21   JC          Première version de la classe
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        adafruit/Adafruit NeoPixel @ ^1.7.0
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    Nombre de leds 8
            GPIO15 : Controlle des 8 leds
    Exemple d'utilisation (ainsi que toutes les commandes héritées de la Librarie Adafruit)
        #include "MyLeds.h"
        MyLeds *myLeds = NULL;
        myLeds->afficherLedsAccepte(delais, delaisFinal, luminosite); /
        myLeds->black();
**/

#ifndef MY_LEDS_H
#define MY_LEDS_H
#include <Adafruit_NeoPixel.h>

//Pour la gestion des leds
//lib_deps = adafruit / Adafruit NeoPixel @^1.7.0
class MyLeds : public Adafruit_NeoPixel {
public:

    MyLeds(uint16_t nbLeds = 8, uint16_t pin = 2, neoPixelType type=NEO_GRB + NEO_KHZ800) : Adafruit_NeoPixel(nbLeds, pin, type){ };
    void afficherLedsAccepte(int delais, int delaisFinal, int luminosite); //Séquence verte et multicolore clignotante
    void afficherLedsRefuse(int delais, int delaisFinal, int luminosite); //Séquence rouge et rouge clignotante 
    void ledsVerts(int luminosite); //Allume en vert
    void ledsRouges(int luminosite); //Allume en rouge
    void ledsHappy(int luminosite); //Séquence multicolore clignotante
    void ledsUnHappy(int luminosite); //Séquence rouge clignotante
    void black(); //Éteint les leds

    
private:
    String lastError; //Garde la dernière erreur connue
    
};
#endif
