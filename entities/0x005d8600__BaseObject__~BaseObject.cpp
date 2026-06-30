// FUNC_NAME: BaseObject::~BaseObject
void __fastcall BaseObject::~BaseObject(undefined4 *this)
{
  int field_0x10; // +0x10
  int field_0x0C; // +0x0C
  int field_0x14; // +0x14
  int **ppPoolPtr; // pointer to memory pool insertion pointer
  int *pPoolPtr;

  // Set vtable to base class vtable (prevent virtual calls during destruction)
  *this = (undefined4 *)&PTR_FUN_00e3edfc;

  field_0x10 = this[4];
  if (field_0x10 != 0) {
    // Free the allocation at +0x10 (tagged with PTR_LAB_01126ed8)
    ppPoolPtr = (int **)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = (undefined4 *)&PTR_LAB_01126ed8;
    pPoolPtr = (int *)*ppPoolPtr;
    *pPoolPtr = *pPoolPtr + 4;           // Advance pool pointer by 4 bytes
    *(int *)*pPoolPtr = field_0x10;
    *ppPoolPtr = (int *)(*ppPoolPtr + 1); // Actually increment the stored pointer by 4 (but cast to int*)
    // The above lines write the tag and the pointer to the memory pool's free list.
  }

  field_0x0C = this[3];
  if (field_0x0C != 0) {
    field_0x14 = this[5];
    // Free the allocation at +0x0C (tagged with PTR_LAB_01126ec4)
    ppPoolPtr = (int **)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = (undefined4 *)&PTR_LAB_01126ec4;
    pPoolPtr = (int *)*ppPoolPtr;
    *pPoolPtr = *pPoolPtr + 4;
    *(undefined4 *)*pPoolPtr = field_0x14;
    *ppPoolPtr = (int *)(*ppPoolPtr + 1);

    // Finally delete the object pointed to by +0x0C using a global deletion function
    (*DAT_0119caf4)(field_0x0C);
  }
}