// FUNC_NAME: refCountedConditionalRelease

// Function at 0x00500630: Reference-counted object release with conditional predicate.
// Calling convention: __fastcall (first param in ECX unused, second param in EDX is context,
// third param on stack is pointer to refcounted object).
// The object's vtable layout:
//   vtable[0] likely some base (unused here)
//   vtable[1] (offset +4): destructor (void (*)(void))
//   vtable[2] (offset +8): test function (bool (*)(void* context))
// Object memory:
//   +0x00: vtable pointer
//   +0x04: reference count (int)

// Returns a non-null pointer if the test succeeded; null otherwise.

typedef void* (*RefCountedTestFunc)(void* context);
typedef void (*RefCountedDestructorFunc)();

struct RefCountedObject {
    void** vtable;          // +0x00
    int refCount;           // +0x04
};

undefined1* __fastcall refCountedConditionalRelease(
    void* unusedThis,           // ECX - not used (may be left from macro expansion)
    void* context,              // EDX - passed to test function
    RefCountedObject* obj       // stack param - object to release
)
{
    // Local variable used as placeholder for success indicator
    undefined1 successIndicator = 0;

    if (obj != (RefCountedObject*)0x0) {
        // Call vtable test method at offset 8
        bool canRelease = ((RefCountedTestFunc)obj->vtable[2])(context);

        // Always decrement reference count
        obj->refCount--;
        if (obj->refCount == 0) {
            // Call vtable destructor at offset 4
            ((RefCountedDestructorFunc)obj->vtable[1])();
        }

        if (canRelease) {
            // Return address of local zero (conceptually a success flag)
            return &successIndicator;
        }
    }
    return (undefined1*)0x0;
}