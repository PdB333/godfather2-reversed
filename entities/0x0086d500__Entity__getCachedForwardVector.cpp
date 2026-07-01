// FUNC_NAME: Entity::getCachedForwardVector
#pragma pack(push, 1)
struct Vec3 {
    float x, y, z;
};
#pragma pack(pop)

// Forward declarations of external functions
Vec3* __stdcall getPlayerTransformRotationMatrix(void); // returns pointer to matrix? Actually returns something at offsets 0x20 and 0x28
void __stdcall normalizeVector(Vec3* v); // normalizes the vector in place

// Lazily computes and caches forward direction vector from a rotation matrix (likely from player/camera transform)
// Returns pointer to internal Vec3 at +0x0C
Vec3* __thiscall Entity::getCachedForwardVector(void* this_ /* ecx = param_1 */) {
    // +0x24: bool flag indicating whether direction is cached
    if (*(char*)((int)this_ + 0x24) == 0) {
        // Get the source transformation (e.g., rotation matrix) from a global/static
        // The source is likely a 4x4 matrix; offsets 0x20 and 0x28 extract the forward row/column
        void* rotMatrix = getPlayerTransformRotationMatrix();
        // Copy forward vector from rotation matrix: 8 bytes from +0x20 and 4 bytes from +0x28 -> 12-byte Vec3
        *(double*)((int)this_ + 0x0C) = *(double*)((int)rotMatrix + 0x20);
        *(float*)((int)this_ + 0x14) = *(float*)((int)rotMatrix + 0x28);
        // Normalize the initial vector
        Vec3 localVec = *(Vec3*)((int)this_ + 0x0C);
        normalizeVector(&localVec);
        // Write back normalized result
        *(Vec3*)((int)this_ + 0x0C) = localVec;
        // Mark cache as valid
        *(char*)((int)this_ + 0x24) = 1;
    }
    // Return pointer to cached direction vector
    return (Vec3*)((int)this_ + 0x0C);
}