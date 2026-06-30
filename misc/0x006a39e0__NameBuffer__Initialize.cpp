// FUNC_NAME: NameBuffer::Initialize
wchar_t* __thiscall NameBuffer::Initialize(wchar_t* this, const wchar_t* src) {
    // Clear two wchar_t fields at offsets +0x40 and +0x42 bytes (indices 0x20, 0x21)
    this[0x20] = L'\0';
    this[0x21] = L'\0';

    // Copy up to 32 wchar_t into the main name buffer (starting at this[0])
    _wcsncpy_s(this, 0x20, src, 0x20);

    // Clear remaining specified fields:
    // Indices 0x22-0x25: byte offsets +0x44, +0x46, +0x48, +0x4A
    this[0x22] = L'\0';
    this[0x23] = L'\0';
    this[0x24] = L'\0';
    this[0x25] = L'\0';

    // Indices 0x3E-0x41: byte offsets +0x7C, +0x7E, +0x80, +0x82
    this[0x3E] = L'\0';
    this[0x3F] = L'\0';
    this[0x40] = L'\0';
    this[0x41] = L'\0';

    return this;
}