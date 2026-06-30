// FUNC_NAME: NPC::checkVisibility
// Function address: 0x0054f240
// Checks line-of-sight/visibility between this NPC and a target.
// Uses position at +0x64 (x), +0x68 (y), +0x6c (z) and per-frame velocity/offset at +0x70, +0x74, +0x78.
// Also uses a pointer at +0x14 to a target object with direction vector at +0x10, +0x14, +0x18.
// Flags at +0xe4 bit0 selects whether to add velocity offsets.
// Returns a uint bitmask derived from a default value (passed in EAX) and a distance threshold result.
// Global constants:
//  g_sqrMaxDist (0x00e44598) - squared distance threshold for initial check
//  g_sqrEpsilon (0x00e2cbe0) - epsilon for squared length comparisons
//  g_invDistThreshold (0x00e2b1a4) - used to compute 1/length (normalization factor)
//  g_dotThreshold (0x00e2e780) - minimum dot product for visibility
// Offset based on best-guess structure layout.

#include <cmath>

uint __fastcall NPC::checkVisibility(int thisPtr)
{
    float fVar1, fVar5, fVar6, fVar7, fVar8, fVar9;
    int iVar2;
    uint uVar3, uVar4;
    float local_2c, local_28; // squared lengths
    float vecX, vecY, vecZ; // direction vector from self to target (with offset)
    float tDirX, tDirY, tDirZ; // target's direction vector

    // Default return value from EAX (probably a bitmask)
    uVar3 = in_EAX & 0xffffff00;

    // Read self position (x: +0x64, y: +0x68, z: +0x6c)
    float selfX = *(float*)(thisPtr + 0x64);
    float selfY = *(float*)(thisPtr + 0x68);
    float selfZ = *(float*)(thisPtr + 0x6c);

    // Read optional velocity offsets (vx: +0x70, vy: +0x74, vz: +0x78)
    float velX = *(float*)(thisPtr + 0x70);
    float velY = *(float*)(thisPtr + 0x74);
    float velZ = *(float*)(thisPtr + 0x78);

    // Squared distance from something (maybe origin?) to self
    float selfSqrDist = selfX * selfX + selfY * selfY + selfZ * selfZ;

    if (g_sqrMaxDist < selfSqrDist) {
        // Beyond max distance, skip expensive checks
        // (g_sqrMaxDist likely stored at 0x00e44598)
        return uVar3;
    }

    // Compute vector to target (add velocity if flag allows)
    if ((*(byte*)(thisPtr + 0xe4) & 1) == 0) {
        vecX = selfX + velX;
        vecY = selfY + velY;
        vecZ = selfZ + velZ;
    } else {
        // In else branch, decompiler shows odd reinterpretation of double at +0x64.
        // Likely a decompilation artifact; assume just position without velocity.
        vecX = selfX;
        vecY = selfY;
        vecZ = selfZ;
    }

    // Compute squared length of vec
    float sqrLenVec = vecX * vecX + vecY * vecY + vecZ * vecZ;
    if (sqrLenVec <= g_sqrEpsilon) {
        // Too short, cannot normalize; set length to 0, inv length 0
        local_28 = 0.0f;
        fVar5 = 0.0f;
    } else {
        local_28 = sqrtf(sqrLenVec);
        fVar5 = g_invDistThreshold / local_28; // scale factor for normalization? Or angle threshold?
    }

    // Read target's direction vector from pointer at +0x14
    iVar2 = *(int*)(thisPtr + 0x14);
    float tDirX = *(float*)(iVar2 + 0x10);
    float tDirY = *(float*)(iVar2 + 0x14);
    float tDirZ = *(float*)(iVar2 + 0x18);

    float sqrLenTDir = tDirX * tDirX + tDirY * tDirY + tDirZ * tDirZ;
    if (sqrLenTDir <= g_sqrEpsilon) {
        local_2c = 0.0f;
        fVar6 = 0.0f;
    } else {
        local_2c = sqrtf(sqrLenTDir);
        fVar6 = g_invDistThreshold / local_2c;
    }

    // Normalize target direction
    float normDirX = fVar6 * tDirX;
    float normDirY = fVar6 * tDirY;
    float normDirZ = fVar6 * tDirZ;

    if (local_2c <= 0.0f) {
        local_2c = 0.0f;
        normDirX = 0.0f;
        normDirY = 0.0f;
        normDirZ = 0.0f;
    }

    // Dot product between normalized self->target vector and target's forward vector?
    // Note: fVar5 * vec components might be scaling; we use fVar5 as inverse length? Unclear.
    float dot = fVar5 * vecX * normDirX + fVar5 * vecY * normDirY + fVar5 * vecZ * normDirZ;

    // Compute ratio of lengths (target direction length / self direction length)
    float lenRatio = local_2c / local_28;

    // Read threshold at +0xa8 (dot product minimum?)
    float minDot = *(float*)(thisPtr + 0xa8);

    if (minDot <= dot && g_sqrEpsilon <= lenRatio) {
        // Visibility succeeded; pack return value
        // uVar4 comes from some bit packing (from iVar2+0x10 maybe as uint3)
        // CONCAT31 macro: combine high byte of uVar4 with 1
        uVar3 = CONCAT31((uint3)((uint)(iVar2 + 0x10) >> 8), 1); // obscure: shift address? Probably not.
        return uVar3;
    }

    // Visibility failed; return default (possibly with bit0 cleared)
    return uVar3;
}