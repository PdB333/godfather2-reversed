// FUNC_NAME: Presentation::Presentation

#include <cstddef>

// Forward declarations
class WorkQueue;
class Process;
class ParentObject;

// External functions (from engine)
extern void* AllocateMemory(std::size_t size);               // FUN_009c8e50
extern void* PoolAllocatorCreate();                          // FUN_0066f240
extern int   PoolAllocatorGetSize(void* allocator);          // FUN_009c8e80
extern int   CreateProcess(int* params, WorkQueue* queue);   // FUN_004265d0
extern void  ProcessInit1();                                 // FUN_00622570
extern void  ProcessInit2();                                 // FUN_00622090

// Global pointer
extern Presentation* g_pPresentation; // DAT_012234ac

// Virtual tables (defined elsewhere)
extern void* PTR_FUN_00e414d8;  // vtable for Presentation
extern void* PTR_LAB_00e414c4;  // vtable for WorkQueue

// ---------------------------------------------------------------------------
// WorkQueue class (size 0x1C, fields at offsets 0x14 and 0x18)
class WorkQueue {
public:
    // vtable layout (index * 4):
    // 0: destructor
    // 1: void Release(int handle, int param)
    // 2: void DoSomething()
    // 3: void Cleanup()
    void** vtbl;

    int   field_0x04;      // +0x04
    int   field_0x08;      // +0x08
    int   field_0x0C;      // +0x0C
    int   field_0x10;      // +0x10
    int   currentTasks;    // +0x14  (puVar3[5])
    int   maxTasks;        // +0x18  (puVar3[6])

    void Initialize(int* descArray) {
        // FUN_0066f290
    }

    void Release(int handle, int param) {
        reinterpret_cast<void(*)(int,int)>(vtbl[1])(handle, param);
    }

    void DoSomething() {
        reinterpret_cast<void(*)()>(vtbl[2])();
    }

    void Cleanup() {
        reinterpret_cast<void(*)()>(vtbl[3])();
    }
};

// ---------------------------------------------------------------------------
// Process class (size 0x24)
class Process {
public:
    void** vtbl;  // +0x00
    // ... other fields
};

// ---------------------------------------------------------------------------
// Parent object (passed as param_4)
class ParentObject {
public:
    void** vtbl;

    void CallVirtual() {
        reinterpret_cast<void(*)()>(vtbl[2])();
    }
};

// ---------------------------------------------------------------------------
// Presentation class (size at least 0x20)
class Presentation {
public:
    void** vtbl;              // +0x00
    ParentObject* parent;     // +0x04
    int   unknownZero;        // +0x08
    Process* process1;        // +0x0C
    Process* process2;        // +0x10
    int   someParam;          // +0x14
    WorkQueue* workQueue;     // +0x18
    int   poolHandle;         // +0x1C

    // Constructor
    Presentation(int param2, int param3, ParentObject* param4, int param5);
};

// Reconstructed constructor
Presentation* __thiscall Presentation::Presentation(
    Presentation* this,
    int param2,
    int param3,
    ParentObject* parent,
    int param5)
{
    int* piVar1;
    int iStack_24;
    bool bAllocFailed1;
    bool bAllocFailed2;
    WorkQueue* pWQ;
    Process* pProc;
    int localDesc[3];        // layout: uStack_20, uStack_1c, iStack_18 (size 0xC)
    int poolDesc[4];         // layout: uStack_20(0x18), uStack_1c(4), uStack_14(0x28), uStack_10(4)

    // Store global singleton
    g_pPresentation = this;

    // Set vtable and parent
    this->vtbl = (void**)&PTR_FUN_00e414d8;
    this->parent = parent;

    // Call virtual on parent (index 2 = offset 8)
    parent->CallVirtual();

    // Store param5
    this->someParam = param5;

    // Prepare pool description for WorkQueue::Initialize
    poolDesc[0] = 0x18;   // block size 1
    poolDesc[1] = 4;      // initial count 1
    poolDesc[2] = 0x28;   // block size 2
    poolDesc[3] = 4;      // initial count 2

    // Create pool allocator and store handle in poolHandle
    piVar1 = (int*)PoolAllocatorCreate();
    this->poolHandle = PoolAllocatorGetSize(piVar1);

    // Allocate and initialize WorkQueue
    pWQ = (WorkQueue*)AllocateMemory(0x1C);
    if (pWQ != nullptr) {
        pWQ->vtbl = (void**)&PTR_LAB_00e414c4;
        pWQ->Initialize(poolDesc);
        pWQ->maxTasks = 1;      // puVar3[6] = 1
        pWQ->currentTasks = 0;  // puVar3[5] = 0
    }
    this->workQueue = pWQ;

    // --- Create first process (process1) ---
    pProc = (Process*)AllocateMemory(0x24);
    bAllocFailed1 = (pProc == nullptr);
    if (bAllocFailed1) {
        pProc = nullptr;
    } else {
        // Prepare local descriptor array (all zeros)
        localDesc[0] = 0;
        localDesc[1] = 0;
        localDesc[2] = 0;

        // Call virtual on workQueue (index 2)
        this->workQueue->DoSomething();

        // Create process (returns handle/status)
        iStack_24 = CreateProcess(localDesc, this->workQueue);

        // Initialize first process type
        ProcessInit1();
    }
    this->process1 = pProc;
    if (!bAllocFailed1) {
        if (iStack_24 != 0) {
            this->workQueue->Release(iStack_24, 0);  // vtable[1]
        }
        this->workQueue->Cleanup();  // vtable[3]
    }

    // --- Create second process (process2) ---
    pProc = (Process*)AllocateMemory(0x24);
    bAllocFailed2 = (pProc == nullptr);
    if (bAllocFailed2) {
        pProc = nullptr;
    } else {
        localDesc[0] = 0;
        localDesc[1] = 0;
        localDesc[2] = 0;

        this->workQueue->DoSomething();

        iStack_24 = CreateProcess(localDesc, this->workQueue);

        // Initialize second process type
        ProcessInit2();
    }
    this->process2 = pProc;
    if (!bAllocFailed2) {
        if (iStack_24 != 0) {
            this->workQueue->Release(iStack_24, 0);
        }
        this->workQueue->Cleanup();
    }

    this->unknownZero = 0;
    return this;
}