// FUNC_NAME: Transform::operator=
// Address: 0x0082ac30
// Role: Copy assignment operator for a 7-float transform (position + quaternion)
class Transform {
public:
    // +0x4c position.x, +0x50 position.y, +0x54 position.z
    // +0x60 rotation.w? (or x), +0x64 rotation.x, +0x68 rotation.y, +0x6c rotation.z
    Transform& __thiscall operator=(const Transform& other) {
        if (this != &other) {
            // Unknown preprocessing step (possibly duplicates or cleans source)
            FUN_00820830(other);
            // Copy position
            *(reinterpret_cast<const float*>(&other) + 0x4c / 4) = *(reinterpret_cast<const float*>(this) + 0x4c / 4); // Note: cast adjusted for clarity
            // Simplified copy as per original:
            *(float*)((unsigned int)this + 0x4c) = *(float*)((unsigned int)&other + 0x4c);
            *(float*)((unsigned int)this + 0x50) = *(float*)((unsigned int)&other + 0x50);
            *(float*)((unsigned int)this + 0x54) = *(float*)((unsigned int)&other + 0x54);
            // Copy rotation
            *(float*)((unsigned int)this + 0x60) = *(float*)((unsigned int)&other + 0x60);
            *(float*)((unsigned int)this + 0x64) = *(float*)((unsigned int)&other + 0x64);
            *(float*)((unsigned int)this + 0x68) = *(float*)((unsigned int)&other + 0x68);
            *(float*)((unsigned int)this + 0x6c) = *(float*)((unsigned int)&other + 0x6c);
        }
        return *this;
    }
};