// FUNC_NAME: getEntityPosition
// Address: 0x005677c0
// Purpose: Retrieves a position for the given entity ID by calling a virtual function on a global manager.
// The position is stored in a local array but not used further – likely an stubbed or side-effect function.

#include <cstdint>

// Global constant – pointer to manager singleton (from DAT_012234b8)
extern uint32_t g_WorldManager;

void getEntityPosition(uint32_t entityId) {
    // Temporary buffer for the position (three floats)
    float pos[3] = { 0.0f, 0.0f, 0.0f };

    // The manager's vtable pointer is at g_WorldManager + 0x28
    // The function at that vtable entry takes (entityId, float*) and returns void.
    auto vtablePtr = *reinterpret_cast<void***>(reinterpret_cast<uint32_t*>(g_WorldManager) + 0x28 / 4);
    auto getPosFunc = reinterpret_cast<void (*)(uint32_t, float*)>(vtablePtr);

    getPosFunc(entityId, pos);
}