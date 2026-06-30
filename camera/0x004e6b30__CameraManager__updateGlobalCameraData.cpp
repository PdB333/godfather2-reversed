// FUNC_NAME: CameraManager::updateGlobalCameraData
void __fastcall CameraManager::updateGlobalCameraData(int thisPtr, int sourcePtr)
{
    // Global variables from addresses
    extern float gCompareFloat;   // DAT_00e2af44
    extern float gStoreFloat;     // DAT_01125290
    extern float gStoreVec4[4];   // DAT_011252a0..ac
    extern int   gStoreInt3[3];   // DAT_01125294,98,9c

    float* sourceVec = (float*)sourcePtr;
    if (gCompareFloat <= sourceVec[3])
    {
        gStoreFloat = *(float*)(thisPtr + 0x28);
        gStoreVec4[0] = sourceVec[0];
        gStoreVec4[1] = sourceVec[1];
        gStoreVec4[2] = sourceVec[2];
        gStoreVec4[3] = sourceVec[3];

        // Decompiled code:
        //   uint local_2c, local_28, local_24; (stack)
        //   local_2c = CONCAT31(local_2c._1_3_, *(uint8*)(*(int*)(thisPtr+0x24) + 0x13));
        //   gStoreInt3[0] = local_2c;
        //   gStoreInt3[1] = local_28;
        //   gStoreInt3[2] = local_24;
        // The stack variables are uninitialized. Possibly the code is incomplete.
    }
}