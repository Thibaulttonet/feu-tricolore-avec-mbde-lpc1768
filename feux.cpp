#include "mbed.h"

DigitalIn BP(p20);
DigitalOut LedGreen(p19);
DigitalOut LedOrange(p18);
DigitalOut LedRed(p17);
Timer timer1;
AnalogIn LDR(p16);

int main()
{
    BP.mode(PullUp);
    int etat=0;
    int bouton;
    float lum;
    timer1.start();
    while(1) {

        bouton=BP.read();           //lecture de l'entrée
        lum=LDR.read()*3.3;
        printf("%d\n\r",etat);
        switch (etat) {             //gestion des transitions
            case 0 :
                if(bouton==0) {
                    etat=1;
                    timer1.reset();
                }
                if(lum>0.55) {
                    etat=10;
                    timer1.reset();
                }
                break;
            case 1 :
                if(timer1.read()>2) {
                    etat=2;
                    timer1.reset();
                }
                break;
            case 2 :
                if(timer1.read()>5) {
                    etat=0;
                    timer1.reset();
                }
                break;
            case 10 :
                if(timer1.read()>1) {
                    etat=11;
                    timer1.reset();
                }
                if(lum<0.55) {
                    etat=0;
                }
                break;
            case 11 :
                if(timer1.read()>1) {
                    etat=10;
                    timer1.reset();
                }
                break;
        }
        switch (etat) {             //gestion des actions
            case(0):
                LedGreen.write(1);
                LedOrange.write(0);
                LedRed.write(0);
                break;
            case(1):
                LedGreen.write(0);
                LedOrange.write(1);
                LedRed.write(0);
                break;
            case(2):
                LedGreen.write(0);
                LedOrange.write(0);
                LedRed.write(1);
                break;
            case(10):
                LedGreen.write(0);
                LedOrange.write(1);
                LedRed.write(0);
                break;
            case(11):
                LedGreen.write(0);
                LedOrange.write(0);
                LedRed.write(0);
                break;
        }

    }
}