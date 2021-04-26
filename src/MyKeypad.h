/**
    Class MyKeypad : Gestion d'un keypad Utilisant un GPIO d'un contrôleur ESP32
    @file MyKeypad.h (Héritage : Keypad)
    @author Jérémie Cyr
    @version 1.0 18/04/21  
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      18/04/21   JC          Première version de la classe
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Mark Stanley Keypad @ ^3.1.1
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    Matrix 4x4
            GPIO13 : Row 1
            GPIO12 : Row 2
            GPIO14 : Row 3
            GPIO27 : Row 4
            GPIO26 : Column 1
            GPIO25 : Column 2
            GPIO33 : Column 3
            GPIO32 : Column 4
    Exemple d'utilisation (ainsi que toutes les commandes héritées de la Librarie Adafruit)
        #include "MyKeypad.h"
        myKeypad = new MyKeypad();
        char customKey = myKeypad->getKey(); //Prend la touche qui a été appuyée et la stocke dedans

**/


#ifndef MY_KEYPAD_H
#define MY_KEYPAD_H
#include "Keypad.h"
const byte COLS = 4; //Number of columns
const byte ROWS = 4; //Number of rows



//Pour la gestion du Keypad
//lib_deps = Mark Stanley Keypad @ ^3.1.1
class MyKeypad : public Keypad {
public:
    MyKeypad() : Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS){ };
    void changePassword(char *passBuffer, char *inputBuffer); //change le mot de passe pour celui choisis par l'utilisateur
    void resetInputBuffer(char *inputBuffer); //Sers à modifier le contenu du input buffer pour ne pas pouvoir simplement cliquer sur enter pour déverrouiler la porte sans rerentrer le mot de passe


private:
    String lastError; //Garde la dernière erreur connue
    //Definition of the symbols on the keypad
    char hexaKeys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
    }; 

    byte rowPins[ROWS] = {13, 12, 14, 27}; //pins used for keypad rows
    byte colPins[COLS] = {26, 25, 33, 32}; //pins used for keypad columns

};
#endif
