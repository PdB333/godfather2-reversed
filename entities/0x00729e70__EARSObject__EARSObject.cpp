// FUNC_NAME: EARSObject::EARSObject
void __fastcall EARSObject::EARSObject(void* this)
{
  // Set vtable pointer for this class (offset +0x00)
  *(int**)this = (int*)&PTR_FUN_00d62544;
  // Set secondary vtable or interface pointer at offset +0x3C (0xF * 4)
  *(int**)((char*)this + 0x3C) = (int*)&PTR_LAB_00d62534;
  // Set another table pointer at offset +0x48 (0x12 * 4)
  *(int**)((char*)this + 0x48) = (int*)&PTR_LAB_00d62530;
  // Call base class constructor (assumed EARSObject or similar)
  FUN_00728f70(this);
  // Additional initialization (e.g., global state)
  FUN_0046c640();
}