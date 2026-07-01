// FUNC_NAME: GameManager::setSimManager
void __fastcall GameManager::setSimManager(int thisPtr)
{
    int simManager = FUN_00494d10(); // Returns SimManager instance
    *(int*)(thisPtr + 0x1c) = simManager; // +0x1c: stored SimManager pointer
}