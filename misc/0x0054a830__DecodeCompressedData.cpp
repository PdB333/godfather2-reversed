// FUNC_NAME: DecodeCompressedData

// Address: 0x0054a830
// Role: Decompress a data buffer based on a type identifier. Supports multiple compression formats.
// Offsets in param_1 (DecompressionContext):
//   +0x08: int compressionType (FourCC-like tag)
//   +0x14: char* inputData (pointer to source data)
//   +0x18: int inputSize (size of input data)
//   +0x1c: void* outputData (pointer to decompressed data, written by this function)

int __cdecl DecodeCompressedData(DecompressionContext* ctx)
{
    char* dataPtr;
    int size;
    int result;

    int type = ctx->compressionType; // +0x08

    // Type 0x33a16735: copy input pointer directly and decompress with flag=1
    if (type != 0x33a1672c) {
        if (type == 0x33a16735) {
            ctx->outputData = ctx->inputData; // +0x1c = +0x14
            result = DecompressDirect(ctx->inputSize, 1); // 0x0054a680
            return result;
        }
        // Type 0x33a16731 falls through to the default handling
        if (type != 0x33a16731) {
            // Type 0x33a1671e: special handling with header stripping and extra cleanup
            if (type == 0x33a1671e) {
                dataPtr = ctx->inputData; // +0x14
                ctx->outputData = dataPtr;
                size = ctx->inputSize; // +0x18
                // Check for 'Hkx' prefix (3-byte signature)
                if (dataPtr[0] == 'H' && dataPtr[1] == 'k' && dataPtr[2] == 'x') {
                    // Subtract the size of the header (4th byte indicates header length)
                    size -= (unsigned char)dataPtr[3];
                }
                result = DecompressDirect(size, 0);
                FreeDecompressionContext(&ctx); // 0x004213e0
                SetDecompressedData(result, 1, ctx); // 0x0054a9a0
            }
            return result;
        }
    }

    // Default path for types 0x33a1672c and 0x33a16731
    dataPtr = ctx->inputData;
    ctx->outputData = dataPtr;
    size = ctx->inputSize;
    // Same 'Hkx' header stripping logic
    if (dataPtr[0] == 'H' && dataPtr[1] == 'k' && dataPtr[2] == 'x') {
        size -= (unsigned char)dataPtr[3];
    }
    result = DecompressDirect(size, 0);
    return result;
}