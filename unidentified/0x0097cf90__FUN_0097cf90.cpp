// FUNC_NAME: SomeContainer::removeItemAtIndex
void __fastcall SomeContainer::removeItemAtIndex(int this)
{
  int count;
  int i;
  uint j;
  undefined4 *ptr;
  
  count = *(int *)(this + 0x78);
  if (count != 0) {
    ptr = (undefined4 *)(this + 0x54 + count * 4);
    i = count;
    do {
      i = i + -1;
      *(int *)(this + 0x78) = *(int *)(this + 0x78) + -1;
      if (i != *(int *)(this + 0x78)) {
        *ptr = *(undefined4 *)(this + 0x58 + *(int *)(this + 0x78) * 4);
      }
      if (*(int *)(this + 0x9c) + *(int *)(this + 0x78) + *(int *)(this + 0x54) +
          *(int *)(this + 0x30) == 0) {
        j = 0;
        *(undefined4 *)(this + 0xa0) = 0;
        if (*(int *)(this + 0xdc) != 0) {
          do {
            (**(code **)(**(int **)(*(int *)(this + 0xd8) + j * 4) + 4))();
            j = j + 1;
          } while (j < *(uint *)(this + 0xdc));
        }
      }
      ptr = ptr + -1;
      i = i + -1;
    } while (i != 0);
  }
  return;
}