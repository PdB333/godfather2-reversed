// FUNC_NAME: ParameterSet::hasKey

// Function at 0x00714f30 - Checks if a named parameter exists in the parameter set.
// param_1 (this) : Pointer to ParameterSet object (vtable at +0x00)
// param_2 (key)  : Optional key string; if null, uses default key from getDefaultKey()
// Returns true if key matches the object's parameter (via compareKey).

extern char* g_defaultKey; // _DAT_00d5c458

bool ParameterSet::hasKey(const char* key)
{
    char defaultKeyBuffer[8];   // local_18
    char* effectiveKey;         // reused param_2
    char compareResultBuffer[4]; // auStack_10
    char identifierBuffer[12];  // local_c

    if (key == (const char*)0x0) {
        getDefaultKey(defaultKeyBuffer); // FUN_00714b80
        effectiveKey = defaultKeyBuffer;
    } else {
        effectiveKey = (char*)key;
    }

    // Virtual call at vtable+0x48 - retrieve the object's identifier into identifierBuffer
    (*(this->vtable[0x48]))(this, identifierBuffer); // (**(code **)(*this + 0x48))(local_c)

    // Compare effectiveKey against the object's identifier using a global key
    char cmpResult = compareKey(effectiveKey, compareResultBuffer, g_defaultKey, this); // FUN_00714550

    return (cmpResult == '\0');
}