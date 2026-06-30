// FUNC_NAME: EARSObject::~EARSObject (destructor with memory deallocation flag)
undefined4 * __thiscall EARSObject::~EARSObject(undefined4 *this, byte deleteFlag)
{
  int childPtr;

  childPtr = this[0xc]; // +0x30: pointer to owned child object
  // Set vtable pointers to derived class vtables (before destruction)
  *this = &PTR_FUN_00e39ff4; // vtable for base class 1
  this[4] = &PTR_LAB_00e3a018; // +0x10: vtable for base class 2

  if (childPtr != 0) {
    // Destroy and free the child object
    FUN_00559ca0(childPtr); // child destructor call
    FUN_009c8eb0(childPtr); // operator delete (or custom free)
  }

  // Reset vtable pointers to base class vtables (after child destruction)
  this[4] = &PTR_LAB_00d987cc; // +0x10: base class vtable 2
  *this = &PTR_LAB_00d96914;   // base class vtable 1

  if ((deleteFlag & 1) != 0) {
    // TLS-based deallocation: retrieve memory manager TLS index and call custom free
    TlsGetValue(DAT_01139810); // probably ignored, maybe for side effect
    FUN_00aa26e0(this, *(undefined2 *)(this + 1), 0x27); // free(this, classID, size=0x27)
  }
  return this;
}