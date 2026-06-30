// FUNC_NAME: Entity::setDestroyedFlag
void __fastcall Entity::setDestroyedFlag(int *this)
{
  uint *flagsPtr;
  
  if (*this != 0) {
    // Access flags at offset +0x0C and set bit 0x20000000 (destroyed flag)
    flagsPtr = (uint *)(*this + 0xc);
    *flagsPtr = *flagsPtr | 0x20000000;
  }
}