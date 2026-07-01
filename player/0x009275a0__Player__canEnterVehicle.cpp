// FUNC_NAME: Player::canEnterVehicle
bool __fastcall Player::canEnterVehicle(Player* thisPtr)
{
    // Check if the player is not already in a vehicle (+0x3c7) and is in a state that allows entering (+0x3c5)
    if (thisPtr->field_0x3c7 == 0 && thisPtr->field_0x3c5 != 0) {
        return true;
    }
    return false;
}