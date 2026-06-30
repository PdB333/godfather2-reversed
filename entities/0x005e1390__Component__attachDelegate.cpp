// FUNC_NAME: Component::attachDelegate
// Function address: 0x005e1390
// Reconstructed C++ member function of a component class.
// The component holds a pointer to a delegate object at offset 0x04 and a result/handle at offset 0x08.
// Delegate object is an interface with virtual functions at vtable offsets 0x04, 0x08, 0x0C (functions 2,3,4).

class Component {
public:
    // +0x00: vtable pointer (inherited)
    // +0x04: delegate object pointer
    // +0x08: result/handle (e.g., registration ID)

    void attachDelegate(void* pDelegate, int someId) {
        // Store the delegate pointer at offset 0x04
        *(void**)(this + 4) = pDelegate;

        // Call third virtual function on the delegate (offset 0x08)
        // This might be an initialization or setup step.
        ((void (*)())(*(void***)pDelegate)[2])();

        if (someId != 0) {
            // Call FUN_004265d0 (likely a resource/object creation function)
            // Returns a result stored at offset 0x08
            *(int*)(this + 8) = FUN_004265d0(someId, *(void**)(this + 4));

            // Call second virtual function on delegate (offset 0x04) with arguments: someId and 0
            ((void (*)(int, int))(*(void***)pDelegate)[1])(someId, 0);

            // Call fourth virtual function on delegate (offset 0x0C)
            ((void (*)())(*(void***)pDelegate)[3])();
        } else {
            // No ID: clear result at offset 0x08
            *(int*)(this + 8) = 0;

            // Call only the fourth virtual function
            ((void (*)())(*(void***)pDelegate)[3])();
        }
    }
};

// Note: FUN_004265d0 is an external function that takes an int and a void* and returns an int.
extern int FUN_004265d0(int id, void* delegatePtr);