// FUNC_NAME: EARSObject::construct
void __thiscall EARSObject::construct(void* handle, int param2, int param3, int param4, int param5, int param6) {
  // handle points to a pointer to the actual object (ref-counted handle)
  EARSObjectInternal* objPtr = *(EARSObjectInternal**)handle;

  // Set the vtable pointer at offset +0x14 of the object to the base vtable table
  *(void**)((char*)objPtr + 0x14) = (void*)&PTR_LAB_01124b08;

  // Advance the vtable slot pointer (each slot is 4 bytes)
  void** slotPtr = *(void***)((char*)objPtr + 0x14);
  slotPtr = (void**)((char*)slotPtr + 4);
  *(void***)((char*)objPtr + 0x14) = slotPtr;

  // Call the actual initialization routine
  FUN_004e8760(param2, param3, param4, param5, param6);
}