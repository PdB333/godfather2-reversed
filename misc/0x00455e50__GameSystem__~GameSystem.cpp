// FUNC_NAME: GameSystem::~GameSystem

void __fastcall GameSystem::~GameSystem(undefined4* this)
{
  int* piVar1;
  
  piVar1 = DAT_01223510;  // global singleton pointer to some system
  *this = &PTR_FUN_00e319f0; // set vtable to base class
  this[3] = &PTR_LAB_00e31a00; // set another interface vtable
  this[5] = &PTR_LAB_00e31a0c; // set yet another interface vtable
  (**(code **)(*piVar1 + 0x18))(0); // call virtual function at +0x18 on global object
  this[0xe] = 0; // +0x38 - some pointer cleared
  FUN_009c8f10(this[0xd]); // +0x34 - free memory
  this[0xd] = 0; // null pointer
  this[0xf] = 0; // +0x3c - cleared
  this[0x11] = 0; // +0x44 - cleared
  FUN_009c8f10(this[0x10]); // +0x40 - free memory
  this[0x10] = 0; // null pointer
  this[0x12] = 0; // +0x48 - cleared
  if ((int *)this[6] != (int *)0x0) { // +0x18 - check if pointer not null
    (**(code **)(*(int *)this[6] + 0xc))(); // call virtual function at +0xc on that object
  }
  if (this[0x10] != 0) {
    FUN_009c8f10(this[0x10]); // free memory again (sanity)
  }
  if (this[0xd] != 0) {
    FUN_009c8f10(this[0xd]);
  }
  if (this[10] != 0) { // +0x28 - free memory
    FUN_009c8f10(this[10]);
  }
  if (this[7] != 0) { // +0x1c - free memory
    FUN_009c8f10(this[7]);
  }
  this[5] = &PTR_LAB_00e31a10; // set vtable to derived class final vtable
  DAT_012233f8 = 0; // clear global pointer to this class instance
  FUN_0049c640(); // shutdown subsystem
  FUN_004083d0(); // final cleanup
  return;
}