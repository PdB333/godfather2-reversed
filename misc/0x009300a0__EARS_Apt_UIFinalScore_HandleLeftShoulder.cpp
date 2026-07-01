// Xbox PDB: EARS_Apt_UIFinalScore_HandleLeftShoulder
// FUNC_NAME: StatsScreen::setTab
// Function address: 0x009300a0
// Role: Set the active tab on the player stats screen (Personal/Honors/Scoring)

void __thiscall StatsScreen::setTab(int thisPtr, int newTab) {
    int* currentTab = (int*)(thisPtr + 0xe8); // +0xe8: current display tab (1=Personal,2=Honors,3=Scoring)
    if (*currentTab == newTab) {
        return;
    }

    if (newTab == 1) {
        *currentTab = 1;
        *(int*)(thisPtr + 0x164) = *(int*)(thisPtr + 0x118); // copy personal data pointer from +0x118 to +0x164
        // Show "Personal" screen, flag=0, context=global string DAT_00d88e88, param=0
        showScreen("ShowPersonal", 0, &DAT_00d88e88, 0);
        // Setup personal view with parameters from +0x148 and +0x130
        setupPersonalView(*(int*)(thisPtr + 0x148), *(int*)(thisPtr + 0x130));
    } else if (newTab == 2) {
        *currentTab = 2;
        showScreen("ShowHonors", 0, &DAT_00d88e88, 0);
        // Setup honors view with parameters from +0x140, +0x148, +0x130, +0x13c
        setupHonorsView(
            *(int*)(thisPtr + 0x140),
            *(int*)(thisPtr + 0x148),
            *(int*)(thisPtr + 0x130),
            *(int*)(thisPtr + 0x13c)
        );
    } else if (newTab == 3) {
        *currentTab = 3;
        showScreen("ShowScoring", 0, &DAT_00d88e88, 0);
        // Setup scoring view (no parameters)
        setupScoringView();
    }
    // else: unknown tab, do nothing
}