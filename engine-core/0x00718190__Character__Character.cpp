// FUNC_NAME: Character::Character
void Character::Character(Character *this) {
    // Base class constructor call (FUN_0071d610)
    FUN_0071d610();
    // Initialize fields at offsets +0x90 and +0x94 to zero
    *(int *)((uintptr_t)this + 0x90) = 0; // +0x90
    *(int *)((uintptr_t)this + 0x94) = 0; // +0x94
    // Additional initialization call (FUN_00717850)
    FUN_00717850();
}