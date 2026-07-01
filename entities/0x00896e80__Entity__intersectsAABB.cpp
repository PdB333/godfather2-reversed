// FUNC_NAME: Entity::intersectsAABB
bool __thiscall Entity::intersectsAABB(float* this, float* otherAABB)
{
    // otherAABB is an 8-float array: [minX, minY, minZ, minW? , maxX, maxY, maxZ, maxW?]
    // We ignore the 4th component (W) as it's not used in the final comparison.

    float otherMinX = otherAABB[0];
    float otherMinY = otherAABB[1];
    float otherMinZ = otherAABB[2];
    float otherMaxX = otherAABB[4];
    float otherMaxY = otherAABB[5];
    float otherMaxZ = otherAABB[6];

    // Compute the overlapping region's min and max coordinates in the other box's space.
    // Actually it's computing: overlapMinX = min(otherMinX, otherMaxX), etc.
    float overlapMinX = (otherMinX < otherMaxX) ? otherMinX : otherMaxX; // local_50
    float overlapMinY = (otherMinY < otherMaxY) ? otherMinY : otherMaxY; // local_4c
    float overlapMinZ = (otherMinZ < otherMaxZ) ? otherMinZ : otherMaxZ; // local_48
    float overlapMaxX = (otherMaxX > otherMinX) ? otherMaxX : otherMinX; // local_40
    float overlapMaxY = (otherMaxY > otherMinY) ? otherMaxY : otherMinY; // local_3c
    float overlapMaxZ = (otherMaxZ > otherMinZ) ? otherMaxZ : otherMinZ; // local_38

    // Get the center of this object via virtual function call.
    // The vtable offset 7 (0x1C) is assumed to be a method that fills three floats with (centerX, centerY, centerZ).
    float centerX, centerY, centerZ; // local_5c, fStack_58, fStack_54
    (*(void (__thiscall **)(Entity*, float*))(vftable() + 7))(this, &centerX);

    // Offsets 0x30,0x34,0x38 are negative extents (min relative to center)
    // Offsets 0x40,0x44,0x48 are positive extents (max relative to center)
    // They are stored as floats.
    float minRelX = *(float*)((uint)this + 0x30); // param_1[0xc]
    float minRelY = *(float*)((uint)this + 0x34); // param_1[0xd]
    float minRelZ = *(float*)((uint)this + 0x38); // param_1[0xe]
    float maxRelX = *(float*)((uint)this + 0x40); // param_1[0x10]
    float maxRelY = *(float*)((uint)this + 0x44); // param_1[0x11]
    float maxRelZ = *(float*)((uint)this + 0x48); // param_1[0x12]

    // Compute the min and max of this object's AABB in world space
    float thisMinX = centerX + minRelX;
    float thisMinY = centerY + minRelY;
    float thisMinZ = centerZ + minRelZ;
    float thisMaxX = centerX + maxRelX;
    float thisMaxY = centerY + maxRelY;
    float thisMaxZ = centerZ + maxRelZ;

    // Test overlap on each axis using bit flags.
    // Bits: 4=Z? Actually: bit0: X? We need to check ordering.
    // The code uses bit values: 8,4,2. Order: X:8, Y:4, Z:2 (or reversed).
    // We'll replicate the bit logic.
    byte overlapMinXFlag = (overlapMinX < thisMinX) ? 0 : 8;
    byte overlapMinYFlag = (overlapMinY < thisMinY) ? 0 : 4;
    byte overlapMinZFlag = (overlapMinZ < thisMinZ) ? 0 : 2;
    byte overlapMaxXFlag = (overlapMaxX > thisMaxX) ? 0 : 8;
    byte overlapMaxYFlag = (overlapMaxY > thisMaxY) ? 0 : 4;
    byte overlapMaxZFlag = (overlapMaxZ > thisMaxZ) ? 0 : 2;

    byte minFlags = overlapMinXFlag | overlapMinYFlag | overlapMinZFlag;
    byte maxFlags = overlapMaxXFlag | overlapMaxYFlag | overlapMaxZFlag;

    // Condition: all three bits are set in both masks? Actually the return checks (maxFlags & minFlags) == 0xE.
    // 0xE = 8|4|2 = all three bits.
    // But note: minFlags and maxFlags each only have bits set where the other box is inside this box?
    // Actually, the flags indicate that the point (min or max of other) is inside this box's projection on that axis.
    // For an AABB overlap test, we need the intervals to overlap at least in one point.
    // The expression (maxFlags & minFlags) == 0xE checks that both the min and max of other are on the same side? Hmm.
    // Let's trust the original code.

    return (byte)(maxFlags & minFlags) == 0xE;
}