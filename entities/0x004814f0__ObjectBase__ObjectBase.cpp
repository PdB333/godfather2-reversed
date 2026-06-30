// FUNC_NAME: ObjectBase::ObjectBase
// Address: 0x004814f0
// Role: Constructor for a base game object class, sets vtable pointer and calls base constructor.
// The param_2 flag (byte) indicates ownership: if bit 0 is set, the object self-destructs (deletes itself) after construction.
// This pattern is typical for placement-new constructors in EA EARS engine where the allocation and construction are separated.

void * __thiscall ObjectBase::ObjectBase(ObjectBase *this, byte allocFlag)
{
  // Set virtual function table pointer to the derived class's vtable (at 0x00e33520)
  this->vtablePtr = &PTR_FUN_00e33520;   // +0x00: vtable

  // Call base class constructor (likely TNL::Object or similar)
  // FUN_00454390 probably does common initialization (zeroing fields, etc.)
  BaseClass::constructor(this);

  // If the alloc flag's lowest bit is set, this is a self-allocated object that should be freed after construction
  // This is used for temporary or dynamically allocated objects that require explicit deletion.
  if ((allocFlag & 1) != 0) {
    // Call the destructor and then operator delete to free memory
    // FUN_009c8eb0 likely does: this->~ObjectBase(); operator delete(this);
    freeObjectMemory(this);
  }

  return this;
}