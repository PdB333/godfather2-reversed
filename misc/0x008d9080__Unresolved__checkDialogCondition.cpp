// FUNC_NAME: Unresolved::checkDialogCondition
undefined4 __thiscall checkDialogCondition(int this, int *param_2)
{
  char cVar1;
  undefined4 unaff_ESI;
  int unaff_EDI;
  undefined4 local_8;
  undefined4 local_4;
  
  // Cast engine global? likely a hash lookup context
  local_4 = _DAT_00d7db94;
  local_8 = 0;
  // Call virtual function at vtable offset 0x10 on param_2 (likely a hash table/string manager)
  // using hash 0x383225a1 to check existence or load something
  cVar1 = (**(code **)(*param_2 + 0x10))(0x383225a1,&local_8);
  if ((cVar1 != '\0') && (unaff_EDI != 0)) {
    // Get a value from unaff_EDI + 0x1f6c (field offset 0x1f6c from some structure)
    unaff_ESI = *(undefined4 *)(unaff_EDI + 0x1f6c);
  }
  // Check boolean at this+0x180 (likely a dialog active flag)
  // And bit 5 of field at this+0x25c (likely condition flags)
  if ((*(char *)(this + 0x180) != '\0') && ((*(uint *)(this + 0x25c) >> 5 & 1) != 0)) {
    // Call sub-function FUN_007f80e0 with this and unaff_ESI
    cVar1 = FUN_007f80e0(this,unaff_ESI);
    if ((cVar1 != '\0') && ((*(byte *)(this + 0x25c) & 3) == 0)) {
      return 1;
    }
  }
  return 0;
}