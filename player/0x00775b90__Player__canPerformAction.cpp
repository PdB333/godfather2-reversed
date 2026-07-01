// FUNC_NAME: Player::canPerformAction
bool __thiscall Player::canPerformAction(int param2, int param3, int actionType, int param5) {
    // actionType values 10..18 map to cases 0..8 (switch(actionType - 10))
    // Offsets: +0x5c -> m_pCurrentVehicle (pointer to Vehicle), +0x68 -> m_pCurrentSeat (pointer to seat info)
    // +0x64 (100 decimal) -> m_flags (bit0 = canEnterVehicle?, bit1 = some other flag)
    
    switch (actionType) {
    case 10:  // case 0
    case 17:  // case 7
        // Check bit 0 of flags
        if ((*(uint8*)(this + 0x64) & 1) != 0) {
            return true;
        }
        break;
    
    case 11:  // case 1
        // Check if something is true via external function
        if (FUN_00775740()) {
            return true;
        }
        break;
    
    case 12:  // case 2
        if (FUN_00775770()) {
            return true;
        }
        break;
    
    case 13:  // case 3
        if (FUN_007758f0()) {
            return true;
        }
        break;
    
    case 14:  // case 4
        // Complex condition: game not paused, player not in vehicle or vehicle is null or is empty seat or something
        if ((((FUN_004ac260() != 0) && (*(int*)(this + 0x68) == 0)) || (*(int*)(this + 0x5c) == 0)) ||
            ((*(int*)(this + 0x5c) == 0x48) || (FUN_00724cf0() == 0))) {
            return true;
        }
        break;
    
    case 15:  // case 5
        if ((FUN_004ac260() != 0) && (*(int*)(this + 0x68) != 0)) {
            return true;
        }
        break;
    
    case 16:  // case 6
        // Check bit 1 of flags
        if ((*(uint32*)(this + 0x64) >> 1 & 1) != 0) {
            // If there is a valid vehicle and it is not the empty seat (0x48), set seat from vehicle's seat offset
            if ((*(int*)(this + 0x5c) != 0) && (*(int*)(this + 0x5c) != 0x48)) {
                if (*(int*)(this + 0x5c) != 0) {
                    *(int*)(this + 0x68) = *(int*)(*(int*)(this + 0x5c) + 0x9c); // m_pCurrentSeat = vehicle->seatData
                    return true;
                }
                // Fallback to global zero? Probably a constant 0
                *(int*)(this + 0x68) = 0;  // uRam000000e4 --> 0
                return true;
            }
        }
        break;
    
    case 18:  // case 8
        if ((*(int*)(this + 0x5c) == 0) || (*(int*)(this + 0x5c) == 0x48)) {
            return true;
        }
        break;
    
    default:
        return FUN_004ac640(param2, param3, actionType, param5) != 0;
    }
    
    return false;
}