// Xbox PDB: EARS_Apt_UIHud_ShowObjective
// FUNC_NAME: ObjectiveHud::showObjective
void __thiscall ObjectiveHud::showObjective(ObjectiveHud* this, int x, int y)
{
    // Store objective on-screen position
    this->objectivePosX = x;   // +0xC0
    this->objectivePosY = y;   // +0xC4

    // Trigger objective display event (likely logging/HUD)
    FUN_005a04a0("ShowObjective", 0, &DAT_00d8a64c, 0); // g_gameContext or debug hook

    // Set flag indicating objective is visible (bit 2 at +0x5C)
    this->flags |= 4; // +0x5C

    // Set up animation/timer data for objective fade-in or duration
    AnimationTimer timerData;
    timerData.start = DAT_011303f8; // global start time or duration
    timerData.duration = 0;
    timerData.unknown0 = 0;
    FUN_00408a00(&timerData, 0); // Start timer/animation
}