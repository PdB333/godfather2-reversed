// FUNC_NAME: Entity::getModifiedStat
float __fastcall Entity::getModifiedStat(void) {
    float baseValue = *(float *)(this + 0x304); // +0x304: base stat value

    // Check if stat modification is enabled (bit 2 of flags at +0x2d8)
    if ((*(uint32_t *)(this + 0x2d8) >> 2) & 1) {
        // Get global stats manager singleton
        int statsManager = FUN_007079c0(); // presumably returns pointer to global stats object

        // Select multiplier based on type field at +0x2dc
        switch (*(int32_t *)(this + 0x2dc)) {
        case 1:
            // Multiplier at global +0x2174
            return (float)(*(float *)(statsManager + 0x2174) * baseValue);
        case 2:
        case 3:
            // Multiplier at global +0x217c
            return (float)(*(float *)(statsManager + 0x217c) * baseValue);
        case 4:
            // Multiplier at global +0x2184, update baseValue and fall through to return
            baseValue = *(float *)(statsManager + 0x2184) * baseValue;
            break;
        }
    }
    return baseValue;
}