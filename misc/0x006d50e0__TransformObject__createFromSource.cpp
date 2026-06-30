// FUNC_NAME: TransformObject::createFromSource
// Reconstructed constructor/factory for a transform object with two 64-byte matrix copies
// The function allocates an object of size 0xD0, initializes its vtable, copies data from src+0x60
// into two separate regions of the new object, and returns the new object.

typedef unsigned int uint32;
struct AllocInfo { uint32 field_0; uint32 field_4; uint32 field_8; }; // size 0xC

// Global function: returns a memory allocator singleton
void* __fastcall getAllocator(); // FUN_009c8f80

// Base class constructor? Called with src as parameter
void __fastcall baseInitialize(uint32* src); // FUN_00473950

// Post‑vtable initialization
void __fastcall postVtblInit(); // FUN_00473750

// Cleanup / release a global
void __fastcall releaseGlobal(uint32 global); // FUN_00473b10

// Global variable (offset into data segment)
extern uint32 g_someGlobal; // _DAT_00d5f3b0

// Vtable symbols (defined elsewhere)
extern uint32* TransformObject_vtable;      // PTR_FUN_00d5f3bc
extern uint32* TransformObject_extraVtable; // PTR_LAB_00d5f3b4  (at offset +8)

// The produced object structure (size 0xD0)
struct TransformObject {
    uint32* vtable;              // +0x00
    uint32 _pad[1];              // +0x04? (Not touched, but vtable[2] is set)
    uint32* extraVtable;         // +0x08 (set to TransformObject_extraVtable)
    uint32 _pad_0x0C[5];         // +0x0C to +0x1F (3B? Actually 5*4=20 → ends at 0x20)
    uint32 matrixA[16];          // +0x20 (first copy of 16 dwords)
    uint32 _pad_0x60_0x9F[16];   // +0x60 to +0x9F? Actually padding? But matrixB starts at +0x60
    uint32 matrixB[16];          // +0x60 (second copy of 16 dwords) - note overlap with padding
    uint32 zeroAt0xA0;           // +0xA0 (set to 0)
    uint32 zeroAt0xA4;           // +0xA4 (set to 0)
    uint32 zeroAt0xC0;           // +0xC0 (set to 0)
    // ... remainder up to 0xD0 unused
};

// Source object: assumed to have a transform at offset 0x60
struct SourceObject {
    // ... other fields ...
    uint32 transform[16];        // +0x60
    // ...
};

// The main factory function
uint32* __fastcall FUN_006d50e0(SourceObject* src) {
    uint32* allocator = (uint32*)getAllocator(); // get singleton allocator
    AllocInfo allocInfo = { 2, 0x10, 0 };      // allocation parameters (e.g., alignment flags)
    
    // Allocate object: size 0xD0, using the allocator's vtable
    uint32* newObj = (uint32*)(**(uint32 (__thiscall**)(uint32*, uint32, AllocInfo*))*allocator)(0xD0, &allocInfo);
    
    if (newObj != nullptr) {
        baseInitialize((uint32*)src);                 // initialize base class with source
        newObj[0] = (uint32)TransformObject_vtable;   // set vtable at offset 0
        newObj[2] = (uint32)TransformObject_extraVtable; // set extra vtable at offset 8
        postVtblInit();                               // post‑vtable initialization
        newObj[0x28] = 0;   // +0xA0
        newObj[0x30] = 0;   // +0xC0
        newObj[0x29] = 0;   // +0xA4
        // Now copy 16 dwords from src->transform to newObj->matrixA
        uint32* dstA = newObj + 8;  // offset 0x20 (since newObj is uint32*, index 8 = 0x20)
        uint32* srcTransform = (uint32*)((char*)src + 0x60);
        for (int i = 0; i < 16; ++i) {
            dstA[i] = srcTransform[i];
        }
        // Copy the same 16 dwords to newObj->matrixB at offset 0x60
        uint32* dstB = newObj + 0x18; // offset 0x60 (index 0x18 = 24)
        // Reset srcTransform pointer (note: both loops read from the same source)
        srcTransform = (uint32*)((char*)src + 0x60);
        for (int i = 0; i < 16; ++i) {
            dstB[i] = srcTransform[i];
        }
        releaseGlobal(g_someGlobal);  // cleanup global reference
    }
    return newObj; // returns pointer to TransformObject (or nullptr if alloc failed)
}