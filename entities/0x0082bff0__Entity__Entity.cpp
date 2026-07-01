// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, byte allocateFlag)
{
  int *vtablePtr;
  
  // Set base class vtable pointer at offset 0
  *this = &PTR_FUN_00d73844;
  // Call base class constructor (likely EARSObject or SimObject)
  FUN_0082b490();
  // Set derived class vtable pointer at offset 0xc (second vtable for multiple inheritance)
  this[0xc] = &PTR_LAB_00e32854;
  // Call initialization function (e.g., initComponents or postConstruct)
  FUN_00821f60();
  // If heap allocation flag is set, allocate additional memory (size 0xb0) via vtable
  if ((allocateFlag & 1) != 0) {
    vtablePtr = (int *)FUN_009c8f80();
    (**(code **)(*vtablePtr + 4))(this, 0xb0);
  }
  return this;
}