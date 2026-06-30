// FUNC_NAME: SpatialComponent::addWorldOffset
void SpatialComponent::addWorldOffset(float* offsetVec) {
    // Get the per-thread base pointer from TLS (FS:[0x2C] -> +8)
    int* tlsBase = *(int**)(__readfsdword(0x2C));
    int globalBase = *(int*)(tlsBase + 8); // +8 offset within TLS struct

    // Read the index stored at this+0x10 (e.g., component slot)
    int slotIndex = *(int*)(this + 0x10);
    float* vecPtr = (float*)(globalBase + 0x80 + slotIndex);

    // Save original w component
    float w = vecPtr[3];

    // Add offset to xyz (offsetVec is assumed to have 4 floats, but w is restored)
    vecPtr[0] = vecPtr[0] + offsetVec[0];
    vecPtr[1] = vecPtr[1] + offsetVec[1];
    vecPtr[2] = vecPtr[2] + offsetVec[2];
    vecPtr[3] = vecPtr[3] + offsetVec[3]; // temporarily add, then overwritten below

    // Restore w to original value (position vectors usually have w=1, quaternions might be preserved)
    vecPtr[3] = w;
}