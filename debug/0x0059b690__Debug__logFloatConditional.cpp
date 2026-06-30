// FUNC_NAME: Debug::logFloatConditional
// Address: 0x0059b690
// Role: Logs a float value to debug output, with conditional repetition based on a flag.

class Debug {
public:
    byte flags; // +0x00: bit 0 controls conditional logging
    void __thiscall logFloatConditional(float value);
};

// External helper: converts/processes a float for logging (likely writes to debug stream)
long double __cdecl writeFloatToLog(float value);

void __thiscall Debug::logFloatConditional(float value) {
    long double temp = writeFloatToLog(value);
    if ((flags & 1) != 0) {
        temp = writeFloatToLog((float)temp);
        writeFloatToLog((float)temp);
    }
}