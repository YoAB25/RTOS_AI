#ifndef TACHEADC_H_                     // C Include guards
#define TACHEADC_H_


void TacheADC_CreateTask(void);

void TacheADC_taskFxn(UArg a0, UArg a1);

void myClockSwiFxn(uintptr_t arg0);

uint32_t Sampling(uint_least8_t Board_ADC_Number);

float uVToG_float(uint32_t dataSampled);


#endif     /* TACHEADC_H_ */
