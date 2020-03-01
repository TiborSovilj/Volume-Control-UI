#include "C12832.h"
#include "mbed.h"
#include "Volume.h"

C12832 lcd(p5, p7, p6, p8, p11);

Serial pc1(USBTX,USBRX);


// konstruktor u kojem se pozivaju default-ne vrijednosti svake instance klase
// tipka(pin) je poziv instance DigitalIn klase koja je private
Volume::Volume(PinName pin, int initialVol, int initialVolLcd) : tipka(pin)
{
    vol = initialVol;
    vollcd = initialVolLcd;
}


// funkcija kojom postavljanje volume-a ne ovisi o +/- tipkama
void Volume::setVolume(int arg)
{
    vol=arg;
}

// funkcija kojom postavljanje vollcd-a ne ovisi o +/- tipkama
void Volume::setVolumeLcd(int arg)
{
    vollcd=arg;
}

//postavljanje vrijednosti u 0 ukoliko se stisne MUTE tipka
void Volume::muteFunc()
{
    vol = 0;
    vollcd = 0;
}

// očitavanje ulaza na pin-u i postavljanje u privremeno aktivno stanje
// sve dok je tipka stisnuta
void Volume::detekcija()
{
    ocitanje = tipka.read();
    if (ocitanje > 0.7)
        aktivno = 1;
    else 
        aktivno = 0;
}


// provjerava stanje
bool Volume::isActive()
{
    if (aktivno == 1)
        return true;
    else
        return false;

}

//funkcija za pojačavanje ukoliko stisnemo +
void Volume::volumeUp()
{

    vollcd=vollcd+2;
    vol=vol+1;

    if (vol>63 && vollcd>20) {
        vol=63;
        vollcd=20;
        pc1.printf("NEDOZVOLJENA VELICINA\n");
       
    }
}


//funkcija za stišavanje ukoliko stisnemo -
void Volume::volumeDown()
{
    vollcd=vollcd-2;
    vol=vol-1;

    if (vol<20 && vollcd<-66) {
        vol=20;
        vollcd=-66;
        pc1.printf("NEDOZVOLJENA VELICINA\n");
    }
}

// funkcija koja pri pozivu mainu šalje aktualno stanje parametra vol
int Volume::getVolume()
{
    return vol;
}

// funkcija koja pri pozivu mainu šalje aktualno stanje parametra vollcd
int Volume::getVolumeLcd()
{
    return vollcd;
}
