// FUNC_NAME: SomeClass::processSomeAction
undefined1 FUN_008c4790(int thisPtr)

{
  undefined4 uVar1;
  undefined1 result;
  uint index;
  float10 fVar4;
  int *piVar5;
  int local_1c;
  uint local_18;
  undefined4 local_14;
  int local_10 [3];
  code *local_4;
  
  result = 0;
  index = 0;
  if (*(int *)(thisPtr + 0xfc) != 0) { // +0xFC: some flag/pointer
    piVar5 = &local_1c;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    fVar4 = (float10)FUN_006be800(piVar5); // Get some float value
    FUN_008c4720((float)fVar4,piVar5); // Process the float
    if (local_18 == 0) {
      result = 0;
    }
    else {
      FUN_008c2d00(&local_1c,2,*(undefined4 *)(thisPtr + 0x38)); // +0x38: some parameter
      if (local_18 != 0) {
        do {
          uVar1 = *(undefined4 *)(local_1c + index * 4);
          FUN_006b4730(uVar1,0); // Some operation on element
          FUN_006bf5b0(uVar1); // Another operation
          index = index + 1;
        } while (index < local_18);
      }
      FUN_004d4a60(local_10,1,"{#%u}",0xc55a21ad); // Format string
      FUN_008c0f50(local_10,thisPtr,0); // Some callback
      if (local_10[0] != 0) {
        (*local_4)(local_10[0]); // Call function pointer
      }
      result = 1;
    }
    if (local_1c != 0) {
      FUN_009c8f10(local_1c); // Free memory
    }
  }
  return result;
}