/** MyLeds.cpp 
 * Copyright (C) 2021 Jérémie Cyr
 * All rights reserved.
 *
 * Faire la gestion du ring de leds
 * V1.0 (voir le fichier MyLeds.h)
 **/

#include <Arduino.h>
#include "MyLeds.h"
using namespace std;

 /**
 * ledsVerts
 *
 * Allume les leds en vert
 * 
 * @param int luminosite Luminosité des leds
 */
void MyLeds::ledsVerts(int luminosite) {
  black();
  setBrightness(luminosite);
  setPixelColor(0, Color(0, 255, 0));
  setPixelColor(1, Color(0, 255, 0));
  setPixelColor(2, Color(0, 255, 0));
  setPixelColor(3, Color(0, 255, 0));
  setPixelColor(4, Color(0, 255, 0));
  setPixelColor(5, Color(0, 255, 0));
  setPixelColor(6, Color(0, 255, 0));
  setPixelColor(7, Color(0, 255, 0));
  show();
}

 /**
 * ledsRouges
 *
 * Allume les leds en rouge
 * 
 * @param int luminosite Luminosité des leds
 */
void MyLeds::ledsRouges(int luminosite) {
  black();
  setBrightness(luminosite);
  setPixelColor(0, Color(255, 0, 0));
  setPixelColor(1, Color(255, 0, 0));
  setPixelColor(2, Color(255, 0, 0));
  setPixelColor(3, Color(255, 0, 0));
  setPixelColor(4, Color(255, 0, 0));
  setPixelColor(5, Color(255, 0, 0));
  setPixelColor(6, Color(255, 0, 0));
  setPixelColor(7, Color(255, 0, 0));
  show();
}

 /**
 * ledsHappy
 *
 * Allume chaque leds d'une couleur différente a 35 millisecondes d'intervalle 
 * 
 * @param int luminosite Luminosité des leds
 */
void MyLeds::ledsHappy(int luminosite) {
  black();
  setBrightness(luminosite);
  setPixelColor(0, Color(255, 255, 255)); //En RVB
  delay(35); //En millisecondes
  show();
  setPixelColor(1, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(2, Color(0, 255, 0));
  delay(35);
  show();
  setPixelColor(3, Color(0, 0, 255));
  delay(35);
  show();
  setPixelColor(4, Color(255, 0, 255));
  delay(35);
  show();
  setPixelColor(5, Color(255, 255, 0));
  delay(35);
  show();
  setPixelColor(6, Color(0, 255, 255));
  delay(35);
  show();
  setPixelColor(7, Color(111, 222, 255));
  delay(35);
  show();
}


 /**
 * ledsUnHappy
 *
 * Allume chaque leds en rouge à 35 millisecondes d'intervalle 
 * 
 * @param int luminosite Luminosité des leds
 */
void MyLeds::ledsUnHappy(int luminosite) {
  black();
  setBrightness(luminosite);
  setPixelColor(0, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(1, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(2, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(3, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(4, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(5, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(6, Color(255, 0, 0));
  delay(35);
  show();
  setPixelColor(7, Color(255, 0, 0));
  delay(35);
  show();
}

/**
 * afficherLedsAccepte
 *
 * Démarre une séquence de leds qui clignote vert et multicolore 
 * 
 * @param int delais Délais entre chaque changement de couleur
 * @param int delaisFinal Délais avant d'éteindre les leds à la fin
 * @param int luminosite Luminosité des leds
 */
void MyLeds::afficherLedsAccepte(int delais, int delaisFinal, int luminosite) {
    ledsVerts(luminosite);
    delay(delais);
    black();
    delay(delais);
    ledsHappy(luminosite);
    delay(delais);
    black();
    delay(delais);
    ledsVerts(luminosite);
    delay(delaisFinal);
    black();
}


/**
 * afficherLedsRefuse
 *
 * Démarre une séquence de leds qui clignote rouge
 * 
 * @param int nbreSecondes Temps de veille en secondes
 */
void MyLeds::afficherLedsRefuse(int delais, int delaisFinal, int luminosite) {
    ledsRouges(luminosite);
    delay(delais);
    black();
    delay(delais);
    ledsUnHappy(luminosite);
    delay(delais);
    black();
    delay(delais);
    ledsRouges(luminosite);
    delay(delaisFinal);
    black();
}

/**
 * black
 *
 * Éteint les leds (La fonction de neopixel ne fonctionnait pas)
 * 
 */
void MyLeds::black() {
  setBrightness(0);
  show();
}



