// FUNC_NAME: RaycastQuery::execute
uint __thiscall RaycastQuery::execute(int* this, RaycastResult* result)
{
    // Global constant representing infinite distance (FLT_MAX)
    float infinity = *(float*)0x00e2b1a4;

    // Initialize result structure to default (no hit)
    result->point1[0] = 0.0f; // result[4] as int
    result->point1[1] = 0.0f;
    result->point1[2] = 0.0f;
    result->point1[3] = infinity; // w component set to inf
    result->point2[0] = 0.0f; // result[8]
    result->point2[1] = 0.0f;
    result->point2[2] = 0.0f;
    result->point2[3] = infinity;

    float startDist = result->startDistance; // result[1]
    float endDist   = result->endDistance;   // result[2]
    // this[9] is ray max length (float at offset 0x24)
    float rayLength = *(float*)&this[9] - infinity; // typical use: rayLength = maxRange - infinity? Actually this[9] might be a negative value? We keep as decompiled.

    if (startDist < rayLength)
    {
        // Clamp end distance to ray length
        float clampedEnd = endDist;
        if (rayLength <= endDist)
            clampedEnd = rayLength;

        if (startDist < clampedEnd)
        {
            uint collisionMask = GetCollisionFlags(); // FUN_00571070

            // If this query object equals the ignore object, clear bit 4 (0x10)
            if (this == (int*)result->ignoreObject)
                collisionMask &= ~0x10;
            else
                collisionMask |= 0x10;

            // Save current query state
            int savedFlags  = this[4]; // offset 0x10
            int savedField7 = this[7]; // offset 0x1c
            int savedField8 = this[8]; // offset 0x20

            this[4] |= 0x801000; // set collision flags
            this[7] = *(int*)&clampedEnd; // store clamped end distance
            this[8] = *(int*)&startDist;  // store start distance

            // Virtual call (vtable offset 0xC) – actual raycast implementation
            code* vf = *(code**)(*this + 0xC);
            int hitInfo = (*vf)(result->ignoreObject, collisionMask);

            if (hitInfo != 0)
            {
                // Copy hit data (two 4-vector results) from the raycast engine
                // hitInfo + 0x10: first vector (e.g., hit point)
                // hitInfo + 0x20: second vector (e.g., hit normal)
                result->point1[0] = *(float*)(hitInfo + 0x10);
                result->point1[1] = *(float*)(hitInfo + 0x14);
                result->point1[2] = *(float*)(hitInfo + 0x18);
                result->point1[3] = *(float*)(hitInfo + 0x1C);
                result->point2[0] = *(float*)(hitInfo + 0x20);
                result->point2[1] = *(float*)(hitInfo + 0x24);
                result->point2[2] = *(float*)(hitInfo + 0x28);
                result->point2[3] = *(float*)(hitInfo + 0x2C);
            }

            RestoreCollisionState(); // FUN_0056fb60

            // Restore original query state (the saved values are from stack,
            // but Ghidra shows them as uninitialized locals; likely the compiler
            // saved them on entry and restored here, but the decompile missed.
            // Assume they are correct stack values.)
            this[7] = savedField7; // actually iStack_24
            this[4] = savedFlags;
            this[8] = savedField8; // actually iStack_20

            return (hitInfo != 0) ? 1 : 0;
        }
    }

    // Fallback – return previous EAX value with low byte cleared
    return in_EAX & 0xFFFFFF00;
}