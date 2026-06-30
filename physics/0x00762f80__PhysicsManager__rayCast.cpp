// FUNC_NAME: PhysicsManager::rayCast
// Address: 0x00762f80
// This function performs a ray-sphere (or ray-plane) intersection test.
// param_2: ray structure { vec3 origin, vec3 direction, float length }
// param_3: output hit point (vec3)
// Returns 1 if hit, 0 if miss.

int __thiscall PhysicsManager::rayCast(void* thisPtr, float* ray, float* outHitPoint)
{
    float rayLength = ray[6]; // +0x18 (origin=0, direction=12, length=24)

    // Virtual call to a random number generator (vtable at +0x58, offset 0x2c4)
    void* rngObj = *(void**)((int)thisPtr + 0x58); // +0x58: pointer to RNG object
    int* vtable = *(int**)rngObj;
    float randomFloat = (*(float (__thiscall*)(void*))(vtable[0x2c4 / 4]))(rngObj);

    int scenePtr = FUN_00471610(); // likely returns a pointer to the scene/level

    // +0x78 -> pointer to some sub-object; +0xb0 -> base speed/scale factor
    float baseSpeed = *(float*)(*(int*)((int)thisPtr + 0x78) + 0xb0);
    if (baseSpeed < 0.0f) {
        baseSpeed = _DAT_00d5780c; // g_defaultSpeed or similar constant
    }

    // Scale a stored direction vector (gravity? impulse?) by baseSpeed
    // Offsets +0xac, 0xb0, 0xb4 likely represent a vector (e.g., wind or bullet drop)
    float scaledDirX = *(float*)((int)thisPtr + 0xac) * baseSpeed;
    float scaledDirY = *(float*)((int)thisPtr + 0xb0) * baseSpeed;
    float scaledDirZ = *(float*)((int)thisPtr + 0xb4) * baseSpeed;

    float hitScalar; // stores the intersection t value

    // Call the actual intersection routine
    // Arguments: ray origin, potential sphere center at scenePtr+0x30, ray direction,
    // scaled direction, ray length, random jitter, output scalar
    bool hit = FUN_0084c940(ray, scenePtr + 0x30, ray + 3, &scaledDirX,
                            rayLength, randomFloat, &hitScalar);

    if (hit) {
        // Compute world-space hit point
        outHitPoint[0] = ray[0] + ray[3] * hitScalar;
        outHitPoint[1] = ray[1] + ray[4] * hitScalar;
        outHitPoint[2] = ray[2] + ray[5] * hitScalar;
        return 1;
    }

    return 0;
}