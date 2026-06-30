// FUNC_NAME: Player::frameUpdate
void __thiscall Player::frameUpdate(Player* this, float* optionalRespawnPosition)
{
    char cVar1;
    int iVar2;
    int iVar3;
    int iVar4;

    // Check if this frame update has already been processed (bit 0 of flags at +0x39e)
    if ((*(byte *)(this + 0x39e) & 1) == 0)
    {
        // Global game manager pointer (e.g., GameManager*)
        iVar4 = **(int **)(DAT_012233a0 + 4);
        if ((iVar4 != 0) && (iVar4 != 0x1f30))
        {
            // Get two player position references (likely current and some target)
            iVar2 = FUN_00471610();  // e.g., getCurrentPlayerTransform()
            iVar3 = FUN_00471610();  // e.g., getRespawnTransform()
            // Compute squared distance between positions (offset +0x30 = position x, +0x34 = y, +0x38 = z)
            float dx = *(float *)(iVar3 + 0x30) - *(float *)(iVar2 + 0x30);
            float dy = *(float *)(iVar3 + 0x34) - *(float *)(iVar2 + 0x34);
            float dz = *(float *)(iVar3 + 0x38) - *(float *)(iVar2 + 0x38);
            if (dx*dx + dy*dy + dz*dz < *(float *)(iVar4 + 0x119c)) // within respawn distance threshold
            {
                // Copy the target position to the player's respawn point
                iVar2 = FUN_00471610();  // get current player transform again
                *(Vector3*)(iVar4 + 0x11a8) = *(Vector3*)(iVar2 + 0x30);
                // Set some rotation or flag at +0x11b4
                *(int *)(iVar4 + 0x11b4) = DAT_01205228;
            }
        }

        // Check if state at +0x1ad equals 0x1A (maybe PlayerState::Dead) and weapon pointer at +0x380 is valid
        if ((*(char *)(this + 0x1ad) == 0x1A) && (*(int *)(this + 0x380) != 0))
        {
            // Determine weapon state at +0x3a0
            if ((*(int *)(this + 0x3a0) == 0) || (*(int *)(this + 0x3a0) == 0x48))
            {
                // Weapon is idle or in reload state
                if (*(int *)(this + 0x2d4) == 0)
                    iVar4 = 0;
                else
                    iVar4 = *(int *)(this + 0x2d4) - 0x48; // maybe ammo slot adjustment
                iVar2 = FUN_00471610();
                FUN_006b0fd0(*(int *)(this + 0x380), iVar2 + 0x30, this, iVar4); // weapon fire/update
            }
            else
            {
                if (*(int *)(this + 0x2d4) == 0)
                    iVar4 = 0;
                else
                    iVar4 = *(int *)(this + 0x2d4) - 0x48;
                FUN_008b6fd0(iVar4); // weapon reload or alternative action
            }
        }

        // Mark this frame as processed
        *(ushort *)(this + 0x39e) = *(ushort *)(this + 0x39e) | 1;

        // Reset some timer at +0x314
        FUN_004df590();  // e.g., updateTimerSystem()
        FUN_0070c310(this + 0x314, 0, 0); // clearTimer()

        // Check if global threshold (DAT_00d577a0) is <= player's timer at +0x2e8 and validation passes
        if (((DAT_00d577a0 <= *(float *)(this + 0x2e8)) &&
             (cVar1 = FUN_00481620(), cVar1 != '\0')) &&
            (*(int *)(this + 0x2d4) != 0) &&
            (*(int *)(this + 0x2d4) != 0x48) &&
            (cVar1 = FUN_00481620(), cVar1 != '\0'))
        {
            // Set respawn position
            if (optionalRespawnPosition == (float *)0x0)
            {
                iVar4 = FUN_00471610();
                *(Vector3*)(this + 0x338) = *(Vector3*)(iVar4 + 0x30); // current player position
            }
            else
            {
                *(Vector3*)(this + 0x338) = *(Vector3*)optionalRespawnPosition;
            }
            if (*(int *)(this + 0x2d4) == 0)
                iVar4 = 0;
            else
                iVar4 = *(int *)(this + 0x2d4) - 0x48;
            // Set spawn point and call teleport/update function
            FUN_0084f270(this, iVar4, this + 0x338,
                         *(float *)(this + 0x2e4),
                         *(float *)(this + 0x2e8),
                         *(float *)(this + 0x2ec),
                         *(float *)(this + 0x304),
                         this + 0x344);
        }

        // Release timer handle at +0x398 if valid
        if (*(int *)(this + 0x398) != -1)
        {
            FUN_0090dff0(*(int *)(this + 0x398)); // releaseTimer()
            *(int *)(this + 0x398) = -1;
        }

        // Release some effect/sound handle at +0x390
        {
            int local_c = *(int *)(this + 0x390);
            int local_8 = 0;
            char local_4 = 0;
            FUN_00408a00(&local_c, 0); // releaseSound()
        }
    }

    // Additional check after processing: if player is dead, consider respawn
    cVar1 = FUN_00481660(); // isPlayerDead()
    if (cVar1 != '\0')
    {
        iVar4 = FUN_009c8e50(0x38); // allocateEvent of size 0x38
        if (iVar4 != 0)
        {
            int uVar5 = FUN_0070b890(this); // createRespawnEvent(this)
            FUN_00481690(uVar5); // queueEvent(uVar5)
            return;
        }
        FUN_00481690(0); // queueEvent(nullptr)
    }
    return;
}