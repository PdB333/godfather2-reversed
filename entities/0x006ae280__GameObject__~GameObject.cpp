// FUNC_NAME: GameObject::~GameObject
// Address: 0x006ae280
// Role: Destructor for a common base class. Destroys an embedded subobject at offset 4 and resets vtable pointer to a base vtable.
// The flag (param_2) bit 0 controls whether memory is freed after destruction.

undefined4 * __thiscall GameObject::~GameObject(GameObject *this, byte flags)
{
  // Check if the embedded subobject pointer at offset 4 is non-null
  if (this->subObject != (void *)0x0) {
    // Call destructor on the subobject (address of the embedded field)
    FUN_004daf90(&this->subObject); // subObject destructor
  }
  // Reset vtable to base class vtable (likely for cleanup purposes)
  this->vtable = &PTR_LAB_00e2f0c0; // Base vtable

  // If the low bit of flags is set, free the memory occupied by this object
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // Memory deallocation (likely operator delete)
  }
  return (undefined4 *)this;
}