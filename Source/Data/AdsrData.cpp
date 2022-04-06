//AdsrData.cpp

// For 'Envelope(Amplifier)' of the synthesiser

#include "AdsrData.h"
void AdsrData::update(const float attack, const float decay, const float sustain, const float release)
{
    //Attack
    adsrParams.attack = attack;
    //Decay
    adsrParams.decay = decay;
    //Sustain
    adsrParams.sustain = sustain;
    //Release
    adsrParams.release = release;

    setParameters(adsrParams);
}
