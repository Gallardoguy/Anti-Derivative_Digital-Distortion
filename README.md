# Low Noise Versatile Digital Distortion

![front](images/pedal_front.jpg)
![inside](images/pedal_inside.jpg)

## Goal / Problem Statement

There a few main goals I had in mind with this project. The first was improving the severe noise compared to my last pedal. The second was designing and implementing my own digital filters. This means no external signal processing libraries.
The third was to make a pedal that was a master of one rather than a jack of all trades.

This was so I could improve my own understanding of DSP and filter design, but also to practice anti-aliasing techniques to improve noise performance. I also thought this would be a good opportunity to make this a dedicated distortion pedal since the EQ 
/ tone stack / filtering is basically the only thing that sets two distortion pedals apart. There were other small improvements I also wanted to make such as a way to bypass quantization, anti-aliasing filters on the input and output, and codec input 
voltage protection.



## Distortion Effect

Distortion is a very simple effect to create in analog. All you need are 2 diodes, or 1 zener.
You just put two diodes in reverse in the feedback loop of an amplifier to create soft clipping, or after the op amp shorted to ground for hard clipping. 

By clipping our input we are essentially turning our amplified sine wave into a square wave. This means we are creating harmonics at odd multiples of the base frequency. This gives us a lot to work with since by filtering some harmonics and leaving others, 
we have a lot of possible ways to play with our sound and make it sound even more interesting than it already does. This is why there are so many distortion pedals on the market. It is just as simple to create a digital distortion. We just need to take our 
input samples, amplify them, and then put them through a nonlinear curve. Tanh is a popular soft clipping function. To create hard clipping it’s as simple as amplitude limiting, or an if statement in other words. 


## The Problem With Digital Distortion And Solution

In analog, these harmonics are not an issue. They will go to an amplifier and that's the end of the story. But in digital, these harmonics will alias the moment the samples are processed through the nonlinearity. This creates so much noise, that it 
sounds like white noise with all the harmonic content spread across the spectrum. To fix this, I initially applied oversampling. By sampling at 96k instead of 48k, my bandwidth was doubled, and that directly reduces the amount of harmonics that will 
alias. And, some of the ones that do, will be outside the audible band anyway. But this just didn’t cut it. So I tried upsampling. This involves adding zeros between samples, low pass filtering the signal, applying the distortion, anti-aliasing low pass 
filtering, and then downsampling back to 96k. The most I could get out of thestm32 was 5 times upsampling. This created a temporary sampling rate of 480k. Now this was able to give me the amount of bandwidth needed, to immensely improve the performance 
of the pedal. The before and after was night and day. The drawback, though, was the sheer amount of processing power needed to improve this. I was hoping to get 8 times upsampling, but I was using about 95% of the cpu for 5 times. However, I was quite 
satisfied with the results regardless, but I wanted to optimize the code to get better performance. 

That's when I stumbled onto a paper from 2016 on a technique called anti derivative anti-aliasing. This technique basically involved applying the integral of the nonlinear function rather than the actual nonlinearity. Now, I’m not going to act like I 
understand how it works, the math goes a bit over my head, But I was able to apply it and it worked like magic. It slashed my cpu load, while even performing a bit better. But there was one thing that was wrong. There is an error with my code, but the 
paper didn’t actually give any code so I’m not sure where I went wrong. This causes the nonlinearity to be applied asymmetrically to both cycles of the input. But the crazy part is this is actually a good thing! Since it is asymmetrical, we actually get 
harmonics at even and odd multiples of the base frequency. This is desirable since this mimics the performance of vintage vacuum tubes, which some guitar amps are based on. Guitarists tend to like this sound since it’s similar to their favorite bands 
from when vintage was modern.

## My pedal In Detail

I wanted to take a moment before showing the schematic and waveforms to talk about the features of this pedal. This pedal has a 3 way toggle switch to swap between 3 pedals I took inspiration from. The left position is the Ibanez TS-9 Tube Screamer. This 
is a soft clipping overdrive pedal. The second is the Electro-Harmonix Big Muff Pi. This is an example of Hard Clipping Distortion. The last was a challenge I set for myslelf. It is the Boss HM-2. This is a crazy pedal that chains a gain soft clipping 
stage, into another gain hard clipping stage. Finally it sends this signal into a wild filtering stage. The challenge with this pedal was creating a frequency response that mimics the original. My pedal features 3 knobs: gain, tone, and volume. Since 
this is digital, it's easy to change frequency response as well as the distortion. It has relay bypass to avoid quantization when not in use. This also has a bonus of allowing the pedal to act as a wire even when not plugged into power. I added voltage 
protection to the audio inputs by using the protection of the MCP6004 op amp. It features second order sallen-key input and output filters. I am sampling at 96k. This pedal is based around the Daisy Seed by Electrosmith. It is an audio DSP board 
featuring an STM32H750 as well as a 24 bit stereo codec (This pedal is mono). There is also an indicator LED when the effect is on. This leads me to the art on the pedal. The LED lights the campsire in the art. The art is not mine, it is promo art for 
the video game Outer Wilds. I initially wanted to label the knobs, but I still needed art. Once I saw this art and had the LED idea, I abandonded labels for looks. I justify this by arguing I am the only person who will use this so it's ok since I know. 


## My Pedal's Performance
Here is the Performance of the Overdrive effect of my pedal. Input is a 400mV p-p sine wave at 1KHz. 

## Schematic

## Conclusion / Final Thoughts
