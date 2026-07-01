// FUNC_NAME: UnkLocalClass::resetOrInit
void __fastcall UnkLocalClass__resetOrInit(undefined4 *this)
{
  *(this + 4) = 0; // +0x04 some counter/flag
  FUN_009c8f10(*this); // clear or release resource at *this
  *this = 0; // +0x00 pointer or handle to resource
  *(this + 8) = 0; // +0x08 another field
  return;
}