// FUNC_NAME: EventDispatcher::~EventDispatcher
void __fastcall EventDispatcher::~EventDispatcher(undefined4 *this)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  *this = &PTR_FUN_00d735c8;
  if (this[2] != 0) {
    do {
      piVar1 = (int *)(this[1] + uVar4 * 8);
      // Check if listener slot is empty (second dword == 0) AND
      // the target pointer either null or points back to this slot (i.e., the listener was not properly cleaned up)
      if ((*(int *)(this[1] + 4 + uVar4 * 8) == 0) &&
         (((puVar2 = (undefined4 *)*piVar1, puVar2 == (undefined4 *)0x0 ||
           ((int *)puVar2[1] == piVar1)) && (puVar2 != (undefined4 *)0x0)))) {
        // Call destructor on the listener object (vtable at puVar2)
        (**(code **)*puVar2)(1);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)this[2]);
  }
  // If user data is set, call its destructor function
  if (this[5] != 0) {
    (*(code *)this[8])(this[5]);
  }
  // Clean up listener array elements
  iVar3 = this[2];
  while (iVar3 = iVar3 + -1, -1 < iVar3) {
    if (*(int *)(this[1] + iVar3 * 8) != 0) {
      FUN_004daf90(this[1] + iVar3 * 8);
    }
  }
  // Free listener array
  if (this[1] != 0) {
    FUN_009c8f10(this[1]);
  }
  return;
}