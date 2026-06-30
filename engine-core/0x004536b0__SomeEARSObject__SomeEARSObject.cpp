// FUNC_NAME: SomeEARSObject::SomeEARSObject
class SomeEARSObject {
public:
    // vtable pointer at +0x00
    // Some pointer/handle at +0x04 (likely a 0x40-byte buffer or resource handle)
    void* mResourceHandle;

    // Constructor at 0x004536b0
    SomeEARSObject() {
        // Set vtable pointer (external symbol)
        *(void**)this = &PTR_FUN_00e31850;

        // Allocate 64-byte buffer
        void* alloc = operatorNew(0x40);
        if (alloc == nullptr) {
            mResourceHandle = nullptr;
            return;
        }

        // Get singleton or shared resource
        void* sharedObj = getGlobalResource(); // FUN_009c89c0
        if (sharedObj != nullptr) {
            // Duplicate from shared object's internal buffer at offset 4
            mResourceHandle = duplicateResourceHandle((char*)sharedObj + 4, 1); // FUN_00b92310
        } else {
            // Create empty resource
            mResourceHandle = duplicateResourceHandle(nullptr, 1); // FUN_00b92310
        }
    }

private:
    // Placeholder for operator new (likely just malloc)
    static void* operatorNew(size_t size) {
        // FUN_009c8e50 - could be custom allocator
        return FUN_009c8e50(size);
    }

    // Placeholder for getting a global resource singleton
    static void* getGlobalResource() {
        // FUN_009c89c0
        return FUN_009c89c0();
    }

    // Placeholder for function that creates a resource handle
    static void* duplicateResourceHandle(void* src, int flags) {
        // FUN_00b92310 - src could be source pointer or null
        // flags likely indicates copy vs. create
        return FUN_00b92310(src, flags);
    }

    // External function declarations (from game assembly)
    static void* FUN_009c8e50(size_t size);
    static void* FUN_009c89c0();
    static void* FUN_00b92310(void* src, int flags);
};