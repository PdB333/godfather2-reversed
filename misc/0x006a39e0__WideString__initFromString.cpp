// FUNC_NAME: WideString::initFromString
wchar_t* __thiscall WideString::initFromString(wchar_t* this, wchar_t* source)
{
  // Zero out the first two fields after the main buffer
  this[0x20] = L'\0';
  this[0x21] = L'\0';

  // Copy source into the main buffer (max 0x20 wchar_t)
  _wcsncpy_s(this, 0x20, source, 0x20);

  // Zero out additional fields at various offsets
  this[0x22] = L'\0';
  this[0x23] = L'\0';
  this[0x24] = L'\0';
  this[0x25] = L'\0';
  this[0x3e] = L'\0';
  this[0x3f] = L'\0';
  this[0x40] = L'\0';
  this[0x41] = L'\0';

  return this;
}