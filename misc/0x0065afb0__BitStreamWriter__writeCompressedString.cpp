// FUNC_NAME: BitStreamWriter::writeCompressedString
// Address: 0x0065afb0
// Writes a string to the bitstream using Huffman-like compression.
// 'this' (in EAX) points to a bitstream writer with:
// +0x0c: uint32* bitBuffer (or byte*)
// +0x18: uint32 bitOffset (current write position in bits)
// +0x30: uint32 maxBits (capacity)
// Returns 1 on success.
// Uses a static compression table at gCompressionTable (DAT_01223360).
// Each table entry: 4 bytes bit length, 8 bytes bit pattern (max 64 bits).

extern char DAT_0120588e;              // Global flag, indicates initialization needed
extern byte gCompressionTable[];       // Static table at 0x01223360, size 256 * 12 bytes

// Forward declarations for helper functions (same class)
// __thiscall
bool FUN_0064b7c0();                   // Returns true if buffer can accept more bits (or flush needed?)
void FUN_0064b810(uint bitCount, void* data); // Write raw bits from 'data', little-endian?
void FUN_0065a940();                   // Initialize compression table

int __thiscall BitStreamWriter::writeCompressedString(char* string, uint maxLen)
{
    uint len;
    uint sum;
    uint i;
    uint val;
    uint bitLen;
    byte* bytePtr;
    byte* bitBuf;

    len = maxLen;
    if (string == (char*)0x0)
    {
        // Writing a null string: emit a 0 bit (literal mode) and then a zero length (8 bits).
        if ((*(uint*)(this + 0x18) + 1 <= *(uint*)(this + 0x30)) || 
            (FUN_0064b7c0() != 0))
        {
            // Clear the bit at current offset (write 0)
            bitBuf = (byte*)(*(uint*)(this + 0x0c) + (*(uint*)(this + 0x18) >> 3));
            *bitBuf = *bitBuf & ~(1 << ((byte)*(uint*)(this + 0x18) & 7));
            *(uint*)(this + 0x18) = *(uint*)(this + 0x18) + 1;
        }
        // Write a zero length (8 bits) - the value is 0
        string = (char*)0x0;           // length = 0
        FUN_0064b810(8, &string);      // write 8 zero bits
        return 1;
    }

    // Ensure compression table is initialized
    if (DAT_0120588e == '\0')
    {
        FUN_0065a940();
    }

    // Compute actual string length (up to maxLen)
    bytePtr = (byte*)string;
    while (*bytePtr != 0) { bytePtr++; }
    len = (uint)(bytePtr - (byte*)string);
    if (maxLen < len) { len = maxLen; }

    // Compute sum of compressed bit lengths for each character from table
    // Table entry stride = 12 bytes: offset +4 = bit count, +8 = bit pattern
    sum = 0;
    for (i = 0; i < len; i++)
    {
        byte b = (byte)string[i];
        sum += *(uint*)(gCompressionTable + 4 + b * 12);
    }

    if (len * 8 <= sum)
    {
        // Literal mode: store bits are more or equal to raw? Actually store raw bytes.
        // Write a 0 bit to indicate literal mode.
        if ((*(uint*)(this + 0x18) + 1 <= *(uint*)(this + 0x30)) || 
            (FUN_0064b7c0() != 0))
        {
            bitBuf = (byte*)(*(uint*)(this + 0x0c) + (*(uint*)(this + 0x18) >> 3));
            *bitBuf = *bitBuf & ~(1 << ((byte)*(uint*)(this + 0x18) & 7));
            *(uint*)(this + 0x18) = *(uint*)(this + 0x18) + 1;
        }
        // Write the length as 8 bits
        string = (char*)len;
        FUN_0064b810(8, &string);
        // Write the raw characters (each 8 bits)
        FUN_0064b810(len * 8, string - (char*)len); // Actually the original string pointer
        // Actually need to pass the original pointer: use temporary
        // In decompiled: param_1 = (char*)uVar8; then FUN_0064b810(uVar8 * 8, pcVar2);
        // So we write the raw string bytes.
        FUN_0064b810(len * 8, string); // string still points to the original? No, we overwrote string. Wait recalc.
        // Let's redo: 
        // After setting param_1 = (char*)uVar8, then FUN_0064b810(uVar8*8, pcVar2). So we need original pointer.
        // So we need to keep original pointer.
        // We'll fix below.
    }
    else
    {
        // Compressed mode: write a 1 bit.
        if ((*(uint*)(this + 0x18) + 1 <= *(uint*)(this + 0x30)) || 
            (FUN_0064b7c0() != 0))
        {
            bitBuf = (byte*)(*(uint*)(this + 0x0c) + (*(uint*)(this + 0x18) >> 3));
            *bitBuf = *bitBuf | (1 << ((byte)*(uint*)(this + 0x18) & 7));
            *(uint*)(this + 0x18) = *(uint*)(this + 0x18) + 1;
        }
        // Write the length as 8 bits
        FUN_0064b810(8, &len);
        // For each character, write the Huffman code from table
        for (i = 0; i < len; i++)
        {
            byte b = (byte)string[i];
            uint tableBase = gCompressionTable + b * 12;
            uint bitCount = *(uint*)(tableBase + 4);   // +4: bit length
            void* bitPattern = (void*)(tableBase + 8); // +8: bit pattern (max 8 bytes)
            FUN_0064b810(bitCount, bitPattern);
        }
        return 1;
    }

    // Return from literal path (should be unreachable due to early return? Actually code continues after literal write)
    return 1;
}
```cpp

// Cleaner version with correct variable usage:

int __thiscall BitStreamWriter::writeCompressedString(char* str, uint maxLen)
{
    uint len;
    uint sum;
    uint i;
    byte* bitBuf;
    char* origStr = str;

    if (str == 0)
    {
        // Write null string indicator: 0 bit + 8-bit zero length
        if ((*(uint*)(this + 0x18) + 1 <= *(uint*)(this + 0x30)) || 
            (FUN_0064b7c0()))
        {
            bitBuf = (byte*)(*(uint*)(this + 0x0c) + (*(uint*)(this + 0x18) >> 3));
            *bitBuf &= ~(1 << (*(uint*)(this + 0x18) & 7));
            (*(uint*)(this + 0x18))++;
        }
        len = 0;
        FUN_0064b810(8, &len);
        return 1;
    }

    if (DAT_0120588e == 0)
        FUN_0065a940();

    // Calculate string length (null-terminated, capped by maxLen)
    for (len = 0; len < maxLen && str[len] != 0; len++);

    // Compute sum of Huffman bit lengths for each character
    sum = 0;
    for (i = 0; i < len; i++)
    {
        byte b = (byte)str[i];
        sum += *(uint*)(gCompressionTable + 4 + b * 12);
    }

    if (len * 8 <= sum)
    {
        // Use literal encoding: raw bytes (no compression benefit)
        // Write a 0 bit to indicate literal mode
        if ((*(uint*)(this + 0x18) + 1 <= *(uint*)(this + 0x30)) || 
            (FUN_0064b7c0()))
        {
            bitBuf = (byte*)(*(uint*)(this + 0x0c) + (*(uint*)(this + 0x18) >> 3));
            *bitBuf &= ~(1 << (*(uint*)(this + 0x18) & 7));
            (*(uint*)(this + 0x18))++;
        }
        // Write length (8 bits)
        FUN_0064b810(8, &len);
        // Write raw characters (each 8 bits)
        FUN_0064b810(len * 8, str);
    }
    else
    {
        // Use Huffman compression
        // Write a 1 bit to indicate compressed mode
        if ((*(uint*)(this + 0x18) + 1 <= *(uint*)(this + 0x30)) || 
            (FUN_0064b7c0()))
        {
            bitBuf = (byte*)(*(uint*)(this + 0x0c) + (*(uint*)(this + 0x18) >> 3));
            *bitBuf |= (1 << (*(uint*)(this + 0x18) & 7));
            (*(uint*)(this + 0x18))++;
        }
        // Write length (8 bits)
        FUN_0064b810(8, &len);
        // Write each character's Huffman code
        for (i = 0; i < len; i++)
        {
            byte b = (byte)str[i];
            uint tableBase = gCompressionTable + b * 12;
            uint bitCount = *(uint*)(tableBase + 4);   // number of bits for this symbol
            void* bitData = (void*)(tableBase + 8);    // the actual bits (up to 8 bytes)
            FUN_0064b810(bitCount, bitData);
        }
    }
    return 1;
}