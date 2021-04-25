/** MyOled.cpp 
 * Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Faire la gestion de l'écran Oled
 * V1.0 (voir le fichier MyOled.h)
 * Modifications : Jérémie Cyr | Ajout et modification de fonctionnalités
 **/

#include <Arduino.h>
#include "MyOled.h"
using namespace std;


//Génère des intervales de UNE seconde pour synchroniser le système
//Entre autre les fonctionnalités de veille
void MyOled::vATaskSecondCount(void *pvParameters) {
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        xLastWakeTime = xTaskGetTickCount();
    }
    vTaskDelete(NULL);
}

/**
 * init Initialisation de l'objet
 *
 * La classe nécessite une initialisation préalable après l'instanciation
 * 
 * @param addrI2C Adresse I2C de l'écran OLED
 * @return int 1 : Si erreur d'adresse   0:si ok
 */
int MyOled::init(uint8_t addrI2C) {
    if (!begin(SSD1306_SWITCHCAPVCC, addrI2C)) { 
        return (1);
    }

    //Pour plus de détails, voir la documentation de la librarie Adafruit
    cp437(true);
    clearDisplay();
    setTextColor(SSD1306_WHITE);
    setTextSize(1);
    setCursor(1, 1);
    display();

    xTaskCreate(vATaskSecondCount, "vATask Loop", 10000, NULL, 1, NULL);

    return (0); //Ok
    }




/**
 * DisplayInitialisationSystem 
 * 
 * Affiche sur l'écran la première fenetre d'initialisation
 *
 * @param String nomDuSysteme :  Nom du système à afficher
 */
void MyOled::DisplayInitialisationSystem(string nomDuSysteme) {
    clearDisplay();
    setTextSize(1);

    setCursor(0, 0);
    println(nomDuSysteme.c_str());

    setTextSize(1);

    setCursor(0, 28);
    println("Entrez le code...");

    display();
    delay(300);
}

  
/**
 * DisplayPassword 
 * 
 * Affiche des x sur l'écran au lieu d'afficher les caractères du mot de passe
 *
 * @param String nomDuSysteme :  Nom du système à afficher
 * @param int i :  Compteur
 */
void MyOled::DisplayPassword(string nomDuSysteme, int i) {
    
    char passCache[4];
    if(i == 0)
    {
        clearDisplay();
    }
    setTextSize(1);

    setCursor(0, 0);
    println(nomDuSysteme.c_str());

    setTextSize(1);

    setCursor(0, 28);
    if(i < 4)
    {
        passCache[i] = 120;
        passCache[0] = 120;
        print(passCache[0]);
        print(passCache[1]);
        print(passCache[2]);
        print(passCache[3]);
    }

    display();
    delay(300);
}
 

 /**
 * DisplayWorkingScreen Affiche sur l'écran les données brutes
 *
 * @param String nomDuSysteme :  Nom du système à afficher
 * @param String message :       Message à afficher
 */
void MyOled::DisplayWorkingScreen(string nomDuSysteme, string message) {
    clearDisplay();
    setTextSize(2);

    setCursor(0, 0);
    println(nomDuSysteme.c_str());
   
    setTextSize(1);

    setCursor(0, 28);
    println(message.c_str());

    display();

    }



/**
 * print Affiche une chaine de caractère sur le Oled
 *
 * Affiche une chaine de caractère sur le Oled
 * 
 * @param String toDisplay      Chaine de caractères à afficher
 * @param bool displayAfter     Force un affichage 
 * @param int makeDelaySecondes Attends un nombre de secondes avant de poursuivre
 */
void MyOled::printIt(string toDisplay, bool displayAfter, int makeDelaySecondes) {
    println(toDisplay.c_str());
    if (displayAfter)
        display();
    delay(makeDelaySecondes);
}

/**
 * print Affiche une chaine de caractère sur le Oled
 *
 * Affiche une chaine de caractère sur le Oled
 * 
 * @param int       posx Positionnement en X
 * @param int       posy Positionnement en Y
 * @param String    toDisplay Chaine de caractères à afficher
 * @param bool      displayAfter Force un affichage 
 * @param int       makeDelaySecondes Attends un nombre de secondes avant de poursuivre
 */
void MyOled::printIt(int posx, int posy, string toDisplay, bool displayAfter, int makeDelaySecondes) {
    setCursor(posx, posy);
    printIt( toDisplay,  displayAfter,  makeDelaySecondes);
}

/**
 * printSpecialChar 
 *
 * Affiche  un caractère spécial sur le Oled (é ou o)
 * 
 * @param String spacialCaractere   Caractère é : Accent aigu ou o : Degrée
 * @param int makeDelaySecondes     Attends un nombre de secondes avant de poursuivre
 */
void MyOled::printSpecialChar(string spacialCaractere, int makeDelaySecondes){
    if (spacialCaractere == "é")    write(130); //é
    if (spacialCaractere == "o")    write(248); //Le o du Degre Celcius 167
    delay(makeDelaySecondes);
}

