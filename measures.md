- 99 taps timing without sliding window :
  	- float buffers, -O0 : 2439 → 4878 CPU cycles < sample frequency
	- float buffers, -O2 : 520 → 1040 CPU cycles < sample frequency
	- float buffers, -O2, autoVectorization : 502 → 1004 CPU cycles < sample frequency
	- float buffers, -O2, autoVectorization, intrinsics : 276 → 552 CPU cycles < sample frequency

- 99 taps timing including sliding window :
	- int buffers, -O0 : 9789 → 19578 CPU cycles > sample frequency
	- float buffers, -O0 : 8526 → 16512 CPU cycles > sample frequency
	- float buffers, -O2 : 5100 → 10200 CPU cycles < sample frequency
	- float buffers, -O2, autoVectorization : 2036 → 4072 CPU cycles < sample frequency
	- float buffers, -O2, autoVectorization, intrinsics : 512 → 1024 CPU cycles < sample frequency

- 99 taps timing with accelerator  :
    	- accelerator, -O2 : 3479 → 6958 CPU cycles < sample frequency