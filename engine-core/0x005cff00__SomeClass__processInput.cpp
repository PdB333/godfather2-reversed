// FUNC_NAME: SomeClass::processInput
undefined1 __thiscall SomeClass::processInput(undefined4 param_1, undefined4 param_2, int param_3, int *param_4, int *param_5)
{
  char cVar1;
  undefined1 uVar2;
  undefined4 *in_EAX;
  undefined1 local_fc [72]; // buffer for input data
  float local_b4;            // +0x0: some float value
  float local_b0;            // +0x4: another float value
  int *local_94 [37];        // array of pointers
  
  // Try to get input data from some source
  cVar1 = FUN_005a03a0(param_1, local_fc);
  if (cVar1 == '\0') {
    return 0; // no input available
  }
  
  // If param_3 is zero, just store the raw float values
  if (param_3 == 0) {
    *param_5 = (int)local_b0;
    *param_4 = (int)local_b4;
    *in_EAX = 0;
    return 1;
  }
  
  // Otherwise process the input through some pipeline
  FUN_005d04e0(); // initialize processing
  FUN_005d0580(local_94, local_fc); // parse input buffer into array
  uVar2 = FUN_005d00a0(param_2, param_4, param_5, in_EAX); // process and get results
  
  // Clean up if array was allocated
  if (local_94[0] != (int *)0x0) {
    (**(code **)(*local_94[0] + 4))(); // virtual destructor call
  }
  
  return uVar2;
}