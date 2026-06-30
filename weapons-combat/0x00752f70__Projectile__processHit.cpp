// FUNC_NAME: Projectile::processHit
// Address: 0x00752f70
// Role: Handles projectile impact: raycast detection, impact positioning, sound/spawn effects, and material-based secondary checks

#include <cstdint>

void __thiscall Projectile::processHit(void) {
    // --- Get game camera/transform data ---
    int* pCamera = FUN_00471610(); // likely GetCamera() or GetGameManager()
    float camPosX = *(float*)(pCamera + 0x30);          // camera X (low 32 bits of double)
    float camPosY = *(float*)(pCamera + 0x38);          // camera Y?
    float camPosZ = (float)((uint64_t)*(uint64_t*)(pCamera + 0x30) >> 32) + _DAT_00d64bfc; // camera Z from high bits + offset

    // --- Compute ray origin offset from projectile parameters ---
    // Projectile struct offsets (relative to 'this'):
    // +0x64: float (range? falloff?) -> used as inverse distance factor
    // +0x68: float (direction component)
    // +0x6c: float (direction component)
    float dirComponentX = _DAT_00e44564 - *(float*)(this + 0x64); // 1.0 - m_???
    float dirComponentY = _DAT_00e44564 - *(float*)(this + 0x68);
    float dirComponentZ = _DAT_00e44564 - *(float*)(this + 0x6c);

    // Scale by a global step multiplier (TICK_RATE or similar)
    float step = _DAT_00d5842c; // Global scale factor
    float rayEndX = dirComponentX * step + camPosX;
    float rayEndY = dirComponentY * step + camPosZ;
    float rayEndZ = dirComponentZ * step + camPosY; // note swapped Y/Z?

    // --- First raycast (impact detection) ---
    // Ray from camera to endpoint, with collision flags 0x40136 and 0x1f20020
    float rayStart[3] = { camPosX, camPosY, camPosZ };
    float rayEnd[3] = { rayEndX, rayEndY, rayEndZ };
    FUN_00542650(&rayStart, &rayEnd, 0x40136, 0x1f20020, 0, 0); // Raycast function (likely Havok or custom)

    // --- Setup callback structure for hit result ---
    undefined* vtable = &PTR_FUN_00e32a8c; // vtable for result callbacks
    int hitResultPtr = 0;                  // pointer to hit result struct
    float hitDistance = _DAT_00d5780c;     // default large distance (or 1.0)
    int invalid1 = -1;                     // unused
    int invalid2 = 0;                      // unused
    // Callback fills these locals via FUN_009e5ed0
    undefined local_60[92];                // temporary buffer
    FUN_009e5ed0(&local_60, &vtable);     // Process raycast result (fills hitResultPtr, hitDistance, etc.)

    if (hitResultPtr == 0) {
        return; // no hit
    }

    // --- Hit occurred: store impact data ---
    *(uint32_t*)(this + 0xa4) |= 1;   // flag bit0: impact happened
    *(float*)(this + 0x7c) = hitDistance; // distance to hit

    float impactPosX = hitDistance * step * dirComponentX + camPosX;
    float impactPosY = hitDistance * step * dirComponentY + camPosZ;
    float impactPosZ = hitDistance * step * dirComponentZ + camPosY;
    *(float*)(this + 0x80) = impactPosX; // +0x80 impact position X
    *(float*)(this + 0x84) = impactPosY; // +0x84 impact position Y (actually stored as Z?)
    *(float*)(this + 0x88) = impactPosZ; // +0x88 impact position Z

    // Store hit normal (from raycast result)
    *(float*)(this + 0x8c) = local_300; // normal X
    *(float*)(this + 0x90) = local_2fc; // normal Y
    *(float*)(this + 0x94) = local_2f8; // normal Z

    // Get material ID from hit result
    uint32_t materialId = FUN_00542700(&local_300); // likely extracts material from hit
    *(uint32_t*)(this + 0x98) = materialId;

    // --- Create impact sound (if hit object is valid) ---
    if ((hitResultPtr != 0) && (*(char*)(hitResultPtr + 0x10) + hitResultPtr != 0)) {
        int* soundEvent = 0;
        FUN_004af8c0(&soundEvent, 0x2001); // allocate sound event with ID 0x2001 (impact sound)
        if (soundEvent) {
            // Call vtable function on sound event (offset +0x10) with id 0x55859efa
            int(*fn)(int, int*) = (int(*)(int, int*))(*((int**)*soundEvent) + 0x10);
            uint32_t result = fn(0x55859efa, &soundEvent);
            if (result & 1) {
                soundEvent = (int*)(result & ~1); // align? unclear
            } else {
                soundEvent = 0;
            }
        }
        // Reference management: assign sound to projectile
        int* oldSound = (int*)(this + 0x9c);
        if (soundEvent) {
            int* newSound = soundEvent + 0x48;
            if (*oldSound != newSound) {
                if (*oldSound) {
                    FUN_004daf90(oldSound); // release old reference
                }
                *oldSound = newSound;
                if (newSound) {
                    *(int*)(this + 0xa0) = *(int*)(newSound + 4); // next pointer
                    *(int**)(newSound + 4) = (int**)oldSound;
                }
            }
        } else {
            if (*oldSound) {
                FUN_004daf90(oldSound);
            }
            *oldSound = 0;
        }
    }

    // --- Material-dependent secondary effects ---
    if ((*(int*)(this + 0x98) != 0) && ((*(uint8_t*)(*(int*)(this + 0x98) + 4) & 0xe0) != 0)) {
        // Material has bits set (e.g., wood, metal, concrete) -> spawn decal/particle
        // Compute offset direction for decal placement
        float normalX = *(float*)(this + 0x8c);
        float normalY = *(float*)(this + 0x90);
        float normalZ = *(float*)(this + 0x94);
        float impactX = *(float*)(this + 0x80);
        float impactY = *(float*)(this + 0x84);
        float impactZ = *(float*)(this + 0x88);

        // Offset decal position slightly along normal and tangent
        float decalX = normalX * _DAT_00d58cbc + impactX;
        float decalY = normalY * _DAT_00d58cbc + impactY;
        float decalZ = normalZ * _DAT_00d58cbc + impactZ;
        decalX += _DAT_00d5ef6c; // extra offset

        float decalEndX = normalX * _DAT_00d62b78 + decalX;
        float decalEndY = normalY * _DAT_00d62b78 + decalY;
        float decalEndZ = normalZ * _DAT_00d62b78 + decalZ;

        // Second raycast to check decal placement surface
        FUN_00542650(&decalX, &decalEndX, 0x2, 0x20000, 0, 0); // short ray for decal

        // Repeat callback pattern for decal result
        undefined* decalVtable = &PTR_FUN_00e32a8c;
        int decalHitPtr = 0;
        float decalDist = _DAT_00d5780c;
        int decalInvalid1 = -1;
        int decalInvalid2 = 0;
        undefined decalBuffer[80];
        FUN_009e5ed0(&decalBuffer, &decalVtable);

        if (decalHitPtr != 0) {
            *(uint32_t*)(this + 0xa4) |= 4; // flag bit2: decal placed
        }

        // --- Also check for lateral ricochet or penetration (if no decal placed) ---
        if ((*(uint32_t*)(this + 0xa4) & 4) == 0) {
            // Compute two orthogonal directions to the impact normal
            float crossX = _DAT_00e44564 - normalX;
            float crossY = _DAT_00e44564 - normalY;
            float crossZ = _DAT_00e44564 - normalZ;
            // Use cross product of normal with (0,0,1) or similar?
            float cross2X = crossY * 0.0f - crossZ * 0.0f; // dummy
            float cross2Y = crossZ * 0.0f - crossX * 0.0f;
            float cross2Z = crossX * 0.0f - crossY * 0.0f;
            // Choose direction based on sign (direction to shooter)
            float dirToShooterX = _DAT_00e44564 - crossX;
            float dirToShooterY = _DAT_00e44564 - crossY;
            float dirToShooterZ = _DAT_00e44564 - crossZ;
            if (dirComponentX * dirToShooterX + dirComponentY * dirToShooterY + dirComponentZ * dirToShooterZ < 0.0f) {
                // Flip if pointing away
                dirToShooterX = _DAT_00e44564 - dirToShooterX;
                dirToShooterY = _DAT_00e44564 - dirToShooterY;
                dirToShooterZ = _DAT_00e44564 - dirToShooterZ;
            }
            float ricochetEndX = dirToShooterX * _DAT_00d5ca1c + impactX;
            float ricochetEndY = dirToShooterY * _DAT_00d5ca1c + impactY;
            float ricochetEndZ = dirToShooterZ * _DAT_00d5ca1c + impactZ;

            FUN_00542650(&impactX, &ricochetEndX, 0x40136, 0x1f20020, 0, 0); // ricochet raycast

            // Process ricochet result
            undefined* ricochetVtable = &PTR_FUN_00e32a8c;
            int ricochetHit = 0;
            float ricochetDist = _DAT_00d5780c;
            int ricochetInvalid1 = -1;
            int ricochetInvalid2 = 0;
            undefined ricochetBuffer[80];
            FUN_009e5ed0(&ricochetBuffer, &ricochetVtable);
            if (ricochetHit != 0) {
                *(uint32_t*)(this + 0xa4) |= 2; // flag bit1: ricochet occurred
            }

            // --- Final penetration check ---
            float altImpactZ = *(float*)(this + 0x88);
            float altImpactX_high = (float)((uint64_t)*(uint64_t*)(this + 0x80) >> 32); // weird but correct
            float altPos = altImpactX_high + _DAT_00d5cf70;
            float altPosX = (float)((uint64_t)*(uint64_t*)(this + 0x80) & 0xFFFFFFFF);
            // Determine start of penetration ray
            if ((*(uint32_t*)(this + 0xa4) & 2) == 0) {
                // No ricochet -> use original direction from shooter
                float penStartX = dirComponentX + altPosX;
                float penStartY = dirComponentY + altPosZ; // careful with ordering
                float penStartZ = dirComponentZ + altImpactZ;
            } else {
                // With ricochet -> use new direction from ricochet normal? Actually code uses updated normal.
                float penStartX = _DAT_00e44564 - normalX;
                float penStartY = _DAT_00e44564 - normalZ; // mapping may be off
                float penStartZ = _DAT_00e44564 - normalY;
            }
            // Final raycast for penetration
            FUN_00542650(&altPosX, &penStartX, 0x40120, 0x30000, 0, 0);
            // Process result
            undefined* penVtable = &PTR_FUN_00e32a8c;
            int penHit = 0;
            float penDist = _DAT_00d5780c;
            int penInvalid1 = -1;
            int penInvalid2 = 0;
            undefined penBuffer[80];
            FUN_009e5ed0(&penBuffer, &penVtable);
            if (penHit != 0) {
                *(uint32_t*)(this + 0xa4) |= 4; // flag bit2 re-used for penetration
            }
        }
    }
}