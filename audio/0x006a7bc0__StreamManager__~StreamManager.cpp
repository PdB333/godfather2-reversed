// FUNC_NAME: StreamManager::~StreamManager

void __fastcall StreamManager::~StreamManager(StreamManager* this)
{
    int* vtablePtr;
    
    // Set vtable to base destructor vtable
    this->vtable = (int*)&PTR_LAB_00d5d868;
    this->someVtableOffset2 = (int*)&PTR_LAB_00d5d864;
    
    // Call a virtual destructor function at offset 0xC from vtable of field at offset 0xC
    vtablePtr = *(int**)this->field_0xC;
    (*(void (__thiscall**)(StreamManager*))(vtablePtr[3]))(); // offset 0xC
    
    // Additional cleanup
    streamManagerCleanup(this);  // FUN_006a7840
    
    // Release resource at field +0x24 (field_0x24)
    releaseResource(this->field_0x24);  // FUN_009c8f10
    
    // Destroy child object at field +0x10 (field_0x10)
    void* childObj = this->field_0x10;
    if (childObj != 0) {
        releaseResource(*(void**)((int)childObj + 8));  // field +8
        destroyObject(childObj);  // FUN_009c8eb0
    }
    
    // Switch vtable to completed destructor vtable
    this->someVtableOffset2 = (int*)&PTR_LAB_00d5d85c;
    
    // Mark stream manager as inactive
    gStreamManagerActive = 0;  // DAT_01129984 = 0
    
    // Final cleanup (possibly deallocation)
    finalizeCleanup(this);  // FUN_0049c640
}