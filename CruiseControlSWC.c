#include <Rte_CruiseControlSWC.h>
#include <Sab.h>
#include <Sab_Types.h>

void CruiseControlSWC_CruiseControl(void)
{
    // Get current speed and target speed
    float32 currentSpeed = Rte_IRead_CruiseControl_CurrentSpeed_Value();
    float32 targetSpeed = Rte_IRead_CruiseControl_TargetSpeed_Value();  // Target speed set to 50 km/h
    boolean ccState = Rte_IRead_CruiseControl_CC_State_Value();  // Read Cruise Control state
    boolean AcceleratorPedal = Rte_IRead_CruiseControl_AcceleratorPedal_Value();
    boolean brake = Rte_IRead_CruiseControl_BreakNew_Value();
    
     if (ccState) {
        if (AcceleratorPedal) {
            Rte_IWrite_CruiseControl_Accelerate_Value(1);
            Rte_IWrite_CruiseControl_BrakePedal_Value(0);
        } else if(brake){
            ccState = 0;
        }
        else {
    if (currentSpeed < targetSpeed - 1.0f) {
        Rte_IWrite_CruiseControl_Accelerate_Value(1);
        Rte_IWrite_CruiseControl_BrakePedal_Value(0);
    } else if (currentSpeed > targetSpeed + 1.0f) {
        Rte_IWrite_CruiseControl_Accelerate_Value(0);
        Rte_IWrite_CruiseControl_BrakePedal_Value(1);
    } else {
        Rte_IWrite_CruiseControl_Accelerate_Value(1);
        Rte_IWrite_CruiseControl_BrakePedal_Value(0);
    }
}} else {
        Rte_IWrite_CruiseControl_Accelerate_Value(AcceleratorPedal);
        Rte_IWrite_CruiseControl_BrakePedal_Value(brake);
    }
    
     Rte_IWrite_CruiseControl_CC_State_New_Value(ccState);
}
   