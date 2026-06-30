// FUNC_NAME: SomeClass::destructor
void SomeClass::destructor(void)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *this;
  
  // Set vtable pointer to first vtable (likely base class)
  *this = &PTR_LAB_00e42d64;
  
  // Check if a flag at offset +0x14 (this + 5 * 4) is non-zero
  if (*(char *)(this + 5) != '\0') {
    // Free allocated memory at offset +0x0C (this[3])
    (*(code *)PTR__free_00f0cd8c)(this[3]);
  }
  
  // Set vtable pointer to second vtable (likely derived class)
  *this = &PTR_LAB_00e42de4;
  
  // Iterate through a linked list starting at offset +0x04 (this[1])
  puVar2 = (undefined4 *)this[1];
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[2]; // Next node pointer at offset +0x08
    // Clear node data (first 12 bytes)
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2 = puVar1;
  }
  return;
}