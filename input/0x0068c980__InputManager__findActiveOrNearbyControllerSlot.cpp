// FUNC_NAME: InputManager::findActiveOrNearbyControllerSlot
// Function address: 0x0068c980
// Searches for a controller slot (0-15) that is either active (flag bit set) or within a squared radius from origin.
// If none found, returns 0x12 (18), likely a sentinel value.

#include <cstdint>

uint32_t __thiscall InputManager::findActiveOrNearbyControllerSlot(void) {
    // Check if the manager is initialized (or active count nonzero)
    if (*(int32_t*)(this + 0x2C) != 0) {
        // Get the squared search radius from a global singleton (likely settings or game manager)
        float baseRadius = *(float*)(*(uint32_t*)0x01223464 + 0x1694);
        float radiusSq = baseRadius * baseRadius;

        // Iterate over the 16 controller slots
        for (uint32_t i = 0; i < 16; ++i) {
            // Get pointer to the controller slot data structure
            float* pController = reinterpret_cast<float*>(FUN_00410540(i)); // likely getControllerState(i)
            if (pController != nullptr &&
                *(char*)(pController + 0x3E / sizeof(float)) != '\0') { // +0x3E is a byte (e.g., isConnected)
                
                // Check if the "active" flag (bits 0-13) is set, or if either of two 2D points is outside the radius
                // pController[4] at offset 0x10 is actually a uint32 stored in the float array
                uint32_t flags = reinterpret_cast<uint32_t&>(pController[4]);
                bool flagActive = (flags & 0x3FFF) != 0;
                bool point0Far = radiusSq <= (pController[0]*pController[0] + pController[1]*pController[1]);
                bool point1Far = radiusSq <= (pController[2]*pController[2] + pController[3]*pController[3]);

                if (flagActive || point0Far || point1Far) {
                    return i & 0xFF; // return slot index as byte
                }
            }
        }
    }
    return 0x12; // no suitable slot found
}