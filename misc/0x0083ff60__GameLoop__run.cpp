// FUNC_NAME: GameLoop::run
void GameLoop::run(void* thisPtr) // __thiscall
{
    char isDone;
    
    // Initialize the game loop
    this->init(); // FUN_0043b540
    this->setFlag(0x88daf5f0); // FUN_0043aff0 - set some flag/timer
    
    isDone = this->isQuitRequested(); // FUN_0043b120
    while (isDone == '\0') {
        this->processMessages(); // FUN_0043b210 - poll input/events
        
        int* eventData = (int*)this->getNextEvent(); // FUN_0043abc0 - get next event/entity
        
        // Check if any of the first 4 ints are non-zero (event type/ID)
        if ((((*eventData != 0) || (eventData[1] != 0)) || (eventData[2] != 0)) || (eventData[3] != 0)) {
            this->handleEvent(eventData); // FUN_0083f9c0 - process event
        }
        
        this->advanceEventQueue(); // FUN_0043b1a0 - move to next event
        isDone = this->isQuitRequested(); // FUN_0043b120
    }
}