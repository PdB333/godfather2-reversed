// FUNC_NAME: GodfatherGameManager::update
void __fastcall GodfatherGameManager::update(GodfatherGameManager *this)
{
  int *piVar1;
  uint *puVar2;
  char cVar3;
  
  // Set vtable pointer
  *this = &PTR_LAB_00d72ba0;
  
  // Check if initial update flag is set
  if (*(char *)(this + 0x15) != '\0') {
    FUN_0080c700(); // Some initialization function
    *(undefined1 *)(this + 0x15) = 0; // Clear flag
  }
  
  // Check if game manager has a valid entity manager
  if (this[0x14] != 0) {
    FUN_007ffa80(); // Update entity manager
    
    // Check for a specific entity at offset +0xff0
    if ((*(int *)(this[0x14] + 0xff0) != 0) &&
       (piVar1 = (int *)(*(int *)(this[0x14] + 0xff0) + -0x48), piVar1 != (int *)0x0)) {
      // Process entity with specific vtable offset
      FUN_007fd670(); // Some processing
      FUN_007fc9f0(); // More processing
      FUN_007f6420(6); // Set state/flag 6
      (**(code **)(*piVar1 + 0x290))(1,4); // Call vtable method at offset 0x290
    }
    
    // Process main entity
    FUN_007fd670();
    FUN_007fc9f0();
    FUN_007f6420(6);
    (**(code **)(*(int *)this[0x14] + 0x290))(1,4); // Call vtable method at offset 0x290
    (**(code **)(*(int *)this[0x14] + 0x198))(); // Call vtable method at offset 0x198
    FUN_007f6420(0x2f); // Set state/flag 0x2f
    
    // Check for some condition
    cVar3 = FUN_00481640();
    if (cVar3 != '\0') {
      FUN_00472130(1); // Enable something
      FUN_004721c0(1); // Enable something else
    }
    
    // Check flags at offset +0x1b94
    if ((*(uint *)(this[0x14] + 0x1b94) & 0x300) != 0) {
      FUN_007faca0(); // Handle special state
    }
    
    // Check and clear flag at offset +0x4a4
    if ((~*(byte *)(this[0x14] + 0x4a4) & 1) == 0) {
      puVar2 = (uint *)(this[0x14] + 0x4a4);
      *puVar2 = *puVar2 & 0xfffffffe;
    }
    
    // Check for a specific message/event
    cVar3 = (**(code **)(*(int *)this[0x14] + 0x10))(0x369ac561, &stack0xfffffff4);
    if ((cVar3 != '\0') && (this != (undefined4 *)0x0)) {
      FUN_0072cf00(0); // Handle event
      
      // Check bit 0xb at offset +0x23a
      if (((uint)this[0x23a] >> 0xb & 1) != 0) {
        FUN_007f9690(); // Update something
        FUN_007f6420(0x4b); // Set state/flag 0x4b
      }
      
      // Check flag at offset +0x8e6
      if ((*(byte *)((int)this + 0x8e6) & 1) == 0) {
        FUN_006f8d40(this, 0); // Process something
      }
    }
  }
  
  FUN_004ac1e0(); // Final update
  return;
}