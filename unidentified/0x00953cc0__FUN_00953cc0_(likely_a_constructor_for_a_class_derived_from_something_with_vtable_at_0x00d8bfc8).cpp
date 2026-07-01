// FUNC_NAME: FUN_00953cc0 (likely a constructor for a class derived from something with vtable at 0x00d8bfc8)

void FUN_00953cc0(undefined4 *this)
{
  undefined4 *allocatedMem;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;  // Some allocation flags or type
  local_8 = 0x10; // Size or alignment
  local_4 = 0;   // Additional parameter
  allocatedMem = (undefined4 *)FUN_009c8ed0(0x3c, &local_c); // Allocate 0x3c bytes
  if (allocatedMem != (undefined4 *)0x0) {
    FUN_004aa3b0(this); // Call base class constructor
    *allocatedMem = &PTR_FUN_00d8bfc8; // Set vtable pointer
    allocatedMem[2] = &PTR_LAB_00d8bfc4; // Set another vtable or offset table
    this = allocatedMem;
    if ((*(byte *)(allocatedMem + 0xe) & 0x40) != 0) { // Check flag at +0x38 (0xe * 4)
      (**(code **)*allocatedMem)(1); // Call virtual function with arg 1
      return;
    }
    FUN_00953b80(&this); // Continue initialization
  }
  return;
}