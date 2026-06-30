// FUNC_NAME: TypewriterText::update

void __fastcall TypewriterText::update(TypewriterText* this) {
    // Increment reference count on some resource (e.g., string buffer?)
    int* resource = *(int**)(*(int*)(this + 4) + 0x20); // +0x4: pointer to resource manager; +0x20: pointer to resource
    if (resource) {
        int* refCount = resource + 1; // +0x4: reference count
        (*refCount)++;
    }

    // Try to get current text string from either a global provider or fallback
    char* text = nullptr;
    int* provider = FUN_004ee9f0();  // Returns current text provider (e.g., subtitle system)
    if (provider &&
        ((*(ushort*)(*(int*)(this + 0x24) + 0x2c) & 0x8000) == 0) && // Check some flag (bit 15) on time source?
        (text = *(char**)(provider + 0x20), text != nullptr)) {
        // Got text from provider
    } else {
        // Fallback: call a virtual function from a global table
        text = (*(char* (__stdcall**)(void))(DAT_012234c4 + 0x30))();  // Some function returning char*
        if (text) {
            // text obtained
        } else {
            text = nullptr;
        }
    }

    // Check time condition: only process if current time >= a threshold
    float currentTime = *(float*)(*(int*)(this + 0x24) + 0x58); // Time source (e.g., game time)
    if (text && currentTime >= DAT_00e2b05c) {
        int textLength = strlen(text);
        int cursor = *(int*)(this + 0x40); // Current display position (number of characters shown)

        // If text length is less than cursor, reset cursor (text done?)
        if (textLength < cursor) {
            *(int*)(this + 0x40) = -1;
        }
    }

    // Typewriter effect logic
    if (*(char*)(this + 0x5c) && text && currentTime > DAT_00e2b05c) {
        float speed = *(float*)(this + 0x34); // Characters per second multiplier
        unsigned int charCount = (unsigned int)(speed * currentTime); // How many chars should be visible now
        unsigned int textLen = strlen(text);

        if (textLen < charCount) {
            // All text displayed – mark as inactive
            *(char*)(this + 0x5c) = 0;
        } else {
            // Possibly play sound for new characters since last update
            if (*(int*)(this + 0x40) >= 0) {
                charCount -= *(int*)(this + 0x40); // New characters since last frame
            }
            if ((int)charCount > 0) {
                if (DAT_01205508) {
                    DAT_01205508(); // Call typewriter sound / effect callback
                }
            }
        }
        *(unsigned int*)(this + 0x40) = (unsigned int)(speed * currentTime);
    }

    // Ensure the string pointer is not dangling (just touch it for no reason?)
    if (text) {
        strlen(text); // Compute length and ignore (maybe for safety)
    }

    // Call base class update or reset state
    FUN_004ed830(this);
    *(int*)(this + 0x30) = 0; // Reset some internal flag/timer
    return;
}