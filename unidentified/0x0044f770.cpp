// SpatialGrid::findEntitiesInRange (0x0044f770)
// This function queries the spatial grid for entities within a radius of a given entity's position.
// It collects entities within the bounding sphere (position + radius) into a local array,
// then filters them based on flags and calls further processing functions.
// Parameters:
//   this (param_1): SpatialGrid* - the spatial grid instance
//   pEntity (param_2): Entity* - the entity performing the query (has position at +0x80, flags at +0x94, etc.)

#include <cstdint>
#include <cmath>

// Forward declarations of called functions
uint32_t FUN_0049feb0();  // Unknown, possibly returns a boolean or bitmask
int32_t FUN_0044d960();   // Unknown, likely a line-of-sight or guard check (returns nonzero for success)
void FUN_00450210(Entity* pEntity, const float* aabb, int32_t otherEntity);  // Processes entity (e.g., add to sensed list)
void FUN_0044f5f0(Entity* pEntity, uint32_t filterFlags);  // Called for each entity in local query result

// Global constants (inferred from decompiled)
extern const float DAT_00e31670;  // Used in min
extern const float DAT_00e31660;  // Used in max
extern const float DAT_00e4461c;  // Scale factor
extern const float DAT_00e44598;  // Threshold
extern const uint32_t DAT_00e44648;  // Floating-point bitmask
extern const uint32_t DAT_00e44564;  // Floating-point bitmask
extern const uint32_t DAT_00e2b1a4;  // Integer mask

// Structure offsets for Entity (relative to param_2)
// +0x80: float[4] position (x,y,z, radius) - actually bounding sphere
// +0x88: unused? (accessed as float for scaling)
// +0x90: pointer to some other data (maybe animation controller)
// +0x94: uint32 flags (bits: 0x8 = unknown, 0x10 = unknown, etc.)
// +0x98: int32 result flag (set to 1 if any entity was processed)

// Structure offsets for SpatialGrid (relative to param_1)
// +0x14: uint32 gridDimension (size in cells per side)
// +0x1c: float cellSize (size of each cell in world units)
// +0x20: int32 gridOriginX (minimum world x coordinate)
// +0x24: int32 gridOriginY (minimum world y coordinate)
// +0x34: int** gridData (2D array of pointers to linked lists of entities per cell)
// +0x68: void* someList (array of structures for additional processing, e.g., sensors)

