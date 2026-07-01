// FUNC_NAME: SomeClass::resetState
void __fastcall SomeClass::resetState(float *this)
{
  float *src;
  float *dst;
  float count;
  int size;
  
  src = this + 0x11;
  *this = this[4] + *this;
  FUN_008929c0(this + 5);
  FUN_008929c0(this + 5);
  count = 0.0;
  dst = this + 0x1d;
  if (this[0x1c] != 0.0) {
    size = (int)src - (int)dst;
    do {
      count = (float)((int)count + 1);
      *dst = *(float *)(size + (int)dst);
      dst = dst + 1;
    } while ((uint)count < (uint)this[0x1c]);
  }
  src[0] = 0.0;
  src[1] = 0.0;
  this[0x13] = 0.0;
  this[0x14] = 0.0;
  this[0x15] = 0.0;
  this[0x16] = 0.0;
  this[0x17] = 0.0;
  this[0x18] = 0.0;
  this[0x19] = 0.0;
  this[0x1a] = 0.0;
  this[0x1b] = 0.0;
  return;
}