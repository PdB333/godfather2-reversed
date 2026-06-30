// FUNC_NAME: SomeStruct::constructor
void __fastcall SomeStruct::constructor(undefined4 *this)
{
  *this = 0;                          // +0x00: first dword = 0
  *(undefined2 *)(this + 1) = 0;      // +0x04: first word = 0
  *(undefined2 *)((int)this + 6) = 0; // +0x06: second word = 0
  this[3] = 0;                        // +0x0C: fourth dword = 0
  *(undefined2 *)(this + 2) = 4;      // +0x08: third word = 4 (default value)
  *(undefined2 *)((int)this + 10) = 0; // +0x0A: fourth word = 0
  return;
}