// FUNC_NAME: PlayerStateMachine::handleActionInput
void __thiscall PlayerStateMachine::handleActionInput(PlayerStateMachine* thisPtr, ActionInput* input)
{
    // check if player is not in a specific state
    if ( ((*(uint32_t*)((uint8_t*)thisPtr + 0x550) >> 0xc) & 1) == 0 &&
         *(int32_t*)((uint8_t*)thisPtr + 0x1adc) == 0 &&
         *(int32_t*)((uint8_t*)thisPtr + 0x1af0) == 0 &&
         FUN_007f7b90() == 0 &&
         ((*(uint32_t*)((uint8_t*)thisPtr + 0x554) >> 0x16) & 1) == 0 &&
         input->state != 3 )
    {
        // call a vtable method on the animation object at this+0x4ac
        (*(code**)(**(int32_t**)((uint8_t*)thisPtr + 0x4ac) + 0x1c))();

        uint32_t soundHash = 0;
        uint32_t seed;

        if (input->state == 1)
        {
            seed = FUN_006fbc40(0, 0); // random seed
            soundHash = 0x9ecd1cee;    // "IDLE_SOUND"?
        }
        else if (input->state == 2)
        {
            seed = FUN_006fbc40(0, 0);
            soundHash = 0x9ee00b49;    // "WALK_SOUND"?
        }
        else
        {
            seed = FUN_006fbc40(0, 0);
            soundHash = 0;
        }

        FUN_007f96a0(soundHash, 1, seed, 0); // play sound with hash, priority, seed
        FUN_006fbc70(); // finalize sound setup
    }

    // Prepare event data for a state transition
    int32_t actionBase = 0;
    if (input->actionPtr != 0)
        actionBase = input->actionPtr - 0x48;

    // Set up event structure on stack
    struct EventData {
        void** vtable;      // +0x00
        uint32_t eventHash; // +0x04
        int32_t listPrev;   // +0x08
        int32_t listNext;   // +0x0c
        // more fields...
    } eventData;

    eventData.vtable = &PTR_FUN_00d5dbbc;  // some vtable for events
    eventData.eventHash = 0xcb6ef9c3;      // e.g., "ACTION_EVENT"

    if (actionBase == 0)
        actionBase = 0;
    else
        actionBase = actionBase + 0x48;  // restore original pointer

    eventData.listPrev = 0;
    if (actionBase != 0)
    {
        eventData.listPrev = *(int32_t*)(actionBase + 4);
        *(int32_t**)(actionBase + 4) = &actionBase;  // link into list
    }

    eventData.listNext = 0;
    eventData.someData1 = 0;
    eventData.someData2 = 0;
    eventData.someFlag = 0;
    *(int32_t*)&eventData.some4 = DAT_01205228;  // some constant

    // get a singleton game manager
    int32_t* gameMgr = FUN_00471610();
    eventData.someFlag = 1;
    eventData.someData1 = *(int64_t*)((uint8_t*)gameMgr + 0x30); // time?
    eventData.someData2 = *(int32_t*)((uint8_t*)gameMgr + 0x38);

    // Send the event
    FUN_00408a00(&eventData, 0); // push event to queue
    FUN_007eea00();               // process events

    if (actionBase != 0)
        FUN_004daf90(&actionBase); // remove from list or decrement ref
}