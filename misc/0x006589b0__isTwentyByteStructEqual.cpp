// FUNC_NAME: isTwentyByteStructEqual
bool __fastcall isTwentyByteStructEqual(const TwentyByteStruct* a, const TwentyByteStruct* b)
{
    // Compare first two shorts (offsets 0x00 and 0x02)
    if (a->short0 != b->short0)
        return false;
    if (a->short1 != b->short1)
        return false;
    // Compare four ints at offsets 0x04, 0x08, 0x0C, 0x10
    if (a->int2 != b->int2)
        return false;
    if (a->int3 != b->int3)
        return false;
    if (a->int4 != b->int4)
        return false;
    if (a->int5 != b->int5)
        return false;
    return true;
}

// Hypothetical struct layout (20 bytes total)
// struct TwentyByteStruct {
//     short short0;  // +0x00
//     short short1;  // +0x02
//     int   int2;    // +0x04
//     int   int3;    // +0x08
//     int   int4;    // +0x0C
//     int   int5;    // +0x10
// };