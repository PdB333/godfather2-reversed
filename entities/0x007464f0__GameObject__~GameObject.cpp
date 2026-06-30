// FUNC_NAME: GameObject::~GameObject
undefined4 * __thiscall GameObject::~GameObject(undefined4 *this, byte deleteFlag)
{
  int *childPtr;
  
  // Set vtable to this class's vtable (base class or own)
  *this = &PTR_LAB_00d63e80;
  
  // Check if child object exists and is not flagged for destruction
  if (((*(char *)(this + 0x19) != '\0') &&
       (childPtr = (int *)this[0x16], childPtr != (int *)0x0)) &&
      ((uint)childPtr[0x7d6] >> 0x19 & 1) == 0) {
    // Call virtual function at offset 0x25c on child (likely child's destructor/cleanup)
    (**(code **)(*childPtr + 0x25c))();
  }
  
  // Free second sub-object if present
  if (this[0x17] != 0) {
    destructor_004daf90(this + 0x17);
  }
  
  // Global cleanup function
  function_004ac1e0();
  
  // If deleting destructor, deallocate memory
  if ((deleteFlag & 1) != 0) {
    g_memory_dealloc(this);
  }
  
  return this;
}