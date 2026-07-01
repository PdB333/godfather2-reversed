// FUNC_NAME: Player::exitVehicle
char __fastcall Player::exitVehicle(Player* thisPtr)
{
    char result;
    int vehiclePtr;
    int vehicleBase;
    int* occupantList[4];
    int tempInt;
    unsigned int occupantIndex;
    int* occupant;
    char canExit;
    int vtable;

    // Check if player has a current vehicle and it's not a special type (0x48 = car?)
    if (thisPtr->currentVehicle != NULL && thisPtr->currentVehicle != 0x48) {
        // Get base pointer to vehicle object (offset -0x48 from currentVehicle pointer)
        vehiclePtr = thisPtr->currentVehicle;
        if (vehiclePtr == 0) {
            vehicleBase = 0;
        } else {
            vehicleBase = vehiclePtr - 0x48;
        }
        // Also compute vehicleBase again (duplicate check)
        int otherVehicleBase = vehicleBase; // originally iVar3 and iVar2 were same

        // Check vehicle flags: bit 21 (0x200000) or bit 11 (0x800)
        if (((*(uint*)(vehicleBase + 0xc88) >> 0x15) & 1) != 0 ||
            ((*(uint*)(otherVehicleBase + 0xc88) >> 0xb) & 1) != 0) {

            // Get list of occupants (max 4)
            if (getOccupants(occupantList, 4)) {
                for (int i = 0; i < 4; i++) {
                    occupant = occupantList[i];
                    if (occupant != NULL) {
                        // Check number of occupants in this slot? occupant[0x1d1] is count?
                        for (occupantIndex = 0; occupantIndex < (unsigned int)occupant[0x1d1]; occupantIndex++) {
                            // Get occupant by index
                            int* checkOccupant = getOccupantByIndex(occupantIndex);
                            // Check if this occupant has the "player" flag (bit 14 at +0x1d0)
                            if ((*(uint*)(checkOccupant + 0x1d0) >> 0xe) & 1) {
                                // Compare with the specific occupant stored in vehicle (driver slot)
                                int storedOccupant;
                                if (occupant[0x1d3] == 0) {
                                    storedOccupant = 0;
                                } else {
                                    storedOccupant = occupant[0x1d3] - 0x48;
                                }
                                if (storedOccupant == checkOccupant) {
                                    // Eject occupant (virtual call at vtable+600, index 150)
                                    (*(void(**)(int))(*occupant + 600))(0);
                                    // Release occupant slot
                                    thunk_releaseOccupant(occupantIndex);
                                    break;
                                }
                            }
                        }
                        // Clear occupant slot count
                        occupant[0x56] = 0;
                        // Set flag bit 23 (0x800000) at +0x7d6
                        occupant[0x7d6] |= 0x800000;
                        // If vehicle has bit 11 (0x800) set, play exit sounds
                        if ((*(uint*)(vehicleBase + 0xc88) >> 0xb) & 1) {
                            int vehicleValid = isVehicleValid();
                            if (vehicleValid) {
                                playSound(DAT_01131070);
                                stopSound(vehicleValid);
                            }
                        }
                    }
                }
            }
            // Check if occupant (now vehicle base) can exit via virtual call at vtable+0x290 (index 0xA4)
            canExit = (**(char(**)(void))(*vehicleBase + 0x290))();
            if (canExit) {
                // Query interface on vehicle with hash 0x10e5319e (likely "isPlayerControlled")
                if ((**(char(**)(int, int*))(*vehicleBase + 0x10))(0x10e5319e, &tempInt)) {
                    if (unaff_ESI != 0) { // global? likely a player pointer or flag
                        spawnPlayer();
                    }
                }
                // Clear bit 3 (0x8) in player flags at offset 200 (0xC8)
                *(unsigned short*)(thisPtr + 200) &= 0xfff7;
                // Play "player exit" audio event via global audio manager
                if (**(int**)(DAT_012233a0 + 4) != 0) {
                    int audioContext = getAudioContextIndex();
                    playAudioEvent(0x13, audioContext + 0x30, **(int**)(DAT_012233a0 + 4) - 0x1f30, 0);
                }
                // Set bit 6 (0x40) in player flags
                *(unsigned short*)(thisPtr + 200) |= 0x40;
                // Clear bit 0 (0x1) in player flags
                *(unsigned short*)(thisPtr + 200) &= 0xfffe;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}