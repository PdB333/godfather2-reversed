// FUNC_NAME: someContainer::clear
void __fastcall someContainer::clear(int this)
{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(this + 0x28); // +0x28: pointer to array start
  if (puVar1 != puVar1 + *(int *)(this + 0x2c)) { // +0x2c: element count
    do {
      FUN_009c8eb0(*puVar1); // release each element
      puVar1 = puVar1 + 1;
    } while (puVar1 != (undefined4 *)(*(int *)(this + 0x28) + *(int *)(this + 0x2c) * 4));
  }
  *(undefined4 *)(this + 0x2c) = 0; // reset count to 0
  FUN_009c8f10(*(undefined4 *)(this + 0x28)); // free the array memory
  *(undefined4 *)(this + 0x28) = 0; // clear pointer
  *(undefined4 *)(this + 0x30) = 0; // +0x30: reset capacity
  *(undefined4 *)(this + 0x34) = 0xffffffff; // +0x34: set to -1 (invalid index or sentinel)
  return;
}