// FUNC_NAME: Container::clearElements
void __fastcall Container::clearElements(int *this)
{
  int count = this[1];                // +4: number of elements
  int *array = (int *)this[0];        // +0: pointer to array of 8-byte elements

  // Iterate backwards over the array
  while (count > 0)
  {
    count--;
    // Each element is an 8-byte structure; first field is a pointer
    if (array[count * 2] != 0)       // array[count*2] is the pointer at offset 0 of struct
    {
      FUN_004daf90(&array[count * 2]); // release the structure (likely delete object pointed to)
    }
  }

  // Free the array itself
  if (array != 0)
  {
    FUN_009c8f10(array);
  }

  return;
}