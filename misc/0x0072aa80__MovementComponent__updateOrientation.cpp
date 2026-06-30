// FUNC_NAME: MovementComponent::updateOrientation
void __fastcall MovementComponent::updateOrientation(MovementComponent* this) // 'this' points to subobject at offset 0x3a0 within owning Entity
{
    // Call virtual function at index 0x28 / 4 = 10 on the memory allocator? (likely allocate temporary buffer)
    (**(code**)(*(int*)((char*)this - 0x348) + 0x28))(0x10);

    // Get pointer to the component itself (at offset 0x3a0 from Entity base)
    MovementComponent* component = (MovementComponent*)((char*)this - 0x3a0);
    if (component != nullptr) {
        // Obtain game manager instance (likely GameStateManager or EntityManager)
        int* manager = (int*)FUN_0043b870(DAT_01131040);
        if (manager != nullptr && manager[7] != 0 && manager[7] != 0x48) { // manager[7] at offset 0x1c, check active state
            // Call virtual function at index 0x1c / 4 = 7 on manager (e.g., isPaused())
            char ret = (**(code**)(*manager + 0x1c))(0x100);
            if (ret != 0) {
                // Call virtual function at index 0xc4 / 4 = 49 (getSomeAngle?) returns float
                float angle = (**(code**)(*component + 0xc4))(); // e.g., getYaw()
                // Call virtual function at index 0xc0 / 4 = 48 (computeTargetAngle?) returns float
                float targetAngle = (**(code**)(*component + 0xc0))(angle); // e.g., computeTurnAngle(angle)
                // Set the component's orientation using the computed angle
                FUN_009395a0(component, targetAngle, angle); // e.g., setOrientation(targetAngle, currentAngle)
            }
        }
    }
}