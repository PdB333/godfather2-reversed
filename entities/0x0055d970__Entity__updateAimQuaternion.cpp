// FUNC_NAME: Entity::updateAimQuaternion
// Address: 0x0055d970
// This function reads a 3D position vector from the entity (at +0x30) and a global rotation constant,
// constructs a quaternion (w,x,y,z), and converts it to an output representation.
// It also checks an alert state flag on another object (EDI) and triggers a debug/audio call if set to 7.

void Entity::updateAimQuaternion(void)
{
    // Call base class / helper function (possibly handles frame updates)
    FUN_004b59d0();

    // Debug/log buffer (60 bytes) – likely filled with entity name or state
    char debugBuffer[60];
    FUN_00aa3930(debugBuffer);

    // Read position vector from this+0x30 (x, y, z)
    float posX = *(float *)((uintptr_t)this + 0x30);
    float posY = *(float *)((uintptr_t)this + 0x34);
    float posZ = *(float *)((uintptr_t)this + 0x38);
    // Global constant (e.g., half-angle or w component for direction quaternion)
    float wComponent = DAT_00e2b1a4;

    // Build quaternion on stack: w, x, y, z
    float quat[4] = { posX, posY, posZ, wComponent };

    // Check if another object (likely a state manager or controller at EDI) has an alert flag
    // *((int*)EDI + 0x18) -> another pointer -> char at +0xD8 == 7 (ASCII BEL = alert)
    int *statePtr = *(int **)((uintptr_t)edi + 0x18);
    if (*(char *)((uintptr_t)statePtr + 0xD8) == '\a')
    {
        // Trigger alert effect (e.g., sound, visual, or debug output)
        FUN_009f4240(1, 1, 0);
    }

    // Convert quaternion to a different representation (e.g., forward vector or Euler angles)
    // Output buffer is 16 bytes (4 floats)
    float result[4];
    FUN_009f4ca0(&quat, result);
}