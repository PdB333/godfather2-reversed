// FUNC_NAME: Rect::set
void __thiscall Rect::set(int *this, int x, int y, int width, int height, int param6, int param7)
{
  this[2] = width;   // +0x08: rect width
  this[3] = param6;  // +0x0C: unknown (possibly bottom or right)
  this[4] = height;  // +0x10: rect height
  this[5] = param7;  // +0x14: unknown (possibly bottom or right)
  this[0] = x;       // +0x00: rect left/top x
  this[1] = y;       // +0x04: rect top y
  this[6] = 0;       // +0x18: initialize to zero (possibly flags or padding)
  return;
}