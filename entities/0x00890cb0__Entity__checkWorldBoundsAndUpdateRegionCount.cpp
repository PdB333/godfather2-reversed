// FUNC_NAME: Entity::checkWorldBoundsAndUpdateRegionCount
void __thiscall Entity::checkWorldBoundsAndUpdateRegionCount(int this, int *contextPtr)
{
    int *regionCountPtr;
    int iManager;
    float rawPos[4]; // Actually local_30, local_2c, local_28, local_24 - 4 floats
    float worldPos[3]; // local_20, local_1c, local_18

    // Check if the context matches the expected update type
    if (*contextPtr == kUpdateTypeMagic) {
        // Get the simulation manager or world instance
        iManager = getSimManager();
        // Read the reference point (likely player/camera position) from the manager
        rawPos[0] = *(float *)(iManager + 0x30);
        rawPos[1] = *(float *)(iManager + 0x34);
        rawPos[2] = *(float *)(iManager + 0x38);
        rawPos[3] = kWorldW; // Fixed w component from global

        // Compute the world position of this entity relative to the reference point
        // (this+0x144 is likely the entity's local transform matrix)
        transformPosition(this + 0x144, rawPos, worldPos);

        // Check if the entity's world position is within the worldwide bounding box
        if ((worldPos[0] < kWorldMin) || (kWorldMax < worldPos[0]) ||
            (worldPos[1] < kWorldMin) || (kWorldMax < worldPos[1]) ||
            (worldPos[2] < kWorldMin) || (kWorldMax < worldPos[2])) {
            // Out of bounds: if currently activated, deactivate
            if ((*(int *)(this + 0x184) != 0) && (*(char *)(this + 0x188) != '\0')) {
                regionCountPtr = (int *)(*(int *)(this + 0x184) + 0x18);
                *regionCountPtr = *regionCountPtr - 1;
                *(char *)(this + 0x188) = '\0'; // Mark as inactive
            }
        } else {
            // Within bounds: if not activated, activate
            if ((*(int *)(this + 0x184) != 0) && (*(char *)(this + 0x188) == '\0')) {
                regionCountPtr = (int *)(*(int *)(this + 0x184) + 0x18);
                *regionCountPtr = *regionCountPtr + 1;
                *(char *)(this + 0x188) = '\x01'; // Mark as active
            }
        }
    }
}