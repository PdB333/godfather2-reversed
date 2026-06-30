// FUNC_NAME: SomeNetworkClass::dispatchPacketOrCallback
void __thiscall SomeNetworkClass::dispatchPacketOrCallback
(int thisPtr,undefined4 param_2,undefined4 param_3,int *param_4,int *param_5)

{
  // +0x18 seems to be a virtual method at vtable offset 0x18 (probably a 'process' or 'send' method)
  param_4[6] = thisPtr;
  if (param_5 != (int *)0x0) {
    // Call the method on param_5's vtable, passing param_2, param_3, and param_4
    (**(code **)(*param_5 + 0x18))(param_2,param_3,param_4);
    if ((char)param_3 != '\0') {
      // Set flag bit 2 (0x4) on param_5 if param_3 is truthy
      param_5[5] = param_5[5] | 4;
    }
    return;
  }
  // No param_5, check if thisPtr+4 already has a stored callback/packet
  if (*(int *)(thisPtr + 4) != 0) {
    // Call the method on param_4's vtable, passing param_2, param_3, and the stored callback
    (**(code **)(*param_4 + 0x18))(param_2,param_3,*(int *)(thisPtr + 4));
    // Store new callback/packet to thisPtr+4
    *(int **)(thisPtr + 4) = param_4;
    return;
  }
  // No stored callback, store directly
  *(int **)(thisPtr + 4) = param_4;
  // Call another function (likely a queuing or dispatch routine)
  FUN_00624820(param_2,param_3);
  return;
}