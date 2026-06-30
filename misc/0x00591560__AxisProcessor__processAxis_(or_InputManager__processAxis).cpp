// FUNC_NAME: AxisProcessor::processAxis (or InputManager::processAxis)
// Address: 0x00591560
// Purpose: Normalizes an input axis value using a per-axis processor function, then stores the result in a float buffer.
// Context: EARS engine input system, likely part of ControllerManager or InputManager.
// Global table at DAT_01205570 holds function pointers (0x0C bytes per entry, offset +0x04 is the function pointer).
// DAT_01205574 likely holds the number of entries in that table.
// param_1: raw input value (e.g., joystick axis)
// param_2: context pointer passed to processor callback (probably the 'this' of the owner)
// param_3: pointer to AxisDescriptorSet (see below)
// param_4: pointer to FloatBuffer (holds destination float array and capacity)

// Reconstructed structures:
struct AxisDescriptor {
    int axisId;       // +0x00 - identifies which axis (used as index into global processor table)
    int minValue;     // +0x04 - minimum raw value (for normalization)
    int range;        // +0x08 - range (max - min)
    int storageIndex; // +0x0C - index in the output buffer where the normalized value is stored
};

struct AxisDescriptorSet {
    // +0x00: possibly other data (unused here)
    AxisDescriptor* pDescriptorArray; // +0x04 - pointer to an array of AxisDescriptor (or pointer to a single descriptor used in this call)
};

struct FloatBuffer {
    float* data;      // +0x00
    int capacity;     // +0x04
};

// Extern globals
extern int g_axisProcessorTableSize;  // DAT_01205574
extern void* g_axisProcessorTableBase; // DAT_01205570 (12-byte entries, +0x04 is function pointer)

// Forward declaration of handler when storage index exceeds capacity
void FUN_00591c00(int* pParam); // likely an assert or resize

void AxisProcessor::processAxis(float rawValue, void* context, AxisDescriptorSet* axisSet, FloatBuffer* outBuffer)
{
    // Get the axis descriptor array
    AxisDescriptor* pDescriptor = axisSet->pDescriptorArray; // piVar1 = *(int**)(param_3+4)
    int axisId = pDescriptor->axisId; // iVar2 = *piVar1

    // Validate axis ID against global table size
    if ((axisId >= 0) && (axisId < g_axisProcessorTableSize))
    {
        // Each entry in the global table is 12 bytes; offset +0x04 holds the function pointer
        // pcVar3 = *(code **)(DAT_01205570 + 4 + iVar2 * 0xc)
        void (*processorFunc)(void* context, int axisId, float* pValue) = 
            *(void (**)(void*, int, float*))((char*)g_axisProcessorTableBase + 4 + axisId * 0x0C);

        if (processorFunc != nullptr)
        {
            // Allow the custom processor to modify the floating-point value (in-place)
            processorFunc(context, axisId, &rawValue);
        }
    }

    // Get storage index and capacity
    int storageIndex = pDescriptor->storageIndex; // uVar4 = piVar1[3]
    int capacity = outBuffer->capacity; // param_4[1]

    // If the storage index exceeds capacity, trigger a recovery/assert call
    if ((unsigned int)capacity <= (unsigned int)storageIndex)
    {
        int dummy = 0;
        FUN_00591c00(&dummy);
    }

    // Normalize the value: (rawValue - minValue) / range
    float normalized = (rawValue - (float)pDescriptor->minValue) / (float)pDescriptor->range;

    // Store into the output buffer at the appropriate index
    float* buffer = outBuffer->data; // *piVar5 = *param_4
    buffer[storageIndex] = normalized;
}