// FUNC_NAME: ObjectList::destroyAndClear
void __fastcall ObjectList::destroyAndClear(int *this)
{
  int *end;
  int *current;
  
  end = (int *)this[1];
  for (current = (int *)*this; current < end; current = current + 4) {
    if (*current != 0) {
      // Call the object's destructor function pointer at offset +0x0C
      (*(code *)current[3])(*current);
    }
  }
  if (*this != 0) {
    // Free the array memory
    FUN_009c8f10(*this);
  }
  return;
}