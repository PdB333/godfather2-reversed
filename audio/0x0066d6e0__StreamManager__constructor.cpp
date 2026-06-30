// FUNC_NAME: StreamManager::constructor
// Address: 0x0066d6e0
// Role: Initializes the StreamManager object, allocating a large buffer pool and internal object,
// setting up critical section, and storing self-reference.

class StreamManager {
public:
    // vtable pointer at offset 0x00
    void* vtable0;
    // vtable pointer at offset 0x04 (likely derived class vtable)
    void* vtable4;
    // unknown field at offset 0x08, set to 1
    int field_0x08;
    // buffer pool pointer at offset 0x0C
    void* bufferPool;
    // pool size at offset 0x10
    int poolSize;
    // internal object pointer at offset 0x14? Actually unaff_ESI[5] is 0x10, but wait:
    // Actually unaff_ESI indices: 0->0x0,1->0x4,2->0x8,3->0xC,4->0x10,5->0x14,6->0x18
    // So unaff_ESI[5] = 0x10 (offset 0x14) set to 0x10, but then overwritten? local_8 = 0x10 is used in alloc call.
    // Most likely there is no field at 0x14; it's just a temporary.
    // And unaff_ESI[6] = actualObj at offset 0x18.
    // So the wrapper class has at least 0x1C bytes.
private:
    // internal object (size 0x520)
    // This is pointed to by unaff_ESI[6] (offset 0x18)
    // But we don't have its fields defined here.
    struct InternalObject {
        // +0x000: (maybe vtable, but not set here directly)
        // +0x004: flags? (masked with 1)
        // +0x46d: byte (set to 0)
        // +0x490: int (set to 0)
        // +0x494: int (set to 0x7fffffff)
        // +0x4ac: function pointer (set to &LAB_0066d6d0)
        // +0x4b0: pointer to wrapper (set to this)
        // +0x4e8: CRITICAL_SECTION*
        // total size 0x520
    };

public:
    void __thiscall constructor() {
        // vtable setup for wrapper (this)
        this->vtable0 = &PTR_LAB_00e444a0;   // base vtable
        this->vtable4 = &PTR_LAB_00e444bc;   // derived vtable (overwrites previous at +0x04)
        // Note: Ghidra shows two assignments to unaff_ESI[1] (offset 0x04); first is overwritten.

        // Store pool size
        this->poolSize = 480000;              // 0x75300

        // Prepare allocation parameters
        int allocParams[3] = { 2, 0x10, 0 }; // local_c, local_8, local_4 (alignment?)
        // Allocate pool memory (e.g., buffer for streaming data)
        void* pool = FUN_009c8ef0(480000, allocParams);
        this->bufferPool = pool;

        // Allocate internal object (size 0x520)
        void* obj = FUN_009c8e50(0x520);
        if (obj != 0) {
            // Call base class initializer on the object
            // Parameters: pool, poolSize, and zeros for flags
            obj = FUN_00643f20(pool, this->poolSize, 0, 0, 0, 0);
        }
        InternalObject* internal = (InternalObject*)obj;
        this->field_0x18 = obj; // store in wrapper at offset 0x18

        // Initialize internal object fields
        *(char*)(internal + 0x46d) = 0;           // some flag
        *(int*)(internal + 0x494) = 0x7fffffff;    // max value (e.g., timer or ID)
        *(int*)(internal + 0x490) = 0;             // counter

        // Critical section manipulation
        CRITICAL_SECTION* cs = *(CRITICAL_SECTION**)((int)internal + 0x4e8);
        if (cs != 0) {
            EnterCriticalSection(cs);
            // Abusing DebugInfo field to increment some counter? 
            // This is likely a custom way to store a lock count or recursion.
            cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo->Type + 1);
        }

        // Call internal initialization (e.g., reset state)
        FUN_00647b20((int)internal);

        // Set a flag in the object (bit 0 must be preserved)
        *(unsigned int*)((int)internal + 4) = *(unsigned int*)((int)internal + 4) & 1;

        if (cs != 0) {
            // Restore DebugInfo (decrement counter)
            cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(cs);
        }

        // Store self-reference in internal object
        *(void**)((int)internal + 0x4ac) = &LAB_0066d6d0; // address of this constructor? (likely a function table)
        *(StreamManager**)((int)internal + 0x4b0) = this;  // pointer to owning wrapper
    }
};