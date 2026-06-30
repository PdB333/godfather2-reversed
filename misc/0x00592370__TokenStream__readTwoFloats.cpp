// FUNC_NAME: TokenStream::readTwoFloats
bool __thiscall TokenStream::readTwoFloats(TokenStream* thisPtr, ReadContext* readCtx)
{
    // DAT_01205574: max index for function table
    // DAT_01205570: base of function table (3 function pointers per entry? Actually entry size 0xc)
    // Function pointer signature: void (*)(int context, int index, float* outVec3)
    // readCtx[3] will be set to thisPtr on success

    char* tokenData;
    int index;
    float firstVec[3];
    float secondVec[3];

    // Read first value
    tokenData = *(char**)**(void***)(thisPtr + 8); // double indirection: get first token pointer
    if (*tokenData == '\n') {
        // Token is a reference (function call)
        index = *(short*)(tokenData + 2);
        if (index >= 0 && index < DAT_01205574) {
            auto func = *(code**)(DAT_01205570 + 4 + index * 0xc);
            if (func != nullptr) {
                func(*readCtx, index, firstVec);
            }
        }
    } else {
        // Token is a literal float (located at offset 4)
        firstVec[0] = *(float*)(tokenData + 4);
    }

    // Read second value (next token pointer)
    tokenData = *(char**)(*(int*)(thisPtr + 8) + 4); // get second pointer from the array
    if (*tokenData == '\n') {
        index = *(short*)(tokenData + 2);
        if (index >= 0 && index < DAT_01205574) {
            auto func = *(code**)(DAT_01205570 + 4 + index * 0xc);
            if (func != nullptr) {
                func(*readCtx, index, secondVec);
            }
        }
    } else {
        secondVec[0] = *(float*)(tokenData + 4);
    }

    // Validate range: second must be >= first
    if (secondVec[0] < firstVec[0]) {
        return false;
    }

    // Store this pointer in read context (slot 3)
    readCtx[3] = (undefined4)thisPtr;
    return true;
}