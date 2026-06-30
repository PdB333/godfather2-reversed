// FUNC_NAME: Entity::isActiveAndEnabled
bool __thiscall Entity::isActiveAndEnabled(void *this) {
    char virtualResult;
    
    // Call virtual function at vtable+0x180 (likely isActive())
    virtualResult = (*(char (__thiscall **)(void*))(*(int*)this + 0x180))(this);
    
    // Return true only if virtual result is non-zero AND the byte at +0x161 is non-zero
    // Offset 0x161 is likely a member flag like 'bEnabled' or 'bAlive'
    if (virtualResult != '\0' && *(char *)((int)this + 0x161) != '\0') {
        return true;
    }
    return false;
}