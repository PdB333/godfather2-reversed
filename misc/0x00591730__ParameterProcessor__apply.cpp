// FUNC_NAME: ParameterProcessor::apply
struct ParamDef {
    int m_type;          // +0x00: index into transform function table
    int m_min;           // +0x04: minimum of original range
    int m_range;         // +0x08: range (max - min)
    int m_outputIndex;   // +0x0C: index into output buffer
};

struct OutputBuffer {
    float* data;         // +0x00
    int capacity;        // +0x04
};

// Global constants
extern int g_maxParamTypeCount;  // DAT_01205574
extern void* g_paramTransformTable; // DAT_01205570, table of function pointers (stride 0xC)
extern float g_maxOutputValue;    // DAT_00e2b1a4

// Debug assertion helper
void debugAssertError(); // FUN_00591c00

void __thiscall ParameterProcessor::apply(float inputValue, uint userData, OutputBuffer* output) {
    // Retrieve the current parameter definition (offset 0x04 from 'this')
    ParamDef* paramDef = *(ParamDef**)((char*)this + 4);
    int paramType = paramDef->m_type;
    float transformedValue = inputValue;

    // Apply transformation callback if valid type index
    if (paramType >= 0 && paramType < g_maxParamTypeCount) {
        // Table entries: each 12 bytes, first 4 bytes are function pointer
        TransformFunc func = *(TransformFunc*)((char*)g_paramTransformTable + 4 + paramType * 12);
        if (func != nullptr) {
            func(userData, paramType, &transformedValue);
        }
    }

    // Compute normalized value into output buffer at the specified index
    int idx = paramDef->m_outputIndex;
    if (idx >= output->capacity) {
        debugAssertError();
    }
    float normalized = (transformedValue - (float)paramDef->m_min) / (float)paramDef->m_range;
    output->data[idx] = normalized;

    // Clamp negative values to zero (excluding zero itself)
    if (output->data[idx] < 0.0f && output->data[idx] != 0.0f) {
        if (idx >= output->capacity) {
            debugAssertError();
        }
        output->data[idx] = 0.0f;
    }

    // Clamp to global maximum value
    if (idx >= output->capacity) {
        debugAssertError();
    }
    if (g_maxOutputValue < output->data[idx]) {
        output->data[idx] = g_maxOutputValue;
    }
}