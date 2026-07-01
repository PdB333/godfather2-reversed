// FUNC_NAME: EARSObject::shutdown
void __fastcall EARSObject::shutdown(EARSObject* thisObj)
{
    // +0x54 offset: pointer to a sub-object (e.g., controller, stream handler)
    void* subObject = (thisObj != 0) ? (reinterpret_cast<char*>(thisObj) + 0x54) : 0;
    FUN_0097e300(subObject);  // destroySubObject – cleans up referenced component

    // Retrieve singleton manager (e.g., StreamManager, EntityDataManager)
    void* manager = FUN_0097b860();  // getManagerInstance
    if (manager != 0) {
        // Get first object from manager's list (index 0)
        void* target = FUN_0097b8b0(0);  // getObjectAtIndex(0)
        // Remove/unregister that object from the manager
        FUN_009525f0(target, 0, 0);  // removeObject
    }
}