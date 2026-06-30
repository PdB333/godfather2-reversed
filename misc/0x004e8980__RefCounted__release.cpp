// FUNC_NAME: RefCounted::release
// Function at 0x004e8980: Releases a reference to a ref-counted object.
// The object has a vtable with destructor at offset 4 and a condition check at offset 8.
// The condition function takes a context pointer (param_2) and returns bool.
// If condition is true, returns a non-null sentinel; otherwise returns null.
// Always decrements refCount and deletes object if it reaches zero.

class RefCounted {
public:
    // Object layout:
    // +0: vtable pointer
    // +4: refCount (int)
    // vtable[0] = unknown
    // vtable[1] = destructor (offset 4)
    // vtable[2] = canRelease (offset 8) - takes void* context, returns bool

    int refCount; // +0x4

    virtual ~RefCounted() = 0; // vtable+4
    virtual bool canRelease(void* context) = 0; // vtable+8
};

// Static sentinel for non-null return
static int releaseSentinel = 0;

void* __fastcall RefCounted_release(void* /*unused*/, void* context, RefCounted* obj) {
    if (obj != nullptr) {
        bool canRelease = obj->canRelease(context);
        obj->refCount--;
        if (obj->refCount == 0) {
            delete obj; // calls vtable destructor at offset 4
        }
        if (canRelease) {
            return &releaseSentinel; // non-null pointer indicating success
        }
    }
    return nullptr;
}