// FUN_00425190: GameObjectManager::calculateDistance

// Function computes Euclidean distance between two 3D points stored in an entity's data.
// The entity is identified by handle, which is converted to an index via resolveIndexFromHandle.
// Each entity data block is 0x1d0 bytes; the two points are at offsets 0x00 and 0x10 (within the block).
// Pointer to entity array is at this+0x10.

#include <cmath>

// Forward declaration of handle-to-index conversion (defined elsewhere)
int resolveIndexFromHandle(int handle);

// Structure representing the first 28 bytes of an entity data block.
// Total block size is 0x1d0 = 464 bytes.
struct EntityDataBlock {
    float posX1;   // +0x00
    float posY1;   // +0x04
    float posZ1;   // +0x08
    float pad0C;   // +0x0C (unused, likely alignment)
    float posX2;   // +0x10
    float posY2;   // +0x14
    float posZ2;   // +0x18
    // ... remaining fields up to 0x1d0
};

class GameObjectManager {
public:
    // Returns the distance between the two stored points for the given entity handle.
    float calculateDistance(int handle) {
        int index = resolveIndexFromHandle(handle);
        // Entity array pointer stored at offset +0x10
        EntityDataBlock* entity = reinterpret_cast<EntityDataBlock*>(
            reinterpret_cast<int*>(this)[0x10 / 4] // offset +0x10
        ) + index;

        float dx = entity->posX1 - entity->posX2;
        float dy = entity->posY1 - entity->posY2;
        float dz = entity->posZ1 - entity->posZ2;

        return sqrtf(dx * dx + dy * dy + dz * dz);
    }
};