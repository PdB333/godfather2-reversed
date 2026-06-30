// FUNC_NAME: SimObject::~SimObject()
void __fastcall SimObject::~SimObject(uint* this)
{
    int objectId = this[8];               // +0x20: object identifier or active flag
    // Log destruction if object was active
    if (objectId != 0) {
        uint logData1 = this[5];          // +0x14: first log data
        uint logData2 = this[4];          // +0x10: second log data
        int* logBuffer = (int*)(DAT_01206880 + 0x14); // global log buffer pointer
        // Write entry: marker, object ID, logData2, logData1
        **(int**)logBuffer = &PTR_LAB_011273f4; // entry marker (maybe "EVT")
        *logBuffer = *logBuffer + 4;
        *(int*)*logBuffer = objectId;
        *logBuffer = *logBuffer + 4;
        *(uint*)*logBuffer = logData2;
        *logBuffer = *logBuffer + 4;
        *(uint*)*logBuffer = logData1;
        *logBuffer = *logBuffer + 4;
    }
    // Delete sub-object if present
    if (this[6] != 0) {                  // +0x18: pointer to a sub-object
        (*(void(__thiscall**)(uint))(DAT_0119caf4))(this[6]); // call destructor via function pointer
    }
    // Set vtable to base destructor (presumably)
    *this = &PTR_FUN_00e3f0b4;
    // Call base cleanup
    void* this_ptr = this;
    FUN_00423bf0(&this_ptr);            // deallocate or finalize
    FUN_005d8600();                     // global post-destruction cleanup
}