// FUNC_NAME: BNKStreamManager::Constructor
// Address: 0x006abfa0
// Reconstructed constructor for BNKStreamManager (EARS audio bank stream manager)
// Initializes a large buffer (0x8000 bytes) and sets up vtable pointers.

#include <cstdint>

// Forward declarations for called functions
void __thiscall baseClassConstructor(void* param); // FUN_0046c590
void copyMemory(void* dest, const void* src, uint32_t size); // FUN_00408900 (likely memcpy)

// External global data (0x8000-byte buffer source)
extern const uint8_t DAT_0120e93c[0x8000]; // Global audio data source

// Vtable symbols (from Ghidra)
extern void* PTR_FUN_00d5da8c; // BNKStreamManager vtable
extern void* PTR_LAB_00d5da7c; // Sub-vtable or interface pointer
extern void* PTR_LAB_00d5da78; // Sub-vtable or interface pointer

class BNKStreamManager {
public:
    // Offset 0x00: vtable pointer (set by constructor)
    void* vtable; // +0x00

    // Offset 0x3C (0x0F * 4): Pointer to sub-vtable or interface
    void* subVtable1; // +0x3C

    // Offset 0x48 (0x12 * 4): Pointer to sub-vtable or interface
    void* subVtable2; // +0x48

    // Offset 0x50 (0x14 * 4): Some integer, initialized to 0
    int32_t field_0x50; // +0x50

    // Offset 0x54 (0x15 * 4): 16-bit field, initialized to 0
    uint16_t field_0x54; // +0x54

    // Offset 0x56: Another 16-bit field, initialized to 0
    uint16_t field_0x56; // +0x56

    // Offset 0x58 (0x16 * 4): Some integer, initialized to 0
    int32_t field_0x58; // +0x58

    // Large buffer from offset 0x3C to 0x3C + 0x8000 (if copy occurs)
    // Actually the buffer starts at offset 0x3C, but the structure is likely
    // arranged so that the 0x8000-byte buffer begins here.
    // For simplicity, we treat it as an array starting at offset 0x3C.
    uint8_t buffer[0x8000]; // +0x3C (overlaps with subVtable1? careful: subVtable1 is a pointer, buffer comes after? Actually the copy size 0x8000 suggests the buffer consumes a large area; the pointers at 0x3C and 0x48 are within this buffer? Not exactly. The Ghidra decomp shows that param_1+0xf is passed as destination for copy, meaning the buffer starts at offset 0x3C. The pointers at offset 0x3C and 0x48 are overwritten by the copy? That would be messy. More likely the buffer starts after these fields. Let's reinterpret:
    // Actually, param_1[0xf] is set to &PTR_LAB_00d5da7c before the copy. Then if the copy happens, it overwrites that location? That would destroy the pointer. So likely the buffer is at a different offset. Re-checking decomp: The condition checks DAT_0120e93c != 0, and if true, calls copy(param_1+0xf, &DAT_0120e93c, 0x8000). That means the buffer destination is exactly at offset 0x3C. So if the copy happens, it overwrites the pointer we just set. That seems intentional: the pointer at 0x3C is either a vtable pointer or the start of a buffer. But later, the pointer at 0x48 is set independently. So maybe the class has a union or the buffer is placed such that it does not conflict with subVtable2. The buffer size 0x8000 starting at 0x3C would extend to 0x803C, covering field_0x50, field_0x54, etc. That cannot be right unless those fields are inside the buffer. But the code sets field_0x50, field_0x54, field_0x56, field_0x58 before the conditional copy. If copy overwrites, those values would be destroyed. So likely the copy happens only if DAT_0120e93c != 0, and in that case the fields at 0x50+ might be irrelevant? Or the buffer placement is different: maybe param_1+0xf is not the start of the buffer but a pointer inside the object that points to a separate buffer? But the copy uses it directly as destination. Given the ambiguity, we'll reconstruct exactly as the decompiler shows, noting the offsets.
    
    // For accurate reconstruction, we'll follow the decompiled logic:
    // 1) Call base constructor
    // 2) Set vtable
    // 3) Set subVtable1 at +0x3C
    // 4) Set subVtable2 at +0x48
    // 5) Set field at +0x50 to 0
    // 6) Set short at +0x54 to 0
    // 7) Set short at +0x56 to 0
    // 8) Set field at +0x58 to 0
    // 9) If condition, copy 0x8000 bytes from global into +0x3C (which overwrites subVtable1 and buffer onwards)
    
    // Therefore, the layout is unusual. We'll just implement as per decompilation.
    */

    // Constructor
    BNKStreamManager(void* param_2) {
        baseClassConstructor(param_2); // FUN_0046c590

        vtable = &PTR_FUN_00d5da8c; // Set vtable

        // Set pointers/fields
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + 0x3C) = &PTR_LAB_00d5da7c;
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + 0x48) = &PTR_LAB_00d5da78;
        *reinterpret_cast<int32_t*>(reinterpret_cast<uintptr_t>(this) + 0x50) = 0;
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(this) + 0x54) = 0;
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(this) + 0x56) = 0;
        *reinterpret_cast<int32_t*>(reinterpret_cast<uintptr_t>(this) + 0x58) = 0;

        // If global buffer exists, copy 32KB into this object starting at offset 0x3C
        if (DAT_0120e93c != nullptr) {
            copyMemory(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x3C), &DAT_0120e93c, 0x8000);
        }
    }
};