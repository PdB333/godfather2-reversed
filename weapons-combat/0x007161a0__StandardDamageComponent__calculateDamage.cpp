// FUNC_NAME: StandardDamageComponent::calculateDamage
// Function at 0x007161a0
// Computes random damage based on weapon damage table, critical hit, and damage reduction flag.
int __fastcall StandardDamageComponent::calculateDamage(void* thisPtr) {
    int isCombat;                // result of isCombatActive()
    unsigned int damageIndex;    // random index into weapon table
    void* damageTable;           // this+0x24, pointer to weapon/table
    void* owner;                 // this+0x18, pointer to character/owner
    unsigned int ownerFlags;     // owner flags at +0x8e4
    unsigned int baseDamage;     // base damage from table or fallback
    char isCritical;             // result of isCriticalHit()
    int result;                  // final damage

    isCombat = isCombatActive();          // FUN_00800a90
    result = 0;
    if (isCombat != 0) {
        damageIndex = getRandomSeed();    // FUN_00701050, returns unsigned int
        damageTable = *(void**)((int)thisPtr + 0x24);
        owner = *(void**)((int)thisPtr + 0x18);
        baseDamage = damageIndex;         // fallback if owner or table null

        if (owner != 0) {
            ownerFlags = *(unsigned int*)((int)owner + 0x8e4);
            if ((ownerFlags >> 0xe) & 1) == 0) {
                if (damageTable != 0) {
                    baseDamage = *(unsigned int*)((int)damageTable + 0x88 + damageIndex * 4);
                }
            } else {
                if (damageTable != 0) {
                    baseDamage = *(unsigned int*)((int)damageTable + 0x9c + damageIndex * 4);
                }
            }
        }

        isCritical = isCriticalHit();      // FUN_00701010
        if (isCritical != 0) {
            // Critical: random between base/2 and base, plus another base/2
            result = randInt((baseDamage - (baseDamage >> 1)) + 1);   // FUN_006eb670
            return result + (baseDamage >> 1);
        }

        if ((*(unsigned int*)((int)thisPtr + 0x154) >> 6) & 1) == 0) {
            // Normal: random 1..baseDamage
            result = randInt(baseDamage);   // FUN_006eb670
            return result + 1;
        }

        // Reduced damage (bit 6 set): random 0..2
        result = randInt(3);                // FUN_006eb670
    }
    return result;
}