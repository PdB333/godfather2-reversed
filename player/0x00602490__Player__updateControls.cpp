// FUNC_NAME: Player::updateControls
void __thiscall Player::updateControls(Player *this, int inputState, float timeDelta, int extraData)
{
    // +0x48: vehicle pointer (if non-null, player is in a vehicle)
    if (this->vehicle != 0)
    {
        // Vehicle mode: skip timeDelta parameter
        Player::updateVehicleControls(this, inputState, extraData);
        return;
    }
    // On-foot mode: full parameters
    Player::updateOnFootControls(this, inputState, timeDelta, extraData);
    return;
}