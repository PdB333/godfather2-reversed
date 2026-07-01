// FUNC_NAME: Player::CanEnterVehicle
bool __fastcall Player::CanEnterVehicle(void* thisPtr) {
    // thisPtr is a Player object (or Sentient)
    // +0x88: pointer to vehicle's entry/exit component (VehicleEntryPoint?) or maybe a pointer to a subobject of a vehicle
    char* vehicleEntry = *(char**)((char*)thisPtr + 0x88);
    if (vehicleEntry == nullptr) {
        return false;
    }
    // 0x48 is a special constant representing "already inside" or invalid state
    if ((int)vehicleEntry == 0x48) {
        return false;
    }

    // Offset back to the vehicle base (0x48 is the offset of the member pointed to by vehicleEntry)
    char* vehicleBase = vehicleEntry - 0x48;

    // Check bit 2 of flags at +0xC88 (e.g., vehicle's drivable flag)
    if ((*(uint32_t*)(vehicleBase + 0xC88) >> 2) & 1) {
        // Global game manager (DAT_012233a0) -> get some state object at offset -0x1F30
        uint32_t** globalTable = (uint32_t**)0x012233a0;  // assume extern
        char* globalObj = nullptr;
        if (globalTable[1] != nullptr) {
            globalObj = (char*)globalTable[1] - 0x1F30;
        }
        // +0x8EA: byte flag (bit 0 – maybe driver input lock?)
        if (globalObj != nullptr && (*(uint8_t*)(globalObj + 0x8EA) & 1)) {
            return false;
        }
    }

    // Check if some component at +0xE80 is null (e.g., maybe an animation state)
    if (*(void**)(vehicleBase + 0xE80) == nullptr) {
        // Check bit 11 of flags at +0xC88
        if (((*(uint32_t*)(vehicleBase + 0xC88) >> 0xB) & 1) == 0) {
            // FUN_00806440 returns some global state (0=menu,1=gameplay,2=cutscene?)
            int gameplayMode = FUN_00806440();
            if (gameplayMode != 2) {
                // Check some other field at +0xA9C (non-zero) and that dialog is not active (FUN_0085e090 with 10)
                if (*(int*)(vehicleBase + 0xA9C) != 0 && FUN_0085e090(10) != 0) {
                    return true;
                }
                return false;
            }
        }
    }

    // If +0xE80 is non-null, or bit 11 is set, or gameplay mode is cutscene, we consider it allowable
    return true;
}