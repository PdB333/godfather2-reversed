// FUNC_NAME: Entity::packBits
void __thiscall Entity::packBits(int this, uint param_2, uint param_3, uint param_4)
{
  // Pack three bitfields into a single value and call the underlying pack function
  // The packing order: (in_EAX << 9 | param_3) << 9 | param_4) << 6 | param_2
  // This suggests in_EAX is a 9-bit value, param_3 is 9-bit, param_4 is 9-bit, param_2 is 6-bit
  // Total: 9 + 9 + 9 + 6 = 33 bits (stored in a 32-bit value, likely overflow is intentional or in_EAX is actually 8-bit)
  // +0x0c: pointer to some data structure, +0x08: offset within that structure for the pack function
  FUN_006438e0(((in_EAX << 9 | param_3) << 9 | param_4) << 6 | param_2,
               *(undefined4 *)(*(int *)(this + 0xc) + 8));
  return;
}