// FUNC_NAME: EngineObject::~EngineObject
// Function at 0x004ca5f0: Destructor for EngineObject, cleans up resource at +0x1c and +0x20.

class EngineObject {
    // Class layout inferred from offsets:
    // +0x00: unknown
    // +0x04: pointer to vtable (virtual method table)
    // +0x1c: pointer to allocated resource (buffer, object, etc.)
    // +0x20: size or second resource pointer
    // vtable layout: index 0: unknown, index 1: deallocation function (void* ptr, uint size)

    // Called at 0x004ca810: likely a member cleanup/release function
    void releaseResource(); // assumed name

public:
    // Virtual destructor mechanism: vtable[1] = custom dealloc
    ~EngineObject() {
        // Step 1: call release function on the resource (uses a stack buffer for temporary state?)
        // local_10 is a 12-byte buffer used by releaseResource
        char buffer[12];
        releaseResource(); // actual call passes buffer, this, resource pointer twice

        // Step 2: call virtual deallocation function (index 1 in vtable)
        // vtable at this+0x04
        void** vtable = *(void***)(this + 4); // pointer to vtable
        void (*deallocFunc)(void*, int) = (void (*)(void*, int))(vtable[1]); // second function
        deallocFunc(*(void**)(this + 0x1c), 0x18); // deallocate with size 0x18

        // Step 3: zero out resource pointers
        *(void**)(this + 0x1c) = 0;
        *(void**)(this + 0x20) = 0;
    }
};