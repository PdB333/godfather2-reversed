// FUNC_NAME: ArrayContainer::destroyAll
void __fastcall ArrayContainer::destroyAll(int *this)
{
  int count;
  int idx;
  int *entry;
  int primaryObj;
  int secondaryObj;
  void (*primaryDtor)(int);
  void (*secondaryDtor)(int);

  // struct layout:
  // this+0x00: array pointer (base of entries)
  // this+0x04: number of entries
  // this+0x08: capacity or unused (zeroed at end)
  // each entry is 0x20 bytes:
  //   +0x00: primary object pointer
  //   +0x0C: primary destructor (vtable slot or function pointer)
  //   +0x10: secondary object pointer
  //   +0x1C: secondary destructor

  count = this[1] - 1;
  if (count >= 0) {
    do {
      idx = count * 0x20;
      secondaryObj = *(int *)(this[0] + 0x10 + idx);
      entry = (int *)(this[0] + idx);
      if (secondaryObj != 0) {
        // call secondary destructor via vtable at offset 0x1C
        secondaryDtor = (void (*)(int))entry[7];  // entry[7] is at +0x1C
        secondaryDtor(secondaryObj);
      }
      primaryObj = *entry;
      if (primaryObj != 0) {
        // call primary destructor via vtable at offset 0x0C
        primaryDtor = (void (*)(int))entry[3];  // entry[3] is at +0x0C
        primaryDtor(primaryObj);
      }
      count = count - 1;
    } while (count >= 0);
  }
  this[1] = 0;                      // reset count
  FUN_009c8f10(this[0]);            // deallocate array memory (likely operator delete[])
  this[0] = 0;                      // nullify array pointer
  this[2] = 0;                      // clear capacity or other field
}