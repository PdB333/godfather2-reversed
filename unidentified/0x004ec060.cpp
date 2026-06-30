// FUN_004ec060: SomeClass::queryInterface

bool __thiscall SomeClass::queryInterface(uint32_t interfaceId, void** outInterface)
{
    if (interfaceId == 0x63931d0e) {
        if (outInterface != nullptr) {
            *outInterface = this;
            return true;
        }
        // If outInterface is null, just return true; no pointer written.
    } else {
        if (outInterface != nullptr) {
            *outInterface = nullptr;
        }
        // Second supported interface ID: 0xFFD2E5B1 (== -0x2d1a4f)
        if (interfaceId == 0xFFD2E5B1) {
            if (outInterface != nullptr) {
                *outInterface = this;
            }
            return true;
        }
        // Unsupported interface ID
        return false;
    }
    return true;
}