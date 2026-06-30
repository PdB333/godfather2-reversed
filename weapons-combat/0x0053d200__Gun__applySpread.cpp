// FUNC_NAME: Gun::applySpread
void Gun::applySpread(void)
{
    int weaponModeIndex; // from this+0x2a8
    int weaponDataIndex; // from this+0xa4
    void *weaponData;
    float baseSpread;
    float spreadRatio;
    float spreadX, spreadY;
    float finalSpreadX, finalSpreadY;

    // Get weapon mode (e.g., hip fire, aimed) from +0x2a8
    weaponModeIndex = *(int *)(*(int *)(this + 0x2a8) * 0x20 + 0xe8 + this);
    if (weaponModeIndex == 0) {
        return;
    }

    // Get weapon definition pointer based on weapon index (+0xe0)
    if (*(uint *)(this + 0xe0) < 0x1000) {
        weaponData = &weaponDefinitions[*(uint *)(this + 0xe0)];
    } else {
        weaponData = nullptr;
    }

    // Base spread value, depends on weapon mode
    baseSpread = kBaseSpreadHip; // 0x00e2cd14
    if (*(int *)(this + 0x2a8) == 4) { // Aimed mode?
        baseSpread = kBaseSpreadAimed; // 0x00e4475c
    }

    // Spread ratio from accumulated recoil/accuracy (+0x2ac / +0x2b0)
    spreadRatio = *(float *)(this + 0x2ac) / *(float *)(this + 0x2b0);

    // Determine spread values based on weapon state (+0xa4)
    weaponDataIndex = *(int *)(this + 0xa4);
    if (weaponDataIndex == 0) {
        // First state: base spread divided by weapon's horizontal spread factor (+0x2)
        spreadX = baseSpread / (float)*(ushort *)(weaponData + 2);
        spreadY = 0.0f;
    } else {
        spreadX = 0.0f;
    }
    if (weaponDataIndex == 1) {
        // Second state: base spread divided by weapon's vertical spread factor (+0x4)
        baseSpread = baseSpread / (float)*(ushort *)(weaponData + 4);
        spreadX = 0.0f; // Note: spreadX is overwritten from previous block to 0
    }
    // Note: The decompiled code has a logic issue: variables are overwritten.
    // Reconstructed behavior: final spread values are computed separately.
    if (weaponDataIndex == 0) {
        finalSpreadX = spreadRatio / (float)*(ushort *)(weaponData + 2);
    } else {
        finalSpreadX = 0.0f;
    }
    if (weaponDataIndex == 1) {
        spreadRatio = spreadRatio / (float)*(ushort *)(weaponData + 4);
        // In original: local_14 is overwritten, not used again after?
    } else {
        spreadRatio = 0.0f;
    }

    // Apply the spread values via the weapon's bullet spread function
    // Args: object at this+0x14, weaponData pointer, and pointer to spreadX (and others)
    applyBulletSpread(*(void **)(this + 0x14), weaponDataIndex, &spreadX);
}