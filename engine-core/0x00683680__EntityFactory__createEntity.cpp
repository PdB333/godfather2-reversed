// FUNC_NAME: EntityFactory::createEntity

#include <cstdint>

// Structure passed to memory allocator
struct AllocationConfig {
    int32_t flags;       // +0x00: Allocation flags (e.g., type hint), value 2
    int32_t alignment;   // +0x04: Alignment requirement, value 0x10 (16 bytes)
    int32_t padding;     // +0x08: Unused / additional parameter, value 0
};

// Forward declarations of external functions
// Allocates a block of memory with given config and pool ID.
// Returns non-zero on success (handled as boolean).
extern int32_t allocateMemory(uint32_t size, AllocationConfig* config, uint32_t poolId);

// Initializes an entity object at the given address.
// Returns a handle or status code.
extern uint32_t initializeEntity(uint32_t entity, uint32_t flags, uint32_t param3, uint32_t param4);

// Factory function to create a new entity.
// param_1: Either an entity pointer or ID to be initialized.
// param_2: Memory pool identifier (or context for allocation).
uint32_t EntityFactory::createEntity(uint32_t entity, uint32_t poolId) {
    AllocationConfig config;
    config.flags     = 2;
    config.alignment = 0x10;
    config.padding   = 0;

    // Attempt to reserve memory for a new entity (size 0x390 = 912 bytes).
    int32_t allocResult = allocateMemory(0x390, &config, poolId);
    if (allocResult != 0) {
        // Initialize the entity with specific flags: 0x4000, 3, 0x46.
        uint32_t result = initializeEntity(entity, 0x4000, 3, 0x46);
        return result;
    }
    return 0;
}