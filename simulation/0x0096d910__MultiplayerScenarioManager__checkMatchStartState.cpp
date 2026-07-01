// FUNC_NAME: MultiplayerScenarioManager::checkMatchStartState
void __fastcall MultiplayerScenarioManager::checkMatchStartState(int thisPtr)
{
    uint playerCount;
    float fVar2;
    int *piVar3;
    int iVar4;
    uint local_8;

    playerCount = *(uint *)(thisPtr + 0x1e0); // +0x1e0: m_playerCount
    *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfffcffff; // clear bit 16 (match starting flag)
    
    if (playerCount != 0) {
        local_8 = (uint)(longlong)ROUND(*(float *)(DAT_01129908 + 0x14)); // some time threshold
        if (playerCount <= local_8) {
            fVar2 = (float)(int)playerCount;
            if ((int)playerCount < 0) {
                fVar2 = fVar2 + DAT_00e44578; // float conversion fixup
            }
            FUN_008bcaf0(*(float *)(DAT_01129908 + 0x14) - fVar2); // adjust timer
            if (*(int *)(DAT_01223484 + 8) != 0) {
                FUN_00967f90(); // start match countdown
            }
            FUN_0096cab0(); // update match state
            return;
        }
        return;
    }
    
    // No players - set waiting state
    *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) | 0x10000; // set bit 16 (waiting for players)
    piVar3 = DAT_01129930; // global game manager
    (**(code **)(*DAT_01129930 + 8))(); // virtual call
    FUN_009119e0(); // update lobby state
    
    if (DAT_01223484 != 0) {
        if (((uint)piVar3[0x1bd] >> 0x12 & 1) != 0) { // check bit 18 (rival don save flag)
            if (*(int *)(DAT_01223484 + 8) == 0) {
                FUN_00967fe0(); // cancel match start
                piVar3[0x1bd] = piVar3[0x1bd] & 0xfffbffff; // clear bit 18
            }
            else {
                piVar3[0x1bd] = piVar3[0x1bd] | 0x20000; // set bit 17 (waiting for rival don)
                if ((*(byte *)((int)piVar3 + 0x6f6) & 1) == 0) { // check bit 0 of byte at +0x6f6
                    FUN_0096f7a0("$mp_waiting_for_rival_don_save", 1); // show waiting message
                }
            }
            if (((uint)piVar3[0x1bd] >> 0x13 & 1) != 0) { // check bit 19 (rival don saved)
                *(undefined1 *)(piVar3 + 0x1c1) = 0; // clear byte at +0x1c1
                FUN_00967ec0(piVar3[0x78]); // finalize match start
                *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfff7ffff; // clear bit 19
                return;
            }
            piVar3[0x1bd] = piVar3[0x1bd] | 0x80000; // set bit 19 (rival don saving)
            *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfff7ffff; // clear bit 19
            return;
        }
        
        // Handle match start failure
        if (*(int *)(DAT_012234b8 + 0xc) != 0) { // check some condition
            iVar4 = FUN_009c8e50(0xf0); // allocate memory
            if (iVar4 == 0) {
                iVar4 = 0;
            }
            else {
                iVar4 = FUN_00982280(0); // create match start failed dialog
            }
            FUN_00981eb0("$mp_match_start_failed_refund"); // show refund message
            *(undefined4 *)(iVar4 + 0xc) = 3; // set dialog type
            *(code **)(iVar4 + 0x14) = FUN_00982b30; // set callback
            FUN_00982e10(); // show dialog
        }
    }
    
    *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfff7ffff; // clear bit 19
    return;
}