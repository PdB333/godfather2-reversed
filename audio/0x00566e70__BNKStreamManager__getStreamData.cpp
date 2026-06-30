// FUNC_NAME: BNKStreamManager::getStreamData
int __fastcall BNKStreamManager::getStreamData(int this)
{
    // +0x11c is a pointer to the bank's data block (e.g., a BNK asset in memory)
    int *dataBlock = *(int **)(this + 0x11c);
    if (dataBlock != nullptr) {
        // +0x400 offset typically points to the actual audio stream data within the block
        return (int)(dataBlock + 0x400);
    }
    return 0;
}