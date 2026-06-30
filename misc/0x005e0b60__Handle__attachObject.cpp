// FUNC_NAME: Handle::attachObject
// Function at 0x005e0b60
// __thiscall method to attach an object and an optional second resource (e.g., a reference or handle) to a handle container.
// The handle stores a pointer to the object at offset +0x0C and a second value (resource handle) at +0x10.
// Virtual calls on the object at offsets 0x08, 0x04, and 0x0C correspond to init/release/copy functions.

class Handle {
public:
    void* objectPtr;    // offset +0x00 (vtable pointer for Handle itself)
    // ... other members ...
    // +0x0C: attached object pointer
    // +0x10: second resource value (int or handle)
};

// Forward declarations for internal engine functions
int FUN_004265d0(int param1, void* param2); // e.g., increment reference or copy
void FUN_005e1390(void* param1, int param2); // e.g., initialize or bind

void Handle::attachObject(void* obj, int resource) {
    void* thisPtr = this; // ECX

    // Call virtual function at vtable offset 0x08 on the object (third entry)
    // Typically used for initialisation or AddRef
    (*(void (**)(void*))(*(int*)obj + 8))(obj);

    int secondArg;
    if (resource == 0) {
        secondArg = 0;
    } else {
        secondArg = FUN_004265d0(resource, obj);
    }

    FUN_005e1390(obj, secondArg); // Bind or adjust counts

    // Store object pointer at offset +0x0C of this handle
    *(void**)((char*)thisPtr + 0x0C) = obj;

    // Call same virtual function again (second initialisation step?)
    (*(void (**)(void*))(*(int*)obj + 8))(obj);

    if (resource != 0) {
        // Obtain second resource value from resource parameter using the stored object
        int secondVal = FUN_004265d0(resource, *(void**)((char*)thisPtr + 0x0C));
        *(int*)((char*)thisPtr + 0x10) = secondVal;

        // Call virtual functions at offset 0x04 and 0x0C on the object
        (*(void (**)(int, int))(*(int*)obj + 4))(resource, 0); // e.g., setFlag(resource,0)
        (*(void (**)(void))(*(int*)obj + 12))();              // e.g., finalize()
    } else {
        // No resource – clear second field
        *(int*)((char*)thisPtr + 0x10) = 0;
        (*(void (**)(void))(*(int*)obj + 12))(); // finalize only
    }
}