// FUNC_NAME: PlayerCCTVariables::updateWaterVolumeState

void __fastcall PlayerCCTVariables::updateWaterVolumeState(int thisPtr) {
    int hitResult;
    uint flagsFromHit;

    // Read position from object: vector3 at offset +0x44, +0x48, +0x4c
    float posX = *(float *)(thisPtr + 0x44);
    float posY = *(float *)(thisPtr + 0x48);
    float posZ = *(float *)(thisPtr + 0x4c);

    // Create two points for a vertical ray: one above and one below the current Y
    float waterSurfaceGlobal = _DAT_00d5c458;  // global water surface height offset?
    float someThreshold = _DAT_00d5780c;       // probably zero or a small constant

    // Point1: (posX, posY + waterSurfaceGlobal, posZ)
    // Point2: (posX, posY - someThreshold, posZ) – but we only pass two vectors
    // The decompiler interleaves the floats; we reconstruct as two 3D vectors
    Vector3 point1 = { posX, posY + waterSurfaceGlobal, posZ };
    Vector3 point2 = { posX, posY - someThreshold, posZ };

    // Call shape overlap or raycast: FUN_005425d0(&point1, &point2, 2, 0x80000000, 0, 0)
    // Parameters: start, end, type (2 = vertical?), collisionMask (0x80000000), unused, unused
    bool hitSomething = FUN_005425d0((undefined4 *)&point1, (undefined4 *)&point2, 2, 0x80000000, 0, 0);

    // Prepare hit info structure
    HitInfo hitInfo;
    undefined4 colliderInfo[2] = { 0xffffffff, 0xffffffff };
    float hitDist = someThreshold;  // local_b0
    int hitCount = 0;               // local_80
    int intersectionFound = 0;      // local_70

    // Fill hit info from some global? (FUN_009e69d0 copies from a global buffer)
    FUN_009e69d0((undefined1 *)&hitInfo, (undefined1 *)&colliderInfo);

    if (intersectionFound == 0) {
        // No intersection: set bit 0x10 in +0x89 (e.g., "inWaterVolume" flag)
        *(byte *)(thisPtr + 0x89) |= 0x10;
    } else {
        // Intersection found: clear bit 0x10
        *(byte *)(thisPtr + 0x89) &= 0xef;

        // Retrieve hit object info
        int hitObject = FUN_00542700((undefined4 *)&colliderInfo);
        if (hitObject != 0) {
            flagsFromHit = *(uint *)(hitObject + 4); // flags from hit object
            goto checkBit;
        }
    }
    flagsFromHit = 0;

checkBit:
    if ((flagsFromHit & 0x800) != 0) {
        // Hit object has bit 0x800 set (e.g., "water surface" collider)
        *(byte *)(thisPtr + 0x89) |= 8;   // set bit 3 (maybe "underwater" flag)
        *(byte *)(thisPtr + 0x8a) |= 0x20; // set bit 5 (some other flag)
        return;
    }
    // Not a water surface: clear bit 3, set bit 5
    *(byte *)(thisPtr + 0x89) &= 0xf7;
    *(byte *)(thisPtr + 0x8a) |= 0x20;
    return;
}