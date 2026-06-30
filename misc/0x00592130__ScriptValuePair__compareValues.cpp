// FUNC_NAME: ScriptValuePair::compareValues
// 0x00592130: Compares two float values encoded as either inline floats or references to a global table.
// Used for sorting or condition evaluation in the game's script system.

int __thiscall ScriptValuePair::compareValues(void *this, float *pOut)
{
    char *str1;
    char *str2;
    int index;
    float value1, value2;
    typedef void (*ValueGetter)(int context, int index, float *outVal);

    // --- Resolve first value ---
    str1 = **(char***)((int)this + 8); // +0x8: pointer to ValuePair struct (two char*)
    if (str1[0] == '\n') {
        // Reference to a global table entry
        index = *(short *)(str1 + 2);
        if (index >= 0 && index < g_valueTableSize) {
            ValueGetter getter = (ValueGetter)(*(int*)(g_valueTableBase + 4 + index * 0xC));
            if (getter) {
                getter((int)*pOut, index, &value1);
            }
        }
    } else {
        // Inline float
        value1 = *(float *)(str1 + 4);
    }

    // --- Resolve second value ---
    str2 = *(char**)(*(int*)((int)this + 8) + 4); // +0x4 within ValuePair
    if (str2[0] == '\n') {
        index = *(short *)(str2 + 2);
        if (index >= 0 && index < g_valueTableSize) {
            ValueGetter getter = (ValueGetter)(*(int*)(g_valueTableBase + 4 + index * 0xC));
            if (getter) {
                getter((int)*pOut, index, &value2);
            }
        }
    } else {
        value2 = *(float *)(str2 + 4);
    }

    // --- Compare ---
    if (value1 > value2) {
        pOut[3] = (float)this; // Store this pointer in result (likely for debugging or further processing)
        return 1;
    }
    return 0;
}