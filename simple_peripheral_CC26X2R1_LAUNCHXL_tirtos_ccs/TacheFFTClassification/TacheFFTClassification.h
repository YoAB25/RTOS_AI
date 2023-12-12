#ifndef TACHE_FFT_CLASSIFICATION_H_
#define TACHE_FFT_CLASSIFICATION_H_


void TacheFFTClassification_CreateTask(void);
static void TacheFFTClassification_taskFxn(UArg a0, UArg a1);
void FFTClassificationTrigger(float serie[]);

#endif /*TACHE_FFT_CLASSIFICATION_H_*/
