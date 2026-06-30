// FUNC_NAME: Entity::testFlagMask
uint Entity::testFlagMask(uint flags) {
    uint dummy = 0; // Unused output parameter from virtual call
    bool flagSet = (this->*vtable[4])(flags, &dummy); // vtable+0x10 = vtable[4] on 32-bit
    // Return flags if condition met, otherwise 0
    return -(flagSet) & flags;
}