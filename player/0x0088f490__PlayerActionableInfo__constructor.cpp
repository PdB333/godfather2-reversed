// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d771f4;  // vtable for PlayerActionableInfo
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d771e4;  // +0x3C - some function pointer table
  this[0x12] = &PTR_LAB_00d771e0;  // +0x48 - another function pointer table
  
  // Call base class constructor
  PlayerActionableTargetSM::constructor(this);  // FUN_0088dd20
  
  // Initialize actionable target state machine
  PlayerActionableTargetSM::initialize(this[0x1b]);  // +0x6C - state machine data
  
  // Call some global initialization
  FUN_0046c640();  // likely InputManager or similar singleton init
  
  // Handle allocation flags
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x7c);  // operator delete with size 0x7C
  }
  
  return this;
}