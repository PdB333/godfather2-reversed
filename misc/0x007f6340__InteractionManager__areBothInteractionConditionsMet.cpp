// FUNC_NAME: InteractionManager::areBothInteractionConditionsMet

__fastcall bool InteractionManager::areBothInteractionConditionsMet(int thisPtr)
{
    // Bitfield flags at offsets +0x970 and +0x974 (likely from two sub-objects or state structures)
    uint flagsA = *(uint*)(thisPtr + 0x970);
    uint flagsB = *(uint*)(thisPtr + 0x974);

    // Condition 1: Bit 0 must be set in both (e.g., both entities are active/alive/available)
    if ((flagsA & 1) == 0 || (flagsB & 1) == 0)
        return false;

    // Condition 2: Bit 2 must NOT be set in both simultaneously (e.g., not both in combat)
    if ((flagsA & 4) != 0 && (flagsB & 4) != 0)
        return false;

    // Condition 3: Bit 8 must NOT be set in both simultaneously (e.g., not both in vehicle)
    if ((flagsA & 0x100) != 0 && (flagsB & 0x100) != 0)
        return false;

    return true;
}