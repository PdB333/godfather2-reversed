// FUNC_NAME: SimNpc::SimNpc
// Constructor for SimNpc class (size 0xB0)
// Vtable pointers at +0x00 (Entity base) and +0x30 (Sentient base)
// param_2: bit 0 set if object was allocated on heap (placement delete guard)
undefined4 * __thiscall SimNpc::SimNpc(SimNpc *this, byte flags)
{
  int *allocatorPtr;
  
  this->vtableEntity = &PTR_FUN_00d738e0;  // +0x00: Entity vtable
  Entity::Entity(this);                     // FUN_0082a380 - base Entity constructor
  this->vtableSentient = &PTR_LAB_00e32854; // +0x30: Sentient vtable
  Sentient::Sentient(this);                 // FUN_00821f60 - base Sentient constructor
  if ((flags & 1) != 0) {
    allocatorPtr = (int *)Allocator::getSingleton(); // FUN_009c8f80
    (**(code **)(*allocatorPtr + 4))(this, 0xB0);  // placement delete guard
  }
  return this;
}