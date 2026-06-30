// FUNC_NAME: CrewLeaderComponent::updateActiveJobs
void __fastcall CrewLeaderComponent::updateActiveJobs(CrewLeaderComponent* this)
{
    int i;
    SlotEntry* entry;

    // Check if the "jobsDirty" flag (bit 2) is set at offset 0x3d4
    if ((*(uint*)((int)this + 0x3d4) >> 2 & 1) != 0)
    {
        // Iterate over 20 job slots; each SlotEntry is 12 bytes (0xC)
        // SlotEntry layout (offsets relative to entry start):
        //   +0x00: flags (uint) – bit 1 indicates "active"
        //   +0x04: state (uint)
        //   +0x08: actionType (uint) – compared to 2 (might be "job_go" or similar)
        entry = (SlotEntry*)((int)this + 0x2C); // Array starts at 0x2C
        for (i = 0x14; i > 0; i--)
        {
            // Check if slot is active (flags bit 1) and has action type 2
            if (((entry->flags >> 1 & 1) != 0) && (entry->actionType == 2))
            {
                // Process this slot – calls FUN_006abee0 (likely executeJob)
                this->executeJobAction();
            }
            entry++; // Move to next slot (sizeof SlotEntry = 0xC)
        }

        // Reset the dirty flag and clear slot data
        *(int*)((int)this + 0x3d0) = 0x14;  // +0x3d0: activeJobCount = 20 (reset count)
        *(uint*)((int)this + 0x3d4) &= 0xfffffffb; // Clear bit 2
        *(int*)((int)this + 1000) = 0;       // +0x3e8: some timer/state
        *(int*)((int)this + 0x3ec) = 0;      // +0x3ec: another counter
    }
}