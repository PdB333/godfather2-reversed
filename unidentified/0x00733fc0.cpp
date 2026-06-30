// FUN_NAME: WheeledVehicle::getFacingAngle
// Address: 0x00733fc0
// Role: Returns current facing angle (yaw) of the vehicle; recalculates if dirty flag bit 3 is set.
//       Retrieves heading from physics object at offset 0x30 of the global physics manager.

float WheeledVehicle::getFacingAngle() {
    // Check dirty flag at +0x1f58, bit 3
    if ((*(uint32_t*)(this + 0x1f58) >> 3) & 1) {
        // Clear bit 3
        *(uint32_t*)(this + 0x1f58) &= ~0x8;

        // Only recalculate if state at +0x1c78 is non-zero and not special value 0x48
        if (*(int32_t*)(this + 0x1c78) != 0 && *(int32_t*)(this + 0x1c78) != 0x48) {
            // Get pointer to something (e.g., physics world/chassis)
            int32_t physicsObj = FUN_00471610();  // Returns pointer
            // Fetch X and Y components from physics object at offset 0x30
            float headingX = FUN_00470250(physicsObj + 0x30);
            float headingY = FUN_0046fd30(physicsObj + 0x30);
            // Store computed heading components
            *(float*)(this + 0x204c) = headingX;
            *(float*)(this + 0x2050) = headingY;
        }
    }
    // Return stored Y component (presumably the angle)
    return *(float*)(this + 0x2050);
}