// FUNC_NAME: SpatialManager::queryObjectsInRadius
// Reconstructed from address 0x006021f0
// Performs spatial query: finds all objects within a given radius (squared) from a point.
// Uses a grid-based spatial hash or similar structure with AABB overlap test.
// Calls FUN_005fcce0 on each found object (likely a callback for processing).
// param_1: position (float[3])
// param_2: callback object (assumed vtable at +0x10 for finalization)
// param_3: spatial manager pointer
// param_4: radius squared
// param_5: filter flags (-1 = accept all, 0 = break? unclear)
// Returns 0.

#include <cstdint>

// Forward declarations for called functions
void FUN_00601d80(void* manager);                // Update spatial manager
void FUN_005fcce0();                              // Process found object callback
void FUN_005fc5f0(int param);                     // Finalization function

// Global memory references (abbreviated from decompiled globals)
// These likely point to the spatial hash grid structures.
extern uint16_t uRam0000001a;        // Current cell index
extern uint32_t uRam00000020;        // Base address for cell data array
extern void*    _DAT_00000044;       // Probably array of uint16_t indices
extern void*    _DAT_00000048;       // Pointer to object AABB data (size 0x24 per node)

int __cdecl queryObjectsInRadius(float* position, int* callbackObject, void* spatialManager, float radiusSq, int filterFlags)
{
    int* managerInt = static_cast<int*>(spatialManager);
    if (managerInt[1] != 0)  // +0x04: check if manager is active
    {
        do
        {
            // Filter: if filterFlags is 0 (and not -1), break the loop
            if ((filterFlags != -1) && (filterFlags == 0))
                break;

            // Update the spatial manager (e.g., rebuild grid)
            FUN_00601d80(spatialManager);

            if (uRam0000001a == 0xffff)
            {
                // Branch 1: Current cell is empty (0xffff sentinel)
                uint32_t localIndex = uRam00000020 & 0xffff;
                uint32_t indexVar = uRam00000020 & 0xffff;
                // Iterate over a range: base + low 16 bits, count from high 16 bits
                uint32_t limit = (uRam00000020 >> 0x10) + indexVar;
                while (indexVar < limit)
                {
                    // Read an index from _DAT_00000044
                    indexVar = (uint32_t)(*(uint16_t*)((uintptr_t)_DAT_00000044 + indexVar * 2));
                    // Compute distance squared between position and object at that index
                    float dx = position[0] - *(float*)((uintptr_t)uRam00000020 + indexVar * 0x24);
                    float dy = position[1] - *(float*)((uintptr_t)uRam00000020 + indexVar * 0x24 + 4);
                    float dz = position[2] - *(float*)((uintptr_t)uRam00000020 + indexVar * 0x24 + 8);
                    // Compare with radius squared (param_4)
                    if (dx*dx + dy*dy + dz*dz <= radiusSq)
                    {
                        FUN_005fcce0();  // Process found object
                    }
                    ++localIndex;
                    indexVar = localIndex & 0xffff;
                    // Recompute limit each iteration? (Original code does this)
                    limit = (uRam00000020 & 0xffff) + (uRam00000020 >> 0x10);
                }
            }
            else
            {
                // Branch 2: Current cell has a linked list of AABBs
                // Starting from object at index uRam0000001a
                float* currentNode = (float*)((uintptr_t)_DAT_00000048 + (uint32_t)uRam0000001a * 0x24);
                while (currentNode != nullptr)
                {
                    // Compute squared distance from position to AABB (min/max)
                    // Use separating axis theorem for point-AABB distance
                    float dx = 0.0f;
                    float x = position[0];
                    if (currentNode[0] <= x)
                    {
                        float xOffset = 0.0f;
                        if (currentNode[3] < x)  // If point beyond max.x
                        {
                            x -= currentNode[3];
                            xOffset = x * x;
                        }
                    }
                    else
                    {
                        x -= currentNode[0];
                        dx = x * x;
                    }

                    float dy = 0.0f;
                    float y = position[1];
                    if (currentNode[1] <= y)
                    {
                        float yOffset = 0.0f;
                        if (currentNode[4] < y)
                        {
                            y -= currentNode[4];
                            yOffset = y * y;
                        }
                    }
                    else
                    {
                        y -= currentNode[1];
                        dy = y * y;
                    }

                    float dz = 0.0f;
                    float z = position[2];
                    if (currentNode[2] <= z)
                    {
                        if (currentNode[5] < z)
                        {
                            z -= currentNode[5];
                            dz = z * z;
                        }
                    }
                    else
                    {
                        z -= currentNode[2];
                        dz = z * z;
                    }

                    // Total squared distance to AABB
                    if (dx + dy + dz <= radiusSq)
                    {
                        FUN_005fcce0();  // Process found object
                    }

                    // Follow next link (stored as ushort at offset 7*4 = 28 bytes)
                    uint16_t nextIndex = *(uint16_t*)(currentNode + 7);
                    if (nextIndex == 0xffff)
                        break;
                    currentNode = (float*)((uintptr_t)_DAT_00000048 + (uint32_t)nextIndex * 0x24);
                }
            }
        } while (managerInt[1] != 0);  // Loop while manager remains active

        if (managerInt[1] != 0)
        {
            return 0;  // Unclear early exit
        }
    }

    // Finalization: call FUN_005fc5f0 with 0, then invoke vtable method on callback
    FUN_005fc5f0(0);
    (*(void (**)())(*(int*)callbackObject + 0x10))();  // Call callback's vtable +0x10
    return 0;
}