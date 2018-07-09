#filter-demo

Especially for smallband reception, as in e.g. shortwave reception
one needs decent filters. In the swradio-8 software, the supported devices
only support wide band reception (i.e. 2M or more).
For e.g cw reception, or psk reception, one needs a bandwidth of up to 100 Hz,
so we need decimation and filtering.

Even for DAB, one sometimes does need filtering. The AIRspy, a popular
device, only provides output with fixed rates. The AIRspy mini e.g.
sends out its data with a rate of 3M, since the channels have a width
of 1536K, there is an issue with DX-ing on adjacent channels.

For sw reception, we map from 2112KHz to 96Khz (integer division),
and then to 12 Khz. The actual decoder is free to extract a subband
by further filtering.

To prevent phase issues, filtering is done by Finite Impulse Response
filtering.

Just as an example, filters are shown, based on different windowing
approaches, all with the same setting.

![filter-demo ](/filter-demo-1.png?raw=true)
![filter-demo ](/filter-demo-2.png?raw=true)
![filter-demo ](/filter-demo-3.png?raw=true)
![filter-demo ](/filter-demo-4.png?raw=true)


The parameters to be set are
* the filter depth (we use two filters with a degree of 255, implemented \
through using an FFT technique)
* the signal width, in the range 0 .. 0.5. As an example, if you filter \
a signal with a samplerate of 96000, a band of 9600 equates to a setting
of 0.1.


