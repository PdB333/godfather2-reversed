// FUN_NAME: EARS::Framework::MultiInheritanceObject::destructorChain
void EARS::Framework::MultiInheritanceObject::destructorChain(void)
{
  // Call virtual destructors of base sub-objects in reverse order
  // This->vtable[0] + 4 -> destructor or cleanup method for base at offset 0
  (**(code **)(*this + 4))();   // this->base1.vtable->destructor()

  // Base at offset 0x38 (sizeof=0x38 bytes)
  BaseSubObject2* base2 = reinterpret_cast<BaseSubObject2*>(reinterpret_cast<char*>(this) + 0x38);
  (**(code **)(*(int*)base2 + 4))();  // base2->vtable->destructor()

  // Base at offset 0x70
  BaseSubObject3* base3 = reinterpret_cast<BaseSubObject3*>(reinterpret_cast<char*>(this) + 0x70);
  (**(code **)(*(int*)base3 + 4))();  // base3->vtable->destructor()

  // Free dynamically allocated memory if present
  if (this->field_0xA8 != NULL) {
    FUN_009c8f10(this->field_0xA8);   // likely operator delete or release
  }

  // Restore vtable pointers to base class vtables (after destructor calls)
  this->base3 = &PTR_FUN_00e3f2d8;   // +0x70 vtable set to base3 vtable
  FUN_004de130();                     // cleanup helper (e.g., decrement refcount)

  this->base2 = &PTR_FUN_00e3f2d0;   // +0x38 vtable set to base2 vtable
  FUN_004de130();

  this->vtable = &PTR_FUN_00e3f2c8;  // +0x00 vtable set to base1 vtable
  FUN_004de130();
}