// FUNC_NAME: decodeHuffmanCharacter
// Address: 0x00644820
// Purpose: Decodes a variable-length Huffman-coded character from a bit-packed value.
// The input is an integer (likely read from a bitstream) and the function uses bit-shifting
// to determine the character's code length and offset, mapping to ASCII range ['8'..'~'].
int __fastcall decodeHuffmanCharacter(uint32_t encodedValue)
{
    // Check 6-bit code: values [0..32] map to ASCII [0x38..0x58] ('8'..'X')
    if ((encodedValue >> 6) < 0x21) {
        return (encodedValue >> 6) + 0x38;
    }
    // Check 9-bit code: values [0..20] map to ASCII [0x5B..0x6F] ('['..'o')
    if ((encodedValue >> 9) < 0x15) {
        return (encodedValue >> 9) + 0x5B;
    }
    // Check 12-bit code: values [0..10] map to ASCII [0x6E..0x78] ('n'..'x')
    if ((encodedValue >> 12) < 0x0B) {
        return (encodedValue >> 12) + 0x6E;
    }
    // Check 15-bit code: values [0..4] map to ASCII [0x77..0x7B] ('w'..'{')
    if ((encodedValue >> 15) < 5) {
        return (encodedValue >> 15) + 0x77;
    }
    // Check 18-bit code: values [0..2] map to ASCII [0x7C..0x7E] ('|'..'~')
    if ((encodedValue >> 18) < 3) {
        return (encodedValue >> 18) + 0x7C;
    }
    // Fallback: always maps to 0x7E ('~')
    return 0x7E;
}