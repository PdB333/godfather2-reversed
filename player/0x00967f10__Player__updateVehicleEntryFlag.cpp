// FUNC_NAME: Player::updateVehicleEntryFlag
// Address: 0x00967f10
// Role: Checks if the player is in a waiting-for-vehicle state (state==5) and if the vehicle-ready flag (bit18) is set,
//       then sets the enter-vehicle flag (bit16). Calls a base update function at 0x00982c90 (likely Player::baseUpdate).

class Player {
public:
    // Offsets: +0x1F4 (500) = byte, possibly crouch/cover state flag
    // +0xDC (220) = int, current gameplay state enum (5 = waitingForVehicle)
    // +0x6F4 (1780) = uint, flags bitfield (bit16=0x10000, bit18=0x40000)
    void __thiscall updateVehicleEntryFlag();
};

void __thiscall Player::updateVehicleEntryFlag()
{
    // Call base update (probably does generic state updates)
    FUN_00982c90(); // Player::updateBaseState (0x00982c90)

    // Check conditions: player is in a state supporting vehicle entry,
    // the "near vehicle" flag is already on, and the vehicle is ready to be entered.
    if ((*(unsigned char *)(this + 0x1F4) != 0) &&          // possibly "allowVehicleEntry" flag
        (*(int *)(this + 0xDC) == 5) &&                      // current state == waitingForVehicle
        ((*(unsigned int *)(this + 0x6F4) >> 0x12) & 1) != 0) // bit18 (0x40000) set (vehicle ready)
    {
        *(unsigned int *)(this + 0x6F4) |= 0x10000;         // set bit16 (0x10000) – enter vehicle request
    }
    // No return value.
}