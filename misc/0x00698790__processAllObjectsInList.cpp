// FUNC_NAME: processAllObjectsInList

// Globals: DAT_01129f8c and DAT_01129f90 define the start and end of an array of object pointers.
extern void** g_objectListStart; // DAT_01129f8c
extern void** g_objectListEnd;   // DAT_01129f90

void processAllObjectsInList(void) {
    void** it = g_objectListStart;
    if (it != g_objectListEnd) {
        do {
            void* obj = *it;
            // The object has a vtable; virtual function at offset +8 (index 2) is called.
            // __thiscall: 'this' pointer (obj) is implicitly passed in ecx.
            void (*virtualFunc)(void) = (void (*)(void))((*(void***)obj)[2]);
            virtualFunc();
            ++it;
        } while (it != g_objectListEnd);
    }
}