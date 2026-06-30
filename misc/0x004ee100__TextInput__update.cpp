// FUNC_NAME: TextInput::update
// Function address: 0x004ee100
// This function appears to handle text cursor blinking and auto-scroll/truncation for a UI text input field.
// Offsets documented in comments.
// Uses globals: DAT_00e2b05c (float, possibly current time), DAT_01205508 (function pointer), DAT_012234c4 (data table).

void __fastcall TextInput::update(TextInput* this) {
    int* refCount;
    float styleFloat;
    char c;
    uint scaledLimit;
    int stylePtr;
    char* str;
    uint newLimit;

    // Increment reference count on some object (shared? string?) pointed by this->unk04
    // this+0x04 is likely a pointer to a reference-counted buffer or string object.
    // Dereference: *(this+0x04) -> some object; then object+0x20 -> another object whose ref count is incremented.
    int* obj = *(int**)(this + 4);
    if (obj) {
        int* refObj = (int*)(obj[8]);  // obj+0x20? Actually offset 0x20/4 = 8. So obj[8] is pointer to ref counter.
        if (refObj) {
            (*refObj)++;   // +4 offset? Actually refObj is already pointer to int, so increment.
        }
    }

    // Get a style/state pointer from another function call
    stylePtr = FUN_004ee9f0();  // unknown side effect, returns a pointer (maybe to a text style object?)
    str = nullptr;

    // Determine the string to process: either from style object or from global function
    if (stylePtr) {
        // Check if a style flag (bit 0x8000) is NOT set in this->unknown24->+0x2c
        uint16_t styleFlags = *(uint16_t*)(*(int*)(this + 0x24) + 0x2c);
        if ((styleFlags & 0x8000) == 0) {
            str = *(char**)(stylePtr + 0x20);  // string from style object offset 0x20
        }
    }
    if (!str) {
        // Fallback: call global function pointer from DAT_012234c4 + 0x30
        str = (char*)((* (code**)(DAT_012234c4 + 0x30))())();
    }

    // Compare global time (DAT_00e2b05c) with a style float (this->unknown24->+0x58)
    float time = DAT_00e2b05c;
    float styleTime = *(float*)(*(int*)(this + 0x24) + 0x58);
    if (str && time <= styleTime) {
        // Check string length against this->limit (offset 0x40)
        int len = strlen(str);
        if (len < *(int*)(this + 0x40)) {
            *(int*)(this + 0x40) = -1;  // reset limit to -1
        }
    }

    // Handle cursor blinking / auto-scroll based on flag at offset 0x5c
    if (*(char*)(this + 0x5c) && str && time <= styleTime) {
        // Compute a scaled limit: this->speed (float at +0x34) * styleTime
        float speed = *(float*)(this + 0x34);
        scaledLimit = (uint)(speed * styleTime);

        if (DAT_01205508) {
            // Get string length again
            int len2 = strlen(str);
            if ((uint)(len2) < scaledLimit) {
                *(char*)(this + 0x5c) = 0;  // turn off flag
            } else {
                uint delta = scaledLimit;
                if (*(int*)(this + 0x40) >= 0) {
                    delta = scaledLimit - *(int*)(this + 0x40);
                }
                if ((int)delta > 0) {
                    (*DAT_01205508)();  // call some handler (e.g., recalculate scroll offset)
                }
            }
        }
        *(uint*)(this + 0x40) = scaledLimit;  // update limit
    }

    // Extra strlen (just to advance pointer? not used)
    if (str) {
        while (*str) str++;
    }

    // Call base class update or cleanup
    FUN_004ed830(this);

    // Reset some internal state
    *(int*)(this + 0x30) = 0;
    return;
}