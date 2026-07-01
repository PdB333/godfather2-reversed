// FUNC_NAME: EventScheduler::createEvent
void __thiscall EventScheduler::createEvent(int eventType, int data1, int data2) {
    char systemReady;
    int newEvent;

    systemReady = this->isSystemReady(); // FUN_00481660
    if (systemReady) {
        newEvent = this->allocateMemory(0x40); // allocate 64-byte event block
        if (newEvent == 0) {
            newEvent = 0;
        } else {
            newEvent = this->constructEvent(eventType); // FUN_00794e90
        }
        *(int *)(newEvent + 0x38) = data1; // store first data word
        *(int *)(newEvent + 0x3c) = data2; // store second data word
        this->registerEvent(newEvent); // FUN_00481690
    }
}