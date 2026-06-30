// FUNC_NAME: VariableState::setValue
void __thiscall VariableState::setValue(int this, undefined4 value)
{
  *(undefined4 *)(this + 0x18) = value; // +0x18: value storage
  *(undefined1 *)(this + 0x14) = 2;     // +0x14: state type (e.g., 2 = ACTIVE)
  *(undefined4 *)(this + 0x10) = 9;     // +0x10: status (e.g., 9 = MODIFIED)
  return;
}