// FUNC_NAME: GodfatherGameManager::applyDifficultyProfile
void __fastcall GodfatherGameManager::applyDifficultyProfile(int profileType)
{
    // profileType passed in EAX; this (ECX) points to a config struct with float at +0x0c
    // g_threshold (DAT_00e2e780) is a global difficulty threshold
    float localThreshold = *(float *)(this + 0xc);
    if (g_threshold <= localThreshold) {
        // First profile set (hardcore?)
        // Clamp g_configMin and g_configMax to specific values, and set g_configSettingX accordingly
        if (g_configMin < 22) g_configMin = 22;
        if (g_configMax > 22) g_configMax = 22;
        g_setting1 = 1;

        if (g_configMin < 7) g_configMin = 7;
        if (g_configMax > 7) g_configMax = 7;
        g_setting2 = 0;

        if (g_configMin < 25) g_configMin = 25;
        if (g_configMax > 25) g_configMax = 25;
        g_setting3 = 5;

        if (g_configMin < 24) g_configMin = 24;
        if (g_configMax > 24) g_configMax = 24;
        g_setting4 = 0;

        if (g_configMin < 15) g_configMin = 15;
        if (g_configMax > 15) g_configMax = 15;
        g_setting5 = 0;

        if (g_configMin < 27) g_configMin = 27;
        if (g_configMax > 27) g_configMax = 27;
        g_setting6 = (profileType != 3) ? 1 : 0;

        sub_004EC7A0(); // Internal setup
        g_resPointer1 = g_resource1;
        g_resPointer2 = g_resource2;
        g_resourceFlag = 0;

        if (g_pCurrentManager == &g_defaultManagerBlock) {
            sub_0060A460(g_resource1); // Release resource
            sub_0060A460(g_resPointer2);
        }

        sub_005311D0(); // Process events
        sub_00530A60(); // Update state

        int* alloc = (int*)sub_0060CD00(0xd, 4, 0, 1, 0); // Allocate memory for 13 ints
        float valA = g_floatA;
        float valB = g_floatB;
        if (alloc != 0) {
            alloc[0] = (int)valA; // Note: type punning float to int
            alloc[1] = (int)valA;
            alloc[2] = (int)valB;
            alloc[3] = (int)valA;
            alloc[4] = (int)valB;
            alloc[5] = (int)valB;
            alloc[6] = (int)valA;
            alloc[7] = (int)valB;
            sub_0060CDE0(); // Commit allocation
        }

        sub_00612E00(); // Finalize setup
        g_resPointer2 = 0;
        g_resPointer1 = 0;
        g_otherFlag1 = 0;
        g_otherFlag2 = 0;

        // Second profile set (easier?)
        if (g_configMin < 22) g_configMin = 22;
        if (g_configMax > 22) g_configMax = 22;
        g_setting1 = 1;

        if (g_configMin < 7) g_configMin = 7;
        if (g_configMax > 7) g_configMax = 7;
        g_setting2 = 1;

        if (g_configMin < 25) g_configMin = 25;
        if (g_configMax > 25) g_configMax = 25;
        g_setting3 = 7;

        if (g_configMin < 24) g_configMin = 24;
        if (g_configMax > 24) g_configMax = 24;
        g_setting4 = 0;

        if (g_configMin < 15) g_configMin = 15;
        if (g_configMax > 15) g_configMax = 15;
        g_setting5 = 0;

        if (g_configMin < 27) g_configMin = 27;
        if (g_configMax > 27) g_configMax = 27;
        g_setting6 = 0;

        sub_00417CF0(1, 5, 6); // Start mission mode 1,5,6
    }
}