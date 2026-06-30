// FUNC_NAME: allocateResourceBuffer
// Address: 0x005f1c60
// Role: Initialize global resource buffer with 128-byte capacity and zero out memory.
// Called from main initialization at 0x005e33e0.

#include <cstdint>

// Global resource buffer structure (offsets relative to g_resourceBuffer)
struct ResourceBuffer {
    void* data;       // +0x00 Pointer to allocated memory (initially null)
    int32_t size;     // +0x04 Current allocated size (initially 0)
    int16_t capacity; // +0x08 Maximum capacity (initialized to 128 = 0x80)
    int8_t flags;     // +0x0A Flags (initialized to 0)
};

// External references from other modules
extern int32_t FUN_005f5830(uint32_t size, uint32_t alignment, void* errorHandler);
extern void FUN_005dbc10(void* ptr, uint32_t count);

// Global resource buffer instance
static ResourceBuffer g_resourceBuffer __attribute__((section(".data"))) __attribute__((used));

// Function: allocateResourceBuffer
// Attempts to allocate memory of size 0x80 with alignment 0x90 and a failure handler.
// On success, initializes the global buffer and zeroes the allocated memory.
// Returns 1 on success, 0 on failure.
int32_t allocateResourceBuffer(void)
{
    // FUN_005f5830: Likely memory allocation with error callback (LAB_005f1770)
    char success = FUN_005f5830(0x80, 0x90, &LAB_005f1770);
    if (success != 0) {
        g_resourceBuffer.data = 0;
        g_resourceBuffer.size = 0;
        g_resourceBuffer.capacity = 0x80; // 128
        g_resourceBuffer.flags = 0;
        FUN_005dbc10(&g_resourceBuffer, 0x80); // Zero out the structure (or possibly the allocated memory)
        return 1;
    }
    return 0;
}