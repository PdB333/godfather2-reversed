// FUNC_NAME: SomeArrayClass::clearArray
void __fastcall SomeArrayClass::clearArray(int *this)
{
  int loopCount;
  
  this[0x12] = 0;  // +0x48: array size/count
  this[2] = 0;     // +0x08: some field
  this[1] = 0;     // +0x04: some field
  *this = 0;       // +0x00: some field
  
  loopCount = 3;
  do {
    // Clear up to 5 elements per iteration, up to max 15 elements
    if ((uint)this[0x12] < 0xf) {
      this[this[0x12] + 3] = 0;  // +0x0C + index*4: clear element
      this[0x12] = this[0x12] + 1;
      if ((uint)this[0x12] < 0xf) {
        this[this[0x12] + 3] = 0;
        this[0x12] = this[0x12] + 1;
        if ((uint)this[0x12] < 0xf) {
          this[this[0x12] + 3] = 0;
          this[0x12] = this[0x12] + 1;
          if ((uint)this[0x12] < 0xf) {
            this[this[0x12] + 3] = 0;
            this[0x12] = this[0x12] + 1;
            if ((uint)this[0x12] < 0xf) {
              this[this[0x12] + 3] = 0;
              this[0x12] = this[0x12] + 1;
            }
          }
        }
      }
    }
    loopCount = loopCount + -1;
  } while (loopCount != 0);
  return;
}