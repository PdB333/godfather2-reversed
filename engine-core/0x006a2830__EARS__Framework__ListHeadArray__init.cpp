// FUNC_NAME: EARS::Framework::ListHeadArray::init
void __fastcall ListHeadArray::init(uint *param_1)
{
  // Initialize an array of 6 list head slots.
  // Each slot consists of a vtable pointer and a self-pointer (used as sentinel for circular list).
  // Offsets: slot0 at +0x00, slot1 at +0x08, ..., slot5 at +0x28
  // After the slots, there are two additional fields at +0x30 and +0x34 (likely element count and capacity).
  param_1[0] = (uint)&PTR_FUN_00d5d3c0;      // +0x00: vtable for slot0
  param_1[2] = (uint)&PTR_FUN_00d5d3c0;      // +0x08: vtable for slot1
  param_1[4] = (uint)&PTR_FUN_00d5d3c0;      // +0x10: vtable for slot2
  param_1[6] = (uint)&PTR_FUN_00d5d3c0;      // +0x18: vtable for slot3
  param_1[8] = (uint)&PTR_FUN_00d5d3c0;      // +0x20: vtable for slot4
  param_1[10] = (uint)&PTR_FUN_00d5d3c0;     // +0x28: vtable for slot5
  
  param_1[0xc] = 0;                          // +0x30: count? (initialized to 0)
  param_1[0xd] = 0;                          // +0x34: capacity? (initialized to 0)
  
  // Each slot's self-pointer points back to the beginning of its own node
  // (creates a circular empty list where next/prev point to self).
  param_1[1] = (uint)(param_1);              // +0x04: slot0 self pointer -> itself
  param_1[3] = (uint)(param_1);              // +0x0c: slot1 self pointer -> itself (same address? likely param_1+0x08? Actually the self-pointer for slot1 should point to slot1's node, not the start. But the decompilation shows all set to param_1, which is the base. This may be an artifact of the decompiler, or the slots share the same sentinel? Probably it's a bug in decompilation; each should point to its own slot. But we'll keep as is to match the code exactly.)
  param_1[5] = (uint)(param_1);
  param_1[9] = (uint)(param_1);
  param_1[7] = (uint)(param_1);
  param_1[0xb] = (uint)(param_1);
  return;
}