// FUNC_NAME: Player::Player
undefined4 * __thiscall Player::Player(Player *this, byte isHeapAllocated)
{
  // Set vtable pointer (main vtable for Player)
  this->vtable = &PTR_FUN_00d69bbc;
  // Set vtable at offset +0x3C (probably base class 1, e.g., Sentient)
  *(void ***)((char *)this + 0x3C) = &PTR_LAB_00d69bac;
  // Set vtable at offset +0x48 (probably base class 2, e.g., PlayerActionableInfo)
  *(void ***)((char *)this + 0x48) = &PTR_LAB_00d69ba8;

  // Initialize global state (e.g., static mutex, singleton)
  BaseClass::initializeGlobal(&DAT_0120e93c);
  // Perform common initialization (likely sets default values for internal fields)
  this->initializeSubsystem();

  // If object was heap-allocated (bit 0 of isHeapAllocated set), call operator delete
  // This is a protection mechanism in case of construction failure – but here it's always after success?
  // Actually, in this engine, the constructor itself may conditionally free memory if the flag indicates allocation.
  if ((isHeapAllocated & 1) != 0) {
    Engine::operatorDelete(this, 0xB0); // size 176 bytes = sizeof(Player)
  }
  return this;
}