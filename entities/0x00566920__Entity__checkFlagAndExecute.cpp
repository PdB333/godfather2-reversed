// FUNC_NAME: Entity::checkFlagAndExecute
uint __fastcall Entity::checkFlagAndExecute(void* this) {
    uint flags = *(uint*)((char*)this + 0x2c);
    uint shifted = flags >> 5;
    if ((shifted & 1) != 0) {
        void** subObject = *(void***)((char*)this + 0x0c);
        if (subObject != nullptr) {
            // Call virtual function at vtable+8 (index 2) on subObject
            uint result = (**(uint (__fastcall**)(void*))(*subObject + 8))(); // __fastcall with 'this' in ecx
            if (result == 5) {
                return 1; // Specific state achieved
            }
        }
        // Clear bit 5 of flags (index 5)
        *(uint*)((char*)this + 0x2c) = flags & 0xffffffdf; // Clear bit 5
    }
    // Return the high bits of the original shifted value (bits 13–31 original)
    return shifted & 0xffffff00;
}