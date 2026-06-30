// FUNC_NAME: SomeClass::setColor
void __thiscall SomeClass::setColor(int this, undefined4 *color)
{
  undefined4 r;
  undefined4 g;
  undefined4 b;
  
  r = color[1];
  g = color[2];
  *(undefined4 *)(this + 0x40) = *color;  // +0x40: red component
  *(undefined4 *)(this + 0x44) = r;       // +0x44: green component
  g = DAT_00e2b1a4;                        // global alpha value
  *(undefined4 *)(this + 0x48) = g;       // +0x48: blue component
  *(undefined4 *)(this + 0x4c) = g;       // +0x4c: alpha component
  return;
}