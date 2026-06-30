// FUNC_NAME: Vehicle::constructor

// Function at 0x005f7440: Constructor for a Vehicle-like class (EA EARS engine)
// Initializes member fields, allocates arrays for wheels/axles, and sets up sub-objects.

struct AllocatorInterface {
    virtual ~AllocatorInterface() = 0;
    virtual void* Alloc(size_t size, uint alignment) = 0; // offset 0
    virtual void Free(void* ptr, bool dealloc) = 0;       // offset 4
    virtual void BeginAlloc() = 0;                         // offset 8
    virtual void EndAlloc() = 0;                           // offset 0xC
};

// Forward declarations for helper functions called
extern int FUN_004265d0(void* allocRequest, AllocatorInterface* alloc);
extern void FUN_005f8f90(void* subObj); // offset +0x34
extern void FUN_005f9190(void* subObj); // offset +0x54
extern void* FUN_004abe90(void* base, int numElements, int elementSize, int alignment);
extern int FUN_005f73d0(int count); // returns something stored at +0x30

class Vehicle {
public:
    // vtable, at +0x00
    void** vfTable;

    // Fields
    int field_4;      // +0x04, initialized to 0
    int field_8;      // +0x08, initialized to 0
    int field_C;      // +0x0C, initialized to 0
    AllocatorInterface* allocator; // +0x10, param_2
    int wheelCount;   // +0x14, param_3 (number of wheels)
    int axleCount;    // +0x18, param_4 (number of axles)
    int field_1C;     // +0x1C, param_6
    int field_20;     // +0x20, param_5
    int field_24;     // +0x24, param_7
    void* wheelArray; // +0x28, allocated array of size (wheelCount * 0x14) elements
    void* axleArray;  // +0x2C, allocated array of size (axleCount * 0x50) elements
    int field_30;     // +0x30, result of FUN_005f73d0(axleCount)

    // Sub-objects at known offsets
    // +0x34: sub-object of size ? (initialized by FUN_005f8f90)
    // +0x54: sub-object of size ? (initialized by FUN_005f9190)

    Vehicle(AllocatorInterface* alloc, int wheelCount_, int axleCount_,
            int param5, int param6, int param7) {
        // Set global pointer (maybe gSomeVehicle)
        DAT_01223520 = this;

        // Set vtable pointer (from global data)
        vfTable = (void**)&PTR_FUN_00e407bc;

        // Initialize zero fields
        field_4 = 0;
        field_8 = 0;
        field_C = 0;

        // First allocation block: wheel acquisition
        {
            int allocationRequest[3] = {0, 0, 0}; // local_14, local_10, local_c
            allocator->BeginAlloc();
            int allocResult = FUN_004265d0(allocationRequest, allocator);
            FUN_005f8f90((char*)this + 0x34);
            if (allocResult != 0) {
                allocator->Free((void*)allocResult, 0);
            }
            allocator->EndAlloc();
        }

        // Second allocation block: axle acquisition
        {
            int allocationRequest[3] = {0, 0, 0};
            allocator->BeginAlloc();
            int allocResult = FUN_004265d0(allocationRequest, allocator);
            FUN_005f9190((char*)this + 0x54);
            if (allocResult != 0) {
                allocator->Free((void*)allocResult, 0);
            }
            allocator->EndAlloc();
        }

        // Store configuration parameters
        wheelCount = wheelCount_;
        axleCount = axleCount_;
        field_24 = param7;
        field_1C = param6;
        allocator = alloc;
        field_20 = param5;

        // Allocate wheel array
        allocator->BeginAlloc();
        {
            int allocRequest[3] = {2, 4, 0}; // alignment 4, byteSize? Actually parameters: elementSize=0x14, count=wheelCount, baseOffset=0x20
            int baseAlloc = allocator->Alloc(wheelCount * 0x14 + 0x20, 1); // size includes header
            if (baseAlloc == 0) {
                wheelArray = 0;
            } else {
                wheelArray = FUN_004abe90((void*)(baseAlloc + 0x20), wheelCount, 0x14, 4);
            }
        }
        allocator->EndAlloc();

        // Allocate axle array
        {
            // local_1c = 2, iStack_18 = 4 (alignment?)
            int alignment = 2;
            int byteSize = 4;
            int allocRequest[3] = {0, 0, 0}; // placeholder, but actually uses &alignment as request? Decompiled sets local_1c = (int *)0x2; iStack_18 = 4; but then calls allocator->Alloc with &local_1c.
            // The decompiled: iVar2 = (*(code *)**(undefined4 **)param_1[4])(iVar1 * 0x50 + 0x20,&local_1c);
            // So it calls alloc->Alloc(size, &allocationRequest) with request containing alignment? Let's follow pattern.
            int* allocRequestPtr = (int*)2; // approximate, but we'll replicate as simple
            int baseAlloc = allocator->Alloc(axleCount * 0x50 + 0x20, (void*)&alignment); // alignment passed via struct
            if (baseAlloc == 0) {
                axleArray = 0;
            } else {
                axleArray = FUN_004abe90((void*)(baseAlloc + 0x20), axleCount, 0x50, 4);
            }
        }

        // Store final result from helper
        field_30 = FUN_005f73d0(axleCount);
    }
};

// Note: The exact allocation call for the axle array is complex due to decompilation artifacts.
// The function passes a pointer to a local struct containing alignment info (0x2, 0x4).
// For clarity, we've approximated the allocation interface.