// FUNC_NAME: EANetObject::writeUpdate

// Offset constants
constexpr int kStateBlockOffset = 0x130;       // +0x130: pointer to state block (vtable)
constexpr int kBlockIsEmpty = 0x161;           // +0x161: bool (0 = populated)
constexpr int kFlagsByte = 0x1ac;              // +0x1ac: flags byte (bit0 used)
constexpr int kHasSerialData = 0x164;          // +0x164: bool (non-zero = serialize transform)
constexpr int kTransformSource = 0x54;         // +0x54: source transform (pointer?)
constexpr int kUpdatedFlag = 0x19d;            // +0x19d: bool (set to 1 on update)
constexpr int kTransformOffset = 0x180;        // +0x180: 16 bytes (two doubles? or quaternion+position)
constexpr int kTransformSize = 16;             // bytes
constexpr int kTransformDirty = 0x19c;         // +0x19c: bool (cleared after copy)
constexpr int kTransformSeq = 0x194;           // +0x194: uint32 (sequence number)
constexpr int kControllerId = 0x190;           // +0x190: uint32 (controller/object ID)

// Global data (accessed through import stubs)
extern uintptr_t globWritePointer;             // DAT_01206880 + 0x14 (pointer to write buffer)
extern uintptr_t globWriteVtable;              // PTR_LAB_0110ba94 (vtable for serialized data)
extern void* globValidationFunc;               // DAT_01205498 (callback for validation)
extern uint32_t defaultControllerId;           // DAT_00e2e50c (default ID if validation fails)

// External functions
extern void Func_004a4ce0(void);
extern void Func_00470a10(bool flag);
extern void Func_004785e0(void);

// Forward declaration for state block structure
struct StateBlockVTable; // unknown layout, vtable-only reference

void __fastcall EANetObject::writeUpdate(void* thisPtr)
{
    StateBlockVTable* stateBlock = *(StateBlockVTable**)((char*)thisPtr + kStateBlockOffset);
    if (stateBlock == nullptr) {
        return;
    }

    // If the state block is not empty, call its virtual methods and a global function
    if (*(char*)((char*)thisPtr + kBlockIsEmpty) == '\0') {
        (**(code**)(*(int*)stateBlock + 0x24))();  // stateBlock->vtable[0x24>>2]
        (**(code**)(*(int*)stateBlock + 0x2c))();  // stateBlock->vtable[0x2c>>2]
        Func_004a4ce0();
    }

    // Propagate a flag bit
    Func_00470a10(*(char*)((char*)thisPtr + kFlagsByte) & 1);

    // If we have serialization data pending, write the transform into global buffer
    if (*(int*)((char*)thisPtr + kHasSerialData) != 0) {
        uint32_t* writePtr = (uint32_t*)(globWritePointer + 0x14);
        *(uint32_t**)writePtr = &globWriteVtable;  // write vtable pointer
        *writePtr = *writePtr + 4;                 // advance (maybe for array)
        *(uint32_t*)*writePtr = (uint32_t)((char*)thisPtr + kTransformSource); // write source address
        *writePtr = *writePtr + 4;                 // advance
        *(uint8_t*)*writePtr = 1;                  // write bool (1)
        *writePtr = (*writePtr + 4) & 0xFFFFFFFC;  // align to 4 bytes
    }

    // Mark this object as updated
    *(uint8_t*)((char*)thisPtr + kUpdatedFlag) = 1;

    // Copy 16 bytes from state block to this object's transform fields
    *(uint64_t*)((char*)thisPtr + kTransformOffset) = *(uint64_t*)((char*)stateBlock + 8);
    *(uint64_t*)((char*)thisPtr + kTransformOffset + 8) = *(uint64_t*)((char*)stateBlock + 16);

    // Clear dirty flag and sequence
    *(uint8_t*)((char*)thisPtr + kTransformDirty) = 0;
    *(uint32_t*)((char*)thisPtr + kTransformSeq) = 0;

    // Validate or assign default controller ID
    if (globValidationFunc != nullptr) {
        bool result = ((bool(*)(void*, void*, void*))globValidationFunc)(
            thisPtr,
            (void*)((char*)thisPtr + kTransformOffset),
            (void*)((char*)thisPtr + kControllerId)
        );
        if (!result) {
            goto assignDefault;
        }
    } else {
assignDefault:
        *(uint32_t*)((char*)thisPtr + kControllerId) = defaultControllerId;
    }

    Func_004785e0();
}