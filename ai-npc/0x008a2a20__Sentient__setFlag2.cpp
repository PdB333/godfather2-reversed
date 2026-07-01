// FUNC_NAME: Sentient::setFlag2
void __thiscall Sentient::setFlag2(int this, char value)
{
  if (value != '\0') {
    // Set bit 1 (0x2) at offset +0x37c
    *(uint *)(this + 0x37c) = *(uint *)(this + 0x37c) | 2;
    return;
  }
  // Clear bit 1 (0x2) at offset +0x37c
  *(uint *)(this + 0x37c) = *(uint *)(this + 0x37c) & 0xfffffffd;
  return;
}