// FUNC_NAME: SimManager::initialize
void SimManager::initialize(void)
{
    // FUN_00579870 likely returns a manager or singleton pointer
    int handle = BaseManager::getInstance(); 
    // FUN_00579450 initializes this object with the handle (e.g., binds to global manager)
    this->initWithHandle(handle); // +0x00: this pointer passed implicitly via EAX
    return;
}