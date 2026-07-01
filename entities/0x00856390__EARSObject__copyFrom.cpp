// FUNC_NAME: EARSObject::copyFrom
int __thiscall EARSObject::copyFrom(int this, int source)
{
  FUN_00856030(source);
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(source + 0xc);
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(source + 0x10);
  *(undefined8 *)(this + 0x14) = *(undefined8 *)(source + 0x14);
  *(undefined4 *)(this + 0x1c) = *(undefined4 *)(source + 0x1c);
  *(undefined8 *)(this + 0x20) = *(undefined8 *)(source + 0x20);
  *(undefined4 *)(this + 0x28) = *(undefined4 *)(source + 0x28);
  *(undefined8 *)(this + 0x2c) = *(undefined8 *)(source + 0x2c);
  *(undefined4 *)(this + 0x34) = *(undefined4 *)(source + 0x34);
  *(undefined8 *)(this + 0x38) = *(undefined8 *)(source + 0x38);
  *(undefined4 *)(this + 0x40) = *(undefined4 *)(source + 0x40);
  return this;
}