// FUNC_NAME: someClassName::initFunction
void FUN_005bdc70(void)
{
  undefined4 uVar1;
  int in_EAX;
  int *piVar2;
  
  // Set field at offset +0x20 to 0
  *(undefined4 *)(in_EAX + 0x20) = 0;
  
  // Get global data pointer values
  uVar1 = DAT_011260b4;
  piVar2 = (int *)(DAT_01206880 + 0x14); // +0x14 is likely a pointer or offset within a global structure
  
  // Initialize a vtable-like structure
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0112611c; // Set vtable pointer
  *piVar2 = *piVar2 + 4; // Advance current pointer by 4 bytes
  
  // Set next slot to 0
  *(undefined4 *)*piVar2 = 0;
  *piVar2 = *piVar2 + 4;
  
  // Set next slot to stored value
  *(undefined4 *)*piVar2 = uVar1;
  *piVar2 = *piVar2 + 4;
  
  return;
}