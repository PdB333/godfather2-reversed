// FUNC_NAME: SomeGameObject::setRotationFromSource
void SomeGameObject::setRotationFromSource(SomeGameObject *source) {
    // Known class hierarchy: Entity, Sentient, etc. Offsets in this object:
    // +0x10: rotation quaternion x
    // +0x14: rotation quaternion y
    // +0x18: rotation quaternion z
    // +0x1c: rotation quaternion w
    // Source object uses same layout.

    // Global constant (likely 1.0f or 0.0f) used for w component.
    static const float fixedW = DAT_00e2b1a4;

    // Temporary quaternions for intermediate computation
    struct Quat { float x, y, z, w; };
    Quat temp1 = { 0.0f, 0.0f, 0.0f, fixedW };
    Quat temp2 = { 0.0f, 0.0f, 0.0f, fixedW };

    // First helper: possibly quaternion from euler or orientation setup
    FUN_00582ac0();

    // Second helper: operates on temp1, likely an identity or conversion function
    FUN_0056cba0(&temp1);

    // Copy source rotation axis components (x,y,z) into this rotation
    // temp2.x,temp2.y,temp2.z are all zero, so this is essentially a direct copy
    this->rotation.x = source->rotation.x + temp2.x;
    this->rotation.y = source->rotation.y + temp2.y;
    this->rotation.z = source->rotation.z + temp2.z;

    // Force w component to the fixed constant (overwrites any source contribution)
    this->rotation.w = fixedW;
}