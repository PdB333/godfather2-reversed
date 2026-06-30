// FUNC_NAME: CThreeListContainer::CThreeListContainer
undefined4 * __thiscall CThreeListContainer::CThreeListContainer(undefined4 *this, byte param_2)
{
  // Set vtable pointer for most derived class
  *this = &PTR_FUN_00d5eb60;
  // Set base class vtable pointers for multiple inheritance
  this[0xf] = &PTR_LAB_00d5eb50;   // offset +0x3C (60)
  this[0x12] = &PTR_LAB_00d5eb4c;  // offset +0x48 (72)
  // Initialize the first internal list/queue at offset +0x58 (88)
  FUN_004086d0(this + 0x16);       // generic constructor (e.g., list init)
  FUN_00408310(this + 0x16);       // reset/clear list
  // Initialize the second internal list/queue at offset +0x60 (96)
  FUN_00408310(this + 0x18);       // reset/clear (constructor already called? note: no FUN_004086d0 call, but likely constructor was already called inline? Might be a bug or design)
  // Initialize the third internal list/queue at offset +0x68 (104)
  FUN_00408310(this + 0x1a);       // reset/clear
  // Call a global initializer function
  FUN_0046c640();                  // global state setup
  // If flag bit 0 is set, free this object (operator delete with size 0x70)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0x70);
  }
  return this;
}