// FUNC_NAME: isFlag0Set
// Function at 0x00716790: Returns the lowest bit of a byte at offset 0x154 (likely a flag field).
byte __fastcall isFlag0Set(int thisPtr) {
    return *(byte *)(thisPtr + 0x154) & 1;
}