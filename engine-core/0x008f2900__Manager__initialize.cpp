// FUNC_NAME: Manager::initialize
void __thiscall Manager::initialize(int param_2, int param_3)
{
    int iVar1;
    int stackParam[3] = {0, 0, 0};

    // Release existing resource if allocated
    if (this->resourceObject != (int*)0x0) {
        // Call virtual function on resource object
        (*(code*)this->resourceObject->vtable[0])(0);
        // Call second virtual function on allocator? 
        (**(code**)(this->allocator->vtable + 4))(this->resourceObject, 0x3c);
        this->resourceObject = 0;
    }

    // Check global flag: if not set, clear sound-related flag, else enable and notify system
    if (*(char*)(DAT_01129814 + 0x15) == '\0') {
        this->flags &= 0xfffffffb; // clear bit 2
    } else {
        FUN_0068c590(0); // likely enable sound system
        this->flags |= 4; // set bit 2
    }

    // Store external parameters
    this->paramA = param_2;
    this->paramB = param_3;
    this->state = 8;

    // Attempt to allocate a resource (size 0x3c) via allocator
    iVar1 = (*(code*)this->allocator->vtable[0])(0x3c, stackParam);
    if (iVar1 != 0) {
        iVar1 = FUN_004c01e0(); // convert to proper object
    }
    this->resourceObject = iVar1;

    // Initialize counters
    this->counter1 = 0;
    this->counter2 = 0;
    this->largeCounter = 0; // offset 0x813

    // Check a flag to decide initialization path
    if ((this->flags >> 3 & 1) == 0) {
        // Normal path: register with stream system
        FUN_00408680(&DAT_0112fe28);
        this->streamSlot = 2;
        FUN_004c0b90(&DAT_0112fe28, 2, 0);
        return;
    }

    // Alternative path: call virtual function at vtable offset 0x38
    (**(code**)(this->vtable + 0x38))();
}