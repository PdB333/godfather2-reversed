// FUNC_NAME: EARS::SoundBuffer::create
// Address: 0x0060be80
// Purpose: Creates or initializes a DirectSound-compatible audio buffer with optional streaming support.
// This is likely a static factory method that allocates a SoundBuffer object and sets up its internal state.

#include <cstring> // for memcpy

// Global pointer to the audio manager (likely EARS::SoundManager or similar)
extern void* gSoundManager; // DAT_01205750

// External allocation function for memory pools
extern void* __stdcall memAlloc(int size, int flags); // via DAT_01205868

// External function called after buffer data commit
extern void soundBufferCommit(); // FUN_0060be40

// Forward declaration of the class
class SoundBuffer;

// Structure for the vtable of SoundBuffer (inferred from calls)
struct SoundBufferVTable {
    void* (*method0)();   // placeholder, likely destructor
    void* (*method4)();   // ...
    void* (*method8)();   // ...
    void* (*methodC)();   // ...
    void* (*method10)();  // ...
    void* (*method14)();  // ...
    void* (*method18)();  // ...
    void* (*method1C)();  // ...
    void* (*method20)();  // ...
    void* (*method24)();  // ...
    void* (*method28)();  // ...
    void* (__thiscall* lock)(SoundBuffer* this, void* zero, void* param3, void** bufferPtr, int flags); // +0x2C
    void* (__thiscall* unlock)(SoundBuffer* this); // +0x30
    // ... more methods possible
};

// The SoundBuffer class - size 0x20 (32 bytes)
class SoundBuffer {
public:
    SoundBufferVTable* vtable;           // +0x00: pointer to virtual function table
    SoundBuffer* selfRef;                // +0x04: self-reference (for reference counting? or just tracking)
    uint8_t flags;                       // +0x08: byte flags (bit 0: streaming)
    uint8_t pad1[3];                     // alignment padding
    int size;                            // +0x0C: buffer size in bytes? (param_1)
    uint16_t field10;                    // +0x10: unknown, set to 0
    uint16_t field12;                    // +0x12: unknown, set to 0
    void* bufferPointer;                 // +0x14: pointer to the actual audio data buffer (written after lock)
    // remaining bytes up to 0x20 are likely unused or padding

    // Static factory method to create a SoundBuffer
    // param_1: size (in bytes? probably stereo 16-bit => samples * 2? actually param_1*2 used later)
    // param_2: ignored (unused parameter from decompiled signature)
    // param_3: flags (bits: 0x2, 0x4, 0x8, 0x10)
    // esi (unaff_ESI): optional initial data pointer (passed in register)
    static SoundBuffer* __thiscall create(SoundBuffer* existing, int bufferSize, uint32_t someFlags, void* initialData) {
        SoundBuffer* buf;
        uint32_t allocFlags = 0;
        uint32_t priority = 1; // uVar2, defaults to 1

        if (existing == nullptr) {
            // No pre-allocated buffer, allocate a new one from the game memory pool
            int allocInfo[3] = { 0, 2, 0x10 }; // size=0?, alignment? flags
            buf = (SoundBuffer*)(**(code**)*gSoundManager)(0x20, &allocInfo); // actually uses DAT_01205868, this is approximate
            // The actual call is: (**(code **)*DAT_01205868)(0x20, &local_c);
            // But we don't have the function signature, so we simulate via a global function pointer.
            // For reconstruction, we assume it allocates 0x20 bytes.
            buf = (SoundBuffer*)memAlloc(0x20, 2 | 0x10); // simplified
            buf->selfRef = buf;
        } else {
            buf = existing;
            buf->selfRef = nullptr; // mark as not self-allocated? (in_EAX[1] = 0)
        }

        buf->size = bufferSize;
        buf->bufferPointer = nullptr;
        buf->flags = 0;
        buf->field10 = 0;
        buf->field12 = 0;

        // Determine flags based on param_3
        if ((someFlags & 2) == 0) {
            priority = 2; // if bit 2 clear, priority becomes 2
        }
        if (someFlags & 4) {
            allocFlags |= 0x20;
        }
        if (someFlags & 8) {
            allocFlags |= 0x200;
            priority = ~someFlags & 2; // strange: priority = bit 2 inverted? Original: uVar2 = ~param_3 & 2;
            buf->flags = 1; // streaming flag set
        }
        if (someFlags & 0x10) {
            allocFlags |= 8;
        }

        // Call the global sound manager to create the underlying DirectSound buffer
        // Manager likely has a method at vtable+0x6c: CreateBuffer(size_bytes, flags, format, priority, this_soundBuffer, extra)
        // gSoundManager is a pointer to the manager object, which has a vtable
        // We assume the manager class has a method: int CreateBuffer(int sizeBytes, uint flags, int format, uint priority, SoundBuffer* buffer, int unk)
        int result = ((SoundManagerVTable*)(*(void**)gSoundManager))->createBuffer(gSoundManager, bufferSize * 2, allocFlags, 0x65, priority, buf, 0);

        if (result == 0) {
            // Success: if initial data provided, copy it into the buffer
            if (initialData != nullptr) {
                uint32_t lockFlags = 0;
                if (buf->flags & 1) {
                    lockFlags = 0x3000; // streaming lock flags?
                }
                // Lock the underlying buffer (method at vtable + 0x2C)
                buf->vtable->lock(buf, nullptr, nullptr, &buf->bufferPointer, lockFlags);
                // Copy initial data into the locked buffer
                memcpy(buf->bufferPointer, initialData, bufferSize * 2);
                // Commit changes (internal function)
                soundBufferCommit();
                // Unlock (method at vtable + 0x30)
                buf->vtable->unlock(buf);
            }
        } else if (result == 0x8876017C) { // DSERR_BUFFERLOST
            // Buffer was lost, attempt recovery (calls some error handler with parameter 2)
            // Fixed pointer at 0x00f15a3c likely points to an error handling function
            ((void(*)(int))PTR_FUN_00f15a3c)(2);
        }
        return buf;
    }
};

// The callers (FUN_0060c2a0 and FUN_0060c2e0) would use SoundBuffer::create with appropriate parameters.