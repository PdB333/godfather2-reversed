// FUNC_NAME: GodfatherGameManager::executeStartupSequence
void __fastcall GodfatherGameManager::executeStartupSequence(int *this)

{
  int *somePtr;
  undefined4 stackVal;
  undefined4 typeHash;
  undefined4 *pTypeHash;
  undefined1 unused;
  
  // Check conditions for startup execution:
  // param_1[0x12] (+0x48) is a bool/flag - must be 0 (not started)
  // param_1[0x4a] (+0x4a) has bit 1 set and bit 0 clear (state flags)
  if ((((char)this[0x12] == '\0') && ((*(ushort *)((int)this + 0x4a) & 2) != 0)) &&
     ((*(ushort *)((int)this + 0x4a) & 1) == 0)) {
    somePtr = this + 5;  // +0x14 offset - some sub-object or array
    *(undefined1 *)(this + 0x12) = 1;  // Mark as started
    
    // Register various event handlers/callbacks with the sub-system
    // These appear to be startup sequence event bindings
    FUN_005c0d50(somePtr, &LAB_005bfd10, 0);  // Register handler for event type A
    FUN_005c0d50(somePtr, &LAB_005bfd80, 0);  // Register handler for event type B
    FUN_005c0d50(somePtr, &LAB_005bfc10, 0);  // Register handler for event type C
    FUN_005c0d50(somePtr, &LAB_005bfb80, 0);  // Register handler for event type D
    FUN_005c0d50(somePtr, &LAB_005bfcf0, 0);  // Register handler for event type E
    FUN_005c0d50(somePtr, &LAB_005bfb00, 0);  // Register handler for event type F
    
    // Register a handler on a different sub-object (this + 10 = +0x28 offset)
    FUN_005c0d50(this + 10, &LAB_005bf690, 0);
    
    // Call virtual function at vtable+0x34 (likely initialize/start)
    (**(code **)(*this + 0x34))();
    
    // Register more handlers after initialization
    FUN_005c0d50(somePtr, &LAB_005bfbe0, 0);
    FUN_005c0d50(somePtr, &LAB_005bfc40, 0);
    
    // Execute additional startup logic
    FUN_005bfe50();
    
    // Dispatch an event/notification with type hash and data
    stackVal = (**(code **)(this[4] + 4))();  // Call virtual at sub-object+4
    pTypeHash = &stackVal;
    typeHash = DAT_01222058;
    unused = 0;
    FUN_00408a00(&typeHash, 0);  // Send event with computed hash
  }
  return;
}