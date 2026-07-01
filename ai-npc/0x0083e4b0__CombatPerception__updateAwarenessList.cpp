// FUNC_NAME: CombatPerception::updateAwarenessList
void __thiscall CombatPerception::updateAwarenessList(void* this, bool bForceAll, int param3)
{
    int count = *(int*)((char*)this + 0x98);            // +0x98: number of entries in array
    float thresholdDist = *(float*)((char*)this + 0x6c); // +0x6c: distance threshold (forget range?)
    int* entryArray = *(int**)((char*)this + 0x94);     // +0x94: pointer to array of 8‑byte entries

    for (int i = count - 1; i >= 0; i--)
    {
        int* entryPtr = (int*)entryArray[i * 2]; // first 4 bytes of entry = pointer to some object
        // Skip invalid or special entries (0x48 = deleted/uninitialized?)
        if (entryPtr == 0 || entryPtr == (int*)0x48) continue;
        // If param3 is false, also skip entries whose object has a non‑zero field at +0x110 (maybe "already processed"?)
        if (param3 == 0 && *(int*)((char*)entryPtr + 0x110) != 0) continue;

        if (bForceAll)
        {
            // Get player/camera object (returns pointer to a character or camera)
            int* player = (int*)FUN_00471610();

            // Build a mask from bits 18–25 of this+0xa8 flags
            uint mask = ((*(uint*)((char*)this + 0xa8) >> 0x12) & 0xFF) | 0x0100;

            // Check something related to the player's position (e.g., line of sight?)
            if (FUN_006c0050((float*)((char*)player + 0x30), 1, mask))
            {
                float local_c, local_8, local_4;
                // Get position of *this* object? (or of the entry's object?)
                FUN_00424fb0(&local_c, 0);

                float dx = *(float*)((char*)player + 0x30) - local_c;
                float dy = *(float*)((char*)player + 0x34) - local_8;
                float dz = *(float*)((char*)player + 0x38) - local_4;

                // If the object is farther than thresholdDist, mark it for update
                if (thresholdDist * thresholdDist <= dx*dx + dy*dy + dz*dz)
                {
                    goto label_updateEntry;
                }
            }
            else
            {
                // If the check failed (e.g., out of sight?), still go to update
                goto label_updateEntry;
            }
            // If we reach here, the object is within range – skip update for this entry
        }
        else
        {
label_updateEntry:
            // Global condition: skip if the player pointer is non‑null and equal to some special value (0x1f30)?
            int* gPlayer = **(int***)(DAT_012233a0 + 4);
            if (gPlayer == 0 || gPlayer == (int*)0x1f30 || 
                FUN_007ff880() != (int)((char*)entryPtr - 0x48))
            {
                // Call the actual update function (index i, param3)
                FUN_0083dea0(i, param3);

                // If bit 0 of flags is set, record a random time (maybe for next update)
                if (*(byte*)((char*)this + 0xa8) & 1)
                {
                    float newTime = (float)FUN_0083b4f0();
                    *(float*)((char*)this + 0xa0) = newTime; // +0xa0: next update timer
                }
            }
        }
        // Continue loop to next entry
    }
}