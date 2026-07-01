// Xbox PDB: EARS_Apt_UIHud_StopCrewActionTimer
// FUNC_NAME: PlayerCrewLeaderComponent::stopCrewActionTimer
// Function address: 0x00939710
// Stops the crew action timer, copies a value from the timer manager, and logs.

void __fastcall PlayerCrewLeaderComponent::stopCrewActionTimer(PlayerCrewLeaderComponent* this)
{
    // +0x48: flag indicating crew action timer is active
    if (*(char*)((int)this + 0x48) != '\0')
    {
        // Retrieve the singleton crew timer manager
        int* crewTimerMgr = (int*)getCrewTimerManager();
        if (crewTimerMgr != 0)
        {
            // Another access to the same manager (or a different object returned by same function?)
            int* someSubObject = (int*)getCrewTimerManager();
            // +0x70 on this: likely stores the current timer value
            // +0xC4 on subObject: source timer data
            *(int*)((int)this + 0x70) = *(int*)((int)someSubObject + 0xC4);
        }
        // Debug log: "StopCrewActionTimer" with placeholder parameters
        debugPrint("StopCrewActionTimer", 0, &DAT_00d8a64c, 0);
    }
}