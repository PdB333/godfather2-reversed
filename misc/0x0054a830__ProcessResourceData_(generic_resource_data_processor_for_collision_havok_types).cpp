// FUNC_NAME: ProcessResourceData (generic resource data processor for collision/havok types)
// Address: 0x0054a830
// Role: Processes a data buffer based on a type identifier (offset +0x8).
//       Handles Havok collision data ("Hkx" prefix) and non-havok types.
//       Calls decompressData, freeResourceBuffer, and registerProcessedData as needed.
// Known callees: FUN_0054a680 (decompressData), FUN_004213e0 (freeResourceBuffer), FUN_0054a9a0 (registerProcessedData)

// Constants for type identifiers (likely file type hashes or four-char codes)
enum ResourceType : int {
    kResourceType_HavokV1        = 0x33a1672c, // Havok collision, no extra processing
    kResourceType_UnknownV2      = 0x33a16735, // Some other compressed type (no Havok header)
    kResourceType_HavokV2        = 0x33a16731, // Havok collision, same logic as V1
    kResourceType_FreeOnProcess  = 0x33a1671e  // After decompression, frees buffer and registers
};

// Forward declarations of helper functions (inferred signatures)
// int decompressData(int inputSize, int isCompressed);
// void freeResourceBuffer(void** bufferPtr);
// void registerProcessedData(int result, int flag, void* buffer);

int ProcessResourceData(void* buffer) {
    // Buffer layout (offsets in bytes):
    // +0x00: (unknown, possibly vtable or other)
    // +0x08: resourceType (int)
    // +0x14: dataPointer (char*) – points to the actual resource data
    // +0x18: dataSize (int) – size of the data pointed by dataPointer
    // +0x1c: outputPointer (char*) – set to dataPointer (alias)
    int resourceType = *(int*)((char*)buffer + 0x8);
    char* dataPointer = *(char**)((char*)buffer + 0x14);
    int dataSize = *(int*)((char*)buffer + 0x18);
    int result = 0;

    // Cases for resourceType handling
    if (resourceType == kResourceType_HavokV1 || resourceType == kResourceType_HavokV2) {
        // For Havok types: alias output to same as input
        *(char**)((char*)buffer + 0x1c) = dataPointer;
        // If data starts with "Hkx" header (magic: 'H','k','x'), subtract the version byte at offset 3
        if (dataPointer[0] == 'H' && dataPointer[1] == 'k' && dataPointer[2] == 'x') {
            dataSize -= (unsigned char)dataPointer[3];
        }
        result = decompressData(dataSize, 0); // 0 = not compressed? Or no header?
    }
    else if (resourceType == kResourceType_UnknownV2) {
        // Direct copy of pointer, then decompress with flag 1
        *(char**)((char*)buffer + 0x1c) = dataPointer;
        result = decompressData(dataSize, 1); // 1 = likely compressed
    }
    else if (resourceType == kResourceType_FreeOnProcess) {
        // Similar to Havok handling, but followed by freeing the buffer and registering
        *(char**)((char*)buffer + 0x1c) = dataPointer;
        if (dataPointer[0] == 'H' && dataPointer[1] == 'k' && dataPointer[2] == 'x') {
            dataSize -= (unsigned char)dataPointer[3];
        }
        result = decompressData(dataSize, 0);
        freeResourceBuffer(&buffer);   // frees the original buffer (sets pointer to null)
        registerProcessedData(result, 1, buffer);
    }
    // else: other types ignored (do nothing)
    return result;
}