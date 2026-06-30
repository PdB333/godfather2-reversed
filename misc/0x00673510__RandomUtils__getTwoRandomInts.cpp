// FUNC_NAME: RandomUtils::getTwoRandomInts
// Function at 0x00673510
// __thiscall: this pointer in ESI (implicit first param)
// Parameters: out1 and out2 are output pointers for two integer values
// The field at this+0x1c is a flag that controls whether both outputs get fresh random values
//   or the second is forced to zero.

void __thiscall RandomUtils::getTwoRandomInts(int *out1, int *out2) {
    // First random value (may be discarded if flag == 0)
    int firstRandom = getRandomInt(); // FUN_00676010

    // Check flag at this+0x1c
    if (*(int *)((char *)this + 0x1c) == 0) {
        // Generate two new random values (firstRandom is overwritten)
        int secondRandom = getRandomInt(); // FUN_00676010
        int thirdRandom = getRandomInt();  // FUN_00676010
        *out1 = secondRandom;
        *out2 = thirdRandom;
    } else {
        // Use the first random, second output forced to 0
        *out1 = firstRandom;
        *out2 = 0;
    }
}