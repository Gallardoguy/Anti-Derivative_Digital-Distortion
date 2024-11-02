#include "daisy_seed.h"
#include "DistBP.h"
#include "BMlow.h"
#include "BMhigh.h"
#include "DistHP.h"
#include "TSTone.h"
#include "PeakEQ.h"

using namespace daisy;

DaisySeed  hw;

DistBP bmBP;
BMlow bmLow;
BMhigh bmHigh;

TSTone tstone;
DistHP tsHP;

PeakEQ stage1, stage2, stage3, stage4, stage5;

bool on;
int effect;

float knob1, knob2, knob3;

// CONTEXT FOR THE FUNCTIONS AND MATH BELOW ARE IN THIS PAPER
// https://acris.aalto.fi/ws/portalfiles/portal/27135145/ELEC_bilbao_et_al_antiderivative_antialiasing_IEEESPL.pdf


float x1 = 0;
float x2 = 0;
float x3 = 0;
float f0 = 0;
float f1 = 0;
float f2 = 0;
float f3 = 0;

float ts3AD(float in) {
    float out;

    float absx = abs(in);
    float xx = in*in;

    float num = 6*(2*absx + xx + 1)*log(absx+1) - 2*(xx + 3)*absx - 9*xx;

    out = -1*num/12;

    return out;
}

float ts(float in) {
    return in / (1 + abs(in));
}

float bm3AD(float x) {
    float out;
    float stage1;

    if (x >= 0.4) {
        stage1 = 0.666667*x*x*x;
    } else if(x<= -0.4) {
        stage1 = -1*0.666667*x*x*x;
    } else {
        stage1 = 0.041666*x*x*x*x;
    }

    stage1 *= 40;

    if (stage1 >= 0.4) {
        out = 0.666667*stage1*stage1*stage1;
    } else if(stage1 <= -0.4) {
        out = -1*0.666667*stage1*stage1*stage1; // slilcon diode hard clipping
    } else {
        out = 0.041666*stage1*stage1*stage1*stage1;
    }
    return out;
}

float bm(float in) {
    if (in > 0.4) {
        return 0.4;
    } else if (in < -0.4) {
        return -0.4;
    } else {
        return in;
    }
}

float HM3AD(float in) {
    float out;
    float stage1;

    float absx = abs(in);
    float xx = in*in;

    float num = 6*(2*absx + xx + 1)*log(absx+1) - 2*(xx + 3)*absx - 9*xx;

    stage1 = -1*num/12;

    stage1 *= 40;

    if (stage1 >= 0.17) {
        out = 0.000002833*stage1*stage1*stage1;
    } else if(stage1 <= -0.17) {
        out = -1*0.000002833*stage1*stage1*stage1; // germanium diode hard clipping approximation
    } else {
        out = 0.041666*stage1*stage1*stage1*stage1;
    }
    return out;
}

float hm(float in) {
    if (in > 0.17) {
        return 0.17;
    } else if (in < -0.17) {
        return -0.17;
    } else {
        return in;
    }
}

float dist3ADAA(float x) {
    float out = 0;
    float sigma = 0.00001;

    float x_x1 = x-x1;
    float x1_x2 = x1-x2;
    float x2_x3 = x2-x3;
    float x1_x3 = x1-x3;
    float x_x2 = x-x2;


    if (effect == 0) {

        if(x_x1 < sigma){
            return ts( (x + x1) / 2);
        } else if(x1_x2 < sigma) {
            return ts( (x1 + x2) / 2);
        } else if(x2_x3 < sigma) {
            return ts( (x2 + x3) / 2);
        } else if(x1_x3 < sigma) {
            return ts( (x1 + x3) / 2);
        } else if(x_x2 < sigma) {
            return ts( (x + x2) / 2);
        }

        f0 = ts3AD(x);
        f1 = ts3AD(x1);
        f2 = ts3AD(x2);
        f3 = ts3AD(x3);
    } else if(effect == 1) {

        if(x_x1 < sigma){
            return bm( (x + x1) / 2);
        } else if(x1_x2 < sigma) {
            return bm( (x1 + x2) / 2);
        } else if(x2_x3 < sigma) {
            return bm( (x2 + x3) / 2);
        } else if(x1_x3 < sigma) {
            return bm( (x1 + x3) / 2);
        } else if(x_x2 < sigma) {
            return bm( (x + x2) / 2);
        }

        f0 = bm3AD(x);
        f1 = bm3AD(x1);
        f2 = bm3AD(x2);
        f3 = bm3AD(x3);
    } else {
        if(x_x1 < sigma){
            return hm( (x + x1) / 2);
        } else if(x1_x2 < sigma) {
            return hm( (x1 + x2) / 2);
        } else if(x2_x3 < sigma) {
            return hm( (x2 + x3) / 2);
        } else if(x1_x3 < sigma) {
            return hm( (x1 + x3) / 2);
        } else if(x_x2 < sigma) {
            return hm( (x + x2) / 2);
        }

        f0 = HM3AD(x);
        f1 = HM3AD(x1);
        f2 = HM3AD(x2);
        f3 = HM3AD(x3);
    }
    
    out = 1/x1_x2 * ( 2/x_x2*((f0-f1)/(x_x1) - (f1-f2)/(x1_x2)) - 2/x1_x3*((f1-f2)/(x1_x2) - (f2-f3)/(x2_x3)));

    x3 = x2;
    x2 = x1;
    x1 = x;

    return out;

}


