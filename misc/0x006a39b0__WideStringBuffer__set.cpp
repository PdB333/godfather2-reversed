// FUNC_NAME: WideStringBuffer::set
wchar_t* __thiscall WideStringBuffer::set(wchar_t* source) {
    // Ensure null termination at the end of the buffer (size = 0x22 wchar_t)
    // +0x40: index 0x20 (32nd wchar_t) and +0x42: index 0x21 (33rd wchar_t)
    this->buffer[0x20] = L'\0';
    this->buffer[0x21] = L'\0';

    // Copy at most 0x1F (31) characters from source into buffer, then append null
    // _wcsncpy_s(dest, destSize, src, srcLen)
    _wcsncpy_s(this->buffer, 0x20, source, 0x20);

    return this->buffer;
}