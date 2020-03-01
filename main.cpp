#include "mbed.h"
#include "C12832.h"
#include "Volume.h"

C12832 lcd(p5, p7, p6, p8, p11);
DigitalIn vol_tipk(p12);
DigitalIn mute_tipk(p14);
DigitalIn plus_tipk(p29);
DigitalIn minus_tipk(p20);
DigitalOut mute_out (p15);
int vol=53;
int vollcd=0;



DigitalIn mute(PD_7);       //deklaracija MUTE tipke
float muteReading;          //registriranje MUTE tipke
int muteFlag;               //oznaka da je MUTE aktivan

//pomoćne varijable za spremanje stanja volume-a prije mute-a
int saveVol, saveVolLcd;    

DigitalIn plus(PD_4);       //deklaracija PLUS tipke
DigitalIn minus(PD_5);      //deklaracija MINUS tipke


Serial pc(USBTX,USBRX);

//instanca klase volume sa inicijalnim vrijednostima iz konstruktora
Volume volume(PD_6,53,0);

int main()
{
    pc.printf("POZDRAV\nmolimo pricekajte 2 sekunde\n");
    wait(2);

    while (1) {
        
        /*
        *   ukoliko se detektira pritisak mute tipke, postavlja zastavicu na 1
        */
        
        muteReading = mute.read();
        if (muteReading > 0.7) {
            muteFlag = 1;
            pc.printf ("MUTE\n\n");
            saveVol = volume.getVolume();           //sprema zadnje poznato stanje vol
            saveVolLcd = volume.getVolumeLcd();     //sprema zadnje poznato stanje vollcd
            volume.muteFunc();                      // postavlja vol i vollcd u 0
            wait(1);
            
            /*
            *   sve dok je mute aktivan, program će čekati da se stisne ponovo mute
            *   nakon toga zadnje poznate vrijednosti prije mute-a push-a natrag u 
            *   volume sa setVolume() funkcijom, postavlja zastavicu u 0 i sa
            *   break izlazi iz while petlje
            */
            
            while (muteFlag==1) {           
                muteReading = mute.read();
                if (muteReading > 0.7) {
                    volume.setVolume(saveVol);
                    volume.setVolumeLcd(saveVolLcd);
                    muteFlag = 0;                     // zastavica u 0
                    pc.printf("UNMUTED\nZadanja poznata stanja su:\nvol:\t%d\nvollcd:\t%d\n", saveVol, saveVolLcd);
                    wait(1);
                    break;
                }
            }
        }
        
        
        /* 
        * zastavica za volume, privremena varijabla koja označava jesmo li u 
        * volume modu ili ne
        */
        int volFlag;
        
        /* 
        *   očitavanje VOLUME tipke, ako registrira pritisak na tipku
        *   postavlja zastavicu u 1 i koristi ju za while petlju
        */
        volume.detekcija();
        if (volume.isActive()){
            volFlag = 1;
            pc.printf("prilagodba glasnoce\n");
            wait(0.5);
        }
        // dok je zastavica = 1
        while (volFlag == 1) {
            
            // očitavanje plus tipke
            float readPlus = plus.read();
            if (readPlus > 0.7) {
                volume.volumeUp();
                pc.printf("glasnoca: %d\tlcd: %d\n", volume.getVolume(), volume.getVolumeLcd());
                wait(0.2);
            }
            
            //očitavanje minus tipke
            float readMinus = minus.read();
            if (readMinus > 0.7) {
                volume.volumeDown();
                pc.printf("glasnoca: %d\tlcd: %d\n", volume.getVolume(), volume.getVolumeLcd());
                wait(0.2);

            }
            
            // ponovna detekcija volume tipke, ako ode u 1, izaći će iz podešavanja glasnoće
            volume.detekcija();
            if (volume.isActive()){
                pc.printf(" izasli ste iz volume-a\n");
                volFlag = 0;
                wait(0.5);
                break;   
            }
            
        }


    }
}




            lcd.cls();
            lcd.locate(0,0);
            lcd.printf("MUTE");

                lcd.cls();
                lcd.locate(0,0);
                lcd.printf("UNMUTED");


        int vol=vol_tipk;
        int mute=mute_tipk;

        lcd.cls();                                                           //ispis na ekran
        lcd.locate(0,0);                                                     //ispitivanje stanja tipke Volume
        if(vollcd>0) {
        lcd.printf("GLASNOCA: +%d dB",vollcd);
        } else {
        lcd.printf("GLASNOCA: %d dB",vollcd);
        }
    }
}
