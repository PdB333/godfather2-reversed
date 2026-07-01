// FUNC_NAME: Player::isVehicleEntryAllowed
bool __thiscall Player::isVehicleEntryAllowed(Player* this) {
    // Check bit 14 (0xe) of playerStateFlags at +0xf28
    bool isActionPossible = (this->playerStateFlags >> 0xe) & 1;
    // Check bit 11 (0xb) of vehicleStateFlags at +0xc88
    bool isInCarTransition = (this->vehicleStateFlags >> 0xb) & 1;
    return isActionPossible && !isInCarTransition;
}