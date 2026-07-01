// FUNC_NAME: PlayerStats::setStatLimits
void __thiscall PlayerStats::setStatLimits(int thisPtr, int maxHealth, int maxArmor, int maxAmmo, int maxGrenades, int maxMolotovs)
{
    // Clamp maxHealth to [0, 3000] and store at +0x8C
    int clampedHealth = maxHealth;
    if (maxHealth < 0) {
        clampedHealth = 0;
    } else if (maxHealth > 3000) {
        clampedHealth = 3000;
    }
    *(int *)(thisPtr + 0x8C) = clampedHealth;

    // Clamp maxArmor to [0, 364] and store at +0x90
    int clampedArmor = maxArmor;
    if (maxArmor < 0) {
        clampedArmor = 0;
    } else if (maxArmor > 364) {
        clampedArmor = 364;
    }
    *(int *)(thisPtr + 0x90) = clampedArmor;

    // Clamp maxAmmo to [0, 23] and store at +0x94
    int clampedAmmo = maxAmmo;
    if (maxAmmo < 0) {
        clampedAmmo = 0;
    } else if (maxAmmo > 23) {
        clampedAmmo = 23;
    }
    *(int *)(thisPtr + 0x94) = clampedAmmo;

    // Clamp maxGrenades to [0, 59] and store at +0x98
    int clampedGrenades = maxGrenades;
    if (maxGrenades < 0) {
        clampedGrenades = 0;
    } else if (maxGrenades > 59) {
        clampedGrenades = 59;
    }
    *(int *)(thisPtr + 0x98) = clampedGrenades;

    // Clamp maxMolotovs to [0, 59] and store at +0x9C
    int clampedMolotovs = maxMolotovs;
    if (maxMolotovs < 0) {
        clampedMolotovs = 0;
    } else if (maxMolotovs > 59) {
        clampedMolotovs = 59;
    }
    *(int *)(thisPtr + 0x9C) = clampedMolotovs;
}