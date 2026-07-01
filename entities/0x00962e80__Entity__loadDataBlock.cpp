// FUNC_NAME: Entity::loadDataBlock
void __thiscall Entity::loadDataBlock(Entity *this, uint32_t *dataBlock)
{
  uint32_t *dst;
  int i;

  dst = (uint32_t *)((char *)this + 0x1a8); // m_dataBlockOffset (28 dwords, 0x70 bytes)
  for (i = 28; i != 0; i--) {
    *dst = *dataBlock;
    dataBlock++;
    dst++;
  }
  *(uint32_t *)((char *)this + 0x6f4) |= 0x800; // m_flags, set bit 11 (kDataBlockLoaded)
}