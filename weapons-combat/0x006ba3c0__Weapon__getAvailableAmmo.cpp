// FUNC_NAME: Weapon::getAvailableAmmo
// Address: 0x006ba3c0
// Role: Computes available ammo for a weapon considering capacity percentage, spent ammo, and a no-ammo flag.

unsigned int __thiscall Weapon::getAvailableAmo(void *this) // this is param_1
{
    unsigned int ammoTypeIndex = *(int *)((unsigned char *)this + 0x90);        // +0x90: ammo type index
    unsigned int totalAmmo = *(unsigned int *)((unsigned char *)this + 0x98);   // +0x98: total ammo for this type
    unsigned int capacityPercent = *(unsigned int *)((unsigned char *)this + 0xb8 + ammoTypeIndex * 12); // per-type capacity percentage (0-100)
    unsigned int adjustedAmmo = 0;

    if (capacityPercent < 100) {
        unsigned int allowed = (capacityPercent * totalAmmo) / 100; // max ammo allowed by capacity
        unsigned int spentAmmo = *(unsigned int *)((unsigned char *)this + 0x94); // +0x94: ammo already used (e.g., in magazine)
        if (spentAmmo < allowed) {
            allowed -= spentAmmo; // remaining capacity
        } else {
            allowed = 0;
        }
        if (allowed < totalAmmo) {
            adjustedAmmo = allowed;
        } else {
            adjustedAmmo = totalAmmo;
        }
    } else {
        adjustedAmmo = totalAmmo; // capacity >=100% means no restriction
    }

    // Check for a no-ammo override flag.
    void *overrideComponent = *(void **)((unsigned char *)this + 0x9c); // +0x9c: pointer to a state component (e.g., WeaponComponent)
    if (overrideComponent != (void *)0) {
        unsigned int componentFlags = *(unsigned int *)((unsigned char *)overrideComponent + 0x34); // +0x34: flags
        // Bit 8 (value 0x100) of flags indicates "no ammo" state
        if (((unsigned char)(componentFlags >> 8) ^ 0xFF) & 1) {
            return 0;
        }
    }

    return adjustedAmmo;
}