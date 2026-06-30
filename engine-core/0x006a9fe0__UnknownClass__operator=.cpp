// FUNC_NAME: UnknownClass::operator=
int __thiscall UnknownClass::operator=(UnknownClass *this, UnknownClass *other)
{
  // Self-assignment check: if same object, skip copy
  if (this != other) {
    // Copy members at offsets +4, +0x14, +0x24, +0x34 (16-byte objects each)
    // FUN_004d3e20 likely a copy function for a 16-byte type (e.g., struct Vec4 or Matrix44)
    FUN_004d3e20((int)this + 4, (int)other + 4);        // +0x04: field1
    FUN_004d3e20((int)this + 0x14, (int)other + 0x14);  // +0x14: field2
    FUN_004d3e20((int)this + 0x24, (int)other + 0x24);  // +0x24: field3
    FUN_004d3e20((int)this + 0x34, (int)other + 0x34);  // +0x34: field4

    // Copy members at offsets +0x44, +0x4c, +0x54, +0x5c (8-byte objects each)
    // FUN_004080d0 likely a copy function for an 8-byte type (e.g., struct Vec2 or int64)
    FUN_004080d0((int)this + 0x44, (int)other + 0x44);  // +0x44: field5
    FUN_004080d0((int)this + 0x4c, (int)other + 0x4c);  // +0x4c: field6
    FUN_004080d0((int)this + 0x54, (int)other + 0x54);  // +0x54: field7
    FUN_004080d0((int)this + 0x5c, (int)other + 0x5c);  // +0x5c: field8

    // Copy remaining data fields
    *(int *)((int)this + 100) = *(int *)((int)other + 100);   // +0x64: 4-byte integer
    *(char *)((int)this + 0x68) = *(char *)((int)other + 0x68); // +0x68: 1-byte field
  }
  return (int)this;
}