// FUNC_NAME: SomeClass::getSomeByteField
void __thiscall getSomeByteField(int thisPtr, undefined1 *outByte)
{
  // Dereference pointer at this+0x18, then read byte at offset 0x10 from that pointer
  *outByte = *(undefined1 *)(*(int *)(thisPtr + 0x18) + 0x10);
  return;
}