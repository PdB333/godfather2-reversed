// FUNC_NAME: AIBrainSniper::constructor
undefined4 * __thiscall AIBrainSniper::constructor(undefined4 *this,undefined4 param_2)

{
  // Call base class constructor (AIBrain::constructor)
  FUN_008ce0f0(param_2);
  
  // Set vtable pointer (likely AIBrainSniper vtable)
  *this = &PTR_FUN_00d7cb18;
  
  // Set AI state machine pointers at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d7cb08;   // +0x3C: default state function pointer
  this[0x12] = &PTR_LAB_00d7cb04;  // +0x48: alternative state function pointer
  
  // Initialize target tracking state with magic numbers
  // These are likely sentinel/initialization values for target struct(s)
  this[0x1b] = 0xbadbadba;         // +0x6C: target1 ID marker (invalid)
  this[0x1c] = 0xbeefbeef;         // +0x70: target1 secondary marker
  this[0x1d] = 0xeac15a55;         // +0x74: target2 ID marker (or alternate)
  this[0x1e] = 0x91100911;         // +0x78: target2 secondary marker
  
  return this;
}