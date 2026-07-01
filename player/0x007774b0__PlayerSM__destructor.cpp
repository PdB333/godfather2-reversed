// FUNC_NAME: PlayerSM::destructor
void __fastcall PlayerSM::~PlayerSM(undefined4 *this)
{
  int *vtable;
  
  vtable = (int *)this[0x17]; // +0x5C - vtable pointer for state machine
  *this = &PTR_LAB_00d6821c; // set vtable to base class destructor
  FUN_00460300(0x3f800000); // likely set some float to 1.0f
  if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) { // +0x70 - check if not null and not a special value
    FUN_007768b0(); // cleanup function
  }
  (**(code **)(*vtable + 0x260))(); // call virtual destructor at offset 0x260
  if (((uint)this[0x2b] >> 10 & 1) != 0) { // +0xAC - check bit 10 of flags
    vtable = (int *)FUN_00716420(); // get some manager
    (**(code **)(*vtable + 0x24))(0); // release resource
    (**(code **)(*vtable + 0x28))(0); // release resource
  }
  FUN_007f6420(0x5a); // release audio resource (0x5a = 90)
  if (this[0x1c] != 0) { // +0x70
    FUN_004daf90(this + 0x1c); // delete object
  }
  *this = &PTR_LAB_00d63090; // set vtable to base class
  if (this[0x1a] != 0) { // +0x68
    FUN_004daf90(this + 0x1a); // delete object
  }
  FUN_0080ea60(); // final cleanup
  return;
}