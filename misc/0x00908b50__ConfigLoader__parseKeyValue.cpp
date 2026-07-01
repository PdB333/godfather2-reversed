// FUNC_NAME: ConfigLoader::parseKeyValue
void __thiscall ConfigLoader::parseKeyValue(int this, void* parserHandle)
{
    // Initialize parser with the given handle
    ParserInit(parserHandle);
    // Set parser type using a magic constant (likely identifies chunk type)
    ParserSetType(parserHandle, 0xeee614f8);

    char done = ParserIsDone(parserHandle);
    while (done == '\0') {
        ParserNext(parserHandle);
        int type = ParserGetType(parserHandle);
        if (type == 0) {
            // Type 0: value (string/object) -> store at +0x60
            ParserNext(parserHandle);
            uint value = ParserGetString(parserHandle);  // returns a handle or pointer
            StoreStringAt(this + 0x60, value);           // +0x60 is likely a String* or pointer
        }
        else if (type == 1) {
            // Type 1: key (max 16 chars) -> store at +0x50
            ParserNext(parserHandle);
            char* source = (char*)ParserGetString(parserHandle);
            if (source != (char*)0x0) {
                strncpy((char*)(this + 0x50), source, 0x10);
                *(char*)(this + 0x5f) = '\0';  // null-terminate the 16-byte key buffer
            }
        }
        ParserNext(parserHandle);  // advance to the next element
        done = ParserIsDone(parserHandle);
    }
    return;
}