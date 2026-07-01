// FUNC_NAME: MissionManager::startMission

void __fastcall MissionManager::startMission(MissionManager* this)
{
    int iVar1;
    // Local struct for color/rectangle (size 9 bytes, aligned)
    struct {
        uint32_t field0; // +0x00
        uint32_t field4; // +0x04
        uint8_t  field8; // +0x08
    } localColor;

    // Begin frame / clear screen
    FUN_00481530();
    // Set clear color to black (0xFF000000) with alpha=1
    FUN_0040c1f0(0xff000000, 0, 0, 1);

    iVar1 = g_pCurrentMission; // DAT_01223484
    if ((((g_pCurrentMission != 0) &&
          (*(float*)(g_pCurrentMission + 0x39c) != g_fMissionTimeOverride)) && // _DAT_00d79b60
         (*(int*)(g_pCurrentMission + 0x3a4) != 0)) &&
        (*(int*)(g_pCurrentMission + 0x3a0) != 0))
    {
        // Store mission time into this->missionTime (offset 0x4a)
        this->missionTime = *(float*)(g_pCurrentMission + 0x39c);
        // Store mission ID into this->missionId (offset 0x25)
        this->missionId = *(int*)(iVar1 + 0x3a4);
        // Compute timer duration: seconds * 60000 (milliseconds)
        iVar1 = *(int*)(iVar1 + 0x3a0) * 60000;
        this->timerDuration = iVar1; // offset 0x24
        // Start the mission timer
        FUN_008aada0(iVar1);
    }

    // Set mission active flag (offset 0x47)
    this->missionActive = 1;

    // Additional initialization
    FUN_0093c210();

    // Prepare local color (likely black or transparent)
    localColor.field0 = g_pSomeGlobalColor; // DAT_0112b2a4
    localColor.field4 = 0;
    localColor.field8 = 0;
    FUN_00408a00(&localColor, 0);

    // Call virtual functions
    (this->vtable->method0xF4)(); // offset 0xf4
    FUN_0094e680();
    this->flags |= 0x10; // offset 0x1f

    // Call another virtual function
    (this->vtable->method0xDC)(); // offset 0xdc
}