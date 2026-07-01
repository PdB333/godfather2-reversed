// FUNC_NAME: SomeClass::handleTimerUpdate
void __fastcall SomeClass::handleTimerUpdate(int this)
{
    // +0x60: m_timerIndex or m_currentState (some integer offset)
    int index = (*(int *)(this + 0x60) + 6) % 5;
    FUN_00961a50(index); // Process timer/state based on index

    // Prepare a small structure (maybe Vector3, Color, or params) and call a utility function
    undefined4 local_c = DAT_011302b0; // Global data reference
    undefined4 local_8 = 0;
    undefined1 local_4 = 0;
    FUN_00408a00(&local_c, 0); // Likely clears or sets a structure (e.g., Vector::set)
}