// FUNC_NAME: ResourceLoader::parseMhdvChunk
// Function address: 0x0061e810
// Parses a chunk with signature "MVhd" (0x6468564d) from a data stream.
// Reads: first two ushorts into output[0] and output[1], stream size into output[2].
// Returns success flag at offset 0x23.

char ResourceLoader::parseMhdvChunk(uint* result) {
    uint currentOffset = 0;
    int chunkTag;
    int chunkSize;
    char local_20[4]; // actually part of a 0x18-byte structure
    ushort w1;
    ushort w2;

    // Initialize success flag to false and clear output fields
    *((char*)result + 0x23) = 0;
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;

    // Check if stream pointer (at offset 0xc) is valid
    if (result[3] != 0 && isStreamValid((void*)(result + 3))) {
        int handle = openStream((void*)(result + 3), 1); // open for reading
        if (handle != 0) {
            // Loop through chunks until we find the MVhd chunk
            int bytesRead = readFromStream(handle, &chunkTag, 8);
            while (bytesRead == 8) {
                // Check for MVhd signature (little-endian: M=0x4d, V=0x56, h=0x68, d=0x64)
                if (chunkTag == 0x6468564d) {
                    // When found, and if chunk size is exactly 32 bytes
                    if (chunkSize == 0x20) {
                        // Read the 24-byte payload (contains the two ushorts and padding)
                        if (readFromStream(handle, local_20, 0x18) == 0x18) {
                            // Extract the two ushorts (first 4 bytes of payload)
                            result[0] = w1;
                            result[1] = w2;
                            // Read the stream size from the global table
                            // Table base at *(gGlobal+0x38), index = handle * 0x10
                            uint* table = *(uint**)(DAT_01223378 + 0x38);
                            result[2] = table[handle * 4 + 3]; // offset 0xc in 0x10-entry
                            // Mark success
                            *((char*)result + 0x23) = 1;
                        }
                    }
                    break; // stop searching after finding MVhd (even if size mismatched)
                }

                // Not the target chunk, advance offset and update table
                currentOffset += chunkSize;
                uint* entry = (uint*)(*(int*)(DAT_01223378 + 0x38) + handle * 0x10);
                uint streamSize = entry[3]; // +0xc
                if (streamSize < currentOffset) {
                    currentOffset = streamSize;
                }
                entry[2] = currentOffset; // +0x8

                // Read next chunk header
                bytesRead = readFromStream(handle, &chunkTag, 8);
            }
        }
        closeStream(handle); // clean up
    }
    return *((char*)result + 0x23); // return success flag
}