// FUNC_NAME: Component::tryProcess
void __fastcall Component::tryProcess(int this)
{
    // +0x200: pointer to active behavior/state machine (non-null indicates active)
    if (*(int*)(this + 0x200) != 0) {
        executeActiveBehavior(); // Calls FUN_004df600 - process current behavior
    }
}