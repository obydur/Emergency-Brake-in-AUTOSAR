//Accident Recorder Software Component

//Runnable AccidentRecorder_CheckImpact.

// Input: Acceleration.

// Output: AccidentDetected, stored in NvM
// This software component checks for significant impacts based on acceleration data.
// It reads acceleration data, determines if an accident is detected based on a threshold,
// and writes the result to the RTE.
// AccidentRecorder.c

#include "Rte_AccidentRecorder.h"

void AccidentRecorder_CheckImpact(void)
{
    sint16 acceleration;
    boolean accidentDetected = FALSE;

    Rte_Read_AccidentRecorder_Acceleration(&acceleration);

    if (acceleration < -8000 || acceleration > 8000)  // Threshold in mg
    {
        accidentDetected = TRUE;
    }

    Rte_Write_AccidentRecorder_AccidentDetected(accidentDetected);

    if (accidentDetected)
    {
        // Example of storing in NVM, usually via NvM job call
        Rte_Call_AccidentRecorder_NvM_WriteAccidentData();
    }
}