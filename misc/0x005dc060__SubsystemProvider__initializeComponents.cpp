// FUNC_NAME: SubsystemProvider::initializeComponents

// This function initializes two component objects (size 0x24) and stores them in a container struct.
// It uses a COM-like interface on the calling object to query and release temporary interfaces.
// The container layout:
//   +0x00: (unknown, not used here)
//   +0x04: pointer to this (SubsystemProvider)
//   +0x08: first component
//   +0x0C: second component

struct ComponentContainer {
    void* _unknown0;                      // +0x00
    class SubsystemProvider* provider;    // +0x04
    void* firstComponent;                 // +0x08
    void* secondComponent;                // +0x0C
};

// External functions (constructors for the two component types)
void __fastcall initFirstComponent(void* component, SubsystemProvider* provider);   // FUN_005df540
void __fastcall initSecondComponent(void* component, SubsystemProvider* provider);  // FUN_005dfb00

// Interface helper: queries a temporary interface from the provider
// Returns a handle that must be released via provider->releaseInterface(handle, 0)
int __fastcall queryInterface(void* stackBuf, SubsystemProvider* provider);         // FUN_004265d0

// Allocator: returns 0x24 bytes (or 0 on failure)
void* __fastcall allocateComponent(int size);                                        // FUN_009c8e50 (size=0x24)

class SubsystemProvider {
public:
    // Vtable offsets used:
    // +0x08: ensureReady() - prepares the object before queries
    // +0x04: releaseInterface(void* handle, int param) - releases a temporary interface
    // +0x0C: finalClear() - final cleanup after interface usage
    void ensureReady();
    void releaseInterface(void* handle, int param);
    void finalClear();

    int initializeComponents(ComponentContainer* container) {
        if (this == nullptr) {
            return 0;
        }

        container->provider = this;
        this->ensureReady();

        // ---- First component allocation ----
        void* firstObj = allocateComponent(0x24);
        bool firstAllocated = (firstObj != nullptr);
        if (!firstAllocated) {
            firstObj = nullptr;
        } else {
            // Prepare provider again and query an interface handle
            this->ensureReady();
            int firstHandle = queryInterface(/*stack buffer*/ nullptr, this);  // The actual call uses a local buffer
            initFirstComponent(firstObj, this);

            // Clean up the temporary interface
            if (firstHandle != 0) {
                this->releaseInterface(reinterpret_cast<void*>(firstHandle), 0);
            }
            this->finalClear();
        }
        container->firstComponent = firstObj;

        // ---- Second component allocation ----
        void* secondObj = allocateComponent(0x24);
        bool secondAllocated = (secondObj != nullptr);
        if (!secondAllocated) {
            secondObj = nullptr;
        } else {
            this->ensureReady();
            int secondHandle = queryInterface(/*stack buffer*/ nullptr, this);
            initSecondComponent(secondObj, this);

            if (secondHandle != 0) {
                this->releaseInterface(reinterpret_cast<void*>(secondHandle), 0);
            }
            this->finalClear();
        }
        container->secondComponent = secondObj;

        return 1;
    }
};