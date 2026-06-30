// FUNC_NAME: PathUtils::normalizeSlashes
void __fastcall PathUtils::normalizeSlashes(int *this)
{
  uint index = 0;
  if (this[1] != 0) { // +0x04: string length
    do {
      if (*(char *)(*this + index) == '\\') { // +0x00: pointer to string buffer
        *(char *)(*this + index) = '/';
      }
      index = index + 1;
    } while (index < (uint)this[1]); // iterate over all characters
  }
  return;
}