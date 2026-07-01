//FUNC_NAME: Entity::findNextValidEntity
// Function address: 0x008c00a0
// Searches the entity hash table for the next valid entity (not self, flags bit4=0, bit5=0).
// Uses a hash index stored in *hashIndex; if negative, generates a new random seed.
// Returns the entity's m_targetId (offset +0x54) or 0 if none found.
// Updates *hashIndex to the next slot for subsequent calls.

#include <cstdint>

// Forward declarations
class Entity;
class EntityManager;

// Global singleton pointer to the entity manager (0x01129904)
extern EntityManager* g_pEntityManager;

// Global counter for random seed generation (0x012054b4)
extern uint32_t g_entitySearchCounter;

// Random number generator (FUN_00b9a1c0)
uint32_t generateRandomSeed();

// Entity structure (partial)
class Entity {
public:
    // Offset +0x54: target ID or handle (returned by findNextValidEntity)
    uint32_t m_targetId;

    // Offset +0x84: flags (bit4 = 0 means valid, bit5 = 0 means not excluded)
    uint32_t m_flags;

    // Check if this entity is valid for targeting (bit4=0, bit5=0)
    bool isValidTarget() const {
        return ((m_flags >> 4) & 1) == 0 && ((m_flags >> 5) & 1) == 0;
    }
};

// Entity manager structure (partial)
class EntityManager {
public:
    // Offset +0x30: pointer to array of entity pointers
    Entity** m_ppEntities;

    // Offset +0x34: number of entries in the array
    uint32_t m_numEntities;
};

// Member function of Entity: find the next valid entity in the global hash table
// param_1 (this) = current entity to exclude
// param_2 = pointer to hash index (modified in place)
// Returns the m_targetId of the found entity, or 0 if none
int Entity::findNextValidEntity(uint32_t* hashIndex) {
    EntityManager* pManager = g_pEntityManager;
    Entity** ppEntities = pManager->m_ppEntities;  // +0x30
    uint32_t numEntities = pManager->m_numEntities; // +0x34

    // If the hash index is negative, generate a new random seed
    if ((int32_t)(*hashIndex) < 0) {
        g_entitySearchCounter++;
        *hashIndex = generateRandomSeed();
    }

    int result = 0;
    uint32_t iteration = 0;
    uint32_t currentHash = *hashIndex;

    do {
        if (iteration >= numEntities) {
            return result; // No valid entity found
        }

        uint32_t slot = currentHash % numEntities;
        *hashIndex = slot; // Update the hash index to current slot
        currentHash = slot + 1; // Prepare next hash (will be stored after loop)

        Entity* candidate = ppEntities[slot];
        if (candidate != nullptr && candidate != this && candidate->isValidTarget()) {
            // Found a valid candidate; return its target ID
            result = candidate->m_targetId;
            *hashIndex = currentHash; // Store next hash for subsequent calls
        }

        iteration++;
    } while (result == 0);

    return result;
}