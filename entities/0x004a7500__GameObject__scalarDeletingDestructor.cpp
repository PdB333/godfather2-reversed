// FUNC_NAME: GameObject::scalarDeletingDestructor
// Function at 0x004a7500: Scalar deleting destructor for GameObject (size 0xB0 bytes)
// Switches vtable to this class, releases container at +0xA0, destroys sub-object at +0x10,
// then sets vtable to base class, and optionally calls operator delete.

// External functions (based on known addresses)
void __cdecl subObjectDestructor(void* obj);                 // 0x00610100
void* __cdecl getScalarDeleter();                           // 0x009c8f80 (returns pointer to delete function table)

class GameObject {
public:
    // Vtable pointer
    void* vtable;                                           // +0x00

    // Unknown data up to offset 0x10
    char unknown_04[0x0C];                                  // +0x04 to +0x0F

    // Sub-object pointer (starts at +0x10)
    void* m_pSubObject;                                     // +0x10

    // Padding to offset 0x90
    char pad_14[0x7C];                                      // +0x14 to +0x8F

    // Flag indicating sub-object ownership
    int m_bHasSubObject;                                    // +0x90

    // Padding to offset 0xA0
    char pad_94[0x0C];                                      // +0x94 to +0x9F

    // Container pointer (reference counted? has vtable)
    void* m_pContainer;                                     // +0xA0

    // Destructor with deletion flag (bit 0: delete object)
    void __thiscall destroy(unsigned char deletingFlag) {
        // Step 1: set vtable to this class's vtable
        this->vtable = (void*)0x00e35538;                   // VTable for GameObject

        // Step 2: release container if present
        if (this->m_pContainer != nullptr) {
            // Call first virtual function on container with argument 1 (likely Release())
            void (*containerRelease)(void*, int) = 
                *(void (**)(void*, int))(*(void**)this->m_pContainer);
            containerRelease(this->m_pContainer, 1);
        }

        // Step 3: destroy sub-object at +0x10 if flag is set
        if (this->m_bHasSubObject != 0) {
            subObjectDestructor(reinterpret_cast<char*>(this) + 0x10);
        }

        // Step 4: switch vtable to base class
        this->vtable = (void*)0x00e2f638;                   // VTable for Base class

        // Step 5: optionally free memory
        if ((deletingFlag & 1) != 0) {
            void* deleteFuncTable = getScalarDeleter();
            // Call delete function at index 1 (size + this pointer)
            void (*customDelete)(void*, int) = 
                *(void (**)(void*, int))((int*)deleteFuncTable + 1);
            customDelete(this, 0xB0);                       // Size 176 bytes
        }
    }
};