// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(SomeClass *this)
{
  int *ptr;
  
  // Set vtable to this class's vtable (destructor step)
  this->vtable = (void *)&PTR_FUN_00e37b70;
  
  // If there is a sub-object at offset 0x28, destroy it
  if (this->field_0x28 != 0) {
    FUN_004ff430(); // sub-object destructor
  }
  
  // Call base class destructor
  FUN_004ebba0();
  
  // Switch vtable to base class vtable (after destruction)
  this->vtable = (void *)&PTR_FUN_00e37110;
  
  // Retrieve pointer at offset 0x10 (likely a list node or allocated block)
  ptr = (int *)this->field_0x10;
  if (ptr != 0) {
    // Remove from global free list at g_freeListPtr + 0x14
    int **listPtr = (int **)(DAT_01206880 + 0x14);
    // Write a sentinel vtable pointer to the current free list head
    **(void ***)listPtr = (void *)&PTR_LAB_01123be8;
    // Advance the free list pointer
    *listPtr = *listPtr + 4;
    // Store the pointer being freed
    **(int **)listPtr = ptr;
    // Advance again
    *listPtr = *listPtr + 4;
    
    // Clear the fields
    this->field_0x10 = 0;
    this->field_0x14 = 0;
  }
}