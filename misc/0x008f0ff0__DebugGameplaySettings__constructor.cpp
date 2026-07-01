// FUNC_NAME: DebugGameplaySettings::constructor
void __thiscall DebugGameplaySettings::constructor(DebugGameplaySettings *this)
{
  // Initialize vtable pointer
  *this = &PTR_FUN_00d80ec0; // virtual function table, likely for DebugGameplaySettings

  // Set some internal fields to pointers to static data
  this->field_0x3c = &PTR_LAB_00d80eb0; // +0x3C - maybe default value pointer
  this->field_0x48 = &PTR_LAB_00d80eac; // +0x48 - maybe default value pointer

  // Initialize sub-object at offset 0x50 (size unknown)
  FUN_004086d0(&this->subObjectAt0x50); // +0x50 - likely another class constructor

  // Call some kind of registration or initializer function on different offsets
  FUN_00408310(&this->subObjectAt0x50); // +0x50
  FUN_00408310(&this->field_0x58);      // +0x58 - another offset

  // Static globals initialization (likely debug menu items)
  FUN_00408310(&DAT_0112ddf0); // global debugging toggle
  FUN_00408310(&DAT_0112ddf8); // global debugging toggle

  // Additional setup (maybe hooking or event registration)
  FUN_0046c640();
}