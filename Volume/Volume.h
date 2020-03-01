#ifndef _VOLUME_
#define _VOLUME_


#include "mbed.h"
#include "C12832.h"

class Volume{

private:
    bool aktivno;           // tipka stisnuta?
    float ocitanje;         // pomoćna var za AD pretvorbu
    int vol, vollcd;        
    DigitalIn tipka;        // tipka koja se dodjesljuje svakoj instanci klase
    
public:
    Volume (PinName, int, int);     //konstruktor
    void detekcija();               
    
    void setVolume(int);
    void setVolumeLcd(int);
    void muteFunc();
    bool isActive();
    void volumeUp();
    void volumeDown();  
    int getVolume();
    int getVolumeLcd();  
    
};


#endif