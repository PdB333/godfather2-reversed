// FUNC_NAME: ChaseCamera::constructor(undefined4, undefined4)
undefined4 * __thiscall ChaseCamera::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  // Base class constructor call (likely Camera::constructor or similar)
  FUN_004ac120(param_2,param_3);
  
  // Set vtable pointer (ChaseCamera vtable at 0x00d67ac8)
  *this = &PTR_LAB_00d67ac8;
  
  // Initialize flags at offsets +0x15 and +0x55
  *(undefined1 *)(this + 0x15) = 0;    // +0x15: flag byte 1
  *(undefined1 *)((int)this + 0x55) = 0; // +0x55: flag byte 2
  
  // Function call that initializes default camera settings
  FUN_0084dd20();
  
  // Reset field at offset +0x28 (0x28 * 4 = 0xA0)
  this[0x28] = 0;  // +0xA0: some pointer/ID
  
  // Calculate derived value from field +0x12
  if (this[0x12] == 0) {  // +0x48: base pointer
    iVar2 = 0;
  }
  else {
    iVar2 = this[0x12] + -0x48;  // Subtract offset to get another reference
  }
  this[0x14] = iVar2;  // +0x50: derived pointer
  
  // Two function calls to setup engine-specific data
  FUN_007f62f0();
  FUN_007f62e0();
  
  // Call a virtual method on the object at this[0x14] via vtable offset 0x290
  (**(code **)(*(int *)this[0x14] + 0x290))(0,2);
  
  // Allocate memory (0x10 = 16 bytes)
  FUN_007f63e0(0x10);
  
  // Get a data pointer from a global
  if (this[0x14] == 0) {  // +0x50
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_0043b870(DAT_01131018);  // DAT_01131018: global data pointer
  }
  this[0x29] = uVar1;  // +0xA4: some data handle
  
  // Check flags on object at this[0x14] +0x8E0 for bit operations
  if ((*(uint *)(this[0x14] + 0x8e0) >> 1 & 1) == 0) {
    // If bit 2 is set, call a function
    if ((*(uint *)(this[0x14] + 0x8e0) >> 2 & 1) != 0) {
      FUN_0072cb10(1);  // Possibly enable something
    }
    // Set bit 7 (0x80) on flag at +0x15
    *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 0x80;
  }
  
  return this;
}