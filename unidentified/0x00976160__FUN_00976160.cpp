// FUNC_NAME: SomeClass::initializeSomeState
void __fastcall initializeSomeState(int this)
{
  *(uint *)(this + 0x60) = *(uint *)(this + 0x60) | 0x2000; // Set flag at +0x60 bit 0x2000
  *(undefined4 *)(this + 0x7c) = DAT_011280f0; // +0x7c: copy from global
  *(undefined4 *)(this + 0x80) = DAT_011280f4; // +0x80: copy from global
  *(undefined4 *)(this + 0x84) = DAT_011280f8; // +0x84: copy from global
  *(undefined4 *)(this + 0x88) = DAT_0110ac8c; // +0x88: copy from global
  *(undefined4 *)(this + 0x8c) = DAT_0110ac34; // +0x8c: copy from global
  DAT_0110ac34 = DAT_00d64cc0; // Update global from another global
  DAT_011280f0 = DAT_00d5efb8; // Update global from another global
  DAT_011280f4 = DAT_00e448d8; // Update global from another global
  DAT_011280f8 = DAT_00d8b2a8; // Update global from another global
  DAT_0110ac8c = DAT_00e575a0; // Update global from another global
  DAT_0110acc8 = 0; // Reset global to zero
  return;
}