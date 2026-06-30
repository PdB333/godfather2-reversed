// FUNC_NAME: Entity::isActive
__thiscall unsigned char Entity::isActive(int this)
{
    // Check if the initialization guard bit (0x8A bit 5) is set
    if ((*(unsigned char *)(this + 0x8A) & 0x20) == 0) {
        FUN_006e6700(); // Ensure flags are initialized
    }
    // Return the state of the active flag at byte +0x89, bit 3
    return (*(unsigned char *)(this + 0x89) >> 3) & 1;
}