// FUNC_NAME: AudioDataManager::~AudioDataManager
void __fastcall AudioDataManager::~AudioDataManager(AudioDataManager* this)
{
    int i;
    ManagedObject** objArray;
    ManagedObject* obj;
    int* secondaryMgr;

    // Set vtable to most derived (destructor stage)
    *this = &PTR_FUN_00d7324c;

    // Loop through object array and delete each element
    i = 0;
    if (0 < this->objectCount) {
        do {
            // Pre-delete checks (maybe debug marker)
            FUN_0081c980();
            obj = this->objectArray[i];
            if (obj != (ManagedObject*)0x0) {
                FUN_0081c980();
                // Call virtual destructor at vtable+4 (destructor thunk?)
                (*(code**)(*(int*)*obj + 4))(obj->someData, 0x2c);
                obj->someData = 0;
                // Post-delete cleanup
                FUN_0081d230();
                // Free the object memory
                FUN_009c8eb0(obj);
            }
            i = i + 1;
        } while (i < this->objectCount);
    }

    // Delete secondary manager
    secondaryMgr = this->secondaryManager;
    if (secondaryMgr != (int*)0x0) {
        i = secondaryMgr[1];
        // Call virtual shutdown/release at vtable+12
        (*(code**)(*secondaryMgr + 0xc))();
        FUN_009c8f10(i);
        this->secondaryManager = 0;
    }

    // Free the object array itself
    FUN_009c8eb0(this->objectArray);

    // Free optional extra pointer
    if (this->extraPointer != 0) {
        FUN_009c8f10(this->extraPointer);
    }

    // Reset vtable to base class
    *this = &PTR_LAB_00d73230;

    // Mark manager as destroyed
    DAT_011298a8 = 0;
}