// FUNC_NAME: Player::checkAndUpdateControlledState

void __fastcall Player::checkAndUpdateControlledState(int thisPtr)
{
    bool flag = true;
    int currentIndex = *(int *)(thisPtr + 0x9c);                    // +0x9c: current controlled entity index
    int entityPtr = *(int *)(thisPtr + 0x58 + currentIndex * 8);   // +0x58: array of 8-byte entries (pointer + ?)

    if (entityPtr != 0) {
        int aliveCheck = FUN_006b0ee0(entityPtr);                  // likely checks if entity is alive/valid
        if (aliveCheck != 0) {
            int vehicleState = FUN_006b4860();                    // probably checks if entity is using a vehicle
            if (vehicleState != 0) {
                flag = false;
            }
        }
    }
    *(bool *)(thisPtr + 0xb0) = !flag;                            // +0xb0: flag (e.g., isUsingVehicle, isControllingActive)
    *(int *)(thisPtr + 0x9c) = -1;                                // reset index
}