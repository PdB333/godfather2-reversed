// FUNC_NAME: GodfatherFunObject::initSomeState
void __fastcall GodfatherFunObject::initSomeState(int this)
{
  *(undefined4 *)(this + 0x54) = _DAT_00d5780c; // +0x54: some timer or state flag
  *(undefined4 *)(this + 0x50) = *(undefined4 *)(this + 0x24); // +0x50: copy from +0x24 (likely a pointer or value)
  *(undefined4 *)(this + 0x58) = 0; // +0x58: initialize to 0 (counter or flag)
  *(undefined1 *)(this + 8) = 0; // +0x08: clear first byte (bool/flag)
  return;
}