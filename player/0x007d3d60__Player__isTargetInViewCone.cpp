// FUNC_NAME: Player::isTargetInViewCone
bool Player::isTargetInViewCone(Player* this, int targetHandle)
{
    bool result = false;
    if (this == nullptr) {
        return result;
    }

    int stackTargetHandle = targetHandle;
    // Pre-process or update state
    this->vtable[0x1dc]();

    // Get forward vectors or positions from two entities (maybe player and target)
    Vector3* vecA = reinterpret_cast<Vector3*>(FUN_00471610());
    Vector3* vecB = reinterpret_cast<Vector3*>(FUN_00471610());

    // Dot product of two vectors (e.g., player forward and direction to target)
    float dotProduct = vecA->x * vecB->x + vecA->y * vecB->y + vecA->z * vecB->z;

    // Global cone cosine threshold (e.g., 0.5 for 60° cone)
    if (dotProduct < gConeDotThreshold) {
        return false;
    }

    // Check if the game is in an interactive state (e.g., not paused)
    int interactionState = FUN_00543370();
    if (interactionState != 0) {
        return false;
    }

    // Log or set interaction target
    FUN_00883330(targetHandle, this);

    // Allocate local transform buffer
    float transformBuffer[2];  // e.g., matrix rows or quaternion
    float extraData;           // e.g., scale or offset

    // Retrieve world transform or orientation
    this->vtable[0x1d8](transformBuffer, &extraData);

    // Check some condition on the transform (e.g., not in cover, not ragdolling)
    char conditionCheck = FUN_008754b0(transformBuffer);
    if (conditionCheck == 0) {
        int validity = this->vtable[500](transformBuffer);
        if (validity != 0) {
            return false;
        }
    }

    // Update or finalize transform (e.g., project onto navmesh)
    this->vtable[0x1f0](transformBuffer, transformBuffer);

    // Execute the actual interaction logic (e.g., face target, start grab)
    bool finalResult = FUN_007d3890(&stackTargetHandle, targetHandle, this);
    return finalResult;
}