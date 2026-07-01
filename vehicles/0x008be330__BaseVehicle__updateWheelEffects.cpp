// FUNC_NAME: BaseVehicle::updateWheelEffects
void __thiscall BaseVehicle::updateWheelEffects(undefined4 param_1,int *param_2)

{
  int wheelIndex;
  int wheelDataPtr;
  
  wheelIndex = param_2[1];
  while (wheelIndex = wheelIndex + -1, -1 < wheelIndex) {
    wheelDataPtr = *(int *)(*param_2 + wheelIndex * 4);
    if (*(int *)(wheelDataPtr + 0x174) != 0) {  // +0x174: wheelGroundContact flag
      FUN_006b30a0();  // PlayWheelGroundEffect
    }
    if (*(int *)(wheelDataPtr + 0xfc) != 0) {  // +0xFC: wheelSlip flag
      FUN_006b1990();  // PlayWheelSlipEffect
    }
    FUN_006b5ff0(param_1);  // UpdateWheelForces
  }
  return;
}