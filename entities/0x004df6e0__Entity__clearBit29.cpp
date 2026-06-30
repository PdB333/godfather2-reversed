// FUNC_NAME: Entity::clearBit29
void __fastcall Entity::clearBit29(int *this)
{
  uint *puVar1;
  
  if (*this != 0) {
    puVar1 = (uint *)(*this + 0xc);
    *puVar1 = *puVar1 & 0xdfffffff;  // Clear bit 29 (0x20000000) of flags at +0x0C
  }
  return;
}