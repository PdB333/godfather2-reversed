// FUN_00426890: CApplication::~CApplication

void CApplication::~CApplication()
{
    // Restore original vtable to allow virtual calls during destruction
    this->vtable = &PTR_FUN_00e30bd0;

    // Obtain the global manager instance
    CSomeManager* manager = FUN_009c8f80();
    // Call virtual method at offset 4 (likely Release or Shutdown) with our subsystem pointer and flag
    manager->someReleaseMethod(this->subsystemPtr, 0);  // +0x38

    // Cleanup another subsystem
    FUN_00426ed0();

    // Release allocated resource if present
    if (this->someAllocatedPtr != 0)  // +0x3c
    {
        FUN_009c8f10(this->someAllocatedPtr);
    }

    // Final cleanup procedure
    FUN_00ab4d30();

    // Set vtable to dead state to prevent accidental virtual calls
    this->vtable = &PTR_LAB_00e30bd4;

    // Reset global reference count or singleton flag
    DAT_012233e4 = 0;
}