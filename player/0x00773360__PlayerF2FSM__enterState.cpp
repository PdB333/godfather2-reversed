// FUNC_NAME: PlayerF2FSM::enterState
void __fastcall PlayerF2FSM::enterState(PlayerF2FSM *this)
{
  int *linkedListPtr;
  code *vtblFunc;
  int iVar3;
  int iVar4;
  
  // Allocate memory for state-specific data? (0x30 bytes)
  FUN_007f63e0(0x30);
  
  // Clear lower 3 bits of state flags
  this->stateFlags = this->stateFlags & 0xfffffff8;
  
  // Get the main game object from global data (DAT_012233a0)
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // Subtract offset to get PlayerCCTVariables?
  }
  
  // Handle linked list insertion for state data (offset +0xB0 = this->stateListPtr) (this+0x2c)
  linkedListPtr = (int *)((char *)this + 0xb0);
  if (iVar3 == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar3 + 0x48; // Offset to some structure within PlayerCCTVariables?
  }
  
  if (*linkedListPtr != iVar4) {
    if (*linkedListPtr != 0) {
      FUN_004daf90(linkedListPtr);
    }
    *linkedListPtr = iVar4;
    if (iVar4 != 0) {
      this->stateListPrev = *(int *)(iVar4 + 4); // +0xb4 (this+0x2d)
      *(int **)(iVar4 + 4) = linkedListPtr;
    }
  }
  
  // Call virtual function at offset 0x290 on the state machine
  (**(code **)(*(int *)this->stateMachine + 0x290))(0, 8);
  
  // Check if player can be controlled and not already transitioning
  if (((iVar3 != 0) && ((*(byte *)(iVar3 + 0x8e4) & 1) == 0)) &&
     (((uint)this->stateFlags >> 4 & 1) == 0)) {
    // Set a timer/flag for something (0 = includeDisabled, DAT_00d5ef90 = float?)
    FUN_007f4490(1, 0, DAT_00d5ef90);
    this->stateFlags = this->stateFlags | 0x10; // Set bit 4
  }
  
  // Get another object (family related?) using hash
  iVar3 = 0;
  if ((*linkedListPtr != 0) && (*linkedListPtr != 0x48)) {
    iVar3 = FUN_00625050(0xb47bb605, 0); // Hash lookup
  }
  
  // Handle another linked list (offset +0xa8 = this->anotherListPtr) (this+0x2a)
  linkedListPtr = (int *)((char *)this + 0xa8);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = iVar3 + 0x98; // Offset to some structure
  }
  
  if (*linkedListPtr != iVar3) {
    if (*linkedListPtr != 0) {
      FUN_004daf90(linkedListPtr);
    }
    *linkedListPtr = iVar3;
    if (iVar3 != 0) {
      this->anotherListPrev = *(int *)(iVar3 + 4); // +0xac (this+0x2b)
      *(int **)(iVar3 + 4) = linkedListPtr;
    }
  }
  
  // Set flags on the state machine object (at offsets +0x970 and +0x974)
  *(uint *)(this->stateMachine + 0x970) = *(uint *)(this->stateMachine + 0x970) | 0x800;
  *(uint *)(this->stateMachine + 0x974) = *(uint *)(this->stateMachine + 0x974) | 0x800;
  
  // Some UI or effect function call
  FUN_009c4ea0(0);
  
  this->stateFlags = this->stateFlags | 2; // Set bit 1
  
  // Check and clear a flag in the child state machine?
  if ((*linkedListPtr != 0) && (*linkedListPtr != 0x98)) {
    if (*linkedListPtr == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *linkedListPtr + -0x98;
    }
    if ((*(byte *)(iVar3 + 0x1d0) & 1) != 0) {
      if (*linkedListPtr == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *linkedListPtr + -0x98;
      }
      *(uint *)(iVar3 + 0x1d0) = *(uint *)(iVar3 + 0x1d0) & 0xfffffffe;
      this->stateFlags = this->stateFlags & 0xfffffffd; // Clear bit 1
    }
  }
  
  // Check if player is in a specific state (byte at +0x1b8c equals 4)
  if (*(char *)(this->stateMachine + 0x1b8c) == '\x04') {
    vtblFunc = *(code **)(*(int *)this + 0x2c); // Virtual function at vtable+0x2c
    this->someHash = 0x2ca3cff6; // Hash for state transition
    (*vtblFunc)(0x2ca3cff6, 1, 1, 0, 0x3f800000, 0x3f800000); // Float args: 1.0, 1.0
    (**(code **)(*(int *)this->stateMachine + 0x234))(0, 1);
  }
  
  // Set some value from global
  *(undefined4 *)(this->stateMachine + 0x1eb4) = DAT_01205224;
  
  FUN_007ca8a0();
  return;
}