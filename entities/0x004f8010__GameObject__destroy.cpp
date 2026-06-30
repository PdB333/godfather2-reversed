// FUNC_NAME: GameObject::destroy
// Address: 0x004f8010
// Role: Cleanup/destructor for a game object, releases shared resources, removes from global list.

// Represents a reference-counted object with vtable at offset 0 and refCount at offset 4
struct RefCountedObject {
    void** vtable;   // +0x00
    int refCount;    // +0x04
};

// Container for an intrusive pointer to a reference-counted object
struct SharedResourceContainer {
    char pad0[8];                // +0x00 (unused)
    void* m_pSomePointer;        // +0x08 (cleared in some paths)
    uint32_t m_flags;            // +0x0C (flag set in some paths)
    char pad1[16];               // +0x10 until +0x20
    RefCountedObject* m_pObject; // +0x20 (intrusive pointer)
};

// Global list head (from DAT_01206880 + 0x14)
extern void* g_pGlobalListHead; // points to an array of pointers, used for deferred addition
extern void (*g_releaseComponent)();      // FUN_004ebba0 - releases a sub-component
extern void (*g_handleFlagNotSet)();      // FUN_0051d6b0
extern void (*g_handleFlagSet)();         // FUN_0051b340
extern void (*g_releaseSubObject1)();     // FUN_004f8530
extern void (*g_releaseSubObject2)();     // FUN_009c8eb0

// External vtable pointers
extern void* PTR_LAB_00e37940;   // base vtable (cleanup)
extern void* PTR_FUN_00e37110;   // new vtable after cleanup
extern void* PTR_LAB_01123be8;   // vtable for global list entry

class GameObject {
public:
    // Vtable pointer (offset 0x00)
    void** m_vtable;

    // Various fields – offsets based on unaff_EDI indices:
    // unaff_EDI[1] (offset 0x04) – unused in this function
    // unaff_EDI[2] (offset 0x08) – unused
    // unaff_EDI[3] (offset 0x0C) – unused
    void* m_pGlobalListEntry; // unaff_EDI[4] (offset 0x10) – pointer added to global list
    void* m_pGlobalListEntry2; // unaff_EDI[5] (offset 0x14) – set to 0
    // (offsets 0x18-0x27 unused)
    uint32_t m_flags;         // unaff_EDI[10] (offset 0x28) – bit 0x100 checked
    SharedResourceContainer* m_pSharedContainer; // unaff_EDI[0xB] (offset 0x2C) – container with intrusive pointer
    void* m_pSubObject;       // unaff_EDI[0xD] (offset 0x34) – another sub-object to release
    // (other fields beyond)

    // Destructor / cleanup method
    void destroy() {
        // Set vtable to base class vtable (prevents virtual calls during destruction)
        m_vtable = &PTR_LAB_00e37940;

        // Release three sub-components (e.g., physics, render, AI)
        g_releaseComponent();
        g_releaseComponent();
        g_releaseComponent();

        // Release the shared resource container (offset 0x2C)
        if (m_pSharedContainer != nullptr) {
            // Intrusive pointer release: decrement refCount, delete if zero
            if (m_pSharedContainer->m_pObject != nullptr) {
                RefCountedObject* obj = m_pSharedContainer->m_pObject;
                obj->refCount--; // decrement refCount at offset 4
                if (obj->refCount == 0) {
                    // Call destructor at vtable[1] (second entry)
                    ((void (*)(RefCountedObject*))obj->vtable[1])(obj);
                }
                m_pSharedContainer->m_pObject = nullptr;
            }
            m_pSharedContainer->m_pObject = nullptr; // redundant, but intentional

            // Check flags at offset 0x28
            if ((m_flags & 0x100) == 0) {
                // Set a flag in the container (offset 0xC) and call handler
                m_pSharedContainer->m_flags |= 0x200000;
                g_handleFlagNotSet();
                // Clear a pointer inside container (offset 0x8)
                m_pSharedContainer->m_pSomePointer = nullptr;
            } else {
                // Alternate handler
                g_handleFlagSet();
            }
        }

        // Release another sub-object (offset 0x34)
        if (m_pSubObject != nullptr) {
            g_releaseSubObject1(m_pSubObject);
            g_releaseSubObject2(m_pSubObject);
        }

        // Switch to a new vtable (final state)
        m_vtable = &PTR_FUN_00e37110;

        // Add a pointer (m_pGlobalListEntry, offset 0x10) to a global list
        if (m_pGlobalListEntry != nullptr) {
            // DAT_01206880 + 0x14 is a pointer to a growing array
            void** listArray = (void**)((char*)&g_pGlobalListHead + 0x14); // Assumes g_pGlobalListHead is base
            // Write a vtable to the current position
            *listArray[0] = &PTR_LAB_01123be8; // set vtable for list entry
            // Add the pointer and advance
            listArray[0] = (void*)((int)listArray[0] + 4);
            *(void**)listArray[0] = m_pGlobalListEntry;
            listArray[0] = (void*)((int)listArray[0] + 4);
            // Clear the members
            m_pGlobalListEntry = nullptr;
            m_pGlobalListEntry2 = nullptr;
        }
    }
};