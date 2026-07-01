// FUNC_NAME: 0x0098db20 - ManagerClass::processByKey
// Reconstructed C++ member function. The function iterates over an array of elements (each 20 bytes)
// stored in a container, looking for a specific key. If found or if count is zero, it calls a
// stored callback function. Otherwise it returns without calling.
// Field offsets (relative to this):
// +0x7c: pointer to container object (array starts at container+0x10)
// +0x80: number of elements in the array
// +0x8c: callback function pointer (void (*)(void*))
// +0x94: key value to match against first int of each element

// External functions called (assumed to be part of the same module)
extern void __fastcall FUN_0098ce00(int arg);
extern void __fastcall FUN_0098da50(void);

class ManagerClass {
public:
    // Member function – likely called as __thiscall
    void processByKey() {
        // Lock or prepare processing
        FUN_0098ce00(1);
        FUN_0098da50();

        unsigned int count = *(unsigned int*)((char*)this + 0x80);
        if (count == 0) {
            // No elements – call callback directly
            void (*callback)(void*) = *(void (**)(void*))((char*)this + 0x8c);
            callback(this);
            return;
        }

        int keyToMatch = *(int*)((char*)this + 0x94);
        int* elementArray = *(int**)((char*)this + 0x7c) + 0x10; // container+0x10 points to array

        // Each element is 5 ints (20 bytes)
        for (unsigned int i = 0; i < count; i++) {
            if (*elementArray == keyToMatch) {
                // Found matching element – call the callback
                void (*callback)(void*) = *(void (**)(void*))((char*)this + 0x8c);
                callback(this);
                break;
            }
            elementArray += 5; // move to next element (20 bytes)
        }
    }
};