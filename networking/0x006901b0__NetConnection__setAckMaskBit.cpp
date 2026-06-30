// FUNC_NAME: NetConnection::setAckMaskBit
void __thiscall NetConnection::setAckMaskBit(void *this, uint bitIndex)
{
  uint *ackMaskArray = (uint *)((int)this + 0x249c);
  uint maskIndex = bitIndex >> 5; // divide by 32 to get uint array index
  uint bitInWord = 1 << (bitIndex & 0x1f);
  ackMaskArray[maskIndex] |= bitInWord;
  return;
}