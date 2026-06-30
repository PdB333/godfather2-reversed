// FUNC_NAME: PhysicsObject::updatePosition
void __thiscall PhysicsObject::updatePosition(uint flags, float deltaTime)
{
    // Check if the object is in a static/teleport state (bit 0 set)
    if (*(byte *)(this + 0x88) & 1) {
        // Copy source position directly to destination
        *(Vector3 *)(this + 0x68) = *(Vector3 *)(this + 0x44);
        // Apply a constant vertical offset (gravity-like) to destination Y
        *(float *)(this + 0x6c) += DAT_00d5fb68;
        // Also set the secondary destination (same source, without the offset)
        *(Vector3 *)(this + 0x74) = *(Vector3 *)(this + 0x44);
        return;
    }

    // Calculate displacement from velocity and time
    float displacementX = *(float *)(this + 0x20) * deltaTime;
    float displacementY = *(float *)(this + 0x24) * deltaTime;
    float displacementZ = *(float *)(this + 0x28) * deltaTime;

    // Check for reverse direction (flag == 4)
    if (*(byte *)(this + 0x88) == 4) {
        // Move destination backwards from source
        *(float *)(this + 0x68) = *(float *)(this + 0x44) - displacementX;
        *(float *)(this + 0x6c) = *(float *)(this + 0x48) - displacementY;
        *(float *)(this + 0x70) = *(float *)(this + 0x4c) - displacementZ;
    }
    else {
        // Normal forward movement
        *(float *)(this + 0x68) = *(float *)(this + 0x44) + displacementX;
        *(float *)(this + 0x6c) = *(float *)(this + 0x48) + displacementY;
        *(float *)(this + 0x70) = *(float *)(this + 0x4c) + displacementZ;

        // For flag == 8, also update a secondary destination (e.g., for two-ended objects)
        if (*(byte *)(this + 0x88) == 8) {
            *(float *)(this + 0x74) = *(float *)(this + 0x44) + displacementX;
            *(float *)(this + 0x78) = *(float *)(this + 0x48) + displacementY;
            *(float *)(this + 0x7c) = *(float *)(this + 0x4c) + displacementZ;
        }
    }
    // Apply constant vertical acceleration to the primary destination
    *(float *)(this + 0x6c) += DAT_00d5ca18;
}