// FUNC_NAME: PlayerWallCoverSM::attemptCoverMovement
void __fastcall PlayerWallCoverSM::attemptCoverMovement(PlayerWallCoverSM* thisPtr)
{
    // Offset: this+0x58 -> pointer to Player
    Player* pPlayer = *(Player**)(thisPtr + 0x58);
    
    // Check if player has a cover-blocking flag (bit 0 at offset +0x8E3)
    if ((pPlayer->flags8E3 & 1) != 0) {
        return;
    }
    
    // Get a random time offset? 
    float10 randomVal = FUN_0079eb90(0, 1);
    
    // Retrieve a matrix from a global table indexed by player sub-type? 
    // local_18 is likely a 4x4 matrix, local_14 is part of it
    float matrix[4]; // local_18
    FUN_00425060(matrix, *(int*)(&DAT_00002494 + pPlayer));
    
    double temp = (double)(matrix[3] + (float)randomVal); // local_14 is matrix[3]
    FUN_00b99fcb();
    float zOffset = (float)temp; // local_3c
    
    temp = (double)(matrix[3] + (float)randomVal);
    FUN_00b99e20();
    float xOffset = (float)temp; // local_34
    
    float yOffset = 0.0f; // local_38
    
    char canDoDriveCover = FUN_007fd640(); // check if player is in vehicle?
    
    if (canDoDriveCover == 0) {
        float coverProximity = *(float*)(pPlayer + 0x1FF4); // offset +0x1FF4 (e.g., m_coverDistThreshold)
        
        int* cameraData = (int*)FUN_00471610(); // get camera? returns some struct
        Vector3 desiredPos;
        desiredPos.x = zOffset * DAT_00d58cbc + *(float*)(cameraData + 0x30);
        desiredPos.y = *(float*)(cameraData + 0x34);
        desiredPos.z = xOffset * DAT_00d58cbc + *(float*)(cameraData + 0x38);
        
        int coverResult = FUN_00550d30(&desiredPos, 0, 1.0f - coverProximity);
        if (coverResult != 2 && coverResult != 1) {
            FUN_007ab470(0x21); // enter cover action (maybe play animation)
            return;
        }
    } else {
        char isInCover = FUN_0079ebe0(0);
        if (isInCover != 0) {
            return;
        }
        
        char canExitCover = FUN_007ab500(0x21);
        if (canExitCover == 0) {
            return;
        }
        
        Vector3 coverPoint;
        FUN_00803330(&coverPoint, local_c); // unknown local_c buffer
        
        FUN_0043a210(&zOffset, &zOffset); // adjust offset?
        
        Vector3 targetPoint;
        targetPoint.x = coverPoint.x + zOffset * DAT_00d5ef88;
        targetPoint.y = coverPoint.y + yOffset * DAT_00d5ef88;
        targetPoint.z = coverPoint.z + xOffset * DAT_00d5ef88;
        
        char collisionResult = FUN_0080a080(&targetPoint, local_c, 0, 0);
        if (collisionResult != 0) {
            return;
        }
    }
    
    FUN_007ab4d0(0x21); // exit cover action
}