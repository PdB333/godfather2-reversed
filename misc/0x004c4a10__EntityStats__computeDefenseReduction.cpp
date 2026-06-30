// FUNC_NAME: EntityStats::computeDefenseReduction
int EntityStats::computeDefenseReduction(int param_1) {
    int baseMultiplier = DAT_012058f8 + 1; // global multiplier (tick? increment?)
    long long accumulated = __allmul(in_EAX, 0, baseMultiplier, 0); // in_EAX likely needed but not in signature? Possibly a second param in EAX (e.g., incoming damage)

    void* subData = *(void**)(param_1 + 0x54); // +0x54: pointer to sub-stats (e.g., equipped armor pieces)
    uint slot0Count = 0;
    if (*(int*)(subData + 8) != 0) { // +8: pointer to an array of structures
        slot0Count = *(uint*)(*(int*)(subData + 8) + 0xC); // +0xC: integer value from first array entry
    }

    bool isSpecial = ((*(uint*)(param_1 + 8) & 0x6000) != 0); // +8: flags, check bits 13-14
    accumulated = __allmul(accumulated + (unsigned long long)slot0Count, baseMultiplier, 0);

    int index = (isSpecial ? 3 : 1); // select array slot based on flags (offset 1 or 3)
    int* entry = *(int**)(subData + 8 + index * 8); // array entries are 8 bytes apart (likely pointer + padding)
    uint slot1Count = 0;
    if (entry != 0) {
        slot1Count = *(uint*)(entry + 0xC / 4); // +0xC: integer value
    }
    accumulated = __allmul(accumulated + (unsigned long long)slot1Count, baseMultiplier, 0);

    index = (isSpecial ? 4 : 2); // slot 2 or 4
    int* entry2 = *(int**)(subData + 8 + index * 8);
    int slot2Count = 0;
    if (entry2 != 0) {
        slot2Count = *(int*)(entry2 + 0xC / 4); // +0xC: integer value
    }

    byte baseVal = *(byte*)(param_1 + 4); // +4: byte (base defense)
    byte bonusVal = *(byte*)(param_1 + 7); // +7: byte (bonus defense)
    return (uint)baseVal * (uint)bonusVal + (slot2Count + (int)accumulated) * 0x1A; // 0x1A = 26 (maybe points per unit)
}