void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size) {
    knob1 = hw.adc.GetFloat(0);
    knob2 = hw.adc.GetFloat(1);
    knob3 = hw.adc.GetFloat(2);

    float gain;

    if(effect == 0) {
        for (size_t i = 0; i < size; i++) {
            gain = 1 + knob1*159;
            float dist = dist3ADAA(IN_L[i]*gain);
            tstone.setFreq(500 + knob2*3500);
            OUT_L[i] = knob3*tstone.Process(tsHP.Process(dist));
        }
    } else if(effect == 1) {
        for (size_t i = 0; i < size; i++) {
            gain = 0.2+knob1*0.8;
            float dist = dist3ADAA(IN_L[i]*60*gain);
            float temp = bmBP.Process(dist);
            float low = bmLow.Process(temp);
            float high = bmHigh.Process(temp);
            OUT_L[i] = 4*knob3*(high*knob2 + abs(1-knob2)*low);
        }

    } else if(effect == 2) {
        for (size_t i = 0; i < size; i++) {

            stage1.setGain(-7*knob2);
            stage2.setGain(16*knob2);
            stage3.setGain(-16*knob2);
            stage4.setGain(4*knob2);
            stage5.setGain(4*knob2);

            gain = 20 + knob1*140;
            float dist = dist3ADAA(IN_L[i]*knob1);
            float s1 = stage1.Process(dist);
            float s2 = stage2.Process(s1);
            float s3 = stage3.Process(s2);
            float s4 = stage4.Process(s3);
            float s5 = stage5.Process(s4);
            OUT_L[i] = knob3*s5;
        }
    }

}// end of callback

void InitializeADC()
{
	AdcChannelConfig adc_config[3];
    adc_config[0].InitSingle(hw.GetPin(15));//knob 1
    adc_config[1].InitSingle(hw.GetPin(16));//knob 2
    adc_config[2].InitSingle(hw.GetPin(17));//knob 3
	hw.adc.Init(adc_config, 3);
	hw.adc.Start();
}

int main(void) {

    hw.Configure();
    hw.Init();
    hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_96KHZ);
    hw.SetAudioBlockSize(4);

    InitializeADC();

    bmBP.Init();
    bmHigh.Init();
    bmLow.Init();

    stage1.Init();
    stage1.setParams(20, 300, 0.707);//fc, bw, Q

    stage2.Init();
    stage2.setParams(72, 300, 1.3);

    stage3.Init();
    stage3.setParams(220, 300, 0.707);

    stage4.Init();
    stage4.setParams(1000, 300, 1.707);

    stage5.Init();
    stage5.setParams(1500, 300, 1.707);

    tstone.Init();
    tsHP.Init();

    Switch momentary;
    momentary.Init(seed::D0, 1000); //cmomentary switch pin

    Switch latching;
    latching.Init(seed::D1); // latching swith pin

    Switch3 toggle;
    toggle.Init(seed::D7, seed::D8);

    GPIO sw, led;
    sw.Init(seed::D2, GPIO::Mode::OUTPUT);
    led.Init(seed::D5, GPIO::Mode::OUTPUT);

    sw.Write(true);
    led.Write(false);
    on = false;


    switch(toggle.Read()) {
        case Switch3::POS_LEFT: effect = 2; break;
        case Switch3::POS_CENTER: effect = 1; break;
        case Switch3::POS_RIGHT: effect = 0; break;
        default: effect = 0;
    }

    hw.StartAudio(AudioCallback);

    
    while(1) {

        momentary.Debounce();
        if(momentary.RisingEdge()){ //momentary switch
            on = !on;
        }

        latching.Debounce();    
        on = latching.Pressed(); //latching switch

        if(on) {
            sw.Write(false);
            led.Write(true);
        } else {
            sw.Write(true);
            led.Write(false);
        }

        switch(toggle.Read()) {
            case Switch3::POS_LEFT: effect = 2; break;
            case Switch3::POS_CENTER: effect = 1; break;
            case Switch3::POS_RIGHT: effect = 0; break;
            default: effect = 0;
        }
    }
}