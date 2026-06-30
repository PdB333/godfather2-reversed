// FUNC_NAME: Array::removeAt
void __fastcall Array::removeAt(uint index, int *array)
{
  undefined4 *puVar1;
  
  if (index < array[1] - 1U) {
    do {
      puVar1 = (undefined4 *)(*array + index * 8);
      *puVar1 = *(undefined4 *)(*array + 8 + index * 8);
      puVar1[1] = puVar1[3];
      index = index + 1;
    } while (index < array[1] - 1U);
  }
  array[1] = array[1] + -1;
  return;
}