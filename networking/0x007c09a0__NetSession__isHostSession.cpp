// FUNC_NAME: NetSession::isHostSession
#include <cstdint>

// Function at 0x007c09a0: Checks if the given entity is a host in the current session.
// Allocates a temporary session object, validates its initialization, then checks
// if entity has a host flag (0x800) and if the current session type equals host (0x800).
bool NetSession::isHostSession(void* entity) {
    // Allocate temporary session object (size 0x28)
    void* sessionObject = allocateMemory(0x28); // FUN_00798f50
    bool initialized = initializeSession(sessionObject); // FUN_0079e920

    if (initialized && entity != nullptr) {
        // Check flag at offset +0x4 of entity (likely player flags)
        uint32_t flags = *(uint32_t*)((uint8_t*)entity + 4);
        if (flags & 0x800) {
            int32_t sessionType = getSessionType(); // FUN_007e0710
            if (sessionType == 0x800) { // SESSION_TYPE_HOST
                return true;
            }
        }
    }
    return false;
}