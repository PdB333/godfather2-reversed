// FUNC_NAME: UTF8Encoder::encodeCodepoint
void UTF8Encoder::encodeCodepoint(uint codepoint)
{
  uint encodedByte;

  if ((ushort)codepoint < 0x80) {
    // Single byte (0xxxxxxx) for ASCII range
    FUN_004d44b0(codepoint);
    return;
  }
  if ((ushort)codepoint < 0x800) {
    // Two bytes (110xxxxx 10xxxxxx)
    encodedByte = codepoint >> 6 & 0xffffff1f | 0xffffffc0;
  }
  else {
    // Three bytes (1110xxxx 10xxxxxx 10xxxxxx)
    // First byte: high 4 bits of codepoint
    FUN_004d44b0(codepoint >> 0xc & 0xffffff0f | 0xffffffe0);
    // Second byte: next 6 bits
    encodedByte = codepoint >> 6 & 0xffffff3f | 0xffffff80;
  }
  // Output second or third byte (10xxxxxx)
  FUN_004d44b0(encodedByte);
  // Output last byte (10xxxxxx) for two/three byte sequences
  FUN_004d44b0(codepoint & 0xffffff3f | 0xffffff80);
  return;
}