//FUNC_NAME: Sentient::isDeadOrInvulnerable
bool __thiscall Sentient::isDeadOrInvulnerable(int* thisPtr) {
    // Call virtual function at vtable+0xC0 (likely getHealth or getHitPoints)
    float health = (*(float (__thiscall**)(int*))(*(int*)thisPtr + 0xC0))(thisPtr);
    
    // Check if health > 0 and bit 17 (0x20000) of flags at offset 0x8E0 is not set
    // Bit 17 likely indicates invulnerability or similar
    if ((health > 0.0f) && (((uint)thisPtr[0x238] >> 0x11 & 1) == 0)) {
        return false; // Alive and vulnerable -> not dead or invulnerable
    }
    return true; // Dead or invulnerable
}