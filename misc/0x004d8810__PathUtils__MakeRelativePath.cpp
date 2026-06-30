// FUNC_NAME: PathUtils::makeRelativePath
// 004d8810
// Computes a relative path from 'absolutePath' to 'relativeToPath', stores result in 'relativeOut'.
// Returns 1 on success (buffer large enough), 0 on failure (path too long).
// Uses internal stack buffers for normalization.
bool __fastcall PathUtils::makeRelativePath(const char* absolutePath, char* relativeOut)
{
    uint absLen, relLen;
    uint i, j;
    uint mismatchIdx;
    uint parentDirCount;
    char* normalizedAbs; // local_10
    char* normalizedRel; // local_20
    uint normAbsLen;     // uStack_c
    uint normRelLen;     // uStack_1c
    void (*destroyAbs)(char*); // pcStack_4
    void (*destroyRel)(char*); // pcStack_14

    if (!absolutePath || !*absolutePath) {
        // If absolute path is empty, set relativeOut to something (e.g., "."?)
        normalizePath(relativeOut); // FUN_004d3d90
        return true;
    }

    // Normalize both paths (convert slashes, resolve dots?)
    normalizedRel = (char*)normalizePath(relativeOut); // FUN_004d3bc0 returns normalized string?
    normalizedAbs = (char*)normalizePath(absolutePath); // FUN_004d3bc0
    // Allocate stack strings? (FUN_004d5900 called twice with 1 – might be reference count increase)
    // The following block seems to free any previous string in the "result object" (ESI)
    // We'll skip that part as it's likely internal to the caller's object.
    // For simplicity, we assume the function works with local buffers and output is written to relativeOut.

    // Use stack-allocated buffers (the functon uses alloca? but Ghidra shows local_20 and local_10)
    // We'll simulate with char arrays on stack

    char localBufRel[256]; // local_20, size enough
    char localBufAbs[256]; // local_10
    // In the original, these are pointers to dynamically allocated or alloca'd memory.
    // For reconstruction, we'll assume they are large enough stack buffers.

    // Normalize paths and get lengths
    normRelLen = normalizeAndCopyTo(localBufRel, relativeOut); // FUN_004d3bc0? or set from param?
    normAbsLen = normalizeAndCopyTo(localBufAbs, absolutePath); // similarly
    // In actual code, FUN_004d5900(1) is called twice – maybe to mark buffers as used.

    // Compare first characters
    if (*localBufAbs != *localBufRel) {
        // Different root, cannot make relative; copy relativeOut as is? 
        normalizePath(relativeOut); // maybe reset?
        destroyRel(localBufRel);
        destroyAbs(localBufAbs);
        return true;
    }

    // Find common prefix up to the minimum length
    mismatchIdx = 3;
    if (normRelLen > 3) { // "C:\" etc? starts with 3 chars? Actually the loop starts at index 3
        while (mismatchIdx < normRelLen && 
               mismatchIdx < normAbsLen && 
               localBufRel[mismatchIdx] == localBufAbs[mismatchIdx]) {
            ++mismatchIdx;
        }
    }

    if (mismatchIdx == normAbsLen) {
        // Absolute path is a prefix of relative path (both paths same up to absLen)
        if (localBufAbs[mismatchIdx - 1] != '\\') {
            // If last char of absolute path is not backslash, go to parent count logic
            goto computeParents;
        }
        // If last char is backslash, continue to append remainder
    } else {
        // Not equal at that point – go to parent counting
        if (localBufAbs[mismatchIdx] != '\\' && localBufAbs[mismatchIdx - 1] != '\\') {
            goto computeParents;
        }
        // If it's a backslash, skip it
        ++mismatchIdx;
        goto appendRemainder;
    }

appendRemainder:
    // Append the suffix of the absolute path after the common prefix
    normalizePath(localBufRel + mismatchIdx); // copy suffix
    destroyRel(localBufRel);
    destroyAbs(localBufAbs);
    return true;

computeParents:
    // Count how many parent directories (..) we need to go up in the relative path
    parentDirCount = 0;
    i = mismatchIdx + 1; // start from char after mismatch
    while (i < normAbsLen) {
        if (localBufAbs[i] == '\\') {
            ++parentDirCount;
            ++i; // skip backslash as well? The loop increments by extra 1?
        }
        ++i; // but actual code: uVar5 = uVar2 + 1; then if backslash, uVar5 = uVar2 + 2; 
        // So we need to simulate that properly.
    }
    // Actually the loop increments twice when backslash? Let's reanalyze...
    // The decompiled code: 
    // uVar3 = uVar4 + 1; uVar5 = uVar4;
    // while (uVar2 = uVar5, uVar1 = uVar3, uVar1 < uStack_c) {
    //   uVar5 = uVar2 + 1;
    //   uVar3 = uVar1 + 1;
    //   if (local_10[uVar5] == '\\') {
    //     uVar5 = uVar2 + 2;
    //     uVar3 = uVar1 + 2;
    //     if (uVar5 < uStack_c) {
    //       iVar6 = iVar6 + 1;
    //     }
    //   }
    // }
    // This is tricky: It iterates through absolute path from mismatchIdx+1, increments both indices each iteration, but if a backslash is found, it increments an extra step (skipping the backslash itself?) and counts a parent directory.
    // We'll approximate: For each directory component starting from mismatchIdx+1, count it. The backslash separates components.
    // Simplify: Count the number of backslashes after mismatchIdx+1 until the end? Not exactly.
    // Since this is reconstruction, we'll write a clear version.

    uint pos = mismatchIdx + 1;
    while (pos < normAbsLen) {
        if (localBufAbs[pos] == '\\') {
            parentDirCount++;
            pos++; // skip the backslash? Actually the loop increments pos by 2 when backslash, but also increments index for comparison? Hard.
            // We'll just count backslashes and assume pos increments correctly.
        }
        pos++;
    }

    // Find the last backslash in relative path before mismatchIdx (to get the base directory)
    uint lastRelBackslash = mismatchIdx;
    while (lastRelBackslash > 0 && localBufRel[lastRelBackslash - 1] != '\\') {
        --lastRelBackslash;
    }

    // Check total length: parentDirCount * 3 + (normRelLen - lastRelBackslash) < 0x201
    uint totalLen = parentDirCount * 3 + (normRelLen - lastRelBackslash);
    if (totalLen >= 0x201) {
        destroyRel(localBufRel);
        destroyAbs(localBufAbs);
        return false; // buffer too small
    }

    // Build the relative path in a temp buffer, then copy to relativeOut
    char outputBuffer[0x200];
    uint outPos = 0;
    for (uint k = 0; k < parentDirCount; ++k) {
        outputBuffer[outPos++] = '.';
        outputBuffer[outPos++] = '.';
        outputBuffer[outPos++] = '\\';
    }
    // Append the suffix of relative path after that backslash
    // Using string copy
    for (uint k = lastRelBackslash; k < normRelLen; ++k) {
        outputBuffer[outPos++] = localBufRel[k];
    }
    outputBuffer[outPos] = '\0';
    // Copy to relativeOut
    strcpy(relativeOut, outputBuffer); // FUN_004d4300? Actually FUN_004d4300 may be memcpy or strcpy

    destroyRel(localBufRel);
    destroyAbs(localBufAbs);
    return true;
}

