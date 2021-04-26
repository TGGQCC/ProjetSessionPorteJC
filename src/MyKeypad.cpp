/** MyKeypad.cpp 
 * Copyright (C) 2021 Jérémie Cyr
 * All rights reserved.
 *
 * Faire la gestion du keypad
 * V1.0 (voir le fichier MyKeypad.h)
 **/

#include <Arduino.h>
#include "MyKeypad.h"
using namespace std;
   
 /**
 * changePassword
 *
 * Change le mot de passe pour celui choisis par l'utilisateur
 * 
 * @param char *passBuffer pointeur qui va chercher le mot de passe déja enregistré
 * @param char *inputBuffer pointeur qui va chercher le mot de passe que l'utilisateur a entré
 */
void MyKeypad::changePassword(char *passBuffer, char *inputBuffer)
{
  passBuffer[0] = inputBuffer[0]; //Copie le contenu de inputBuffer dans passBuffer
  passBuffer[1] = inputBuffer[1];
  passBuffer[2] = inputBuffer[2];
  passBuffer[3] = inputBuffer[3];
  inputBuffer[3] = _NULL; //Remet le le dernier input du buffer a null 
}
 
 /**
 * resetInputBuffer
 *
 * Sers à modifier le contenu du input buffer pour ne pas pouvoir simplement cliquer sur enter pour déverrouiler la porte sans rerentrer le mot de passe * 
 * @param char *inputBuffer pointeur qui va chercher le mot de passe que l'utilisateur a entré
 */
void MyKeypad::resetInputBuffer(char *inputBuffer)
{
  //Remet inputBuffer a null 
    inputBuffer[0] = _NULL; 
    inputBuffer[1] = _NULL; 
    inputBuffer[2] = _NULL; 
    inputBuffer[3] = _NULL; 
}


