// FUNC_NAME: PhysicsObject::integratePosition
void __thiscall PhysicsObject::integratePosition(float dt)
{
    // Get pointer to physics state (e.g., velocity vector) at offset 0x24
    float* physicsState = *(float**)(this + 0x24);

    // Access global singleton via thread-local storage (FS:[0x2c])
    // The double dereference yields the singleton instance pointer
    int* globalSingleton = **(int***)(__readfsdword(0x2c));

    // Update position using Euler integration: newPos = oldPos + velocity * dt
    // Velocity components are stored at physicsState + 0xF8 (x) and +0xFC (y)
    float newX = *(float*)(physicsState + 0xF8/4) * dt + *(float*)(this + 0x34/4);
    float newY = *(float*)(physicsState + 0xFC/4) * dt + *(float*)(this + 0x38/4);
    *(float*)(this + 0x34/4) = newX;
    *(float*)(this + 0x38/4) = newY;

    // Retrieve z component from physics state (offset 0xF4)
    float z = *(float*)(physicsState + 0xF4/4);

    // Compute target transform pointer from global singleton
    // globalSingleton + 8 holds a pointer to an array of transforms
    // Then offset by 0x10 plus an index stored at this + 0x10
    int transformIndex = *(int*)(this + 0x10/4);
    void* transformPtr = (void*)(*(int*)(globalSingleton + 2) + 0x10 + transformIndex);

    // Apply the updated world position (x, y, z) to the transform
    setPositionInWorld(newX, newY, z, transformPtr); // 0x0056b8a0
}