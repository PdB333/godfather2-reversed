// FUNC_NAME: Player::releaseVehicle
void __fastcall Player::releaseVehicle(int thisPtr)
{
    int vehiclePtr = *(int *)(thisPtr + 0x1bc8); // +0x1bc8: pointer to current vehicle
    if (vehiclePtr != 0) {
        // Reset vtable pointers of the vehicle to a null/base vtable (PTR_LAB_00d7006c)
        *(void ***)(vehiclePtr + 0xb8) = &PTR_LAB_00d7006c; // +0xb8: vtable slot 1
        *(void ***)(vehiclePtr + 0x9c) = &PTR_LAB_00d7006c; // +0x9c: vtable slot 2
        *(void ***)(vehiclePtr + 0x80) = &PTR_LAB_00d7006c; // +0x80: vtable slot 3
        *(void ***)(vehiclePtr + 100) = &PTR_LAB_00d7006c;  // +0x64: vtable slot 4
        *(void ***)(vehiclePtr + 0x48) = &PTR_LAB_00d7006c; // +0x48: vtable slot 5
        *(void ***)(vehiclePtr + 0x2c) = &PTR_LAB_00d7006c; // +0x2c: vtable slot 6
        sub_9c8eb0(vehiclePtr); // Destroy/release the vehicle object
        *(int *)(thisPtr + 0x1bc8) = 0; // Clear vehicle pointer
        // Clear flags: bit 22 at +0x1b94, bit 4 at +0x974
        *(unsigned int *)(thisPtr + 0x1b94) &= 0xffbfffff; // Clear bit 22 (0x400000)
        *(unsigned int *)(thisPtr + 0x974) &= 0xffffffef;  // Clear bit 4 (0x10)
        sub_9c4ea0(1); // Notify system of vehicle release
        sub_7f60e0();  // Update global state
    }
}