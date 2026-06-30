// FUNC_NAME: PackedStringTable::getCharWithContext(void* ctx, int index)

// Reconstructed from 0x005fca80 - reads a character from a tokenized string buffer.
// The buffer is a structure at param_2 with fields:
// +0x70: pointer to current position (char* current)
// +0x74: offset to end (or remaining length) (int endOffset)
// +0x78: flags (int flags) - if zero, directly returns current[index] packed into high address bits.
//
// The encoding: null bytes indicate a skip count (next byte), non-null bytes are data.
// The function returns a uint where low byte is the character, high 24 bits are part of the current pointer (for debugging).
// Index is passed in ESI (unaff_ESI) - we add an explicit parameter for clarity.

typedef struct PackedStringContext {
    char* current;        // +0x70
    int   endOffset;      // +0x74
    int   flags;          // +0x78
} PackedStringContext;

uint __fastcall PackedString_getChar(void* /*ecx unused*/, PackedStringContext* ctx, int index)
{
    char* pc = ctx->current;
    if (ctx->flags == 0) {
        // Direct access when flags is zero (no tokenization)
        return ( ( (uint)pc >> 8 ) << 8 ) | (uint8)pc[index];
    }

    char* end = pc + ctx->endOffset;
    uint sum = 0;

    if (end <= pc) {
        return (uint)pc & 0xFFFFFF00; // Error/end marker
    }

    do {
        if (*pc == '\0') {
            // Null byte: skip it and add next byte as skip count
            uint8 skip = (uint8)*(pc + 1);
            pc++;
            sum += skip;
            if (index < sum) {
                return (uint)pc & 0xFFFFFF00; // Index beyond current token
            }
        } else {
            if (index <= sum) {
                // Found the character
                return ( ( (uint)pc >> 8 ) << 8 ) | (uint8)*pc;
            }
            sum++;
        }
        pc++;
        if (end <= pc) {
            return (uint)pc & 0xFFFFFF00;
        }
    } while (1);
}