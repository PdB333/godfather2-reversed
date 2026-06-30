// FUNC_NAME: AnimationKeyframeReader::readNormalizedKeyframe
// 0x00631b10 - Reads the next keyframe from a compressed input stream, normalizes it to type 3 (constant float), and writes it to an output buffer.
// Skips sentinel values and invalid keyframes, printing debug "number" when skipping.
// Structure offsets: +0x08 = output buffer write pointer (advanced by 8 on success),
//                    +0x0C = input buffer read pointer (not advanced in this function – done elsewhere)
int __thiscall AnimationKeyframeReader::readNormalizedKeyframe(int thisPtr)
{
    // +0x0C: current read pointer into input keyframe stream
    int* readPtr = *(int**)(thisPtr + 0x0C);
    // +0x08: current write pointer into output buffer
    int* outWritePtr = *(int**)(thisPtr + 0x08);

    // Validate read pointer is within range and non-null
    if (outWritePtr <= readPtr)          // end-of-buffer check
        goto skipInvalid;
    if (readPtr == nullptr)
        goto skipInvalid;

    // Read keyframe type (3 = constant float, 4 = potentially compressed)
    int type = *readPtr;
    float value;

    if (type != 3)
    {
        if (type != 4)
            goto skipInvalid;           // unknown type

        // Type 4: attempt to decode a float from additional data
        float decoded;
        int success = readConvertedFloat(&decoded);  // FUN_00636850
        if (success == 0)
            goto skipInvalid;           // decompression failed

        // Replace current read with a synthetic type-3 frame
        int synthetic[2] = { 3, *(int*)&decoded };
        readPtr = synthetic;
    }

    // Now readPtr points to a valid type-3 frame; extract the float value
    value = *(float*)(readPtr + 1);
    float sentinel = *(float*)0x00e2b05c;   // global sentinel constant (likely 0.0)

    // If the value matches the sentinel, skip this frame and search for a valid one
    if (value == sentinel)
    {
        while (true)
        {
            // Re-fetch pointers – the read pointer may have been advanced by readConvertedFloat
            readPtr = *(int**)(thisPtr + 0x0C);
            outWritePtr = *(int**)(thisPtr + 0x08);

            // Check for valid frame: pointer in range, non-null, and type 3 or valid type 4
            if (outWritePtr > readPtr && readPtr != nullptr)
            {
                int nextType = *readPtr;
                if (nextType == 3)
                    break;                          // valid type 3
                if (nextType == 4)
                {
                    float temp;
                    int res = readConvertedFloat(&temp);
                    if (res != 0)
                        break;                      // valid type 4 converted
                }
            }
            // Invalid or sentinel – log "number" and reset value to 0.0
            consoleDebugPrint("number");             // FUN_00627ac0
skipInvalid:
            value = 0.0f;
        }
    }

    // Write the normalized keyframe (type 3) to the output buffer
    int* outPtr = *(int**)(thisPtr + 0x08);
    *outPtr = 3;                                     // type constant
    double dbl = (double)value;
    setFPURoundingMode();                             // FUN_00d3d41f – likely sets IEEE754 rounding
    *(float*)(outPtr + 1) = (float)dbl;

    // Advance output write pointer by one keyframe (8 bytes)
    *(int**)(thisPtr + 0x08) = outPtr + 2;           // each keyframe is 2 ints

    return 1;                                         // always success
}