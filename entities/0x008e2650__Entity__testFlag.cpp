// FUNC_NAME: Entity::testFlag
#include <cstdint>

class Entity {
public:
    // Virtual function at vtable offset 0x10 (index 4) – checks if a specific flag is set.
    // The 'outExtra' parameter may be used for additional output (unused in this context).
    virtual bool isFlagSet(uint32_t flag, int32_t* outExtra) = 0;
};

// Returns the flag bitmask if the flag is set, otherwise 0.
uint32_t Entity::testFlag(uint32_t flag) {
    int32_t extra = 0;
    bool result = isFlagSet(flag, &extra);
    return (result) ? flag : 0;
}