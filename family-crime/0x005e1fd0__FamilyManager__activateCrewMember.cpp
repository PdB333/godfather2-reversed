// FUNC_NAME: FamilyManager::activateCrewMember
// Function at 0x005e1fd0
// Iterates over 5 crew slots (each 0x4a4 bytes), finds one with matching ID, sets a timer/state to 50, then calls a virtual method.
bool FamilyManager::activateCrewMember(int memberId)
{
    // Calls a validation or update routine (likely a debug/assert function)
    someUpdateFunction(); // 0x005dbc10

    // +0x1744: flag indicating if the family is active (e.g., not disabled)
    if (!*(char*)(this + 0x1744))
    {
        return false;
    }

    // The embedded crew slots start at this+4, each of size 0x4A4.
    // An array of slot IDs is stored at this+0x490, each int spaced 0x4A4 apart.
    // Compare each slot's ID with the given memberId.
    for (int i = 0; i < 5; ++i)
    {
        int slotId = *(int*)(this + 0x490 + i * 0x4A4);
        if (slotId == memberId)
        {
            // Base of the matching crew slot
            CrewSlot* slot = (CrewSlot*)(this + 4 + i * 0x4A4);

            // +0x20c: set some field (e.g., timer count, state) to 50 (0x32)
            slot->field_0x20c = 50;

            // +0x1cc: pointer to a behavior/controller object
            BehaviorController* behavior = slot->behaviorPtr; // offset +0x1cc
            // The behavior's vtable is at global DAT_01223510
            // Call the method at vtable+0x9c with parameter 50
            behavior->vtable->methodAt0x9c(behavior, 50);

            return true;
        }
    }
    return false;
}