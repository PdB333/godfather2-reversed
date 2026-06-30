// FUNC_NAME: PlayerActionableInfo::constructor
void __thiscall PlayerActionableInfo::constructor(void *this)

{
  undefined4 uVar1;
  undefined4 *unaff_EDI;
  undefined4 local_4;
  
  // Initialize actionable info structure (0x6C bytes? based on offsets)
  *(undefined4 *)this = 0;           // +0x00: some pointer/flag
  *(undefined4 *)((int)this + 4) = 0; // +0x04: another pointer/flag
  *(undefined4 *)((int)this + 8) = 0; // +0x08: another pointer/flag
  *(undefined4 *)((int)this + 0xc) = 0; // +0x0C: another pointer/flag
  *(undefined4 *)((int)this + 0x10) = 0xffffffff; // +0x10: invalid handle/ID
  *(undefined4 *)((int)this + 0x14) = 0; // +0x14: some flag
  
  // Set global based on screen resolution
  _DAT_00f0ccb0 = DAT_00e2b1a0; // Default value
  if (0x2d0 < DAT_0120587c) {   // If screen width > 720
    _DAT_00f0ccb0 = DAT_00e445a0; // Use wider value
  }
  
  // Call sub-initializer
  FUN_006700d0(); // Likely initializes some sub-component
  
  // Set more fields
  *(undefined4 *)((int)this + 0x198) = 0xffffffff; // +0x198: invalid handle/ID
  *(undefined4 *)((int)this + 0x1a0) = 0xffffffff; // +0x1A0: invalid handle/ID
  *(undefined4 *)((int)this + 0x1a4) = 0xffffffff; // +0x1A4: invalid handle/ID
  *(undefined4 *)((int)this + 0x19c) = 0;           // +0x19C: some flag
  *(undefined4 *)((int)this + 0x1a8) = 0x6e;        // +0x1A8: some constant (110)
  
  // Initialize action-related objects
  local_4 = 0;
  uVar1 = FUN_00672680(); // Creates some action object
  *(undefined4 *)this = uVar1; // Store at +0x00
  
  uVar1 = FUN_006719c0(&local_4); // Creates another object
  *(undefined4 *)((int)this + 4) = uVar1; // Store at +0x04
  
  FUN_00671040(); // Initialize some system
  
  // Set up action parameters at offset 0x1E28 in the second object
  *(undefined2 *)(uVar1 + 0x1e28) = 3;    // Action type
  *(undefined2 *)(uVar1 + 0x1e2a) = 1;    // Some flag
  *(undefined2 *)(uVar1 + 0x1e2c) = 0x409; // Action ID/parameter
  *(undefined2 *)(uVar1 + 0x1e2e) = 1;    // Another flag
  
  // Finalize initialization
  *(undefined4 *)((int)this + 0x14) = 0; // +0x14: reset flag
  *(undefined4 *)((int)this + 0xc) = 1;  // +0x0C: set active flag
  
  return;
}