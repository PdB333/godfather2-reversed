// FUNC_NAME: PerceptionZoneManager::evaluateZonesForEntity
void __thiscall PerceptionZoneManager::evaluateZonesForEntity(int thisManager, int entity) {
    float threshold = DAT_01205228; // global threshold value for zone activation
    int index = *(int *)(thisManager + 0x18); // current index into zone list (circular buffer)
    int sentinel = *(int *)(thisManager + 0x14); // stop index (end of circular region)
    int capacity = *(int *)(thisManager + 0x10); // maximum number of zones
    ZoneElement *zoneBase = *(ZoneElement **)(thisManager + 0x1c); // base pointer to zone array

    // Set busy flag on entity (bit 0 at offset 0x2658)
    *(uint *)(entity + 0x2658) |= 1;

    // Iterate until we loop back to the sentinel index
    while (index != sentinel) {
        ZoneElement *zone = zoneBase + index * 0x28; // each zone element is 0x28 bytes

        // If this zone's activation threshold (float at +0x24) is >= global threshold
        if (threshold <= zone->activationFloat) { // +0x24
            // Prepare a small context struct (5 bytes total: 4 bytes + 1 byte)
            ZoneContext context;
            context.field0 = DAT_0112dd08; // some global constant/ID
            context.field4 = 0;

            // Decide the sub-object pointer for the entity: either null or entity+0x3c
            void *target = (entity != 0) ? (void *)(entity + 0x3c) : 0;
            FUN_00408bf0(&context, target, 0); // call external handler
        }

        // Advance index, wrapping around if beyond capacity
        index++;
        if (capacity <= index) {
            index = 0;
        }
    }

    // Clear busy flag on entity
    *(uint *)(entity + 0x2658) &= 0xfffffffe;
}

// ------------------------------------------------------------
// Supporting type definitions (for clarity)
// ------------------------------------------------------------
// ZoneElement (size 0x28)
struct ZoneElement {
    char unknown[0x24];
    float activationFloat; // +0x24 - threshold for triggering
};

// Small context passed to the handler (size 5 bytes)
struct ZoneContext {
    int field0;  // +0x00 (e.g., zone ID or global constant)
    char field4; // +0x04 (likely a boolean or sub‑type)
};

// Known external function (address 0x00408bf0)
// void FUN_00408bf0(ZoneContext *ctx, void *target, int unknownZero);