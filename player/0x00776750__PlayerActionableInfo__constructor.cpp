// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)

{
  int *piVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  int *piVar5;
  
  // Call base class constructor (likely EARSObject or similar)
  FUN_0073e160(param_2,param_3);
  // Set vtable pointer
  *this = &PTR_LAB_00d6821c;
  // Initialize member variables at offsets +0x70 to +0x98 (0x1c*4 to 0x26*4)
  this[0x1c] = 0;  // +0x70
  this[0x1d] = 0;  // +0x74
  this[0x1e] = 0;  // +0x78
  this[0x1f] = 0;  // +0x7C
  this[0x20] = 0;  // +0x80
  this[0x21] = 0;  // +0x84
  this[0x22] = 0;  // +0x88
  piVar5 = this + 0x1c;  // Pointer to +0x70
  this[0x23] = 0;  // +0x8C
  this[0x24] = 0;  // +0x90
  this[0x25] = 0;  // +0x94
  this[0x26] = 0;  // +0x98
  this[0x28] = 0;  // +0xA0
  this[0x29] = 0;  // +0xA4
  uVar2 = DAT_00d5f00c;  // Some global value
  this[0x2b] = 0x40;  // +0xAC - flags, default 0x40
  piVar1 = (int *)this[0x17];  // +0x5C - some object pointer
  this[0x2c] = uVar2;  // +0xB0
  // Check some capability via vtable at offset 0x1bc
  cVar3 = (**(code **)(*piVar1 + 0x1bc))();
  if (cVar3 == '\0') {
    this[0x2b] = this[0x2b] & 0xfffffbff;  // Clear bit 10 (0x400)
  }
  else {
    this[0x2b] = this[0x2b] | 0x400;  // Set bit 10
  }
  // Get some object (likely a manager or system)
  iVar4 = FUN_007ff880();
  if (iVar4 == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar4 + 0x48;  // Offset into the object
  }
  // Linked list insertion at +0x70
  if (*piVar5 != iVar4) {
    if (*piVar5 != 0) {
      FUN_004daf90(piVar5);  // Remove from list
    }
    *piVar5 = iVar4;
    if (iVar4 != 0) {
      this[0x1d] = *(undefined4 *)(iVar4 + 4);  // +0x74 - next pointer
      *(int **)(iVar4 + 4) = piVar5;  // Update previous node's next
    }
  }
  // Update +0xB0 from another system
  if (((*piVar5 != 0) && (*piVar5 != 0x48)) && (iVar4 = FUN_00542d70(), iVar4 != 0)) {
    this[0x2c] = *(undefined4 *)(iVar4 + 0xb4);
  }
  // Get the object pointer (adjusting for offset)
  if (*piVar5 == 0) {
    piVar5 = (int *)0x0;
  }
  else {
    piVar5 = (int *)(*piVar5 + -0x48);
  }
  // Call virtual function at vtable offset 0x1f8 on the object
  (**(code **)(*piVar5 + 0x1f8))(piVar1,this + 0x20);  // +0x80 as parameter
  return this;
}