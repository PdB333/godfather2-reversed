// FUNC_NAME: RefCountedObject::releaseAndDeleteIfZero
void __cdecl RefCountedObject::releaseAndDeleteIfZero(void* obj) {
    // Enter critical section protecting the reference count global table
    EnterCriticalSection(/* DAT_00e3f4f4 */ &g_refCountCriticalSection);

    // Release a reference to the object; returns non-null if object should be deleted
    void* releasedObj = ReleaseRefFromGlobalTable(/* DAT_01223508 */ g_objectTable, obj);

    if (releasedObj != nullptr) {
        // Call the object's destructor via vtable (first entry assumed)
        void (*destructor)(void*) = *(void(**)(void*))releasedObj;
        destructor(releasedObj);
    }
}