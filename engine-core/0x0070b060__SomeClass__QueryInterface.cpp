// FUNC_NAME: SomeClass::QueryInterface
int __thiscall SomeClass::QueryInterface(uint typeId, void** outPtr)
{
    // Known interface IDs: 0x32223764 and 0xFFD2E5B1
    if (typeId == 0x32223764) {
        if (outPtr != nullptr) {
            *outPtr = this;
            return 1;
        }
    }
    else {
        if (outPtr != nullptr) {
            *outPtr = nullptr;
        }
        // Check for second interface (negative constant)
        if (typeId != 0xFFD2E5B1) {
            return 0;
        }
        if (outPtr != nullptr) {
            *outPtr = this;
        }
    }
    return 1;
}