// FUNC_NAME: EntityManager::setEntityTransform
// Function address: 0x004e6c80
// Sets a 4-component transform (position/quaternion) and a float state for an entity identified by ID.
// Updates an entity list (per category) used for light/shadow or visibility updates.

#include <cstdint>

// Forward declarations
uint8_t getGlobalFlags();
void setGlobalFlags(const uint8_t* flags);

// Global data pointers (from DAT_01223398)
// gEntityManager -> +0x08: HashTable* pHashTable (struct with +0x04: bucket array, +0x08: numBuckets)
// HashTable bucket entry: +0x00: uint key (ID), +0x04: void* object, +0x08: next*

// Global arrays for entity lists
// DAT_0119474c: int* gSpecialEntityListCount (for bVar5=true)
// DAT_01194754: int* gSpecialEntityList (array of pairs [typePtr, entityPtr])  // first element of array?
// DAT_01194750: int* gNormalEntityListCount (for bVar5=false)
// DAT_0119475c: int* gNormalEntityList (array of pairs)

// Global float constant (DAT_00e2b05c) - likely 0.0f or -1.0f

// Entity offsets:
// +0x20: pointer for linked list (next entity in list of same type)
// +0x24: pointer to type descriptor (e.g., model, skeletal mesh) with flags at +0x14
// +0x30-0x3c: transform (4 floats/ints)
// +0x84: float (e.g., time, scale, alpha)
// +0x90: int state (0 = active, 4 = destroyed?)

void EntityManager::setEntityTransform(uint32_t entityId, uint32_t* pTransform, float stateFloat) {
    // Hash table lookup to find entity by ID
    void* pEntity = nullptr;
    // Assume gEntityManager is a global pointer to the entity manager data
    int* pManagerBase = (int*)gEntityManager;
    if (pManagerBase) {
        int* pHashTable = (int*)*(pManagerBase + 2);      // *(pManagerBase + 8) -> data at +0x08
        if (pHashTable) {
            int* pBucketArray = (int*)*(pHashTable + 1);  // .+0x04
            int numBuckets = *(pHashTable + 2);           // .+0x08
            int bucketIndex = entityId % numBuckets;
            uint32_t** ppEntry = (uint32_t**)(pBucketArray + bucketIndex * 1); // each entry is a pointer
            uint32_t* pEntry = *ppEntry;
            while (pEntry) {
                if (pEntry[0] == entityId) {
                    pEntity = (void*)pEntry[1]; // entity pointer at offset 4
                    break;
                }
                pEntry = (uint32_t*)(pEntry[2]); // next entry
            }
        }
    }

    // If entity not found, pEntity remains null, but code proceeds without returning.
    // The original code does not check for null after the loop, so we mirror that.
    if (!pEntity) {
        // fall through – entity pointer will be zero, leading to writes to invalid address.
        // This is likely an assert or debug situation; we preserve the original behavior.
    }

    // Write transform data to entity at offsets 0x30-0x3c
    uint32_t* entityData = (uint32_t*)pEntity;
    entityData[0x30 / 4] = pTransform[0];
    entityData[0x31 / 4] = pTransform[1];
    entityData[0x32 / 4] = pTransform[2];
    entityData[0x33 / 4] = pTransform[3];

    // Write state float to offset 0x84
    *(float*)((uint8_t*)pEntity + 0x84) = stateFloat;

    // Determine entity category and update entity list
    int entityState = *(int*)((uint8_t*)pEntity + 0x90);
    if (entityState != 0 && entityState != 4) {
        // Determine which list to use based on stateFloat and a flag in the type descriptor
        bool bSpecial = false;
        uint8_t* pTypeDesc = *(uint8_t**)((uint8_t*)pEntity + 0x24);
        if (stateFloat == gSpecialFloatConstant && (pTypeDesc[0x14] & 0x80) != 0) {
            bSpecial = true;
        }

        int* pListCount;
        int** pListArray; // pointer to array of pairs

        if (bSpecial) {
            pListCount = &gSpecialEntityListCount;
            pListArray = &gSpecialEntityList;
        } else {
            pListCount = &gNormalEntityListCount;
            pListArray = &gNormalEntityList;
        }

        int maxEntries = (bSpecial ? 2 : 4); // derived from (-(uint)bSpecial & 0xfffffffd) + 4

        int i = 0;
        bool bFound = (*pListCount == 0); // if count is zero, we go to else branch
        if (*pListCount > 0) {
            // Search for matching type pointer in list
            for (i = 0; i < *pListCount; i++) {
                int typePtr = (*pListArray)[i * 2];
                if (bSpecial || (typePtr == *(int*)((uint8_t*)pEntity + 0x24))) {
                    // Found type slot; update entity pointer if different
                    int existingEntity = (*pListArray)[i * 2 + 1];
                    if (existingEntity != (int)pEntity) {
                        // Store previous entity pointer somewhere? Actually writing to entity's +0x20
                        *(int*)((uint8_t*)pEntity + 0x20) = existingEntity;
                        (*pListArray)[i * 2 + 1] = (int)pEntity;
                    }
                    bFound = true;
                    break;
                }
            }
            bFound = (i == *pListCount) ? false : true; // if loop finished without break, not found
        }

        if (!bFound && i < maxEntries) {
            // Add new entry
            *(int*)((uint8_t*)pEntity + 0x20) = 0; // no linked entity
            (*pListArray)[i * 2 + 1] = (int)pEntity;
            (*pListArray)[i * 2] = *(int*)((uint8_t*)pEntity + 0x24); // type
            (*pListCount)++;
        }

        if (!bSpecial) {
            // Update global flags for normal list
            uint8_t flags = getGlobalFlags();
            flags |= (1 << (i & 0x1f)); // mark slot as used
            setGlobalFlags(&flags);
        }
    }
}