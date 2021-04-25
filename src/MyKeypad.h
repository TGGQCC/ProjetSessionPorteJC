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
        MyKeypad *myKeypad = new MyKeypad(makeKeymap(hexakeyss), rowPins, colPins, ROW, COL);


**/


#ifndef MY_KEYPAD_H
#define MY_KEYPAD_H
#include "Keypad.h"
const byte COLS = 4; //Number of columns
const byte ROWS = 4; //Number of rows
char hexaKeys[ROWS][COLS] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}}; //Definition of the symbols on the keypad
byte rowsPins[ROWS] = {13, 12, 14, 27}; //Pins used for the keypad rows
byte colsPins[COLS] = {26, 25, 33, 32}; //Pins used for the keypad columns

//Pour la gestion du Keypad
//lib_deps = Mark Stanley Keypad @ ^3.1.1
class MyKeypad : public Keypad {
public:

    MyKeypad(char hexakeyss[ROWS][COLS] = hexaKeys, byte rowPins[ROWS] = rowsPins, byte colPins[COLS] = colsPins, byte ROW = ROWS, byte COL= COLS) : Keypad(makeKeymap(hexakeyss), rowPins, colPins, ROW, COL){ };
    char showKey(MyKeypad aKeypad); //TEST      
    
private:
    String lastError; //Garde la dernière erreur connue
    
};
#endif
