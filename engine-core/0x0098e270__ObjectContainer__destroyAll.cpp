// FUNC_NAME: ObjectContainer::destroyAll
void __fastcall ObjectContainer::destroyAll(int *this)
{
  int count = this[1] - 1; // number of slots minus 1 for loop index
  if (count >= 0)
  {
    int offset = count * 0x4c; // each slot is 0x4c bytes
    do
    {
      // Slot structure layout (offsets relative to slot base):
      // +0x00: pointer to object A (calls vtable+0x0c)
      // +0x10: pointer to object B (calls vtable+0x1c)
      // +0x20: pointer to object C (calls vtable+0x2c)
      // +0x30: pointer to object D (calls vtable+0x3c)
      int *slotBase = (int *)(this[0] + offset);
      int objectD = *(int *)(this[0] + 0x30 + offset); // object at slot+0x30
      if (objectD != 0)
      {
        (*(void (**)(int))slotBase[0xf])(objectD); // call destructor at vtable offset 0x3c
      }
      if (slotBase[8] != 0) // slot+0x20
      {
        (*(void (**)(int))slotBase[0xb])(slotBase[8]); // call destructor at vtable offset 0x2c
      }
      if (slotBase[4] != 0) // slot+0x10
      {
        (*(void (**)(int))slotBase[7])(slotBase[4]); // call destructor at vtable offset 0x1c
      }
      if (slotBase[0] != 0) // slot+0x00
      {
        (*(void (**)(int))slotBase[3])(slotBase[0]); // call destructor at vtable offset 0x0c
      }
      count--;
      offset -= 0x4c;
    } while (count >= 0);
  }
  if (this[0] != 0)
  {
    deallocateMemory(this[0]); // free the slot array
  }
}