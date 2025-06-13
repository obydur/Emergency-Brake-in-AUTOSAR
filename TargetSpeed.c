#include <Rte_TargetSpeedControl.h>
#include <Sab.h>
#include <Sab_Types.h>

static float32 targetSpeed = 10.0;
static uint8 prevBtnState = 0;  // Variable to track the previous state of the button

void TargetSpeedControl_Target(void)
{
    uint8 btn = Rte_IRead_Target_ButtonState_Value();

    // Check if the button is pressed and was previously not pressed (button press event)
    if (btn == 1 && prevBtnState == 0 && targetSpeed <= 125.0f) {
        targetSpeed += 5.0f;
        Sab_SubmitInfo("TargetSpeed = %.1f", targetSpeed);
    } 
    // Check if the button is pressed and was previously not pressed (button press event)
    else if (btn == 2 && prevBtnState == 0 && targetSpeed >= 15.0f) {
        targetSpeed -= 5.0f;
    }

    // Update the previous button state for the next cycle
    prevBtnState = btn;

    Rte_IWrite_Target_TargetSpeed_Value(targetSpeed);
}