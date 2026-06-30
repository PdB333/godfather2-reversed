// FUNC_NAME: updateAnimSlotValue
// Address: 0x00591160
// Role: Evaluates a value from a provider function table (indexed by low 6 bits of a byte) and stores it in an array slot, with bounds checking and error handling.

// Global default value used if no valid provider is invoked
extern float g_defaultAnimValue; // DAT_00e2b1a4

// Global array of value provider function pointers (indexed by providerIndex)
// Max index 0x22 (34 providers)
typedef float (*ValueProviderFunc)(int arg);
extern ValueProviderFunc g_valueProviderTable[]; // DAT_0103b050

// Error handler called when slot index exceeds array capacity
void __fastcall handleSlotArrayError(int* errorCode); // FUN_00591c00

// The function receives its primary context via registers:
//   EAX - pointer to a slot descriptor (struct { uint8_t providerIndex; int16_t slotIndex; })
//   ESI - pointer to a slot array structure (struct { float* data; uint32_t count; })
//   EDX - argument passed to the selected value provider
// This is an internal calling convention used by the animation system.
void __fastcall updateAnimSlotValue(int unused, int providerArg)
{
    // Pointer to slot descriptor passed via EAX
    struct SlotDescriptor {
        uint8_t providerIndex;  // +0x00 (low 6 bits used)
        uint8_t padding;       // +0x01 (unused)
        int16_t slotIndex;     // +0x02
    }* desc;

    // Pointer to slot array passed via ESI
    struct SlotArray {
        float* data;   // +0x00
        uint32_t count; // +0x04
    }* array;

    // These are register variables; in the reconstructed function we treat them as implicit.
    // For correctness, we note that the caller ensures these are set before calling.
    // In the actual binary, the compiler uses register allocation for EAX and ESI.
    float value = g_defaultAnimValue;

    // Use low 6 bits of the descriptor's first byte as index into provider table
    uint8_t providerIdx = desc->providerIndex & 0x3f;
    if (providerIdx < 0x23) {
        value = (float)g_valueProviderTable[providerIdx](providerArg);
    }

    int16_t slotIdx = desc->slotIndex;

    // Bounds check: if slot index is beyond array capacity, call error handler
    if ((uint32_t)slotIdx >= array->count) {
        int errorCode = 0;
        handleSlotArrayError(&errorCode);
    }

    // Store the computed value into the slot's data array
    array->data[slotIdx] = value;
}