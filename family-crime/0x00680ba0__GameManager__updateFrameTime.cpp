// FUNC_NAME: GameManager::updateFrameTime
// Function at 0x00680ba0: Retrieves a value from the engine via FUN_006808c0 and stores it at offset 0x20.
// This is likely part of a frame/timing update for the singleton GameManager instance.
void GameManager::updateFrameTime() {
    // Pointer to the global GameManager singleton (stored at DAT_01129878)
    int* pManager = (int*)DAT_01129878;
    
    // Call a helper function (likely returns current frame time or similar value)
    // The function takes the GameManager pointer as an argument.
    int frameTime = FUN_006808c0((int)pManager);  // probably getCurrentFrameTime
    // Store the retrieved value at offset +0x20 (e.g., m_frameTime)
    *(int*)(pManager + 0x20) = frameTime;
}