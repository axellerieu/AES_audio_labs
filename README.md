# AES_audio_labs
Repository to share my audio filtering implementations.

## Description of the project

There are three files included in this repository. 

One of them, *measures.md*, references the number of CPU cycles of a Zybo z7 ARM processor when running an audio filtering application under different optimization conditions.

The other two ones are different versions of the main function of the application. 

The software version uses a for loop to update the buffers and then applies the filter to them (convolution with filtering coefficients).

The accelerator version on the other hand uses a Finite Impulse Response (FIR) to improve and fasten the filtering process. The FIR was included in the in the SDK application project with the right coefficients for the filter.



The two implementations are part of a bigger project including the architecture of the system, libraries,...
It was part of an SDK project meant to be deployed on an fpga.

