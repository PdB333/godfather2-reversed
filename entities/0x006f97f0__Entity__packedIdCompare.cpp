// FUNC_NAME: Entity::packedIdCompare
uint __thiscall Entity::packedIdCompare(void *this, int compareId)
{
  int storedVal = *(int *)((char *)this + 0x3c); // +0x3c: stored identifier/pointer

  if (storedVal != 0) {
    int adjusted = storedVal - 0x48;              // subtract offset to get base value
    // Pack high 24 bits of adjusted and low byte of equality check
    return ((uint)((uint)adjusted >> 8) << 8) | (uint)(adjusted == compareId);
  }
  return (uint)(compareId == 0);
}