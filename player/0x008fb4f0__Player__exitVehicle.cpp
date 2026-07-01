// FUNC_NAME: Player::exitVehicle
// Function address: 0x008fb4f0
// Role: Handles player exiting a vehicle, setting flags, timers, and performing exit animations.
// This function is a member of the Player class (EARS::Player).
// It checks if the vehicle is valid and if the player is not already in a certain state.
// It then calls vehicle exit preparation, updates flags, stores exit type, and starts an exit timer.

uint __thiscall Player::exitVehicle(Player* this, Vehicle* vehicle, char immediateExit)
{
    uint* puVar1;
    uint uVar2;
    int exitType;
    // Timer structure for exit delay
    struct {
        int field_0;
        int field_4;
        char field_8;
    } exitTimer;

    uVar2 = 0;
    // Guard: vehicle must be valid, and the player must have a valid vehicle component (at +0x160)
    // and the bit at offset 0x249c within that component must not be set (bit 0x08000000? Actually bit 27 of that uint)
    if ((vehicle != (Vehicle*)0) && (*(int*)(this + 0x160) != 0) &&
        ((*(uint*)(*(int*)(this + 0x160) + 0x249c) >> 0x1b & 1) == 0)) {
        // Prepare and execute vehicle exit
        vehicleExitPrepare(vehicle);  // FUN_008fa2b0
        vehicleExit(vehicle);         // FUN_008f8370

        // Clear bit 3 (0x8) in flags at +0xa8 (e.g., maybe "inVehicle" flag)
        *(uint*)(this + 0xa8) = *(uint*)(this + 0xa8) & 0xfffffff7;
        // Set bit 1 (0x2) in flags at +0x170 (e.g., "exitingVehicle" flag)
        *(uint*)(this + 0x170) = *(uint*)(this + 0x170) | 2;

        // Set or clear bit 8 (0x100) in flags at +0x170 based on immediateExit parameter
        if (immediateExit == '\0') {
            *(uint*)(this + 0x170) = *(uint*)(this + 0x170) & 0xfffffeff;
        }
        else {
            *(uint*)(this + 0x170) = *(uint*)(this + 0x170) | 0x100;
        }

        // Set bit 6 (0x40) in flags at +0x170 (e.g., "exitInProgress")
        *(uint*)(this + 0x170) = *(uint*)(this + 0x170) | 0x40;

        // Set a bit in the vehicle component at +0x160 +0x249c (bit 0x40000, i.e., 1<<18)
        puVar1 = (uint*)(*(int*)(this + 0x160) + 0x249c);
        *puVar1 = *puVar1 | 0x40000;

        // Store the vehicle's exit type (from vehicle+0x50) into this+0x178
        *(int*)(this + 0x178) = *(int*)(vehicle + 0x50);
        // Get the exit type value (likely 0,1,2) and store it at this+0x174
        exitType = getExitType(*(int*)(vehicle + 0x50));  // FUN_008fa5d0
        *(int*)(this + 0x174) = exitType;

        // Play exit sound using global audio objects
        playExitSound(DAT_01205224, DAT_012067e8);  // FUN_008faf10

        // If exit type is 2 (e.g., "jump out" or "panic"), trigger additional actions
        if (*(int*)(this + 0x174) == 2) {
            onExitTypeTwo();  // FUN_008fb330
            onExitTypeTwoAction();  // FUN_008fa460
        }

        // Initialize exit timer (0 duration, 0 interval, 0 flags)
        exitTimer.field_0 = DAT_0112fe64;  // likely global timer value
        exitTimer.field_4 = 0;
        exitTimer.field_8 = 0;
        startTimer(&exitTimer, 0);  // FUN_00408a00

        uVar2 = 1;  // Return success
    }
    return uVar2;
}