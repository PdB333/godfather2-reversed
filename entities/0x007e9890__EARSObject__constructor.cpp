// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_007ab5e0(param_2,param_3);
  
  // Set vtable pointer
  *this = &PTR_LAB_00d6fdd8;
  
  // Get some engine singleton/manager instance
  puVar1 = (undefined4 *)FUN_007ab150();
  
  // Copy value from offset +0x04 of that instance to this+0x78 (0x1e * 4)
  this[0x1e] = puVar1[1];
  
  // Call virtual methods on the instance (likely reference counting or initialization)
  (**(code **)*puVar1)(2);
  (**(code **)*puVar1)(1);
  
  // Get another engine singleton/manager
  iVar2 = FUN_007ab130();
  
  // Copy value from offset +0x04 to this+0x74 (0x1d * 4)
  this[0x1d] = *(undefined4 *)(iVar2 + 4);
  
  // Get yet another instance and call method with parameter 0x3f (63)
  puVar1 = (undefined4 *)FUN_007ab130();
  (**(code **)*puVar1)(0x3f);
  
  // Check if this+0x58 (0x16 * 4) is non-zero (some flag)
  if (this[0x16] != 0) {
    // Load from global data pointer and call function to get resource/asset
    uVar3 = FUN_0043b870(DAT_01131018);
    this[0x1f] = uVar3;  // Store at this+0x7C
    return this;
  }
  
  // Otherwise set to null
  this[0x1f] = 0;
  return this;
}