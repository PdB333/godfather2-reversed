// FUNC_NAME: Component::setTargetActive
void __thiscall Component::setTargetActive(char isActive)
{
    // this->m_pTargetEntity (offset +0x8) is a pointer to an entity object
    int* entityPtr = *(int**)(this + 8);
    if (entityPtr != nullptr) {
        // Entity offset +0x33c is an active flag (byte)
        *(char*)(entityPtr + 0x33c) = isActive;
    }

    // this->m_flags (offset +0x2c) bit 0 tracks local active state
    if (isActive != '\0') {
        *(uint*)(this + 0x2c) |= 1;
    } else {
        *(uint*)(this + 0x2c) &= ~1;
    }
}