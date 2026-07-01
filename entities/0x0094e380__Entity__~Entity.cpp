// FUNC_NAME: Entity::~Entity

// Destructor for class Entity (vtable at 0x00d8b9a8, secondary vtable at 0x00d8b984, tertiary vtable at 0x00d8b8bc)
// Releases owned sub-objects and unregisters from event system.
void __thiscall Entity::~Entity(void)
{
  // Set vtable pointers (likely to base class vtables)
  this->vtable = &PTR_FUN_00d8b9a8;   // +0x00: primary vtable
  this->vtable2 = &PTR_LAB_00d8b984;  // +0x04: secondary vtable
  this->vtable3 = &PTR_LAB_00d8b980;  // +0x4C (0x13*4): tertiary vtable

  // Release sub-object pointers (stored at offsets +0x58, +0x60, +0x68, +0x70, +0x74, +0x78, +0x7C)
  FUN_009c8f10(this->subObject1);   // +0x58 (0x16*4)
  FUN_009c8f10(this->subObject2);   // +0x60 (0x18*4)
  FUN_009c8f10(this->subObject3);   // +0x68 (0x1A*4)
  FUN_009c8f10(this->subObject4);   // +0x70 (0x1C*4)
  FUN_009c8f10(this->subObject5);   // +0x74 (0x1D*4)
  FUN_009c8f10(this->subObject6);   // +0x78 (0x1E*4)
  FUN_009c8f10(this->subObject7);   // +0x7C (0x1F*4)

  // Unregister from event system (two callbacks)
  FUN_005c02f0(this->vtable2, &LAB_0094e300, 1);
  FUN_005c02f0(this->vtable2, &LAB_0094e340, 1);

  // Destroy optional owned objects if present
  if (this->ownedObject1 != 0) {       // +0xA8 (0x2A*4)
    (*(code *)this->ownedObject1Dtor)(this->ownedObject1); // +0xB4 (0x2D*4)
  }
  if (this->ownedObject2 != 0) {       // +0x98 (0x26*4)
    (*(code *)this->ownedObject2Dtor)(this->ownedObject2); // +0xA4 (0x29*4)
  }

  // Restore tertiary vtable to base version
  this->vtable3 = &PTR_LAB_00d8b8bc;   // +0x4C: base tertiary vtable

  // Decrement global singleton counter
  g_instanceCount = 0;                 // DAT_0112b9b8
  FUN_005c16e0();                     // Static cleanup
  return;
}