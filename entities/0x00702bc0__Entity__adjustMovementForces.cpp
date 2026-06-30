// FUNC_NAME: Entity::adjustMovementForces
void __thiscall Entity::adjustMovementForces(void *this, float *outX, float *outY, float *outZ) {
    // Read initial raw forces from this object at offsets 0x47c, 0x480, 0x484 (likely a force/velocity vector)
    *outY = *(float *)((int)this + 0x47c);
    *outX = *(float *)((int)this + 0x480);
    *outZ = *(float *)((int)this + 0x484);
    normalizeVector(outX, outY, outZ); // Normalize or process the direction vector

    // Check flag bit 2 at offset 0x2d8 (state flags)
    if (((*(uint *)((int)this + 0x2d8) >> 2 & 1) != 0) && (g_pPlayer = getPlayerEntity(), g_pPlayer != (void *)0x0) && (g_pPlayer = getPlayerEntity(), g_pPlayer != (void *)0x0)) {
        // Scale forces by player's movement factors (offsets 0x2118 and 0x211c)
        *outY = *(float *)((int)g_pPlayer + 0x2118) * *outY;
        *outX = *(float *)((int)g_pPlayer + 0x211c) * *outX;

        // Check flag bit 7 (altered movement mode)
        if ((*(uint *)((int)this + 0x2d8) >> 7 & 1) != 0) {
            void *player2 = getPlayerEntity();
            float scaleY;
            if ((*(uint *)((int)player2 + 0x8e0) >> 1 & 1) == 0) {
                scaleY = *(float *)((int)this + 0x2fc); // Default Y scale
            } else {
                scaleY = *(float *)((int)this + 0x300); // Alternate Y scale
            }
            *outY = scaleY * *outY;
        }

        // Additional conditions: player in vehicle? or other states
        if ((((*(uint *)((int)g_pPlayer + 0x8e8) >> 2 & 1) != 0) || ((*(byte *)((int)g_pPlayer + 0x249f) & 1) != 0)) || (isPlayerInVehicle() != L'\0')) {
            float scaleX, scaleY2;
            if ((((*(uint *)((int)g_pPlayer + 0x249c) >> 0x17 & 1) != 0) || ((*(uint *)((int)g_pPlayer + 0x8e0) >> 9 & 1) != 0)) || ((*(uint *)((int)g_pPlayer + 0x249c) >> 0x18 & 1) != 0)) {
                scaleY2 = getRandomFloat(); // Random factor from FUN_00702360
                scaleX = *(float *)((int)this + 0x308); // Additional X scale from this object
            } else {
                scaleX = g_defaultScale; // _DAT_00d5780c
                scaleY2 = g_defaultScale;
            }
            float origX = *outX;
            float origY = *outY;
            *outX = origX * scaleX;
            *outY = origY * scaleY2; // Note: scaleY2 is applied to Y, but original logic uses fVar7 for Y, fVar8 for X
            // Additional Z adjustment based on differences? Original code seems incomplete.
            float diff = *outY - *outX; // Actually fVar7 = fVar8 * fVar7 - *param_2; but we need to check original
            if (g_threshold < diff) {
                *outZ = (*outZ / diff) * (origY - origX);
            }
        }
    }
}