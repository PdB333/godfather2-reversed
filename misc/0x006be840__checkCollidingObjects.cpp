// FUNC_NAME: checkCollidingObjects
void checkCollidingObjects(void* objA, void* objB, uint32_t eventData)
{
    // Check if objA is of a specific class identified by hash 0x637b907
    if (*(int*)((uint8_t*)objA + 0x54) == 0x637b907) {
        // objA is of the expected type (e.g., bullet, projectile, or player)
        bool result = someCheckFunction(); // FUN_006b34a0
        if (result == false) {
            logEvent(0x661cde1, eventData, 0); // FUN_008c3660 - failure/ignore event
        }
        return;
    }
    // Check if objB is of the same type
    if (*(int*)((uint8_t*)objB + 0x54) == 0x637b907) {
        logEvent(0x789a9424, eventData, 0); // FUN_008c3660 - alternative event
        return;
    }
    // Neither object matches the type; log a generic event
    logEvent(0xe522174b, eventData, 0); // FUN_008c36b0 - default event
}