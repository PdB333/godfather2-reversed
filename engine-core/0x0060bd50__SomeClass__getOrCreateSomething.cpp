// FUNC_NAME: SomeClass::getOrCreateSomething
int * __fastcall SomeClass::getOrCreateSomething(undefined4 *this)
{
  undefined4 uVar1;
  int *piVar2;
  undefined4 local_4;
  
  // Check if some flag at offset +0x1C (this+7*4) is set
  if (*(char *)(this + 7) != '\0') {
    uVar1 = 0;
    local_4 = 0;
    // Check another flag at offset +0x0C (this+3*4)
    if (*(char *)(this + 3) != '\0') {
      uVar1 = 0x3000; // Some flag value
    }
    piVar2 = (int *)*this; // Dereference first member (likely a pointer)
    // Call virtual function at vtable+0x2C (some initialization/creation method)
    (**(code **)(*piVar2 + 0x2c))(piVar2,0,0,&local_4,uVar1);
    return piVar2;
  }
  // If flag not set, set byte at offset +0x1D to 1
  *(undefined1 *)((int)this + 0x1d) = 1;
  // Return the value at offset +0x10 (this[4])
  return (int *)this[4];
}