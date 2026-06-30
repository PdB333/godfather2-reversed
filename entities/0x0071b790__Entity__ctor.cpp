// FUNC_NAME: Entity::ctor
// Address: 0x0071b790
// Role: Constructor for an Entity subclass with multiple inheritance (5 virtual base classes).
// The size of the object is 400 bytes (0x190).
// param_2 flag: bit 0 set indicates dynamically allocated memory; if set, calls operator delete on failure.

__thiscall Entity * Entity::ctor(Entity *this, byte allocateFlag)
{
  // Set vtable pointer for the most derived class
  this->vtable = (void *)&PTR_FUN_00d61c28; // First vtable (main class)

  // Set additional vtable pointers for multiply inherited interfaces
  // Offsets from this: +0x3C (0xf*4), +0x48 (0x12*4), +0x50 (0x14*4), +0x54 (0x15*4), +0x58 (0x16*4)
  *(void **)((char *)this + 0x3C) = (void *)&PTR_LAB_00d61c18;
  *(void **)((char *)this + 0x48) = (void *)&PTR_LAB_00d61c14;
  *(void **)((char *)this + 0x50) = (void *)&PTR_LAB_00d61c10;
  *(void **)((char *)this + 0x54) = (void *)&PTR_LAB_00d61bb0;
  *(void **)((char *)this + 0x58) = (void *)&PTR_LAB_00d61b48;

  // Call base class constructor(s) or initialization routine
  FUN_008d8620(); // Likely base class constructor or initializer

  // If the object was dynamically allocated, call operator delete to free memory
  // (This is a fallback for failed construction? Actually, after successful construction, it's called? Unusual.)
  if ((allocateFlag & 1) != 0) {
    FUN_0043b960(this, 400); // operator delete(this, 400)
  }

  return this;
}