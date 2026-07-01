// FUNC_NAME: SomeClass::renderOrUpdateSomething
void SomeClass::renderOrUpdateSomething(int param_1)
{
  if ((*(byte *)(param_1 + 0x170) & 1) != 0) {
    // +0x170: flags byte, bit 0 indicates some mode (e.g., debug/editor mode)
    // +0x88: some pointer (e.g., renderer or context)
    // +0x98: some data buffer (e.g., transform or state)
    // +0x7c: some parameter (e.g., time delta or ID)
    FUN_0093f540(*(undefined4 *)(param_1 + 0x88), param_1 + 0x98, 0, *(undefined4 *)(param_1 + 0x7c), 0);
    return;
  }
  // Normal path: use a label/callback address (LAB_00922890) instead of null
  FUN_0093f540(*(undefined4 *)(param_1 + 0x88), param_1 + 0x98, &LAB_00922890,
               *(undefined4 *)(param_1 + 0x7c), 0);
  return;
}