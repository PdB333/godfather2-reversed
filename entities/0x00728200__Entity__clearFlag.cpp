// FUNC_NAME: Entity::clearFlag
// Function address: 0x00728200
// Role: Sets a boolean flag at object offset +0x150 to false (0). Called during initialization or reset.
void __thiscall Entity::clearFlag()
{
    // Offset +0x150 - presumed bool flag (e.g., bActive, bInitialized, or similar state)
    *(uint8_t*)((uintptr_t)this + 0x150) = 0;
}