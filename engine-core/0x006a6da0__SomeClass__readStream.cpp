// FUNC_NAME: SomeClass::readStream
void __thiscall SomeClass::readStream(void* thisPtr, undefined4 stream) {
    char isEnd;
    int type;
    undefined4 value;

    FUN_0046c710(stream);                   // Possibly initialize stream reading
    FUN_0043aff0(stream, 0xadc23d35);       // Read magic number for version check
    isEnd = FUN_0043b120();                 // Check if end of stream
    do {
        if (isEnd != 0) {
            return;
        }
        FUN_0043b210();                     // Advance to next token?
        type = FUN_0043ab70();              // Read type identifier (0, 1, or 2)
        if (type == 0) {
            FUN_0043b210();                 // Skip or read next?
            value = FUN_0043ab90();         // Read a value
            int fieldOffset = (int)thisPtr + 0x50;
            FUN_004089b0(fieldOffset, value); // Assign to field at +0x50
        } else if (type == 1) {
            FUN_0043b210();
            value = FUN_0043ab90();
            int fieldOffset = (int)thisPtr + 0x58;
            FUN_004089b0(fieldOffset, value); // Assign to field at +0x58
        } else if (type == 2) {
            int fieldOffset = (int)thisPtr + 0x60;
            FUN_0043b210(fieldOffset);      // Possibly prepare field for complex read
            FUN_0043ad10(fieldOffset);      // Read complex data (e.g., string)
        }
        FUN_0043b1a0();                     // Finalize token read?
        isEnd = FUN_0043b120();             // Check end again
    } while (true);
}