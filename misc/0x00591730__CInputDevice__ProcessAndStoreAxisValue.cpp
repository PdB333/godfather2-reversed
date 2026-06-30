// FUNC_NAME: CInputDevice::ProcessAndStoreAxisValue
// Address: 0x00591730
// Role: Normalizes raw axis input using a type-specific modifier callback, then stores the result into an output buffer with clamping.

typedef void (*AxisModifierCallback)(void* context, int axisIndex, float* value);

// Each entry in the global axis modifier table (DAT_01205570) has a function pointer at offset 4.
// The table is indexed by axis type, each entry is 12 bytes.
struct AxisModifierEntry {
    char unknown0[4];         // +0x00
    AxisModifierCallback callback; // +0x04
    char unknown8[4];         // +0x08
};

extern AxisModifierEntry* g_axisModifierTable;   // DAT_01205570
extern int g_numAxisTypes;                       // DAT_01205574
extern float g_maxNormalizedValue;               // DAT_00e2b1a4

// Assert failure function (FUN_00591c00)
void AssertFailure(void* condition);

struct AxisRecordInfo {
    int typeIndex;   // +0x00 – axis type used to index into modifier table
    int subtract;    // +0x04 – subtrahend in normalization
    int divisor;     // +0x08 – divisor in normalization (should be > 0)
    int writeIndex;  // +0x0C – index into output buffer where result is stored
};

struct OutputBuffer {
    float* buffer;  // +0x00 – pointer to array of normalized floats
    int capacity;   // +0x04 – number of elements the buffer can hold
};

void __thiscall CInputDevice::ProcessAndStoreAxisValue(
    float rawValue,
    void* modifierContext,
    AxisRecordInfo* recordInfo,
    OutputBuffer* output)
{
    float normalizedValue = rawValue;

    // Apply modifier callback if axis type is valid
    if (recordInfo->typeIndex >= 0 && recordInfo->typeIndex < g_numAxisTypes)
    {
        AxisModifierEntry* entry = &g_axisModifierTable[recordInfo->typeIndex];
        if (entry->callback != nullptr)
        {
            entry->callback(modifierContext, recordInfo->typeIndex, &normalizedValue);
        }
    }

    // Bounds check before writing
    if ((unsigned int)output->capacity <= (unsigned int)recordInfo->writeIndex)
    {
        AssertFailure(nullptr);
    }

    // Normalize: (value - subtract) / divisor
    output->buffer[recordInfo->writeIndex] =
        (normalizedValue - (float)recordInfo->subtract) / (float)recordInfo->divisor;

    // Clamp negative values very close to zero to exactly 0
    if ((unsigned int)output->capacity <= (unsigned int)recordInfo->writeIndex)
    {
        AssertFailure(nullptr);
    }
    float* stored = &output->buffer[recordInfo->writeIndex];
    if (*stored <= 0.0f && *stored != 0.0f)
    {
        if ((unsigned int)output->capacity <= (unsigned int)recordInfo->writeIndex)
        {
            AssertFailure(nullptr);
        }
        output->buffer[recordInfo->writeIndex] = 0.0f;
    }

    // Clamp to global maximum
    if ((unsigned int)output->capacity <= (unsigned int)recordInfo->writeIndex)
    {
        AssertFailure(nullptr);
    }
    if (g_maxNormalizedValue < output->buffer[recordInfo->writeIndex])
    {
        if ((unsigned int)output->capacity <= (unsigned int)recordInfo->writeIndex)
        {
            AssertFailure(nullptr);
        }
        output->buffer[recordInfo->writeIndex] = g_maxNormalizedValue;
    }
}