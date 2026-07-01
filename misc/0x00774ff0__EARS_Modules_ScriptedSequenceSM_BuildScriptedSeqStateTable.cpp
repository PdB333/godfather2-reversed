// Xbox PDB: EARS_Modules_ScriptedSequenceSM_BuildScriptedSeqStateTable
// FUNC_NAME: ScriptedSequenceSM::initStateTable
void ScriptedSequenceSM::initStateTable(void)
{
    // Get the global state machine table for scripted sequences
    void* scriptedSequenceTable = thunk_FUN_004dafd0("scriptedSequenceTable");
    int tableEntryCount = FUN_00621530(scriptedSequenceTable);
    if (tableEntryCount == 0) {
        // Allocate a new table and register it globally
        scriptedSequenceTable = FUN_009c8f80();
        FUN_004ad9d0("scriptedSequenceTable", scriptedSequenceTable);

        // Register default/unassigned state (ID -1)
        FUN_004adae0(&DAT_00d64b74, 0xffffffff);
        FUN_004acf70(10);             // Unknown state property (maybe initial state flags)
        FUN_004acff0(8);              // Another state property
        FUN_004acc70(&DAT_00d63afc, 0x12); // Attach empty string with value 0x12 (maybe a transition)

        // Register "gotoSS" state (go to scripted sequence)
        FUN_004acc70("gotoSS", 10);
        FUN_004adae0("gotoSS", 0xffffffff);
        FUN_004acf70(0xb);
        FUN_004acff0(8);
        FUN_004acc70(&DAT_00d63afc, 0x12);
        FUN_004acc70("gotoPos", 0xc);

        // Register "gotoPos" state (go to position)
        FUN_004acc70("waitAtSS", 0xb); // Wait at scripted sequence
        FUN_004acc70("faceOrient", 0xd); // Face orientation

        // Register "faceOrient" state
        FUN_004acc70(&DAT_00d63afc, 0x12);
        FUN_004adae0("gotoPos", 0xffffffff);
        FUN_004acf10("MustFollowPathST", 1); // Set "must follow path" state to 1
        FUN_004acc70(&DAT_00d63afc, 0x12);
        FUN_004acc70("faceOrient", 1);
        FUN_004adae0("faceOrient", 0xffffffff);
        FUN_004acf70(0xd);
        FUN_004acf70(0x10);
        FUN_004acc70(&DAT_00d63afc, 0x12);
        FUN_004acc70("waitAtSS", 1);

        // Register "waitAtSS" state
        FUN_004adae0("waitAtSS", 0xffffffff);
        FUN_004acf70(0xd);
        FUN_004acf70(0xe);
        FUN_004acff0(0xe);
        FUN_004acc70(&DAT_00d63afc, 0x12);
        FUN_004acc70("action", 0x10); // Action type state
        FUN_004acff0(8);
        FUN_004adae0("action", 0xffffffff);
        FUN_004acf70(0xc);
        FUN_004acff0(8);
        FUN_004acc70(&DAT_00d63afc, 0x12);
        FUN_004acc70(&DAT_00d63afc, 0xe);
        FUN_004acc70("action", 0xf);
        FUN_004adae0(&DAT_00d63afc, 0xffffffff);
        FUN_004acf70(0xf);

        // Register the state machine class with its vtable/init routine
        FUN_004adc90(0xe8b1c0e8, &LAB_00774f00, "ScriptedSequenceSM");
        FUN_004ada40(); // Finalize the table registration
    }
    return;
}