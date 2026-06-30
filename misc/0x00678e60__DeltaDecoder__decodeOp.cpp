// FUNC_NAME: DeltaDecoder::decodeOp
// Address: 0x00678e60
// Role: Decodes variable-length delta-coded 2D position data from a nibble bitstream.
// The function reads a nibble opcode from the bitstream and applies one of 16 delta operations.
// It outputs one or two short pairs to the output buffer and updates internal context.

#include <cstdint>

// Forward declarations for helper functions.
extern uint8_t readFlag();                    // FUN_00678370
extern void readFlagTwo();                    // FUN_006783a0
extern int16_t readDeltaFromTable(int index); // FUN_00679360
extern int8_t readSmallDelta();               // FUN_006796b0
extern int16_t readMediumDelta();             // FUN_006792b0
extern void applyDelta(void* context, int16_t* ptr = nullptr); // FUN_00679420

// Bitstream helper: reads a nibble (4 bits) from a byte-aligned stream.
// Structure: byte* m_pReadBuffer;  int16_t m_nibbleFlag; (0 = high nibble next, 1 = low nibble next)
struct NibbleBitStream {
    uint8_t* m_pReadBuffer; // +0x00
    int16_t  m_nibbleFlag;  // +0x04 (0 or 1)
};

inline uint8_t readNibble(NibbleBitStream* bs) {
    uint8_t nibble;
    if (bs->m_nibbleFlag == 0) {
        nibble = *bs->m_pReadBuffer >> 4; // high nibble
        bs->m_nibbleFlag = 1;
    } else {
        nibble = *bs->m_pReadBuffer & 0x0F; // low nibble
        bs->m_nibbleFlag = 0;
        bs->m_pReadBuffer++; // advance to next byte
    }
    return nibble;
}

// Delta context: stores current and previous position samples.
// Offsets from 'this' (param_1).
struct DeltaContext {
    /* +0x104 */ int16_t m_currentX;
    /* +0x106 */ int16_t m_currentY;
    /* +0x108 */ int16_t m_previousX;
    /* +0x10a */ int16_t m_previousY;
};

// Main decode function.
// param_1 (ECX) : pointer to DeltaContext
// param_2        : pointer to output count (written to)
// EAX            : pointer to NibbleBitStream
// EDI            : pointer to output buffer (int16_t[6])
void decodeOp(DeltaContext* ctx, int16_t* outCount, NibbleBitStream* bs, int16_t* outBuffer) {
    int16_t sVar7;
    int16_t tempX, tempY;

    // Read initial nibble (opcode)
    uint8_t opcode = readNibble(bs);

    outBuffer[0] = ctx->m_currentX;
    outBuffer[1] = ctx->m_currentY;

    if (opcode < 0) { // signed comparison, but opcode is uint8; as per decompilation: if (sVar7 < 0) -> opcode >= 0x80? Actually sVar7 is from param_2? Wrong, but we keep logic as decompiled. Probably an error in decompiler; we ignore this branch, it's never taken because opcode is 0..15.
        // Not reachable in practice; case 6 is used for this? The decompiler misinterpreted.
        opcode = 6; // fallback? Actually the code:
        // if (sVar7 < 0) { bVar5 = 6; } else ...
        // sVar7 = *param_2; but that's read before switch? No, sVar7 = *param_2 is set earlier but that is the initial value from caller. Might be a reuse of register. We'll trust the switch on bVar5 which is the nibble.
    }

    // Process opcode
    switch (opcode) {
    case 0: {
        *outCount = 1;
        uint8_t flag = readFlag();
        if ((flag & 8) == 0) {
            tempX = readDeltaFromTable(0);
            outBuffer[0] = tempX;
        } else {
            tempY = readDeltaFromTable(1);
            outBuffer[1] = tempY;
        }
        break;
    }
    case 1: {
        *outCount = 1;
        int8_t delta = readSmallDelta();
        outBuffer[0] = (int16_t)delta + ctx->m_currentX;
        break;
    }
    case 2: {
        *outCount = 1;
        int8_t delta = readSmallDelta();
        outBuffer[1] = (int16_t)delta; // Actually set to m_currentY + delta later? No, goto LAB_00678f7a: unaff_EDI[1] = sVar7 + *(short *)(param_1 + 0x106). But sVar7 is the delta. So it adds to currentY. In decompiler, case 2 sets outBuffer[1] to delta + m_currentY. We'll replicate.
        outBuffer[1] = (int16_t)delta + ctx->m_currentY;
        break;
    }
    case 3: {
        *outCount = 1;
        int16_t delta = readMediumDelta();
        outBuffer[0] = delta + ctx->m_currentX;
        break;
    }
    case 4: {
        *outCount = 1;
        int16_t delta = readMediumDelta();
        outBuffer[1] = delta + ctx->m_currentY;
        break;
    }
    case 5: {
        *outCount = 1;
        readFlag();
        applyDelta(ctx);
        return;
    }
    case 6: {
        *outCount = 0;
        readFlag();
        applyDelta(ctx);
        return;
    }
    case 7:
        goto label_0x0079072;
    case 8:
        goto label_0x00790f7;
    case 9:
        readFlag();
        goto label_0x0079072;
    case 10:
        readFlag();
        goto label_0x00790f7;
    case 11:
        readFlagTwo();
label_0x0079072: {
        *outCount = 2;
        applyDelta(ctx);
        int16_t* buf = outBuffer + 2;
        int16_t v0 = readDeltaFromTable(0);
        *buf = v0;
        outBuffer[3] = outBuffer[1];
        applyDelta(ctx, buf);
        outBuffer[4] = *buf;
        int16_t v1 = readDeltaFromTable(1);
        outBuffer[5] = v1;
        applyDelta(ctx, outBuffer + 4);
        return;
    }
    case 12:
        readFlagTwo();
label_0x00790f7: {
        *outCount = 2;
        applyDelta(ctx);
        outBuffer[2] = outBuffer[0];
        int16_t v1 = readDeltaFromTable(1);
        outBuffer[3] = v1;
        applyDelta(ctx, outBuffer + 2);
        int16_t v0 = readDeltaFromTable(0);
        outBuffer[4] = v0;
        outBuffer[5] = outBuffer[3];
        applyDelta(ctx, outBuffer + 4);
        return;
    }
    case 13:
        readFlag();
        goto label_0x00791ef;
    case 14:
        readFlagTwo();
        goto label_0x00791ef;
    case 15:
        readFlag();
        readFlagTwo();
label_0x00791ef: {
        int16_t x0 = ctx->m_currentX;
        int16_t y0 = ctx->m_currentY;
        int16_t x1 = ctx->m_previousX;
        int16_t y1 = ctx->m_previousY;
        *outCount = 2;
        outBuffer[0] = x0 * 2 - x1;
        outBuffer[1] = y0 * 2 - y1;
        applyDelta(ctx);
        int16_t* buf = outBuffer + 2;
        *buf = outBuffer[0];
        outBuffer[3] = outBuffer[1];
        applyDelta(ctx, buf);
        outBuffer[4] = *buf;
        outBuffer[5] = outBuffer[3];
        applyDelta(ctx, outBuffer + 4);
        return;
    }
    default:
        return;
    }

    // Common epilogue for cases that fall through (0-4 except 5,6)
    sVar7 = outBuffer[0];
    ctx->m_previousX = ctx->m_currentX;
    ctx->m_previousY = ctx->m_currentY;
    ctx->m_currentX = sVar7;
    ctx->m_currentY = outBuffer[1];
}