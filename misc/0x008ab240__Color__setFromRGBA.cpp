// FUNC_NAME: Color::setFromRGBA
void __thiscall Color::setFromRGBA(int this, int otherColor, undefined1 *alphaByte, undefined4 unused)
{
  // Copy RGBA values from source structure at otherColor+4 through otherColor+0x1C (6 floats? actually 6 uint32s)
  *(undefined4 *)(this + 0x14) = *(undefined4 *)(otherColor + 4);    // +0x14 = red?
  *(undefined4 *)(this + 0x18) = *(undefined4 *)(otherColor + 8);    // +0x18 = green?
  *(undefined4 *)(this + 0x1c) = *(undefined4 *)(otherColor + 0xc);  // +0x1c = blue?
  *(undefined4 *)(this + 0x20) = *(undefined4 *)(otherColor + 0x10); // +0x20 = alpha?
  *(undefined4 *)(this + 0x24) = *(undefined4 *)(otherColor + 0x14); // +0x24 = extra?
  *(undefined4 *)(this + 0x28) = *(undefined4 *)(otherColor + 0x18); // +0x28 = ?
  *(undefined4 *)(this + 0x2c) = *(undefined4 *)(otherColor + 0x1c); // +0x2c = ?
  *(undefined1 *)(this + 0x30) = *alphaByte;                        // +0x30 = explicit alpha byte override
  FUN_008a85f0(unused);                                              // Possibly finalize/validate
  return;
}