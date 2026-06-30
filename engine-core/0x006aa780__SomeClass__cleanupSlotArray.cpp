// FUNC_NAME: SomeClass::cleanupSlotArray
void __fastcall SomeClass::cleanupSlotArray(int thisPtr)
{
  int i;
  SlotStruct *slotPtr; // points to current slot during iteration
  int *fieldPtr;        // pointer to a field within the slot (used for vtable reset)

  // Start from the end of the slot array (offset 0x390 is after the last slot)
  slotPtr = (SlotStruct *)(thisPtr + 0x390);
  // Start from a fixed offset 0x360 (some field in the slot)
  fieldPtr = (int *)(thisPtr + 0x360);

  for (i = 7; i >= 0; i--)
  {
    // Move to previous slot (each slot is 0x1b bytes)
    slotPtr = (SlotStruct *)((char *)slotPtr - 0x1b);
    // Reset the slot's vtable pointer (or some control field) to a global constant
    *fieldPtr = (int)&PTR_FUN_00d5d9b0;
    fieldPtr = (int *)((char *)fieldPtr - 0x1b);

    // Destroy up to 4 sub-objects within the slot
    if (slotPtr->subObject1 != 0)
    {
      // Call destructor via vtable (vtable entry at -0x17 relative to slotPtr)
      ((void (__thiscall *)(void *))slotPtr->destructorVtable1)(slotPtr->subObject1);
    }
    if (slotPtr->subObject2 != 0)
    {
      ((void (__thiscall *)(void *))slotPtr->destructorVtable2)(slotPtr->subObject2);
    }
    if (slotPtr->subObject3 != 0)
    {
      ((void (__thiscall *)(void *))slotPtr->destructorVtable3)(slotPtr->subObject3);
    }
    if (slotPtr->subObject4 != 0)
    {
      ((void (__thiscall *)(void *))slotPtr->destructorVtable4)(slotPtr->subObject4);
    }
  }
}