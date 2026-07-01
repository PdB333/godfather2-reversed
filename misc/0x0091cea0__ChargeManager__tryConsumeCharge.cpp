// FUNC_NAME: ChargeManager::tryConsumeCharge
// Function address: 0x0091cea0
// Role: Attempts to consume a charge from an internal pool, updating external resource count if conditions are met.
// Offsets:
//   +0x94: byte flag (active/inactive)
//   +0xa4: uint chargeCount (number of charges available)
//   +0x9c: int reserveThreshold (minimum charges to keep, computed as max(1, chargeCount-5))
//   +0x98: int updatedChargeCount (chargeCount - 1 after consumption)

void __thiscall ChargeManager::tryConsumeCharge(int *externalCount, int increment)
{
    uint chargeCount;

    // Check if system is active, external resource not full, and we have more than 1 charge
    if ((*(char *)(this + 0x94) == '\0') && ((uint)(*externalCount + increment) < 10) &&
        (chargeCount = *(uint *)(this + 0xa4), 1 < chargeCount))
    {
        int reserve = 1;
        if (5 < chargeCount)
        {
            reserve = chargeCount - 5;
        }
        *(int *)(this + 0x9c) = reserve;
        *(uint *)(this + 0x98) = chargeCount - 1;
        FUN_0091cd80(0, 0); // Possibly triggers an event or callback
    }
    // Always update the external resource count
    FUN_0095c540(externalCount, increment);
}