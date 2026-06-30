// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
    int *pRefCountStruct; // pointer to reference count structure at this[0x36]
    int *pCountField;     // pointer to the count field within the structure
    int count;
    
    // Set vtable pointers to static destructor state (prevents virtual calls)
    *this = &PTR_FUN_00d5f228;
    this[0xf] = &PTR_LAB_00d5f214;
    this[0x12] = &PTR_LAB_00d5f210;
    this[0x14] = &PTR_LAB_00d5f20c;
    
    // Decrement reference count
    pRefCountStruct = (int *)this[0x36];
    pCountField = pRefCountStruct + 1;
    *pCountField = *pCountField - 1;
    count = *pCountField;
    if (count == 0) {
        // Call the destructor stored in the reference count structure
        (**(code **)(*pRefCountStruct + 4))();
    }
    
    // Destroy sub-object at offset 0x2d (likely a container or resource)
    DestructSubObject(this + 0x2d);
    CleanupSubObject(this + 0x2d);
    
    // Destroy sub-object at offset 0x2f
    DestructSubObject(this + 0x2f);
    CleanupSubObject(this + 0x2f);
    
    // Call base class destructor
    BaseClassDestructor(this);
    
    // Check and clear pointer at offset 0x32
    if (this[0x32] == 0) {
        LogNullPointer(); // or AssertFail
    } else {
        // Clear the embedded object at offset +8 of the pointed-to structure
        *(undefined4 *)(this[0x32] + 8) = 0;
        this[0x32] = 0;
    }
    
    // Check and clear pointer at offset 0x34
    if (this[0x34] == 0) {
        LogNullPointer();
    } else {
        *(undefined4 *)(this[0x34] + 8) = 0;
        this[0x34] = 0;
    }
    
    // Global post-destruction cleanup
    PostDestructCleanup();
    
    return;
}