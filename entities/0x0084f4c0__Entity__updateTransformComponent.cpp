// FUNC_NAME: Entity::updateTransformComponent
// Reconstructed C++ for address 0x0084f4c0
// Role: Updates one component of a 4-float vector (offset 0x1a0-0x1ac) using time-based interpolation,
// then passes the result to a virtual method via vtable at offset 0xd0.

// Global constants (addresses from DAT_ref)
extern float g_timeScale;       // DAT_012067e8
extern float g_globalMultiplier; // DAT_00e4499c

// Forward declaration of the class containing this method
class SomeEntity;

// Virtual function typedef: void (*SetTransformFunc)(void* this, const Vector4* transform);
// The class at offset 0xd0 has a vtable; function at slot 16 (0x40/4) receives a Vector4 pointer.

struct Vector4 {
    float x;  // +0x00
    float y;  // +0x04
    float z;  // +0x08
    float w;  // +0x0c
};

// Thischall method: Entity::updateTransformComponent(float deltaTime)
void __thiscall Entity::updateTransformComponent(int thisPtr, float deltaTime)
{
    // Read original components from object offsets (0x1a0, 0x1a4, 0x1a8, 0x1ac)
    float origX = *(float*)(thisPtr + 0x1a0);
    float origY = *(float*)(thisPtr + 0x1a4);
    float origZ = *(float*)(thisPtr + 0x1a8);
    float origW = *(float*)(thisPtr + 0x1ac);

    // Compute new Y component: time-integrated
    float newY = g_timeScale * deltaTime * g_globalMultiplier + origY;

    // Assemble the updated transform vector
    Vector4 localTransform;
    localTransform.x = origX;
    localTransform.y = newY;    // Updated
    localTransform.z = origZ;
    localTransform.w = origW;

    // Call debug/profile function (no parameters)
    FUN_009f2000();

    // Virtual call: get vtable pointer at offset 0xd0, then vtable slot 16 (offset 0x40)
    void* vtablePtr = *(void**)(thisPtr + 0xd0);
    void (*setTransform)(void*, const Vector4*) = (void (*)(void*, const Vector4*))(*(int*)((int)vtablePtr + 0x40));
    setTransform(thisPtr, &localTransform);
}