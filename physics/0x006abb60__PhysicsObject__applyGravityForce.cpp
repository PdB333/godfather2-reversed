// FUNC_NAME: PhysicsObject::applyGravityForce

struct PhysicsObject {
    float field_0x20; // +0x20 - likely velocity component (e.g., Y-velocity)
    float field_0x2c; // +0x2c - likely acceleration component to apply
};

extern float s_gravityForce; // DAT_01205228 - global gravity constant per frame

void __fastcall PhysicsObject::applyGravityForce() {
    // Add global gravity constant to current velocity to produce acceleration
    this->field_0x2c = this->field_0x20 + s_gravityForce;
}