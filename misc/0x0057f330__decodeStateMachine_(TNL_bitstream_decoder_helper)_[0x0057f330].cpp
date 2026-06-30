// FUNC_NAME: decodeStateMachine (TNL bitstream decoder helper) [0x0057f330]
// This function implements a state machine for decoding a variable-length bit field from a byte stream.
// It reads bits from the current byte (pointed to by g_ppStreamPos) and transitions between states 1,3,5,7.
// The state parameter (int&) is updated, and the stream pointer is advanced by 1 or 2 bytes depending on the decoded bits.
// This is likely used in TNL packet deserialization for reading compressed integers or flags.

// Global pointer to the current read position in the byte stream (pointer to byte*)
static byte** g_ppStreamPos = nullptr;

void __fastcall decodeStateMachine(int& state)
{
    byte* pCurrentByte = *g_ppStreamPos;  // read current pointer

    switch (state)
    {
    case 1: // State 1: examine bits 0-1
        switch (*pCurrentByte & 0x03)
        {
        case 0: // bits 00
            state = 3;
            *g_ppStreamPos = pCurrentByte + 2; // advance 2 bytes
            break;
        case 1: // bits 01
            state = 7;
            *g_ppStreamPos = pCurrentByte + 2;
            return;
        case 2: // bits 10
            state = 3;
            *g_ppStreamPos = pCurrentByte + 1;
            return;
        case 3: // bits 11
            state = 7;
            *g_ppStreamPos = pCurrentByte + 1;
            return;
        }
        break;

    case 3: // State 3: examine bits 2-3
        switch (*pCurrentByte & 0x0C)
        {
        case 0: // bits 00
            state = 5;
            *g_ppStreamPos = pCurrentByte + 2;
            return;
        case 4: // bits 01
            state = 1;
            *g_ppStreamPos = pCurrentByte + 1;
            return;
        case 8: // bits 10
            state = 5;
            *g_ppStreamPos = pCurrentByte + 1;
            return;
        case 12: // bits 11
            state = 1;
            // no advance (stays at same byte? Actually *g_ppStreamPos unchanged)
            return;
        }
        break;

    case 5: // State 5: examine bits 4-5
        switch (*pCurrentByte & 0x30)
        {
        case 0: // bits 00
            goto case1_flag; // jump to state 1 case 1 (bits 01)
        case 16: // bits 01
            goto case2_flag; // jump to state 1 case 2 (bits 10)
        case 32: // bits 10
            goto case3_flag; // jump to state 1 case 3 (bits 11)
        case 48: // bits 11
            state = 3;
            return;
        }
        break;

    case 7: // State 7: examine bits 6-7
        switch (*pCurrentByte & 0xC0)
        {
        case 0: // bits 00
            goto case3_01; // jump to state 3 case 1 (bits 01)
        case 64: // bits 01
            goto case3_10; // jump to state 3 case 2 (bits 10)
        case 128: // bits 10
            goto case3_11; // jump to state 3 case 3 (bits 11)
        case 192: // bits 11
            state = 5;
            return;
        }
        break;
    }

    // Implicit return if no match

    // Helper labels to map goto targets (decompiler artifact)
    case1_flag:
        state = 7;
        *g_ppStreamPos = pCurrentByte + 2;
        return;
    case2_flag:
        state = 3;
        *g_ppStreamPos = pCurrentByte + 1;
        return;
    case3_flag:
        state = 7;
        *g_ppStreamPos = pCurrentByte + 1;
        return;
    case3_01:
        state = 1;
        *g_ppStreamPos = pCurrentByte + 1;
        return;
    case3_10:
        state = 5;
        *g_ppStreamPos = pCurrentByte + 1;
        return;
    case3_11:
        state = 1;
        return;
}