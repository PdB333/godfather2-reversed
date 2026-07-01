// FUNC_NAME: EntityManager::Constructor
int __thiscall EntityManager::Constructor(EntityManager *this, byte param_2)
{
  // Set vtable pointer at offset +0x18
  *(undefined ***)(this + 0x18) = &PTR_LAB_00e355fc;
  
  // Call base class constructor
  FUN_0064d150();
  
  // If the 0x1 bit is set in param_2, call destructor (construction cleanup on failure?)
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return (int)this;
}