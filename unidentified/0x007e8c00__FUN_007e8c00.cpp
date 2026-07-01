// FUNC_NAME: SomeClass::checkAndTriggerRandomEvent
char __thiscall checkAndTriggerRandomEvent(int this, int param_2, undefined4 param_3, undefined4 param_4)
{
  int iVar1;
  char cVar2;
  uint uVar3;
  
  cVar2 = '\0';
  // Check if current random event count is below max (DAT_01205224) and param_2 is valid
  if ((((*(uint *)(this + 0x764) < DAT_01205224) && (param_2 != 0)) &&
      // Check param_2's type or state at offset +0x1ed8
      ((iVar1 = *(int *)(param_2 + 0x1ed8), iVar1 == 0 ||
       // If type is 0x48 or certain flag bit is not set
       ((iVar1 == 0x48 || ((~(byte)((uint)*(undefined4 *)(iVar1 + 0x3c) >> 8) & 1) != 0)))))) &&
     // Call validation function
     (cVar2 = FUN_007e8700(param_2, param_3, param_4), cVar2 != '\0')) {
    // Generate random delay for next event
    uVar3 = _rand();
    *(uint *)(this + 0x764) =
         uVar3 % (uint)(*(int *)(this + 0x760) - *(int *)(this + 0x75c)) +
         *(int *)(this + 0x75c) + DAT_01205224;
  }
  return cVar2;
}