bool __thiscall SpatialGrid::findEntitiesInRange(Entity* pEntity)
{
    float fVar1;
    uint16_t uVar2;
    uint32_t uVar3;
    uint32_t in_EAX;
    int32_t* piVar4;
    int32_t iVar5;
    float* extraout_ECX;
    float* pfVar6;
    int32_t iVar7;
    int32_t iVar8;
    int32_t iVar9;
    int32_t unaff_FS_OFFSET;
    float fVar10, fVar11, fVar13, fVar14, fVar15, fVar16;
    __m128 auVar12;
    __m128 local_220;
    uint32_t local_23c;
    int32_t local_238;
    int32_t local_234;
    uint32_t local_230;
    int32_t local_210[131];  // Array to hold collected entity pointers

    // Clear result flag
    *(int32_t*)(pEntity + 0x98) = 0;

    // If flag 0x8 is set, call some function (might be to update something)
    if ((*(uint8_t*)(pEntity + 0x94) & 0x8) != 0) {
        in_EAX = FUN_0049feb0();
    }

    // Get bounding sphere from entity: position + radius
    pfVar6 = (float*)(pEntity + 0x80);
    fVar13 = *(float*)(this + 0x1c) * *pfVar6;  // cellSize * position.x
    // Truncate to integer grid cell index (via floating-point hacks)
    fVar10 = (float)(DAT_00e44648 | DAT_00e44564 & (uint32_t)fVar13);
    fVar10 = (fVar13 + fVar10) - fVar10;
    fVar14 = *(float*)(pEntity + 0x88) * *(float*)(this + 0x1c);  // cellSize * something (maybe radius?)
    // Compute cell coordinates
    iVar9 = (int32_t)(fVar10 - (float)(-(uint32_t)((float)(DAT_00e44564 & (uint32_t)fVar13) < fVar10 - fVar13) & DAT_00e2b1a4)) - *(int32_t*)(this + 0x20);
    fVar10 = (float)(DAT_00e44648 | DAT_00e44564 & (uint32_t)fVar14);
    fVar10 = (fVar14 + fVar10) - fVar10;
    iVar8 = (int32_t)(fVar10 - (float)(-(uint32_t)((float)(DAT_00e44564 & (uint32_t)fVar14) < fVar10 - fVar14) & DAT_00e2b1a4)) - *(int32_t*)(this + 0x24);

    // Check if within grid bounds
    if ((((-1 < iVar9) && (in_EAX = *(uint32_t*)(this + 0x14), iVar9 < (int32_t)in_EAX)) &&
         (-1 < iVar8)) && (iVar8 < (int32_t)in_EAX)) {
        // Cell is valid
        if ((*(uint8_t*)(pEntity + 0x94) & 0x8) != 0) {
            FUN_0049feb0();
            pfVar6 = extraout_ECX;  // Recover the pointer after call? Possibly clobbered
        }
        // Get linked list of entities in this cell
        piVar4 = *(int32_t**)(*(int32_t*)(this + 0x34) + (*(int32_t*)(this + 0x14) * iVar8 + iVar9) * 4);
        local_234 = 0;  // Count of entities found

        if (piVar4 != nullptr) {
            fVar10 = *pfVar6;         // entity position x
            fVar13 = pfVar6[1];       // entity position y
            fVar14 = pfVar6[2];       // entity position z
            fVar1 = pfVar6[3];        // entity radius
            do {
                iVar8 = *piVar4;      // entity pointer in list
                fVar16 = fVar14 - *(float*)(iVar8 + 0x18);  // dz
                fVar15 = fVar13 - *(float*)(iVar8 + 0x14);  // dy
                fVar11 = fVar10 - *(float*)(iVar8 + 0x10);  // dx
                // Check distance squared (using sqrt) against combined radius
                if (std::sqrt(fVar11 * fVar11 + fVar15 * fVar15 + fVar16 * fVar16) <=
                    *(float*)(iVar8 + 4) + fVar1) {
                    local_210[local_234] = iVar8;
                    local_234++;
                }
                piVar4 = (int32_t*)piVar4[1];  // next in linked list
            } while (piVar4 != nullptr);
        }

        // Determine filter flags based on entity's flags
        uVar3 = *(uint32_t*)(pEntity + 0x94);
        if (((uVar3 & 0x8) == 0) || (*(int32_t*)(pEntity + 0x90) == 0)) {
            if ((uVar3 & 0x10) == 0) {
                local_23c = ~(uVar3 >> 5) & 4;
            } else {
                local_23c = 8;
            }
        } else {
            local_23c = ( -(uint32_t)((*(uint8_t*)(*(int32_t*)(pEntity + 0x90) + 0xac) & 4) != 0) & 0xfffffffc) + 8;
        }

        // Iterate over another list (probably sensors or additional entities) from the grid's data at +0x68
        iVar9 = **(int32_t**)(unaff_FS_OFFSET + 0x2c);  // Some thread-local or global data
        uVar2 = *(uint16_t*)(iVar9 + 0x10);  // Some flag mask
        iVar8 = *(int32_t*)(iVar9 + 8);
        iVar7 = *(int32_t*)(this + 0x68);
        local_230 = 0;
        if (*(int32_t*)(iVar7 + 0x88 + iVar8) != 0) {  // Number of items in list
            local_238 = 8;
            do {
                iVar7 = *(int32_t*)(local_238 + iVar7 + iVar8);  // Pointer to structure
                if (iVar7 != 0) {
                    uVar3 = *(uint32_t*)(*(int32_t*)(iVar7 + 0x18) + 0x7c + iVar8);
                    iVar8 = *(int32_t*)(iVar7 + 0x18) + iVar8;
                    // Check flags and call FUN_0044d960 (probably line-of-sight or other condition)
                    if ((((local_23c & uVar3) != 0) &&
                         ((*(uint32_t*)(iVar8 + 0x80) & (uint32_t)uVar2) == (uint32_t)uVar2)) &&
                        (((uVar3 & 2) != 0 || (iVar5 = FUN_0044d960(), iVar5 != 0))) &&
                        (((uVar3 & 1) != 0 || (iVar5 = FUN_0044d960(), iVar5 == 0)))) {
                        // Clamp AABB (bounding box) of object
                        auVar12 = _mm_min_ps(*(__m128*)(iVar8 + 0x40), _mm_set1_ps(DAT_00e31670));
                        local_220 = _mm_max_ps(auVar12, _mm_set1_ps(DAT_00e31660));
                        // Compute a distance or priority value
                        if ((uVar3 & 0x1000) == 0) {
                            fVar10 = (local_220.m128_f32[2] + local_220.m128_f32[1] + local_220.m128_f32[0]) * DAT_00e4461c;
                        } else {
                            fVar10 = *(float*)(iVar8 + 0x88);
                        }
                        // If below threshold, process the entity
                        if (DAT_00e44598 < fVar10) {
                            *(float*)(iVar8 + 0x84) = fVar10;
                            FUN_00450210(pEntity, (float*)&local_220, iVar7);
                        }
                    }
                }
                iVar8 = *(int32_t*)(iVar9 + 8);
                iVar7 = *(int32_t*)(this + 0x68);
                local_238 += 4;
                local_230++;
            } while (local_230 < *(uint32_t*)(iVar7 + 0x88 + iVar8));
        }

        // Call FUN_0044f5f0 for each entity found in the spatial query
        for (int32_t* ptr = local_210; ptr != local_210 + local_234; ++ptr) {
            FUN_0044f5f0(pEntity, local_23c);
        }

        return (*(int32_t*)(pEntity + 0x98) != 0);
    }

    // Out of bounds or other failure: return result from earlier call
    return (in_EAX & 0xffffff00) != 0;  // Actually returns in_EAX with lower byte cleared; for simplicity treat as bool
}