// FUNC_NAME: EARSObjectBase::initializeWithValidation

class EARSObjectBase {
public:
    // Four signature words at start of object
    int magic1;  // +0x00
    int magic2;  // +0x04
    int magic3;  // +0x08
    int magic4;  // +0x0C

    // Allocated from pool, 0xE0 bytes total
};

// Allocation flags: { type=2, align=0x10, unknown=0 }
struct AllocParams {
    int type;
    int alignment;
    int unknownFlag;
};

// Manager-like object returned from FUN_004aac50
struct ManagerObject {
    void* vtable;          // +0x00
    // offset +0x0E: bit6 indicates something
    // offset +0x20 (puVar2[8]): reference count or flag
};

extern ManagerObject* FUN_004aac50();  // returns manager pointer
extern void* FUN_009c8ed0(int size, AllocParams* params);  // memory allocator
extern void FUN_00450780(int m1, int m2, int m3, int m4, ManagerObject* mgr);  // fixup signature
extern void FUN_0044fbd0(ManagerObject* globalMgr);  // cleanup / deref

static const int EXPECTED_MAGIC1 = 0xBABDB9BA;
static const int EXPECTED_MAGIC2 = 0xBEEFBEEF;
static const int EXPECTED_MAGIC3 = 0xEAC15A55;
static const int EXPECTED_MAGIC4 = 0x91100911;

// __thiscall: this in ECX (EAX in decompiled, likely __thiscall with this in EAX due to Ghidra)
ManagerObject* EARSObjectBase::initializeWithValidation() {
    AllocParams params;
    params.type = 2;
    params.alignment = 0x10;
    params.unknownFlag = 0;

    // Allocate 0xE0 bytes for this object
    void* memBlock = FUN_009c8ed0(0xE0, &params);
    if (memBlock == nullptr) {
        return nullptr;
    }

    ManagerObject* mgr = FUN_004aac50();  // get manager / context
    if (mgr != nullptr) {
        // Check bit6 of byte at offset +0x0E
        if ((*(unsigned char*)((char*)mgr + 0x0E) & 0x40) != 0) {
            // Call first virtual function with argument 1 (likely error/abort)
            void (*func)(int) = *(void (**)(int))mgr->vtable;
            func(1);
            return nullptr;
        }

        // Validate object signature
        if (magic1 != EXPECTED_MAGIC1 || magic2 != EXPECTED_MAGIC2 ||
            magic3 != EXPECTED_MAGIC3 || magic4 != EXPECTED_MAGIC4) {
            FUN_00450780(magic1, magic2, magic3, magic4, mgr);
        }

        // If reference count / flag at offset +0x20 is set
        if (mgr[8] != 0) {
            extern ManagerObject* g_globalManager;  // DAT_012233a4
            FUN_0044fbd0(g_globalManager);
        }
    }

    return mgr;
}