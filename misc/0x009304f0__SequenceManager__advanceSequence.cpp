// FUNC_NAME: SequenceManager::advanceSequence
// Address: 0x009304f0
// This function advances a state machine for a presentation sequence (likely honors/scoring display).
// State at +0xE8: 1=init, 2=show honors, 3=show scoring/finish.

void __thiscall SequenceManager::advanceSequence()
{
    int state = *(int*)(this + 0xE8); // current sequence state

    if (state == 1)
    {
        *(int*)(this + 0xE8) = 2;
        // Trigger "ShowHonors" event (probably plays a cutscene or animation)
        ShowEvent("ShowHonors", 0, &DAT_00d88e88, 0); // FUN_005a04a0
        // Start honors presentation with parameters from object:
        // +0x140, +0x148, +0x130, +0x13c (likely positions/timing)
        startHonorSequence(
            *(float*)(this + 0x140), // some float value
            *(float*)(this + 0x148), // another float
            *(float*)(this + 0x130), // third float
            *(float*)(this + 0x13c)  // fourth float
        ); // FUN_0092e790
    }
    else if (state == 2)
    {
        *(int*)(this + 0xE8) = 3;
        // Trigger "ShowScoring" event
        ShowEvent("ShowScoring", 0, &DAT_00d88e88, 0); // FUN_005a04a0
        // Start scoring sequence
        startScoringSequence(); // FUN_0092fec0
    }
    else if (state == 3)
    {
        // Finalize sequence (e.g., clean up, transition)
        finishSequence(1); // FUN_009300a0
    }
    // else ignore other states
}