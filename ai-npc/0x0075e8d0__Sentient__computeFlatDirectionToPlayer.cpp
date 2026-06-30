// FUNC_NAME: Sentient::computeFlatDirectionToPlayer
void __thiscall Sentient::computeFlatDirectionToPlayer(float *outDirection, float *outDistance)
{
    // Get reference position (likely player or camera) via global/singleton
    int targetTransform = getPlayerTransform(); // Returns pointer to some transform struct
    if (!targetTransform) {
        // Safety: zero out direction and distance
        outDirection[0] = 0.0f;
        outDirection[1] = 0.0f;
        outDirection[2] = 0.0f;
        *outDistance = 0.0f;
        return;
    }

    // Compute vector from this object's world position (at +0x60, +0x64, +0x68) to target's position (at +0x30, +0x34, +0x38)
    float dx = this->position[0] - *(float *)(targetTransform + 0x30);
    float dy = this->position[1] - *(float *)(targetTransform + 0x34);
    float dz = this->position[2] - *(float *)(targetTransform + 0x38);

    // Flatten to horizontal plane: zero Y component
    outDirection[0] = dx;
    outDirection[1] = 0.0f;
    outDirection[2] = dz;

    // Compute horizontal length using temporary vector
    float flatVec[3] = {dx, 0.0f, dz};
    float length = vec3Length(flatVec); // returns sqrt(dx*dx + dz*dz)

    // Store length
    *outDistance = length;

    // Note: The original code redundantly copies back, but it's effectively the same.
}