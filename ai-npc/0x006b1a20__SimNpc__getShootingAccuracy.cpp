// FUNC_NAME: SimNpc::getShootingAccuracy
uint32_t __fastcall SimNpc::getShootingAccuracy(SimNpc* this) {
    uint32_t accuracy = *(uint32_t*)((int)this + 200);  // +0xC8 - base shooting accuracy attribute
    if (*(int*)((int)this + 0x16c) != 0) {              // +0x16C - maybe "isInVehicle" or "isSuppressed" flag
        accuracy = 0;                                    // return 0 when in vehicle/suppressed
    }
    return accuracy;
}