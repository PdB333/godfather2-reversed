// FUNC_NAME: HealerSpawner::constructor
undefined4 * __fastcall HealerSpawner::constructor(undefined4 *this)

{
  // Global pointer to the healer spawner instance
  DAT_01129898 = this;
  
  // Set vtable pointer (first entry)
  this[0] = &PTR_FUN_00d82328;
  
  // Set vtable pointer (second entry) - likely a different interface or base class
  this[1] = &PTR_LAB_00d82318;
  
  // Initialize spawner state: active = 1, timer = 0
  this[2] = 1;  // +0x08: active flag
  this[3] = 0;  // +0x0C: timer/counter
  
  // Store string "spawn_healer" at global address 0x0112ff44
  FUN_00408240(&DAT_0112ff44, "spawn_healer");
  
  // Store string "fs_DCG_0h" at global address 0x0112ff4c
  FUN_00408240(&DAT_0112ff4c, "fs_DCG_0h");
  
  // Process/initialize the string at 0x0112ff44 (likely a hash or lookup)
  FUN_00408680(&DAT_0112ff44);
  
  return this;
}