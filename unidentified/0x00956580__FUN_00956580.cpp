// FUNC_NAME: SomeClass::clearFlag
// Function address: 0x00956580
// Role: Sets a boolean flag at offset 0x18 to false (0). Likely part of initialization or reset.
void __fastcall SomeClass::clearFlag() {
    *(uint8_t*)(this + 0x18) = 0; // +0x18: bool flag
}