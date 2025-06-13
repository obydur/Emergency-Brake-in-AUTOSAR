#include <Rte_Emergency_Brake.h>

void Emergency_Brake_Emergency()
{
    float32 speed = Rte_IRead_Emergency_CurrentSpeed_Value(); // km/h
    float32 distance = Rte_IRead_Emergency_DistanLeading_Value(); // meters
    boolean ccState = Rte_IRead_Emergency_CurrentSpeed_Value();

    float32 speed_mps = speed / 3.6f;
    float32 d_brake = (speed_mps * speed_mps) / (2.0f * 14.0f); // deceleration = 14 m/s^2

    if (distance < d_brake + 5.0f) {
        Rte_IWrite_Emergency_CC_State_Value(1);
        Rte_IWrite_Emergency_CC_State_New_Value(0); // deactivate CC
    } else {
        Rte_IWrite_Emergency_CC_State_Value(0);
        Rte_IWrite_Emergency_CC_State_New_Value(ccState); // preserve state
    }
}