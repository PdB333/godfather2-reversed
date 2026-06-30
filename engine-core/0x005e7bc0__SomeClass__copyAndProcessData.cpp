// FUNC_NAME: SomeClass::copyAndProcessData
void SomeClass::copyAndProcessData(void)
{
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = *in_EAX;          // Copy first dword from source (this +0x0)
  local_1c = in_EAX[1];        // Copy second dword from source (this +0x4)
  local_18 = in_EAX[2];        // Copy third dword from source (this +0x8)
  local_14 = DAT_00e2b1a4;     // Load global constant (likely a static or singleton pointer)
  FUN_005e7440(&local_20);     // Process the copied data
  return;
}