// FUNC_NAME: ControllerState::ControllerState
// Function at 0x00480020, constructor for controller state object
// Structure layout (offsets in bytes):
//   +0x00: vtable pointer (PTR_FUN_00e33384)
//   +0x3C: pointer to interface vtable (PTR_LAB_00e333a0)
//   +0x48: pointer to another interface vtable (PTR_LAB_00e333b0)
//   +0x50: stateArray[32] (uint32)
//   +0xD0: field1 (uint32)
//   +0xD4: field2 (uint16)
//   +0xD6: field3 (uint16)
//   +0xD8: field4 (uint32)
//   +0xDC: field5 (uint16)
//   +0xDE: field6 (uint16)

ControllerState * __thiscall ControllerState::ControllerState(ControllerState *this, uint32_t initParam)
{
  // Call base class constructor (unknown base)
  FUN_0046c590(initParam);
  
  // Set up vtable pointers
  this->vtable = (ControllerStateVtable *)&PTR_FUN_00e33384;
  this->interface1Vtable = (Interface1Vtable *)&PTR_LAB_00e333a0;  // +0x3C
  this->interface2Vtable = (Interface2Vtable *)&PTR_LAB_00e333b0;  // +0x48
  
  // Zero out the 32-element state array (indices 0x14..0x33, offsets 0x50..0xCC)
  // The compiler unrolled the loop in a specific order; we just zero them all.
  uint32_t *stateArray = &this->stateArray[0];  // +0x50
  for (int i = 0; i < 32; i++) {
    stateArray[i] = 0;
  }
  
  // Zero out the remaining fields
  this->field1 = 0;  // +0xD0 (uint32)
  *(uint16 *)((uint8_t *)this + 0xD4) = 0;  // +0xD4 (uint16)
  *(uint16 *)((uint8_t *)this + 0xD6) = 0;  // +0xD6 (uint16)
  
  this->field4 = 0;  // +0xD8 (uint32)
  *(uint16 *)((uint8_t *)this + 0xDC) = 0;  // +0xDC (uint16)
  *(uint16 *)((uint8_t *)this + 0xDE) = 0;  // +0xDE (uint16)
  
  return this;
}