// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject *this)
{
  // Set base vtable pointer (offset 0x00)
  *this = &PTR_FUN_00e31e38;
  // Set initial secondary vtable pointer (offset 0x08)
  this[2] = &PTR_LAB_00e31e44;

  // Call virtual function at vtable offset 0x0C from the object pointed to by field at +0x0C
  // This is likely an init hook for sub-objects
  (**(code **)(*(int *)this[3] + 0xC))();

  // Call memory manager initialization
  FUN_00ab4d30();
  // Call game-specific initialization
  FUN_00463400();
  // Initialize sub-object at offset 0x1C (this+7*4)
  FUN_00463210(&this[7]);

  // Cleanup previous if any (field at +0x10)
  if (this[4] != 0) {
    FUN_009c8f10(this[4]);
  }

  // Update vtable pointer (offset 0x08) to final vtable
  this[2] = &PTR_LAB_00e31e48;
  // Reset global initialized flag
  DAT_0122345c = 0;
  // Call thread/reset system
  FUN_0049c640();
  return;
}