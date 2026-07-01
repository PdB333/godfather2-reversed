// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(undefined4 *this)
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  *this = &PTR_FUN_00d922e0; // vtable pointer
  this[4] = &PTR_LAB_00d922cc; // some other vtable or data pointer
  FUN_00408310(&DAT_0113096c); // likely decrement reference count or unregister
  if (this[0x24] != 0) { // +0x90 - some pointer member
    FUN_009c8f10(this[0x24]); // free/release
    this[0x24] = 0;
  }
  iVar1 = this[0x1e]; // +0x78 - array/container pointer
  if (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + -0x10); // element count stored at offset -0x10
    while (iVar2 = iVar2 + -1, -1 < iVar2) {
      FUN_00556860(); // release each element
    }
    FUN_009c8f10(iVar1 + -0x10); // free container header
  }
  if (this[8] != 0) { // +0x20
    FUN_00997d90(this[7]); // +0x1c - release associated resource
  }
  puVar3 = (undefined4 *)this[9]; // +0x24
  if (puVar3 != (undefined4 *)0x0) {
    if ((*(short *)(puVar3 + 1) != 0) && // ref count check
       (*(short *)((int)puVar3 + 6) = *(short *)((int)puVar3 + 6) + -1,
       *(short *)((int)puVar3 + 6) == 0)) {
      (**(code **)*puVar3)(1); // release if ref count reaches 0
    }
    this[9] = 0;
  }
  FUN_00997280(); // cleanup
  if ((int *)this[0x27] != (int *)0x0) { // +0x9c
    (**(code **)(*(int *)this[0x27] + 0x10))(1); // release
  }
  puVar3 = (undefined4 *)this[0x26]; // +0x98
  if ((*(short *)(puVar3 + 1) != 0) && // ref count
     (*(short *)((int)puVar3 + 6) = *(short *)((int)puVar3 + 6) + -1,
     *(short *)((int)puVar3 + 6) == 0)) {
    (**(code **)*puVar3)(1); // release
  }
  iVar1 = this[0x12]; // +0x48 - some index
  if (-1 < iVar1) {
    TlsGetValue(DAT_01139810); // get thread-local storage
    FUN_00aa26e0(this[0x10], iVar1 << 4, 0x17); // free memory block
  }
  uVar4 = this[0xf]; // +0x3c
  if (-1 < (int)uVar4) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(this[0xd], (uVar4 & 0x3fffffff) * 0xc0, 0x17); // free memory block
  }
  iVar1 = this[0xc]; // +0x30
  if (-1 < iVar1) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(this[10], iVar1 << 6, 0x17); // free memory block
  }
  *this = &PTR_FUN_00d587e0; // final vtable
  FUN_004083d0(); // final cleanup
  return;
}