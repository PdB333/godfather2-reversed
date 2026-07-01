// FUNC_NAME: Entity::resetMovementState
// Function address: 0x007c13c0
// Role: Resets linear/angular velocity and speed timer when over threshold (likely speed limiter)

bool __fastcall Entity::resetMovementState(Entity *this) {
    char isActive;
    
    isActive = FUN_00410eb0(); // likely checks if game is unpaused or entity is active
    if (isActive && (DAT_00d6bfe0 < *(float *)((int)this + 0xbc))) {
        // Reset linear velocity (x, y, z) at +0xA4, +0xA8, +0xAC
        *(float *)((int)this + 0xA4) = 0.0f;
        *(float *)((int)this + 0xA8) = 0.0f;
        *(float *)((int)this + 0xAC) = 0.0f;
        // Reset angular velocity (x, y, z) at +0xB0, +0xB4, +0xB8
        *(float *)((int)this + 0xB0) = 0.0f;
        *(float *)((int)this + 0xB4) = 0.0f;
        *(float *)((int)this + 0xB8) = 0.0f;
        // Reset speed threshold at +0xBC
        *(float *)((int)this + 0xBC) = 0.0f;
        return true;
    }
    return false;
}