// FUNC_NAME: SomeClass::updateTwoWayTrigger
void __fastcall SomeClass::updateTwoWayTrigger(int this)
{
  char cVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  // Get current state from two different trigger sources (e.g., two pressure plates or two zones)
  fVar3 = (float)FUN_008c51a0(1,this + 0x1c,0);  // Get trigger state from first source (offset +0x1C)
  fVar4 = (float)FUN_008c52f0(1,this + 0x28,0,0,0); // Get trigger state from second source (offset +0x28)
  
  // Compare the two trigger states
  cVar1 = FUN_008bd7c0(fVar3,fVar4);
  
  if (cVar1 == '\0') {
    // States are different - activate first trigger
    iVar2 = FUN_006bf050(this + 0x1c);  // Get trigger object from first source
    if (iVar2 != 0) {
      FUN_008c29f0(*(undefined4 *)(this + 0x10),iVar2);  // Activate trigger (offset +0x10 = some manager/owner)
    }
  }
  else {
    // States are same - activate second trigger
    iVar2 = FUN_006bf050(this + 0x28);  // Get trigger object from second source
    if (iVar2 != 0) {
      FUN_008c2ab0(*(undefined4 *)(this + 0x10),iVar2);  // Deactivate trigger (offset +0x10 = some manager/owner)
      return;
    }
  }
  return;
}