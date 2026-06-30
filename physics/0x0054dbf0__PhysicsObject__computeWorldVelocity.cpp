// FUNC_NAME: PhysicsObject::computeWorldVelocity
void __thiscall PhysicsObject::computeWorldVelocity(float *outVelocity) {
    // Subobject at offset +0x18 (likely a motion state or rigid body)
    // Call virtual function at vtable+0x18 that returns a pointer to orientation data (5 floats?)
    float *data = (float *)(*(int (__thiscall **)(int))(*(int *)(this + 0x18) + 0x18))(*(int *)(this + 0x18));

    // The returned data contains at least 5 floats; likely a quaternion or matrix row
    float a = data[0]; // data[0]
    float b = data[1]; // data[1]
    float c = data[2]; // data[2]
    float d = data[3]; // data[3]
    float e = data[4]; // data[4]

    float scale = DAT_00e2cd54; // Global speed/scale factor (e.g., game units per second)

    // Combine orientation components to produce a world-space velocity vector
    outVelocity[0] = (c + a) * scale; // x component
    outVelocity[1] = (d + a) * scale; // y component
    outVelocity[2] = (e + b) * scale; // z component
}