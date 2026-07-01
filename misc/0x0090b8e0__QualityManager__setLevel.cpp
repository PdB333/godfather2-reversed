// FUNC_NAME: QualityManager::setLevel
void __thiscall QualityManager::setLevel(void* this, int newLevel)
{
    int* storedLevel = (int*)((char*)this + 0x14); // +0x14: current quality level

    if (*storedLevel < newLevel) {
        if (newLevel != 1) {
            FUN_007e7df0(0x33); // play sound for non-default level change
        }
        if (newLevel == 6) {
            FUN_007e7df0(0x35); // play special sound for highest level
        }
        *storedLevel = newLevel;
        FUN_0090b480(); // apply quality change (e.g., graphics update)
    }
}