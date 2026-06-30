// FUNC_NAME: EARSObject::~EARSObject

void __thiscall EARSObject::~EARSObject(void)
{
  // Set vtable pointer to the derived class vtable (PTR_FUN_00d61b38)
  *(int **)this = (int *)0x00d61b38;

  // Call base class destructor (FUN_007ee320)
  baseClassDestructor(this);

  // Run class-specific cleanup (FUN_0071afb0)
  cleanupFunction();

  // Delete three owned objects at offsets +0x10, +0x18, +0x20
  if (*(int *)((char *)this + 0x20) != 0) {
    deleteObjectWrapper((int *)((char *)this + 0x20));
  }
  if (*(int *)((char *)this + 0x18) != 0) {
    deleteObjectWrapper((int *)((char *)this + 0x18));
  }
  if (*(int *)((char *)this + 0x10) != 0) {
    deleteObjectWrapper((int *)((char *)this + 0x10));
  }

  // Reset vtable to the base class vtable (PTR_LAB_00d61acc)
  *(int **)this = (int *)0x00d61acc;
}