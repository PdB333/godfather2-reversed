// FUNC_NAME: SomeClass::clearMembers
uint32 SomeClass::clearMembers(void)
{
  if (this == (SomeClass *)0x0) {
    return 0;
  }
  // +0x04: some pointer, +0x14-0x17: flag byte at +0x14 (offset 5 words)
  if ((this->somePointer != (void *)0x0) && ((this->flags & 1) != 0) && 
      (*(int *)(DAT_01223518 + 4) != 0)) {
    // vtable call at offset 4 on the object pointed to by DAT_01223518+4
    (**(code **)(**(int **)(DAT_01223518 + 4) + 4))(this->somePointer, 0);
  }
  // +0x04: somePointer
  this->somePointer = (void *)0x0;
  // +0x08: someInt1
  this->someInt1 = 0;
  // +0x0c: someInt2
  this->someInt2 = 0;
  // +0x10: someInt3
  this->someInt3 = 0;
  // +0x00: someInt0 (base)
  this->someInt0 = 0;
  // +0x14: flags
  this->flags = 0;
  return 1;
}