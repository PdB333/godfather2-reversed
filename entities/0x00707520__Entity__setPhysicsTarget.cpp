// FUNC_NAME: Entity::setPhysicsTarget
void __thiscall Entity::setPhysicsTarget(int *thisPtr, int *targetVec4)
{
    // Check if target vector is non-zero (all 4 components zero implies no movement)
    if (targetVec4[0] == 0 && targetVec4[1] == 0 && targetVec4[2] == 0 && targetVec4[3] == 0) {
        return;
    }

    // Get some engine-provided ID (e.g., physics world handle, session ID, or random seed)
    // FUN_005e3070 likely returns a uint32 from engine context
    uint32_t engineID = FUN_005e3070();

    // Create a physics body or handle based on the target vector and engine ID
    // Returns 0 on failure
    int physicsHandle = FUN_005e6500(targetVec4, engineID);
    if (physicsHandle != 0) {
        // Get a base transform offset from the entity's parent or some manager
        // FUN_00471610 likely returns a pointer to a transform matrix
        int baseTransform = FUN_00471610();

        // Attach the physics body to the entity at offset +0x30 into the transform
        FUN_005e6580(physicsHandle, baseTransform + 0x30); // +0x30 = position offset within transform

        // Call virtual function at vtable offset 0x58 (likely getRotationQuaternion or similar)
        // (**(code **)(*this + 0x58))() returns a 32-bit value (e.g., packed rotation or quaternion)
        uint32_t rotationValue = (*(code **)(*thisPtr + 0x58))();

        // Set the physics body's rotation
        FUN_005e67c0(physicsHandle, rotationValue);
    }
    return;
}