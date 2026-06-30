// FUNC_NAME: Vehicle::constructor
undefined4 * __thiscall Vehicle::constructor(undefined4 *this, byte flags)
{
  int *vtablePtr;
  
  *this = &PTR_FUN_00e41380;  // Base class vtable (likely BaseVehicle)
  BaseVehicle::constructor();  // FUN_0061f6d0 - base class initialization
  *this = &PTR_LAB_00e41338;  // Vehicle vtable override
  
  if ((flags & 1) != 0) {
    vtablePtr = (int *)operatorNew(0xe0);  // FUN_009c8f80 - allocation
    (**(code **)(*vtablePtr + 4))(this, 0xe0);  // Call placement new with size
  }
  
  return this;
}