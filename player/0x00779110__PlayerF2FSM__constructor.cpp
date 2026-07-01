// FUNC_NAME: PlayerF2FSM::constructor
undefined4 * __thiscall PlayerF2FSM::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  
  // Call base class constructor
  FUN_0073e160(param_2, param_3);
  
  // Initialize vtable pointers and state
  this[0x1c] = &PTR_FUN_00e2f19c;  // +0x70 - vtable for F2F state
  this[0x1d] = 1;                   // +0x74 - state ID
  this[0x1e] = 0;                   // +0x78 - substate
  this[0x20] = 0;                   // +0x80 - timer
  this[0x1f] = &PTR_LAB_00d58278;  // +0x7c - vtable pointer
  *this = &PTR_LAB_00d68390;       // +0x00 - vtable
  this[0x1c] = &PTR_LAB_00d68380;  // +0x70 - vtable
  this[0x1f] = &PTR_FUN_00d6836c;  // +0x7c - function pointer
  
  // Initialize linked list node
  piVar1 = this + 0x22;            // +0x88 - linked list node
  *piVar1 = 0;                     // +0x88 - next pointer
  this[0x23] = 0;                  // +0x8c - prev pointer
  this[0x24] = 0;                  // +0x90 - flags
  this[0x2b] = 0;                  // +0xac - some state
  
  // Get or create some object
  iVar3 = FUN_007ff880();
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = iVar3 + 0x48;
  }
  
  // Link into a list
  if (*piVar1 != iVar3) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1);  // Remove from list
    }
    *piVar1 = iVar3;
    if (iVar3 != 0) {
      this[0x23] = *(undefined4 *)(iVar3 + 4);  // +0x8c - prev pointer
      *(int **)(iVar3 + 4) = piVar1;
    }
  }
  
  // Check some condition and set flags
  cVar2 = FUN_00543050(this[0x17]);  // +0x5c - some object
  if (cVar2 != '\0') {
    this[0x24] = this[0x24] | 0x10;  // +0x90 - set flag bit 4
  }
  
  // Additional initialization
  if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
    if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
      FUN_0043b870(DAT_0112ded0);
    }
    FUN_009aefd0(this + 0x1f, 0x8000);  // +0x7c - some buffer
  }
  
  // Clear remaining fields
  this[0x2a] = 0;  // +0xa8
  this[0x29] = 0;  // +0xa4
  this[0x28] = 0;  // +0xa0
  this[0x27] = 0;  // +0x9c
  this[0x26] = 0;  // +0x98
  this[0x25] = 0;  // +0x94
  
  return this;
}