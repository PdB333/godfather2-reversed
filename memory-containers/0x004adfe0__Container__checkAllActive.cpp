// FUNC_NAME: Container::checkAllActive
byte Container::checkAllActive() {
    byte result = 1;
    undefined4* current = (undefined4*)((uint)this + 8); // begin of array at +0x08
    for (uint i = 0; i < *(uint*)((uint)this + 4); i++) { // count at +0x04
        byte itemActive = FUN_00621450(*current); // check first dword of each 20-byte element
        result &= itemActive;
        current += 5; // advance 20 bytes (5 * sizeof(int))
    }
    return result;
}