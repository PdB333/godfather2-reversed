// FUNC_NAME: Submission::Constructor
undefined4 * __fastcall Submission::Constructor(undefined4 *this)
{
  this[0] = 0;
  this[1] = 0;
  this[2] = 0;
  this[3] = 0;
  this[5] = 0;
  this[6] = 0;
  this[4] = 2;  // +0x10: some enum or state initialized to 2
  this[7] = 0;  // +0x1c: something zeroed
  _memset(this + 8, 0, 0x30);  // +0x20: zero out 0x30 bytes
  return this;
}