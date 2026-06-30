// FUNC_NAME: SomeEARSObject::destructor
void __thiscall SomeEARSObject_destructor(undefined4 *this)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  *this = &PTR_FUN_00e39f10; // vtable setup
  if (this[6] != 0) {
    FUN_009e7530(this[6]); // release/delete something (audio?)
  }
  this[6] = 0;
  
  // Handle member at offset +0x1C (this[7])
  if (this[7] != 0) {
    puVar1 = *(undefined4 **)(this[7] + 0x10); // get ref count from some structure
    if ((*(short *)(puVar1 + 1) != 0) && // check reference count
       (*(short *)((int)puVar1 + 6) = *(short *)((int)puVar1 + 6) + -1,
       *(short *)((int)puVar1 + 6) == 0)) {
      (**(code **)*puVar1)(1); // delete self if ref count hits 0
    }
    FUN_009f01a0(); // release some resource
  }
  
  // Handle member at offset +0x20 (this[8]) similar to above
  if (this[8] != 0) {
    puVar1 = *(undefined4 **)(this[8] + 0x10);
    if ((*(short *)(puVar1 + 1) != 0) &&
       (*(short *)((int)puVar1 + 6) = *(short *)((int)puVar1 + 6) + -1,
       *(short *)((int)puVar1 + 6) == 0)) {
      (**(code **)*puVar1)(1);
    }
    FUN_009f01a0();
  }
  
  // Handle member at offset +0x14 (this[5])
  if ((undefined4 *)this[5] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[5])(1); // virtual delete
  }
  
  // Handle linked list at offset +0xD8 (this[0x36])
  iVar2 = this[0x36];
  if (iVar2 != 0) {
    puVar1 = *(undefined4 **)(iVar2 + 4);
    if (puVar1 == this + 0x36) {
      *(undefined4 *)(iVar2 + 4) = this[0x37];
      this[0x2f] = &PTR_LAB_00e39ea4; // set vtable to singleton base
      return;
    }
    puVar3 = (undefined4 *)puVar1[1];
    while (puVar3 != this + 0x36) {
      puVar1 = (undefined4 *)puVar1[1];
      puVar3 = (undefined4 *)puVar1[1];
    }
    puVar1[1] = this[0x37];
  }
  this[0x2f] = &PTR_LAB_00e39ea4; // set vtable to singleton base
  return;
}