// FUNC_NAME: DeltaDecoder::DecodeDeltaPair (or BitStreamDecoder::DecodeTwoDeltas)
// This function decodes two delta values from a bitstream using a control byte (passed in EAX).
// It updates internal state tracking the last decoded values for prediction.
void __fastcall DecodeDeltaPair(DeltaDecoderState* state, short* outValues, BitStream* bitStream, uint control)
{
    char c;
    byte nibble;
    short decoded;
    uint mode1 = control & 3;
    
    // Decode first value
    if (mode1 == 1) {
        // 4-bit signed delta (nibble, offset by -8)
        if (bitStream->bitOffset == 0) {
            nibble = *bitStream->dataPtr >> 4;
            bitStream->bitOffset = 1;
        } else {
            nibble = *bitStream->dataPtr & 0xF;
            bitStream->bitOffset = 0;
            bitStream->dataPtr++;
        }
        outValues[0] = (short)nibble + state->lastValue0 + -8;
    }
    else if (mode1 == 2) {
        // Variable-length coded value: read 8-bit base, then if small use exp-Golomb escape
        if (bitStream->bitOffset == 0) {
            c = *bitStream->dataPtr;
            bitStream->dataPtr++;
        } else {
            c = *bitStream->dataPtr;
            byte* nextPtr = bitStream->dataPtr + 1;
            bitStream->dataPtr = nextPtr;
            c = *nextPtr >> 4 + c * 0x10;  // Combine nibbles to get full byte?
        }
        // If c is in [-8,7], use exp-Golomb coded value instead
        if ((unsigned short)((short)c + 8) < 0x10) {
            decoded = ReadExpGolomb(0);  // Escaped by FUN_00679360
            outValues[0] = decoded;
        } else {
            outValues[0] = state->lastValue0 + (short)c;
        }
    }
    else if (mode1 == 3) {
        // Use exp-Golomb coded delta (FUN_006792b0)
        decoded = ReadSignedExpGolomb();  // FUN_006792b0 returns a signed delta?
        outValues[0] = decoded + state->lastValue0;
    }
    // Update state for next delta
    state->prevValue0 = state->lastValue0;
    state->lastValue0 = outValues[0];

    // Now decode second value using control bits [2:3]
    uint mode2 = (control >> 2) & 3;

    if (mode2 == 1) {
        if (bitStream->bitOffset == 0) {
            nibble = *bitStream->dataPtr >> 4;
            bitStream->bitOffset = 1;
        } else {
            nibble = *bitStream->dataPtr & 0xF;
            bitStream->bitOffset = 0;
            bitStream->dataPtr++;
        }
        decoded = (short)nibble + state->lastValue1 + -8;
    }
    else if (mode2 == 2) {
        if (bitStream->bitOffset == 0) {
            c = *bitStream->dataPtr;
            bitStream->dataPtr++;
        } else {
            c = *bitStream->dataPtr;
            byte* nextPtr = bitStream->dataPtr + 1;
            bitStream->dataPtr = nextPtr;
            c = *nextPtr >> 4 + c * 0x10;
        }
        if ((unsigned short)((short)c + 8) < 0x10) {
            decoded = ReadExpGolomb(1);
        } else {
            outValues[1] = state->lastValue1 + (short)c;
            goto updateState;  // jump to common update
        }
    }
    else if (mode2 == 3) {
        decoded = ReadSignedExpGolomb();
        decoded = decoded + state->lastValue1;
    }
    else {
        goto updateState; // mode2 == 0: no change?
    }
    outValues[1] = decoded;

updateState:
    state->prevValue1 = state->lastValue1;
    state->lastValue1 = outValues[1];
}

// Structure definitions for context
struct DeltaDecoderState {
    short lastValue0;   // +0x104
    short lastValue1;   // +0x106
    short prevValue0;   // +0x108
    short prevValue1;   // +0x10A
};

struct BitStream {
    byte* dataPtr;      // current read pointer
    short bitOffset;    // 0..7, bits consumed in current byte
    // total bits? Not needed here
};