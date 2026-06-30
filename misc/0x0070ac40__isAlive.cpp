// FUNC_NAME: isAlive
// Address: 0x0070ac40
// Checks if the object is alive (active and not destroyed)

bool isAlive() {
    // Virtual function at vtable+0x180: typically "isActive" or "isEnabled"
    // Returns true if the object is currently active (not in a dormant state)
    bool isActive = reinterpret_cast<bool (__thiscall *)(void*)>( 
        *(void**)(*(int*)this + 0x180) 
    )(this);

    // Offset 0x161: usually a "destroyed" or "dead" flag (0 = not destroyed, 1 = destroyed)
    bool isDestroyed = *(char*)((char*)this + 0x161) != 0;

    // Object is considered alive only if active AND not destroyed
    return isActive && !isDestroyed;
}