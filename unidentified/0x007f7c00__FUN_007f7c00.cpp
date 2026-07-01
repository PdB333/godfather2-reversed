// FUNC_NAME: SomeClass::isDigitOrColon
// Function address: 0x007f7c00
// Role: Checks if value at offset 0x1010 falls within a specific range (0x2f-0x3b) likely testing if a character is a digit or colon.
// Returns 1 if value is in range [0x2f, 0x3b] (inclusive), else 0.

bool __fastcall SomeClass::isDigitOrColon(int this) {
    int fieldValue = *(int*)(this + 0x1010); // offset 0x1010: some integer field (possibly char code)
    bool result = false;
    if (fieldValue == 0x2f || fieldValue == 0x30 || fieldValue == 0x31 || fieldValue == 0x32 ||
        fieldValue == 0x33 || fieldValue == 0x34 || fieldValue == 0x35 || fieldValue == 0x36 ||
        fieldValue == 0x37 || fieldValue == 0x38 || fieldValue == 0x39 || fieldValue == 0x3a ||
        fieldValue == 0x3b) {
        result = true;
    }
    return result;
}