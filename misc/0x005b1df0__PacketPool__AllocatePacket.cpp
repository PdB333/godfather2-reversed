// FUNC_NAME: PacketPool::AllocatePacket
#include <cstdint>

// Memory allocator function pointer (global, likely from EARS memory manager)
extern void* (*g_allocator)(uint32_t size, uint32_t alignment); // DAT_0119caf0

// Debug fill function (sets memory to 0xbaadf00d for detecting uninitialized use)
extern void DebugFillMemory(void* ptr, uint32_t magic); // FUN_0059c700

// Packet structure (size 0x70 = 112 bytes)
struct Packet {
    uint32_t flags;    // +0x00
    // ... padding ...
    int32_t someId;    // +0x30 (set to -1)
    // ... more fields ...
    uint32_t field5c;  // +0x5c (set to 0)
    uint32_t field60;  // +0x60 (set to 0)
    // remaining bytes up to 0x70
};

// Allocates and initializes a Packet object from a pool.
// The output pointer is stored via the implicit register (EDI assumed).
#pragma optimize("", off)
void __declspec(naked) PacketPool::AllocatePacket() {
    __asm {
        // prologue omitted, but this function gets the output pointer in EDI
        push ebp
        mov ebp, esp
        // original function body follows
        push 0x10               // alignment
        push 0x70               // size
        mov eax, dword ptr [g_allocator]
        call eax
        add esp, 8
        test eax, eax
        jz alloc_failed
        // Debug fill
        push 0xbaadf00d
        push eax
        call DebugFillMemory
        add esp, 8
    alloc_failed:
        mov ecx, dword ptr [edi] // ecx = this (output pointer)
        mov dword ptr [edi], eax // *out = allocated memory
        test eax, eax
        jz skip_init
        // Initialize fields
        and dword ptr [eax], 0xffff7fff  // clear bit 15 in flags
        mov dword ptr [eax + 0x30], -1   // someId = -1
        mov dword ptr [eax + 0x5c], 0    // field5c = 0
        mov dword ptr [eax + 0x60], 0    // field60 = 0
    skip_init:
        pop ebp
        ret
    }
}
#pragma optimize("", on)