// FUNC_NAME: VersionString::compare

// Function at 0x00964d50
// Compares an input version string with an internal version string stored at this+0x1f5.
// Versions are dot-separated numeric tokens (e.g., "1.2.3").
// Returns: 0 equal, 1 input < internal, 2 input > internal,
//          3 input empty or shorter, 4 internal empty or shorter, 5 too many tokens (>3)

int __thiscall VersionString::compare(VersionString* this, const char* inputVersion) {
    // Internal version string buffer at offset +0x1f5
    byte* internalVersion = reinterpret_cast<byte*>(reinterpret_cast<int>(this) + 0x1f5);

    // Zero out both strings (likely to reset or clear)
    FUN_004d3bc0(const_cast<char*>(inputVersion));
    FUN_004d3bc0(internalVersion);

    // Tokenizer structures for both versions
    struct Tokenizer {
        char* token;        // +0x00
        int length;         // +0x04
        int unknown1;       // +0x08
        void (*destructor)(void*); // +0x0C
    } tokenizerInput, tokenizerInternal;

    // Initialize tokenizers and check for first token
    if (!FUN_00962cc0(&tokenizerInput)) {
        // Input version has no tokens
        (*tokenizerInternal.destructor)(tokenizerInternal.token); // cleanup internal
        (*tokenizerInput.destructor)(tokenizerInput.token);       // cleanup input
        return 3;
    }

    if (!FUN_00962cc0(&tokenizerInternal)) {
        // Internal version has no tokens
        (*tokenizerInput.destructor)(tokenizerInput.token);
        (*tokenizerInternal.destructor)(tokenizerInternal.token);
        return 4;
    }

    int partIndex = 0;
    while (true) {
        char* tokenInput = nullptr;
        char* tokenInternal = nullptr;

        if (partIndex == 3) {
            // Reset tokenizers for fourth part (shouldn't happen normally)
            FUN_004d3e20(&tokenizerInternal);
            FUN_004d3e20(&tokenizerInput);
        } else {
            // Extract next tokens using '.' as delimiter (DAT_00e40868)
            FUN_004d5210(&DAT_00e40868, &tokenInput, &tokenizerInput);
            FUN_004d5210(&DAT_00e40868, &tokenInternal, &tokenizerInternal);
        }

        if (tokenInput == nullptr) {
            // Input version has no more tokens
            break;
        }

        if (tokenInternal == nullptr) {
            // Internal version has no more tokens
            if (tokenInternal != nullptr) {
                (*tokenizerInternal.destructor)(tokenInternal);
            }
            if (tokenInput != nullptr) {
                (*tokenizerInput.destructor)(tokenInput);
            }
            if (tokenizerInternal.token != nullptr) {
                (*tokenizerInternal.destructor)(tokenizerInternal.token);
            }
            if (tokenizerInput.token != nullptr) {
                (*tokenizerInput.destructor)(tokenizerInput.token);
                return 4;
            } else {
                return 4;
            }
        }

        // Compare numeric values of tokens
        long valInput = _atol(tokenInput ? tokenInput : "");
        long valInternal = _atol(tokenInternal ? tokenInternal : "");

        if (valInput < valInternal) {
            // Input version is less
            if (tokenInternal != nullptr)
                (*tokenizerInternal.destructor)(tokenInternal);
            if (tokenInput != nullptr)
                (*tokenizerInput.destructor)(tokenInput);
            if (tokenizerInternal.token != nullptr)
                (*tokenizerInternal.destructor)(tokenizerInternal.token);
            if (tokenizerInput.token != nullptr)
                (*tokenizerInput.destructor)(tokenizerInput.token);
            return 1;
        } else if (valInput > valInternal) {
            // Input version is greater
            if (tokenInternal != nullptr)
                (*tokenizerInternal.destructor)(tokenInternal);
            if (tokenInput != nullptr)
                (*tokenizerInput.destructor)(tokenInput);
            if (tokenizerInternal.token != nullptr)
                (*tokenizerInternal.destructor)(tokenizerInternal.token);
            if (tokenizerInput.token != nullptr)
                (*tokenizerInput.destructor)(tokenizerInput.token);
            return 2;
        }

        // Tokens are equal, clean up and continue
        if (tokenInternal != nullptr)
            (*tokenizerInternal.destructor)(tokenInternal);
        if (tokenInput != nullptr)
            (*tokenizerInput.destructor)(tokenInput);

        partIndex++;
        if (partIndex > 3) {
            // Exceeded maximum expected parts (3)
            if (tokenizerInternal.token != nullptr)
                (*tokenizerInternal.destructor)(tokenizerInternal.token);
            if (tokenizerInput.token != nullptr)
                (*tokenizerInput.destructor)(tokenizerInput.token);
            return 5;
        }
    }

    // Input version ran out of tokens
    if (tokenInternal == nullptr) {
        // Both ran out simultaneously? Or internal also empty?
        if (tokenInternal != nullptr)
            (*tokenizerInternal.destructor)(tokenInternal);
        if (tokenInput != nullptr)
            (*tokenizerInput.destructor)(tokenInput);
        if (tokenizerInternal.token != nullptr)
            (*tokenizerInternal.destructor)(tokenizerInternal.token);
        if (tokenizerInput.token != nullptr)
            (*tokenizerInput.destructor)(tokenizerInput.token);
        return 3;
    } else {
        // Internal still has tokens, input is a prefix
        if (tokenInternal != nullptr)
            (*tokenizerInternal.destructor)(tokenInternal);
        if (tokenInput != nullptr)
            (*tokenizerInput.destructor)(tokenInput);
        if (tokenizerInternal.token != nullptr)
            (*tokenizerInternal.destructor)(tokenizerInternal.token);
        if (tokenizerInput.token == nullptr) {
            return 4;
        }
        (*tokenizerInput.destructor)(tokenizerInput.token);
        return 4;
    }
}