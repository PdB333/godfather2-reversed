// FUNC_NAME: CrewLeaderComponent::hasReadyCrewSlot
// Function at 0x0090b180: Checks if any crew slot (at this+0x18) has bit0=1 and bit1=0.
// Each slot is 36 bytes (9 uint32s). Returns 1 if found, 0 otherwise.
// __fastcall: this in ECX.

bool __fastcall CrewLeaderComponent::hasReadyCrewSlot(void)
{
    uint *slotFlags = (uint *)((int)this + 0x18); // +0x18: start of crew slot array (4 slots)
    int slotIndex = 0;

    while (true)
    {
        // Check if slot is "ready": bit0 set (active) and bit1 clear (not busy/pending)
        if ((*slotFlags & 1) != 0 && ((*slotFlags >> 1) & 1) == 0)
        {
            return true;
        }

        slotIndex++;
        slotFlags += 9; // advance to next slot (9 * 4 = 36 bytes)
        if (slotIndex > 3)
        {
            return false;
        }
    }
}