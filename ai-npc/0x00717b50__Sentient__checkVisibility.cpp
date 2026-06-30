// FUNC_NAME: Sentient::checkVisibility
// Address: 0x00717b50
// Role: Checks if a target position (from two camera transforms) is within a view cone defined by a direction vector and FOV threshold.
// The function returns a 32-bit value with low byte = 1 if visible, 0 otherwise; high 24 bits contain status flags from distance comparison.

#include <cmath>

// Forward declarations for external functions
extern void* __fastcall GetCameraTransform(); // FUN_00471610 - returns pointer to transform (XMFLOAT3 at +0x30, +0x34, +0x38)
extern float g_fSquaredDistanceMin;           // _DAT_00d577a0 - minimum squared distance (epsilon)
extern float g_fSquaredDistanceDefault;       // DAT_00d5ef84 - default distance when equal
extern float g_fCosHalfFov;                  // DAT_00d5780c - cosine of half FOV (global default)
extern float g_fConeFactor;                  // DAT_00d5779c - factor for cone dot product

struct Vector3 {
    float x, y, z;
};

uint __fastcall Sentient::checkVisibility(void* thisObj) {
    // +0x330: pointer to a direction source (e.g., camera component)
    uint directionSourcePtr = *(uint*)((char*)thisObj + 0x330);
    if (directionSourcePtr == 0) {
        return 0;
    }

    // +0x48 offset from source pointer yields the actual direction provider (vtable)
    void* directionProvider = *(void**)(directionSourcePtr - 0x48);
    if (directionProvider == 0) {
        return 0;
    }

    // Virtual call to get forward direction vector (vtable+0x4c)
    Vector3 forwardDir;
    typedef void (__thiscall* GetDirFunc)(void*, Vector3*);
    GetDirFunc getDir = *(GetDirFunc*)(*(uint*)directionProvider + 0x4c);
    getDir(directionProvider, &forwardDir);  // fills three floats

    // Get two camera transforms (likely from two different views or frames)
    void* transformA = GetCameraTransform(); // +0x30 = x, +0x34 = y, +0x38 = z
    void* transformB = GetCameraTransform();

    Vector3 posA, posB;
    posA.x = *(float*)((char*)transformA + 0x30);
    posA.y = *(float*)((char*)transformA + 0x34);
    posA.z = *(float*)((char*)transformA + 0x38);

    posB.x = *(float*)((char*)transformB + 0x30);
    posB.y = *(float*)((char*)transformB + 0x34);
    posB.z = *(float*)((char*)transformB + 0x38);

    // Difference vector
    Vector3 diff;
    diff.x = posA.x - posB.x;
    diff.y = posA.y - posB.y;
    diff.z = posA.z - posB.z;

    // Squared distance
    float sqDist = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;

    // Encode status flags for squared distance comparison
    uint statusFlags = 0;
    if (std::isnan(sqDist) || std::isnan(g_fSquaredDistanceMin)) {
        statusFlags |= (1 << 2); // NAN flag
    }
    if (sqDist < g_fSquaredDistanceMin) {
        statusFlags |= 2; // less than flag
    }
    if (sqDist == g_fSquaredDistanceMin) {
        statusFlags |= (1 << 6); // equal flag
        sqDist = g_fSquaredDistanceDefault; // use default distance when equal
    }

    // Build high 24 bits from statusFlags and a nibble from (transformB+0x30) upper word? (unusual)
    uint high24 = ((uint)((char*)transformB + 0x30) >> 16) & 0xFFFF; // from the high word of address? Actually original: CONCAT21((short)((uint)(iVar3+0x30) >> 0x10), ...)
    // That part seems to take bits from the address of the transform's x component? Strange, but we preserve logic:
    uint combined = (high24 << 8) | statusFlags; // CONCAT21: (short) high16 -> high 16 bits, then statusFlags in low byte? Actually CONCAT21(a,b) puts a (16-bit) in high 16 and b (8-bit) in low 16? The original CONCAT21 is 3-byte with b as low 8? Need to match exactly.
    // Reinterpret: original: CONCAT21((short)((uint)(iVar3+0x30) >> 0x10), (status bytes)). CONCAT21 takes a 2-byte and 1-byte to form 3 bytes. So high24 should be that 3-byte value.
    // For simplicity, we'll compute as: uint threeBytes = ( ((uint)((char*)transformB+0x30) >> 16) << 8 ) | (statusFlags & 0xFF);
    uint threeBytes = ( (((uint)((char*)transformB + 0x30) >> 16) & 0xFFFF) << 8 ) | (statusFlags & 0xFF);

    // Dot product of diff with forward direction
    float dot = diff.x * forwardDir.x + diff.y * forwardDir.y + diff.z * forwardDir.z;

    // Get FOV threshold: default global or per-object override
    float cosHalfFov = g_fCosHalfFov;
    if (*(int*)((char*)thisObj + 0x24) != 0) {
        cosHalfFov = *(float*)(*(int*)((char*)thisObj + 0x24) + 0x58);
    }

    // Cone test: if cos(angle) < threshold, then not in cone
    float angleCos = dot * g_fConeFactor / sqDist; // normalized dot (since diff is not normalized? Actually the original divides by sqDist, which is squared distance, not sqrt. This gives a value that is not cosine. Looking at original: (fVar5*local_c + fVar6*unaff_EBX + fVar8*fStack_8)*DAT_00d5779c / fVar9. That is (diff · forwardDir) * factor / sqDist. That is not a cosine unless factor=1 and sqrt(sqDist). But the code uses sqDist (squared). So maybe they compare squared cosine? Or it's a different metric.
    // To match original, we keep the same formula.
    if (cosHalfFov <= angleCos) {
        // Visible -> low byte = 1
        return (threeBytes << 8) | 1; // CONCAT31(threeBytes, 1) -> low byte 1, high 24 from threeBytes
    }

    // Not visible -> low byte = 0, keep high 24 from directionSourcePtr? Actually original returns uVar4 & 0xffffff00, where uVar4 comes from (uint)uVar1 << 8, so low byte zero.
    return (threeBytes << 8) & 0xFFFFFF00; // Pad with zeros in low byte
}