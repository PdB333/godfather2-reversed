// FUNC_NAME: BaseObject::constructor
// Function address: 0x00821fb0
// Role: Constructor for BaseObject class, with optional specific initialization based on flag.

undefined4 __thiscall BaseObject::constructor(BaseObject *this, byte initFlag)
{
  // Call base class constructor (likely parent class initialization)
  FUN_00821f60(); // Base::constructor(this)
  
  // If the flag's lowest bit is set, perform additional setup
  if ((initFlag & 1) != 0) {
    FUN_009c8eb0(this); // BaseObject::specificInit(this)
  }
  
  return (undefined4)this;
}