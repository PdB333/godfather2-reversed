// FUNC_NAME: Player::canSeeTarget
// Address: 0x00767710
bool __fastcall Player::canSeeTarget(void* thisPtr)
{
    float posDiffX, posDiffY, posDiffZ;
    float diffLen, dotForward;
    float* diffVec;
    int entityPtr;
    int managerPtr;
    int cameraPtr;
    int playerPtr;
    bool result = false;

    // +0x5c: pointer to world/scene manager
    int worldPtr = *(int*)((int)thisPtr + 0x5C);
    // +0x21E4: entity index? likely the target entity
    entityPtr = *(int*)(worldPtr + 0x21E4);
    // Hash lookup for a global manager (e.g., CameraManager)
    managerPtr = thunk_FUN_00624bd0(0x6862a74c);

    if ( (entityPtr != 0) &&
         (*(char*)(entityPtr + 0x88) == 0x01) &&   // +0x88: is active/visible flag
         (managerPtr != 0) &&
         ((*(uint*)(managerPtr + 0xA8) >> 0x0E & 1) != 0) ) // +0xA8 bit 14: e.g., camera active
    {
        // Two calls to FUN_00471610 – likely returns camera and player transform structs
        cameraPtr = FUN_00471610();   // camera object
        playerPtr = FUN_00471610();   // player object

        // Compute difference between entity position and player position
        // entity position at +0x44, +0x48, +0x4C
        // player position at +0x30, +0x34, +0x38
        posDiffX = *(float*)(entityPtr + 0x44) - *(float*)(playerPtr + 0x30);
        posDiffY = *(float*)(entityPtr + 0x48) - *(float*)(playerPtr + 0x34);
        posDiffZ = *(float*)(entityPtr + 0x4C) - *(float*)(playerPtr + 0x38);

        diffVec = &posDiffX;
        // Normalize vector and return length in ST0
        FUN_0043a210(diffVec, diffVec);
        diffLen = *((float*)&extraout_ST0);  // compiler artifact: ST0 value

        // Dot product: camera forward direction (camera +0x20) with diff vector
        dotForward = *(float*)(cameraPtr + 0x20) * posDiffX +
                     *(float*)(cameraPtr + 0x24) * posDiffY +
                     *(float*)(cameraPtr + 0x28) * posDiffZ;

        if (dotForward > 0.0f)   // target in front of camera
        {
            // Global thresholds for angular and distance checks
            extern float DAT_00d659e8;   // max dot threshold (close)
            extern float DAT_00d659e4;   // min distance threshold (close)
            extern float _DAT_00d659e0;  // max distance threshold (close)
            extern float DAT_00d659dc;   // min distance threshold (far)
            extern float _DAT_00d659d8;  // max distance threshold (far)

            // Check two sets of thresholds: close-range vs far-range
            bool inCloseRange = (_DAT_00d659e8 <= dotForward && diffLen < DAT_00d659e4 && _DAT_00d659e0 < diffLen);
            bool inFarRange  = (dotForward < _DAT_00d659e8 && diffLen < DAT_00d659dc && _DAT_00d659d8 < diffLen);

            if (inCloseRange || inFarRange)
            {
                // Additional check: dot product of entity facing direction (entity+0x38) with camera forward
                float entityFaceDot = *(float*)(entityPtr + 0x38) * *(float*)(cameraPtr + 0x20) +
                                      *(float*)(entityPtr + 0x3C) * *(float*)(cameraPtr + 0x24) +
                                      *(float*)(entityPtr + 0x40) * *(float*)(cameraPtr + 0x28);
                if (entityFaceDot > 0.0f)
                {
                    // Virtual call on worldPtr vtable+0x48 – likely a raycast/visibility test
                    (**(code**)(*(int*)worldPtr + 0x48))(diffVec);   // passes diffVec as parameter
                    int u1 = 0, u2 = 0;
                    FUN_00716420(diffVec, entityPtr + 0x44, u1, u2); // line-of-sight trace?
                    result = (bool)FUN_00714550(diffVec, entityPtr + 0x44, u1, u2);
                }
            }
        }
    }
    return result;
}