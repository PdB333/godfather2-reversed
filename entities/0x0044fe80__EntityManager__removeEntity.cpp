// FUNC_NAME: EntityManager::removeEntity
// Function at 0x0044fe80: Removes an entity from the appropriate list based on its type.
// If the entity is the active object, selects a new active object using a distance heuristic.
// Returns a 64-bit value: lower 32 bits = index of removed entity, upper 32 bits = new count.

#include <cstdint>

// Engine global singleton accessible via FS:[0x2c]
struct EngineGlobal {
    uint8_t pad0[8];
    int32_t unk8; // +8, base offset used for entity lists
};

struct EntityManager {
    int32_t listBaseOffset; // +0x68, adds to engine base to locate entity arrays
};

uint64_t __fastcall EntityManager::removeEntity(uint32_t someParam, EntityManager* managerObj, void* entityToRemove) {
    // someParam is unused as input and reused as a local temporary

    uint32_t type = *(uint32_t*)((uint8_t*)entityToRemove + 0x20);

    if (type == 2) {
        EngineGlobal* engine = *(EngineGlobal**)(*(intptr_t*)(__readfsdword(0x2c) + 0x2c));
        int32_t base = engine->unk8 + 0x8c;
        int32_t arrayBase = base + managerObj->listBaseOffset;

        uint32_t count = *(uint32_t*)(arrayBase + 0x80);
        uint32_t index = 0;
        if (count != 0) {
            while (*(int32_t*)(arrayBase + index * 4) != (int32_t)entityToRemove) {
                index++;
                if (index >= count) {
                    // Not found, return with count and index
                    return ((uint64_t)count << 32) | index; // count = someParam? Actually count is overwritten
                }
            }
            // Found at index, remove from list by swapping with last element
            if (index < count - 1) {
                uint32_t last = *(uint32_t*)(arrayBase + (count - 1) * 4);
                *(uint32_t*)(arrayBase + index * 4) = last;
            }
            *(int32_t*)(arrayBase + 0x80) = count - 1; // decrement count
            return ((uint64_t)(count - 1) << 32) | index;
        }
        return ((uint64_t)count << 32) | 0; // empty list
    }

    if (type == 1 || type == 0xf) {
        EngineGlobal* engine = *(EngineGlobal**)(*(intptr_t*)(__readfsdword(0x2c) + 0x2c));
        int32_t arrayBase = managerObj->listBaseOffset + 8 + engine->unk8;

        uint32_t count = *(uint32_t*)(arrayBase + 0x80);
        uint32_t index = 0;

        // Find and remove the entity from the list
        while (index < count) {
            if (*(int32_t*)(arrayBase + index * 4) == (int32_t)entityToRemove) {
                // Entity found, call destructor/cleanup
                FUN_00450a10(); // likely __thiscall destructor for entityToRemove

                // If the removed entity was the current active object, clear the active pointer
                int32_t activePtr = *(int32_t*)(managerObj->listBaseOffset + 4 + engine->unk8);
                if ((int32_t)entityToRemove == activePtr) {
                    *(int32_t*)(managerObj->listBaseOffset + 4 + engine->unk8) = 0;
                }
                break;
            }
            index++;
        }

        // After removal, if there is no active object and there are remaining entities, select a new active
        if (*(int32_t*)(managerObj->listBaseOffset + 4 + engine->unk8) == 0) {
            int32_t listOffset = managerObj->listBaseOffset;
            int32_t unk8 = engine->unk8;
            int32_t listStart = listOffset + unk8; // same as arrayBase - 8?
            // Actually arrayBase = listOffset + 8 + unk8, so listStart = listOffset + unk8 is arrayBase - 8
            int32_t remainingCount = *(int32_t*)(listStart + 0x88); // count of remaining? Different offset
            if (remainingCount > 0) {
                uint32_t bestIndex = 0;
                int32_t bestEntity = 0;
                // Iterate through remaining entities to find the one with smallest heuristic sum
                for (uint32_t i = 0; i < remainingCount; i++) {
                    int32_t candidate = *(int32_t*)(listStart + 8 + i * 4); // arrayBase + i*4? Actually listStart+8 = arrayBase
                    // The candidate array is at listStart+8 (which is arrayBase)
                    if (i == 0) {
                        // First candidate becomes default
                        bestEntity = candidate;
                    } else {
                        // Compare heuristic sums: three floats at offsets 0x40, 0x44, 0x48 from the object's transformation matrix
                        int32_t transCurrent = *(int32_t*)(bestEntity + 0x18);
                        int32_t transCandidate = *(int32_t*)(candidate + 0x18);
                        float sumCurrent = *(float*)(transCurrent + unk8 + 0x40) + *(float*)(transCurrent + unk8 + 0x44) + *(float*)(transCurrent + unk8 + 0x48);
                        float sumCandidate = *(float*)(transCandidate + unk8 + 0x40) + *(float*)(transCandidate + unk8 + 0x44) + *(float*)(transCandidate + unk8 + 0x48);
                        if (sumCandidate < sumCurrent) {
                            bestEntity = candidate;
                        }
                    }
                }
                // Set the best entity as the new active object
                *(int32_t*)(managerObj->listBaseOffset + 4 + engine->unk8) = bestEntity;
            }
        }

        return ((uint64_t)someParam << 32) | index; // someParam unchanged for this type path
    }

    return 0; // fallthrough for other types
}