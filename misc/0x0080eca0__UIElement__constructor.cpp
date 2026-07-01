// FUNC_NAME: UIElement::constructor

undefined4 * __thiscall UIElement::constructor(undefined4 *this, undefined4 param2, undefined4 param3)

{
  int iVar1;
  char cVar2;
  int unaff_retaddr;
  undefined4 uStack_18;
  undefined8 uStack_14;
  undefined4 uStack_c;
  
  FUN_0080e6a0(param2, param3);  // Base class constructor call
  *this = &PTR_LAB_00d72db0;      // Set vtable pointer
  this[0x16] = 0;                 // +0x58: some flag/state
  this[0x1d] = 0;                 // +0x74: some flag/state
  this[0x19] = 0;                 // +0x64: some flag/state
  this[0x18] = 0;                 // +0x60: some flag/state
  this[0x17] = 0;                 // +0x5c: some flag/state
  this[0x1c] = 0;                 // +0x70: some flag/state
  this[0x1b] = 0;                 // +0x6c: some flag/state
  this[0x1a] = 0;                 // +0x68: some flag/state
  iVar1 = this[0x14];             // +0x50: pointer to some object (probably engine core)
  FUN_005512c0(1);                // Some initialization function
  *(uint *)(iVar1 + 0x4a4) = *(uint *)(iVar1 + 0x4a4) | 1;  // Set bit 0 at +0x4a4
  *(undefined8 *)(iVar1 + 0x424) = 0;   // Clear 8 bytes at +0x424
  *(undefined4 *)(iVar1 + 0x42c) = 0;   // Clear 4 bytes at +0x42c
  FUN_007f63e0(0x5d);             // Register callback/resource with ID 0x5d
  this[0x1f] = _DAT_00d5780c;     // +0x7c: set from global variable
  this[0x1e] = 0;                 // +0x78: clear
  this[0x22] = 0;                 // +0x88: clear
  this[0x21] = 0;                 // +0x84: clear
  this[0x20] = 0;                 // +0x80: clear
  this[0x25] = 0;                 // +0x94: clear
  this[0x24] = 0;                 // +0x90: clear
  this[0x23] = 0;                 // +0x8c: clear
  *(byte *)(this + 0x26) = (byte)((uint)((int *)this[0x14])[0x238] >> 1) & 1;  // Extract bit 1 from +0x8E0 (238*4) into +0x98
  param3 = 0;
  cVar2 = (**(code **)(*(int *)this[0x14] + 0x10))(0x383225a1,&param3);  // Call virtual function at offset 0x10 (likely QueryInterface/GetSystem)
  if ((cVar2 != '\0') && (unaff_retaddr != 0)) {
    cVar2 = FUN_00481620();       // Check if some system/feature is enabled
    if (cVar2 != '\0') {
      FUN_0079fb90(0xb,0x200000001,CONCAT44(uStack_18,(uint)*(byte *)(this + 0x26)),uStack_14,
                   uStack_c);     // Log/notify with type 0xB and flags 0x200000001
      return this;
    }
    *(bool *)(this + 0x26) = *(int *)(unaff_retaddr + 0x22d4) != 0;  // Update +0x98 from retaddr+0x22D4
    *(undefined1 *)(unaff_retaddr + 0x22cc) = 1;                      // Set byte at retaddr+0x22CC to 1
  }
  return this;
}