// FUNC_NAME: Debug::~Debug
void __thiscall Debug::~Debug(void) {
    // Set vtable to base class destructor's vtable
    this->vtable = &gDebugBaseVtable;
    // Set another vtable pointer at offset 0xC (likely a secondary vtable or interface)
    this->secondaryVtable = &gDebugSecondaryVtable;

    // Release static debug resources (likely output streams or history)
    Debug::releaseStaticData(&DAT_0112ff08);
    Debug::releaseReference(&DAT_0112ff08);
    Debug::releaseReference(&DAT_0112ff00);
    Debug::releaseReference(&DAT_0112fef4);

    // If there is a child object at offset 0x1C, delete it
    if (this->childObject != nullptr) {
        deleteChildObject(this + 0x1C); // FUN_004daf90
    }

    // If there is a string buffer at offset 0x10, delete it
    if (this->stringBuffer != nullptr) {
        deleteStringBuffer(this->stringBuffer); // FUN_009c8f10
    }

    // Update vtable to final destructor stage
    this->secondaryVtable = &gDebugFinalVtable;

    // Reset global debug initialization flag
    gDebugInitialized = 0;

    // Final cleanup of static resources
    Debug::finalCleanupStaticData(); // FUN_004083d0
}