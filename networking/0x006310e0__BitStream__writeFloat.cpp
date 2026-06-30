// FUNC_NAME: BitStream::writeFloat
int BitStream::writeFloat(void)
{
    int *readPos;
    float floatVal;
    int local_10;
    float local_c;

    readPos = *(int **)(this + 0xc); // mReadPos
    if (readPos <= *(int **)(this + 8)) // mWritePos? or end?
        goto skip;
    if (readPos == nullptr)
        goto skip;
    if (*readPos != 3) {
        if (*readPos != 4)
            goto skip;
        // Type 4: need to convert from another representation
        int converted = FUN_00636850(&floatVal); // might be convertFloat()
        if (converted == 0)
            goto skip;
        local_10 = 3;
        local_c = floatVal;
        readPos = &local_10; // override with new type? dubious
    }
    floatVal = (float)readPos[1];
    if (floatVal == DAT_00e2b05c) { // sentinel value
        while (true) {
            readPos = *(int **)(this + 0xc);
            if (readPos <= *(int **)(this + 8) || readPos == nullptr)
                break;
            if (*readPos == 3)
                break;
            if (*readPos != 4)
                break;
            int ret = FUN_00636850(&local_10);
            if (ret != 0)
                break;
            // If we reach here, invalid entry
            FUN_00627ac0(PTR_s_number_00e2a8a8); // debug print "number"
            floatVal = 0.0f;
        }
    }
skip:
    if (readPos <= *(int **)(this + 8) || readPos == nullptr)
        floatVal = 0.0f;

    int *writePos = *(int **)(this + 8);
    *writePos = 3; // write type tag
    double doubleVal = (double)floatVal;
    FUN_00b9b988(); // likely FPU state sync
    writePos[1] = (float)doubleVal;
    *(int *)(this + 8) = (int)writePos + 8;
    return 1;
}