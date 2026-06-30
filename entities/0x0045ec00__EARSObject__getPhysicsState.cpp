// FUNC_NAME: EARSObject::getPhysicsState
int __thiscall EARSObject::getPhysicsState(float *outVelocity, D3DXVECTOR4 *outRotation)
{
    PhysicsBody *body = *(PhysicsBody **)((char *)this + 0x218); // entity's physics body
    if (body != nullptr)
    {
        if (outVelocity != nullptr)
        {
            // Read velocity vector from body (X, Y, Z, W)
            float vx = *(float *)((char *)body + 0x90); // +0x90: velocity.x
            float vy = *(float *)((char *)body + 0x94); // +0x94: velocity.y
            float vz = *(float *)((char *)body + 0x98); // +0x98: velocity.z
            float vw = *(float *)((char *)body + 0x9c); // +0x9c: velocity.w (unused?)

            outVelocity[0] = vx;
            outVelocity[1] = vy;
            outVelocity[2] = vz;
            outVelocity[3] = vw;

            float scale = *(float *)((char *)this + 0x294); // speed multiplier (e.g., from character state)
            const float defaultScale = *(float *)0x00e2b1a4; // global default (likely 1.0f)
            if (scale != defaultScale)
            {
                // Scale only the positional components; keep the w component as-is
                outVelocity[0] = scale * outVelocity[0];
                outVelocity[1] = scale * outVelocity[1];
                outVelocity[2] = scale * outVelocity[2];
                outVelocity[3] = vw; // restore original w
            }
        }

        if (outRotation != nullptr)
        {
            // Read rotation quaternion from body
            float rx = *(float *)((char *)body + 0x80); // +0x80: rotation.x
            float ry = *(float *)((char *)body + 0x84); // +0x84: rotation.y
            float rz = *(float *)((char *)body + 0x88); // +0x88: rotation.z
            float rw = *(float *)((char *)body + 0x8c); // +0x8c: rotation.w

            outRotation->x = rx;
            outRotation->y = ry;
            outRotation->z = rz;
            outRotation->w = rw;
        }

        return 1; // success
    }
    return 0; // no physics body
}