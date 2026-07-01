//FUNC_NAME: Player::clampHealthToMax
// Function address: 0x00989430
// Role: Clamps the current health value to the maximum health value, then calls a setter.
// Offsets: +0x68 = current health, +0x70 = maximum health

void __fastcall Player::clampHealthToMax(Player* this)
{
    int clampedHealth;
    int currentHealth = *(int*)((char*)this + 0x68); // current health
    int maxHealth = *(int*)((char*)this + 0x70);     // maximum health

    // Take the minimum of current and max health
    if (maxHealth <= currentHealth) {
        clampedHealth = maxHealth;
    } else {
        clampedHealth = currentHealth;
    }

    // Call the setter with the clamped value
    FUN_009893a0(clampedHealth);
}