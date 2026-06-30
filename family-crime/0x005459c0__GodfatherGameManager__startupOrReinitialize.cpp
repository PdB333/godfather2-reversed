// FUNC_NAME: GodfatherGameManager::startupOrReinitialize
// Address: 0x005459c0
// Role: Initializes or reinitializes all game subsystems. Checks virtual function at vtable+0x198 for initialization state.

class GodfatherGameManager {
public:
    // Virtual function table offset 0x198: bool isInitialized();
    virtual bool isInitialized();

    // Subsystem pointers (stored at offsets from this)
    int* m_pSubsystemA;       // +0x374 (offset 0xdd * 4)
    int* m_pSubsystemB;       // +0x388 (offset 0xe2 * 4)
    int* m_pSubsystemC;       // +0x384 (offset 0xe1 * 4)
    int* m_pSubsystemD;       // +0x368 (offset 0xda * 4)
    int* m_pSubsystemE;       // +0x37c (offset 0xdf * 4)
    int* m_pSubsystemF;       // +0x380 (offset 0xe0 * 4)
    int* m_pSubsystemG;       // +0x378 (offset 0xde * 4)
    int* m_pSubsystemH;       // +0x38c (offset 0xe3 * 4)

    void startupOrReinitialize(void* context); // param_2 = context or resource manager
};

// External memory allocation: alloc(size, pool) returns pointer
int* __stdcall earsAllocate(uint size, uint pool);
// External constructors for subsystems (they initialize the allocated block)
void constructSubsystemA();
void constructSubsystemB();
// ... etc.

// Update/think functions for subsystems
void updateSystemA();
void updateSystemB();
void updateSystemC(GodfatherGameManager* this);
void updateSystemD(void* context, GodfatherGameManager* this);
void updateSystemE(void* context, GodfatherGameManager* this);
void updateSystemF(void* context, int* subsystemEPtr, GodfatherGameManager* this);
void updateSystemG(int* subsystemFPtr, GodfatherGameManager* this);
void updateSystemH(int* subsystemHPtr);

void __thiscall GodfatherGameManager::startupOrReinitialize(void* context) {
    // Check if this is the first time initialization
    if (!isInitialized()) {
        // First-time initialization: allocate and construct all subsystems

        // Get thread-local allocator (side effect)
        TlsGetValue(g_tlsAllocatorIndex);

        // Allocate 48 bytes from pool 0xb for subsystem A and construct it
        int* subA = earsAllocate(0x30, 0xb);
        *(short*)(subA + 4) = 0x30; // size stored for tracking?
        subA = constructSubsystemA(); // returns pointer after construction
        updateSystemA(); // maybe initialize
        m_pSubsystemA = subA; // +0xdd

        TlsGetValue(g_tlsAllocatorIndex);
        // Similarly allocate and construct subsystem B
        int* subB = earsAllocate(0x30, 0xb);
        *(short*)(subB + 4) = 0x30;
        subB = constructSubsystemB();
        updateSystemB();
        m_pSubsystemB = subB; // +0xe2

        // Common initialization step (regardless of first time)
        updateSystemC(this); // +0x?

        // Initialize subsystems that need context
        m_pSubsystemC = initializeSubsystemC(context, this); // +0xe1
        m_pSubsystemD = initializeSubsystemD(context, this); // +0xda
        m_pSubsystemE = initializeSubsystemE(context, this); // +0xdf
        m_pSubsystemF = initializeSubsystemF(context, this); // +0xe0

        // Subsystem G doesn't need context
        m_pSubsystemG = initializeSubsystemG(); // +0xde

        // Allocate and construct subsystem H
        TlsGetValue(g_tlsAllocatorIndex);
        int* subH = earsAllocate(0x14, 0xb);
        *(short*)(subH + 4) = 0x14;
        subH = constructSubsystemH();
        updateSystemH(subH);
        m_pSubsystemH = subH; // +0xe3

        return;
    }
    else {
        // Already initialized: reinitialize/update existing subsystems
        updateSystemA();
        updateSystemB();
        updateSystemC(this);
        updateSystemD(context, this);
        updateSystemE(context, this);
        updateSystemF(context, m_pSubsystemE, this); // uses subsystemE pointer
        updateSystemG(m_pSubsystemF, this);          // uses subsystemF pointer
        updateSystemH(m_pSubsystemH);
        return;
    }
}