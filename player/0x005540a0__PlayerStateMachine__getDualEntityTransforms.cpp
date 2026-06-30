// FUNC_NAME: PlayerStateMachine::getDualEntityTransforms
// Address: 0x005540a0
// Retrieves the world transform (or component transform) for two different entities.
// The first entity is the 'this' pointer (ECX), the second is passed via ESI (unaff_ESI).
// Each entity has a component pointer at offset 0x28.
// The component is considered valid if its flag at +0x18 is 0x01 and a derived pointer 
// (signed char offset at +0x10 added to the component base) is non-null.

#include <cstdint>

// Forward declaration: fills a 4-float buffer (likely a quaternion or matrix row) for a given entity.
void getComponentTransform(int* entity, float* outTransform);

void PlayerStateMachine::getDualEntityTransforms() {
    // --- First entity (this) ---
    int* componentPtr1 = *(int**)(this + 0x28);        // +0x28: pointer to a component (e.g., bone/anim joint)
    // Buffer for first transform (4 floats – e.g., quaternion)
    float transform1[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    // Check if the component is active (flag at +0x18 == 1) and if a derived pointer is valid
    if ( (*(char*)(componentPtr1 + 0x18) == 0x01) &&
         (*(char*)(componentPtr1 + 0x10) + (int32_t)componentPtr1 != 0) )
    {
        getComponentTransform(this, transform1);   // Fill transform for first entity
    }

    // --- Second entity (passed in ESI) ---
    int* componentPtr2 = *(int**)(unaff_ESI + 0x28);  // +0x28: same component pointer
    // Buffer for second transform (overlaps in stack with first, offset 0x10)
    float transform2[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    if ( (*(char*)(componentPtr2 + 0x18) == 0x01) &&
         (*(char*)(componentPtr2 + 0x10) + (int32_t)componentPtr2 != 0) )
    {
        getComponentTransform((int*)unaff_ESI, transform2);   // Fill transform for second entity
    }

    return;
}