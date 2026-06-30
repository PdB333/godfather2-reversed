// FUNC_NAME: Player::exitVehicle

// Function at 0x00707cd0
// Called when player exits a vehicle. Clears the in-vehicle flag and
// calls the vehicle detachment function (FUN_00540700).
void __thiscall Player::exitVehicle(Player* this)
{
    // Offset 0x1b0: m_pCurrentVehicle (pointer to vehicle entity)
    // Offset 0x1d0: m_flags (bitfield)
    // Bit 0xd (0x2000): FLAG_IN_VEHICLE
    static const uint FLAG_IN_VEHICLE = 0x2000;

    void* pVehicle = *(void**)((uint)this + 0x1b0);
    uint flags = *(uint*)((uint)this + 0x1d0);

    if (pVehicle != NULL && (flags & FLAG_IN_VEHICLE) != 0)
    {
        // Clear the "inside vehicle" flag
        *(uint*)((uint)this + 0x1d0) = flags & ~FLAG_IN_VEHICLE;

        // Notify vehicle that player is leaving
        FUN_00540700(pVehicle);
    }
}