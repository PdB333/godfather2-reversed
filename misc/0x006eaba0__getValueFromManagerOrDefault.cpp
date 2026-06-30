// FUNC_NAME: getValueFromManagerOrDefault
#include <cstdint>

// Global pointer to a manager object (e.g., InputManager, DataManager).
// Checked before attempting to call a method on it.
extern void* gSomeManager;  // DAT_0112a9c0

/**
 * Retrieves a value from a manager if available, otherwise returns
 * the high 24 bits of the caller’s EAX register (masked off low byte).
 * 
 * The function is typically called with an implicit value in EAX (the
 * “default” value).  The explicit parameter likely identifies which
 * value to fetch from the manager.
 *
 * @param param1  Index or key passed to the manager’s method.
 * @return        Either the result of gSomeManager->method(param1),
 *                or the default value with its low byte cleared.
 */
uint32_t FUN_006eaba0(uint32_t param1) {
    uint32_t result;  // in_EAX value captured at entry

    // Extract high 24 bits of whatever was in EAX.
    result = (uint32_t)((intptr_t)__eax() & 0xFFFFFF00);

    if (gSomeManager != nullptr) {
        result = FUN_006f6ed0(gSomeManager, param1);
    }
    return result;
}