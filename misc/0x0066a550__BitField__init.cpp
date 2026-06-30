// FUNC_NAME: BitField::init
void BitField::init(void)
{
  uint *thisPtr; // unaff_ESI
  uint mask; // in_EAX

  thisPtr[2] = 0; // +0x08: bit count
  *thisPtr = 0;   // +0x00: initialized flag
  _memset((void *)thisPtr[3], 0, thisPtr[1] * 4); // +0x0C: buffer, +0x04: buffer size in dwords
  *(uint *)thisPtr[3] = mask & 0xfffffff; // store first dword with mask (27 bits)
  *thisPtr = (uint)(*(int *)thisPtr[3] != 0); // set initialized flag if any bits set
  return;
}