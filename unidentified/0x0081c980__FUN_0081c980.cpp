// FUNC_NAME: SomeContainer::clearAndDestroy
void __fastcall SomeContainer::clearAndDestroy(undefined4 *this)
{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  piVar1 = (int *)this[6]; // +0x18: pointer to list head
  piVar4 = (int *)*piVar1; // first element
  *piVar1 = (int)piVar1;   // make list circular (point to self)
  *(undefined4 *)(this[6] + 4) = this[6]; // +0x1C: tail = head
  this[7] = 0; // +0x1C: count = 0
  if (piVar4 != (int *)this[6]) {
    do {
      piVar1 = (int *)*piVar4; // save next pointer
      if (piVar4[4] != 0) { // +0x10: some resource pointer
        FUN_004daf90(piVar4 + 4); // release resource
      }
      piVar4[2] = (int)&PTR_FUN_00e32808; // +0x08: set vtable to destructor
      puVar3 = (undefined4 *)piVar4[3]; // +0x0C: child list head
      while (puVar3 != (undefined4 *)0x0) {
        puVar2 = (undefined4 *)puVar3[1]; // +0x04: next sibling
        puVar3[1] = 0;
        *puVar3 = 0;
        puVar3 = puVar2;
      }
      (**(code **)(*(int *)*this + 4))(piVar4,0x2c); // call vtable[1] (destructor with size)
      piVar4 = piVar1;
    } while (piVar1 != (int *)this[6]);
  }
  return;
}