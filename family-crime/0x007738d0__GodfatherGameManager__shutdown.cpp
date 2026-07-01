// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)
{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char cVar4;
  int iVar5;
  
  // Set vtable pointers for shutdown state
  *this = &PTR_LAB_00d67d7c;
  this[0x1c] = &PTR_LAB_00d67d78;
  this[0x25] = &PTR_LAB_00d67d74;
  
  // Call base shutdown and set thread priority
  FUN_00773560(); // BaseGameManager::shutdown
  FUN_007f6420(3); // SetThreadPriority(3)
  
  // Clear some flags at offset 0x970 and 0x974 in the object at this[0x28]
  *(uint *)(this[0x28] + 0x970) = *(uint *)(this[0x28] + 0x970) & 0xfffff7ff;
  *(uint *)(this[0x28] + 0x974) = *(uint *)(this[0x28] + 0x974) & 0xfffff7ff;
  
  piVar1 = this + 0x2a;
  // Check if there's a valid object at this[0x2a] (not null and not 0x98)
  if ((this[0x2a] != 0) && (this[0x2a] != 0x98)) {
    if (*piVar1 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *piVar1 + -0x98;
    }
    // Clear bit 0 at offset 0x1d0 if set
    if ((*(byte *)(iVar5 + 0x1d0) & 1) != 0) {
      if (*piVar1 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = *piVar1 + -0x98;
      }
      *(uint *)(iVar5 + 0x1d0) = *(uint *)(iVar5 + 0x1d0) & 0xfffffffe;
    }
  }
  
  // Check if we should call some cleanup function
  cVar4 = FUN_007fd640(); // IsGameActive?
  if ((cVar4 != '\0') && (cVar4 = FUN_007f7c50(), cVar4 == '\0')) {
    FUN_007fcd60(); // Some cleanup
  }
  
  FUN_007ff050(0); // Clear some state
  
  // Free memory at this[0x2c] and this[0x2a] if non-null
  if (this[0x2c] != 0) {
    FUN_004daf90(this + 0x2c); // operator delete
  }
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1); // operator delete
  }
  
  // Set vtable for cleanup
  this[0x25] = &PTR_FUN_00e32808;
  
  // Walk a linked list at this[0x26] and clear entries
  puVar3 = (undefined4 *)this[0x26];
  while (puVar3 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)puVar3[1];
    puVar3[1] = 0;
    *puVar3 = 0;
    puVar3 = puVar2;
  }
  
  // Final cleanup
  FUN_007ca830(); // Some manager cleanup
  *this = &PTR_LAB_00d63090; // Set final vtable
  
  if (this[0x1a] != 0) {
    FUN_004daf90(this + 0x1a); // operator delete
  }
  
  FUN_0080ea60(); // Final shutdown
  return;
}