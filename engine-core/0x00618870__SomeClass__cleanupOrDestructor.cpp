// FUNC_NAME: SomeClass::cleanupOrDestructor
void SomeClass::cleanupOrDestructor(void)
{
  int *piVar1;
  // unaff_ESI is the 'this' pointer (__thiscall)
  
  // +0x1c: pointer to some resource (maybe a stream or buffer)
  if (*(int *)(this + 0x1c) != 0) {
    // Call FUN_006065a0 to release/free that resource with a flag 0
    FUN_006065a0(*(int *)(this + 0x1c), 0);
    *(int *)(this + 0x1c) = 0; // null out the pointer
  }
  
  // +0x14: pointer to an object with a vtable (likely a base class or interface)
  piVar1 = *(int **)(this + 0x14);
  if (piVar1 != (int *)0x0) {
    // Call virtual destructor or release method at vtable+8
    (**(code **)(*piVar1 + 8))(piVar1);
    *(int *)(this + 0x14) = 0;
  }
  
  // +0x18: another similar pointer
  piVar1 = *(int **)(this + 0x18);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(int *)(this + 0x18) = 0;
  }
  
  return;
}