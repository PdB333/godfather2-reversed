// FUNC_NAME: GameObject::setOrientation
// 0x004deb80 - Sets the object's orientation quaternion. If valid (non-zero x,y,z), copies from input to internal buffer and updates pointer. Otherwise zeros x,y,z and clears pointer.
void __thiscall GameObject::setOrientation(float *quat)
{
    // Check for null pointer and non-zero rotation (x, y, z)
    if (quat != nullptr && 
        (quat[0] != 0.0f || quat[1] != 0.0f || quat[2] != 0.0f))
    {
        float x = quat[0];
        float y = quat[1];
        float z = quat[2];
        float w = quat[3];

        // Copy quaternion into internal storage at +0xD0
        *(float *)(this + 0xD0) = x;   // +0xD0: orientation quaternion x
        *(float *)(this + 0xD4) = y;   // +0xD4: orientation quaternion y
        *(float *)(this + 0xD8) = z;   // +0xD8: orientation quaternion z
        *(float *)(this + 0xDC) = w;   // +0xDC: orientation quaternion w

        // Set pointer at +0xBC to point to the internal quaternion data
        *(float **)(this + 0xBC) = (float *)(this + 0xD0); // +0xBC: pointer to current orientation
    }
    else
    {
        // Clear rotation parts (x,y,z) and null the pointer; w is left unchanged
        *(float *)(this + 0xD0) = 0.0f; // +0xD0: orientation quaternion x = 0
        *(float *)(this + 0xD4) = 0.0f; // +0xD4: orientation quaternion y = 0
        *(float *)(this + 0xD8) = 0.0f; // +0xD8: orientation quaternion z = 0
        *(float **)(this + 0xBC) = nullptr; // +0xBC: clear pointer
    }
}