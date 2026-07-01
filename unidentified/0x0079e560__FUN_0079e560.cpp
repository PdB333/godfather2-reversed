// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(SomeClass* this)
{
  undefined4 *puVar1;
  undefined1 local_24 [4];
  undefined4 *local_20;
  int local_1c [2];
  undefined1 local_14;
  undefined **local_c;
  
  // Call base class destructor or cleanup function
  FUN_0072de20(this);
  
  local_14 = 1;
  local_c = &PTR_LAB_00e52818;
  
  // Call some cleanup function
  FUN_0081dab0(local_24);
  
  // If there's an allocated object, free it
  if (local_1c[0] != 0) {
    FUN_004daf90(local_1c);
  }
  
  // Free linked list nodes (likely a list of allocated resources)
  while (local_20 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)local_20[1]; // Get next node pointer (+0x04)
    local_20[1] = 0;                    // Clear next pointer
    *local_20 = 0;                      // Clear data pointer
    local_20 = puVar1;                  // Move to next node
  }
  
  return;
}