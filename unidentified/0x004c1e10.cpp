// FUN_004c1e10: EARSObject::queryInterface
bool __thiscall EARSObject::queryInterface(int interfaceHash, int* outInterface) {
    // Check for known interface identifiers (likely hash values from EA's container system)
    if (interfaceHash == 0xD16A98A9) {
        *outInterface = reinterpret_cast<int>(this);
        return true;
    }

    *outInterface = 0;
    if (interfaceHash == 0x38523FC3) {
        *outInterface = reinterpret_cast<int>(this);
    }

    return *outInterface != 0;
}