// Helper functions (guesses):
static uint normalizeAndCopyTo(char* dest, const char* src) {
    // Normalize slashes and copy, return length
    // ... placeholder
    uint len = 0;
    while (*src) {
        if (*src == '/') {
            *dest++ = '\\';
        } else {
            *dest++ = *src;
        }
        src++;
        len++;
    }
    *dest = '\0';
    return len;
}

static void normalizePath(char* path) {
    // Convert forward slashes to backslashes? Or remove trailing backslash?
}

static void destroyAbs(char* buf) { /* free or nothing */ }
static void destroyRel(char* buf) { /* free or nothing */ }

// Note: This reconstruction is simplified. The original code has many intricacies (dot handling, etc.).
// The actual function likely resides in a path utility library and handles edge cases differently.// FUNC_NAME: PathUtils::computeRelativePath
// 004d8810
// Computes a relative path from 'absolutePath' to 'relativeToBase' and stores result in 'outRelative'.
// The function assumes both paths are absolute (e.g., "C:\...").
// Returns 1 on success (buffer large enough), 0 if result exceeds 0x200 characters.
// Uses normalized paths (backslashes only) internally.

bool __fastcall PathUtils::computeRelativePath(const char* absolutePath, char* outRelative)
{
    // Internal normalized strings (dynamically allocated or stack)
    char* normAbs;   // local_10
    char* normBase;  // local_20
    uint normAbsLen; // uStack_c
    uint normBaseLen;// uStack_1c

    // Destructor function pointers for the normalized strings (e.g., free or delete[])
    void (*destroyNormAbs)(char*);   // pcStack_4
    void (*destroyNormBase)(char*);  // pcStack_14

    // Check if input is empty
    if (!absolutePath || !*absolutePath) {
        // If absolute path is empty, set out to something (e.g., ".")
        pathNormalize(outRelative);                  // FUN_004d3d90
        return 1;
    }

    // Normalize both paths (convert forward slashes to backslashes, resolve dot components)
    normBase = pathNormalizeCopy(outRelative);       // FUN_004d3bc0 (returns new string)
    normAbs  = pathNormalizeCopy(absolutePath);      // FUN_004d3bc0

    // Reference count? (stub functions)
    pathRefCountInc(1);                              // FUN_004d5900
    pathRefCountInc(1);                              // FUN_004d5900

    // Free any previous result if stored (likely in caller's ESI object)
    // ... omitted for clarity

    // Compare first characters (drive letters etc.)
    if (*normAbs != *normBase) {
        // Different roots – cannot make relative; just copy base path as fallback
        pathNormalize(outRelative);
        destroyNormBase(normBase);
        destroyNormAbs(normAbs);
        return 1;
    }

    // Find common prefix (skip first 3 chars for "C:\" pattern)
    uint mismatchIdx = 3;
    if (normBaseLen > 3) {
        while (mismatchIdx < normBaseLen && 
               mismatchIdx < normAbsLen && 
               normBase[mismatchIdx] == normAbs[mismatchIdx])
        {
            mismatchIdx++;
        }
    }

    if (mismatchIdx == normAbsLen) {
        // Absolute path is a prefix of base path
        if (normAbs[mismatchIdx - 1] != '\\') {
            goto computeParents;
        }
        // If it ends with backslash, just append the remainder of base path
    } else {
        if (normAbs[mismatchIdx] != '\\' && normAbs[mismatchIdx - 1] != '\\') {
            goto computeParents;
        }
        // Found a common directory boundary, skip the backslash
        mismatchIdx++;
        goto appendRemainder;
    }

appendRemainder:
    // Copy the suffix of base path after the common prefix
    pathNormalize(normBase + mismatchIdx);           // FUN_004d3d90 (modifies normBase)
    destroyNormBase(normBase);
    destroyNormAbs(normAbs);
    return 1;

computeParents:
    // Count how many "..\" we need to go up from base to match the common ancestor
    uint parentCount = 0;
    uint pos = mismatchIdx + 1;
    while (pos < normAbsLen) {
        if (normAbs[pos] == '\\') {
            parentCount++;
            pos++; // Skip the backslash (accounts for two increments in original)
        }
        pos++;
    }

    // Find last backslash in base path before the mismatch point
    uint lastBaseSep = mismatchIdx;
    while (lastBaseSep > 0 && normBase[lastBaseSep - 1] != '\\') {
        lastBaseSep--;
    }

    // Calculate total length required: (3 chars per "..\") + remainder of base path after last separator
    uint totalLen = parentCount * 3 + (normBaseLen - lastBaseSep);
    if (totalLen >= 0x201) {
        destroyNormBase(normBase);
        destroyNormAbs(normAbs);
        return 0; // Too long for target buffer
    }

    // Allocate temporary output buffer (size at least totalLen+1)
    char* tempBuf = (char*)pathAlloc(parentCount * 3 + (normBaseLen - lastBaseSep) + 1); // FUN_004d3fe0
    // Write the "..\" sequence
    for (uint i = 0; i < parentCount; i++) {
        pathWriteChar(tempBuf, '.');   // FUN_004d44b0 (0x2e)
        pathWriteChar(tempBuf, '.');   // FUN_004d44b0 (0x2e)
        pathWriteChar(tempBuf, '\\');  // FUN_004d44b0 (0x5c)
    }
    // Append the remainder of base path (after the separator)
    pathAppendString(tempBuf, normBase + lastBaseSep); // FUN_004d4300 (strcpy-like)

    // Copy result to output (the original function appears to write directly to outRelative via preceding calls)
    // For reconstruction, we assume the result is stored in outRelative (or through the same pathNormalize call)
    // The original uses pathNormalize(outRelative) at the end? Actually it calls pathNormalize with the constructed result.
    // We'll simulate by copying.
    strcpy(outRelative, tempBuf); // Or use the pathNormalize call

    destroyNormBase(normBase);
    destroyNormAbs(normAbs);
    return 1;
}

// Placeholder helper function signatures (to be replaced with actual names based on known utilities)
static char* pathNormalizeCopy(const char* src); // normalize and return new string
static void pathNormalize(char* str);            // normalize in place
static void pathRefCountInc(int increment);      // internal reference counting
static void pathWriteChar(char*& buf, char ch);  // write char and advance pointer
static void pathAppendString(char*& dst, const char* src); // append string
static void* pathAlloc(size_t size);             // allocate buffer
// ... destructor functions assumed to be freed appropriately

// Note: The actual implementation uses stack-allocated strings (local_20 and local_10) via alloca or similar.
// This reconstruction uses dynamic allocation for clarity, but the original likely uses alloca for performance.
// The function pointer calls (pcStack_14, pcStack_4) are replaced by explicit destructors in this version.