// FUNC_NAME: AnimCurve::generateKeyframes
int __thiscall AnimCurve::generateKeyframes(int this, void* outputBuffer, int count, float* scaleFactors)
{
    // Offsets from 'this':
    float startTime = *(float*)(this + 0x30);   // +0x30: start time/value
    float endTime   = *(float*)(this + 0x34);   // +0x34: end time/value
    float duration  = *(float*)(this + 0x38);   // +0x38: duration scaling
    float amplitude = *(float*)(this + 0x3c);   // +0x3c: amplitude

    float product = startTime * duration;
    float step = (endTime - startTime) / (float)(count - 1);

    int i = 0;

    // Header fields of output buffer
    *(char*)(outputBuffer + 0xe) = (char)count;                    // +0xe: number of keyframes
    *(ushort*)(outputBuffer + 0x1c) = (ushort)((char)count - 1);   // +0x1c: count-1

    if (count > 0) {
        char* blockPtr = (char*)(outputBuffer + 0xf);             // +0xf: start of first keyframe block (0x20 bytes each)
        ushort* indexPtr = (ushort*)(outputBuffer + 0x3c);        // +0x3c: array of indices? (only written for later keyframes)

        float interpAccum = product;
        float currentTime = startTime;

        do {
            // Zero header fields (offsets +0xc, +0xd)
            blockPtr[-3] = '\0';
            blockPtr[-2] = '\0';

            if (i != 0) {
                *indexPtr = (ushort)i & 0xFF;
                indexPtr += 0x10;   // advance by 0x20 bytes (sizeof(ushort)*0x10)
            }

            *blockPtr = (i != 0) + 1;   // +0x0: key type (1 for first, 2 for subsequent)

            // Write float at offset +0x0 (scale * currentTime)
            *(float*)(blockPtr - 0xf) = *scaleFactors * currentTime;

            // Zero header fields (offsets +0x4..+0x7)
            blockPtr[-11] = '\0';
            blockPtr[-10] = '\0';
            blockPtr[-9]  = '\0';
            blockPtr[-8]  = '\0';

            // Call to likely FPU math function (e.g., sin/cos) using product as input
            double mathResult = (double)product;
            FUN_00b99fcb();   // result on FPU stack, used below

            interpAccum = duration * step + interpAccum;
            currentTime = step + currentTime;

            // Write float at offset +0x8 (mathResult * amplitude * scaleFactors[2])
            *(float*)(blockPtr - 7) = (float)mathResult * amplitude * scaleFactors[2];

            product = interpAccum;
            startTime = currentTime;   // reused variable

            FUN_00414aa0();   // another helper function

            i++;
            blockPtr += 0x20;   // next keyframe block
        } while (i < count);
    }

    return 1;
}