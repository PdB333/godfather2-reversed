// FUNC_NAME: AudioDecoder::decompressBlock
// Address: 0x0057b8b0
// Role: Decodes a block of compressed audio data using Huffman-like decoding
// The function reads a bitmask to determine which elements are present,
// then decodes variable-length codes for each element, and finally
// decodes 8 final values (likely PCM samples or coefficients).

#include <cstdint>

// External tables for Huffman decoding (from data sections)
extern int32_t g_huffmanTable1[16]; // DAT_00e2c758
extern int32_t g_huffmanTable2[16]; // DAT_00e2c720

// External function: decodes a value from the stream (float cast to int)
// First param: pointer to stream pointer (updated after read)
// Second param: float scale factor (passed as float)
// Third param: integer scale (passed as int)
extern float decodeValue(uint8_t** pStream, float scaleFactor, int32_t scaleInt);

// Config structure at this[2] (offset 0x08)
struct DecoderConfig {
    int32_t flags;          // +0x04 (value & 0xff) < 10 check
    int32_t offset20;       // +0x20
    uint8_t* stream1;       // +0x24 (used if flags < 10)
    int32_t offset28;       // +0x28
    uint8_t* stream2;       // +0x2c (used if flags >= 10)
};

// Output structure at *this (offset 0x00) - 8 int32 values
struct DecodedOutput {
    int32_t values[8];
};

uint32_t AudioDecoder::decompressBlock(uint8_t* pStreamConfig, int32_t numElements, int32_t outputScale)
{
    // Equivalent to in_EAX:
    // this[0] = output buffer (DecodedOutput)
    // this[2] = pStreamConfig (DecoderConfig*)
    // this[3] = bitfield pointer (uint32_t*)
    // this[4] = outputScale (int32_t)
    // this[5] = numElements (int32_t)

    DecodedOutput* pOutput = reinterpret_cast<DecodedOutput*>(this[0]);
    DecoderConfig* pConfig = reinterpret_cast<DecoderConfig*>(this[2]);
    uint32_t* pBitfield = reinterpret_cast<uint32_t*>(this[3]);
    int32_t scale = static_cast<int32_t>(this[4]);
    int32_t count = static_cast<int32_t>(this[5]);

    // Check if the bit for the first element is set? Actually iVar2 is count,
    // but condition uses *(uint *)(iVar1 + (iVar2>>5)*4) & (1 << (iVar2&0x1f))
    // So it checks the bit at index equal to count? That is odd. Possibly a
    // global flag to see if the block is present.
    uint32_t bitmaskWord = pBitfield[count >> 5];
    if (!(bitmaskWord & (1 << (count & 0x1f))))
    {
        // Block not present, zero output
        pOutput->values[0] = 0;
        pOutput->values[1] = 0;
        pOutput->values[2] = 0;
        pOutput->values[3] = 0;
        pOutput->values[4] = 0;
        pOutput->values[5] = 0;
        pOutput->values[6] = 0;
        pOutput->values[7] = 0;
        return 1;
    }

    // Determine which stream pointer to use based on config flag (byte at offset 4)
    uint8_t* pStream;
    int32_t streamOffset;
    if ((pConfig->flags & 0xff) < 10)
    {
        pStream = pConfig->stream1;
        streamOffset = pConfig->offset20;
    }
    else
    {
        pStream = pConfig->stream2;
        streamOffset = pConfig->offset28;
    }

    // The streamOffset appears to be a count or flag used for loop direction.
    // If negative, loop forward; else loop backward? Actually the code has two identical loops.
    // We'll unify with a single loop.

    // Decode elements based on bitmask
    for (int32_t i = 0; i < count; i++)
    {
        // Check if element i is present
        if (pBitfield[i >> 5] & (1 << (i & 0x1f)))
        {
            // Decode multiple values from stream using Huffman-like scheme
            // This pattern repeats for several symbols (depth 7-8) to decode
            // a set of coefficients.
            for (int step = 0; step < 7; step++) // approximate depth
            {
                // Each step reads a nibble and possibly extends with 16-bit literal
                uint8_t nibble = *pStream & 0x0f;
                int32_t skip;
                if (nibble == 5)
                {
                    // Special case: read 16-bit value as offset
                    skip = *reinterpret_cast<uint16_t*>(pStream + 2);
                }
                else
                {
                    // Use lookup tables: value = table1[nibble] * (packed_two_nibbles) + table2[nibble]
                    // packed_two_nibbles = (pStream[1] << 4) | (pStream[0] >> 4)
                    int32_t packed = (pStream[1] << 4) | (pStream[0] >> 4);
                    skip = g_huffmanTable1[nibble] * packed + g_huffmanTable2[nibble];
                }
                // Advance stream
                pStream += skip;
                // Continue consuming next nibble... (the code repeats)
            }
        }
    }

    // After decoding all elements, decode 8 final values (likely PCM samples)
    float temp = static_cast<float>(scale);
    float decodedVal;
    decodedVal = decodeValue(&pStream, temp, scale);
    pOutput->values[0] = static_cast<int32_t>(decodedVal);
    decodedVal = decodeValue(&pStream, decodedVal, scale);
    pOutput->values[1] = static_cast<int32_t>(decodedVal);
    decodedVal = decodeValue(&pStream, decodedVal, scale);
    pOutput->values[2] = static_cast<int32_t>(decodedVal);
    decodedVal = decodeValue(&pStream, decodedVal, scale);
    pOutput->values[3] = static_cast<int32_t>(decodedVal);
    decodedVal = decodeValue(&pStream, decodedVal, scale);
    pOutput->values[4] = static_cast<int32_t>(decodedVal);
    decodedVal = decodeValue(&pStream, decodedVal, scale);
    pOutput->values[5] = static_cast<int32_t>(decodedVal);
    decodedVal = decodeValue(&pStream, decodedVal, scale);
    pOutput->values[6] = static_cast<int32_t>(decodedVal);
    decodedVal = decodeValue(&pStream, decodedVal, scale);
    pOutput->values[7] = static_cast<int32_t>(decodedVal);

    return 1;
}