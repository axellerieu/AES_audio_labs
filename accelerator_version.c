int main()
{

	init_platform();

	print("Started!\n\r");

	// Initialising the audio controller
	AudioInitialize(SCU_TIMER_ID, AUDIO_IIC_ID, AUDIO_CTRL_BASEADDR);

	// Initialising the AUDIO FIFO
	initialize_FIFO(AUDIO_FIFO);

	// Initialising the FIR FIFO
	initialize_FIFO(FIR_FIFO);


	// Initialising the samples for right and left sounds
	float SampleL, SampleR;

	// initialising the left and right buffers as float pointers
	float bufferL[FILTER_TAP_NUM], bufferR[FILTER_TAP_NUM];

	// iterator for the loop (to print after 300 samples)
	int j=0;
	// convolution variables for left and right channels
	float convolutionL = 0;
	float convolutionR = 0;
	// variables to store the time before and after the process
	int before;
	int after;
	// Flag to switch between the accelerator and the software implementation
	short int accelerator = 1;

	while (1){

		// reading the left and right samples from the audio FIFO
		SampleL = (float) I2SFifoRead(AUDIO_FIFO);
		SampleR = (float) I2SFifoRead(AUDIO_FIFO);


		//	Measure the number of clock cycles before the process 
		if(j==300){
			before = Xil_In32(GLOBAL_TMR_BASEADDR + GTIMER_COUNTER_LOWER_OFFSET);
		}

		// software implementation is used (refer to the other file)
		if (accelerator == 0) {
			for(int i=FILTER_TAP_NUM-1; i>0; i--){
				bufferL[i] = bufferL[i-1];
				bufferR[i] = bufferR[i-1];
			}

			bufferL[0] = SampleL;
			bufferR[0] = SampleR;

			convolutionL = convolution(bufferL);
			convolutionR = convolution(bufferR);
		}

		// accelerator implementation is used
		else if (accelerator == 1){
			// sending the left and right samples to the FIR FIFO
			// for the accelerator to process
			I2SFifoWrite(FIR_FIFO, SampleL);
			I2SFifoWrite(FIR_FIFO, SampleR);
			
			// retrieving the processed samples from the accelerator
			// only when there is enough data to filter
			if(j==FILTER_TAP_NUM){
				convolutionL = I2SFifoRead(FIR_FIFO);
				convolutionR = I2SFifoRead(FIR_FIFO);
			}

		}


		//	Measure the number of clock cycles after the process
		// Printing the difference = the number of clock cycles of the total process
		if (j==300){
			after = Xil_In32(GLOBAL_TMR_BASEADDR + GTIMER_COUNTER_LOWER_OFFSET);
			xil_printf("count process total time = %d \r\n", after - before);
		}

		j++;


		// sending the processed samples to the audio FIFO
		I2SFifoWrite(AUDIO_FIFO, (u32)convolutionL);
		I2SFifoWrite(AUDIO_FIFO, (u32)convolutionR);

	}

	cleanup_platform();
	return 0;
}