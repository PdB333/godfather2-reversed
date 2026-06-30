// FUNC_NAME: searchFloatTableWithPermutation

struct SearchContext {
    int   param_0;   // +0x00: unknown (unused in this function)
    int   startIdx;  // +0x04: initial search offset (adjusted by +2 for unrolled loop)
    uint  maxIdx;    // +0x08: number of elements in the table
    float value;     // +0x0c: value to compare
};

// Global permutation mask (bitwise AND with current index to produce actual table index)
extern int g_permutationMask;   // DAT_010c2678

// Global float threshold table (accessed via permuted indices)
extern float g_floatTable[];    // DAT_010c2680

// Persistent search cursor – avoids restarting from the beginning each call
extern uint g_searchCursor;     // DAT_012054b4

// __fastcall: ecx unused, edx = pointer to SearchContext
uint __fastcall searchFloatTableWithPermutation(int /*unused*/, SearchContext* ctx)
{
    uint resultIdx = 0;
    uint endIdx = ctx->maxIdx;
    int adjustedStart = ctx->startIdx + 2;

    if (adjustedStart > endIdx) {
        adjustedStart = endIdx;
    }

    uint cursor = g_searchCursor;

    // Unrolled main loop: process 4 indices per iteration
    if (adjustedStart > 3) {
        do {
            // Check first element of the quad
            float val0 = g_floatTable[g_permutationMask & cursor];
            if (ctx->value <= val0) {
                g_searchCursor = cursor + 1;
                return resultIdx;
            }
            uint nextCursor = cursor + 2;
            g_searchCursor = nextCursor;
            float val1 = g_floatTable[g_permutationMask & (cursor + 1)];
            if (ctx->value <= val1) {
                return resultIdx + 1;
            }
            nextCursor = cursor + 3;
            g_searchCursor = nextCursor;
            float val2 = g_floatTable[g_permutationMask & (cursor + 2)];
            if (ctx->value <= val2) {
                return resultIdx + 2;
            }
            cursor += 4;
            g_searchCursor = cursor;
            float val3 = g_floatTable[g_permutationMask & cursor];
            if (ctx->value <= val3) {
                return resultIdx + 3;
            }
            resultIdx += 4;
        } while (resultIdx < adjustedStart - 3);
    }

    // Handle remaining elements (less than 4)
    if (resultIdx < adjustedStart) {
        while (true) {
            uint tblIdx = g_permutationMask & g_searchCursor;
            g_searchCursor++;
            if (ctx->value <= g_floatTable[tblIdx]) {
                break;
            }
            resultIdx++;
            if (resultIdx >= adjustedStart) {
                return resultIdx;
            }
        }
    }

    return resultIdx;
}