// FUNC_NAME: PathBuilder::buildPaths
void __thiscall PathBuilder::buildPaths(int* outParam_2, char* dest1, char* dest2, char* dest3, int maxLen)
{
    char* baseString;
    char* tempString;
    int extraArg;
    FUN_005c4660_func stringBuilder1;
    FUN_00603d30_func intToStrFunc;
    FUN_00604000_func intToStrFunc2;

    // Store first output: this->outputValue at +0x14
    *outParam_2 = this->outputValue; // param_1[5]

    baseString = this->baseFormat; // param_1[0]
    if (baseString == (char *)0x0) {
        baseString = &DAT_0120546e; // default placeholder string
    }

    // Build first part: baseString + formatArg
    stringBuilder1(dest1, baseString, maxLen, this->formatArg); // param_1[1]

    // Convert integer at +0x18 to string
    intToStrFunc(this->index1, &tempString, 1); // param_1[6]

    baseString = tempString;
    if (baseString == (char *)0x0) {
        baseString = &DAT_0120546e;
    }

    // Build second part: baseString + index1 string
    stringBuilder1(dest2, baseString, maxLen, 0); // extraArg = 0

    // Convert sum of two integers at +0x1C and +0x20 to string
    intToStrFunc2(this->index2 + this->index3, &tempString, 1); // param_1[7] + param_1[8]

    baseString = tempString;
    if (baseString == (char *)0x0) {
        baseString = &DAT_0120546e;
    }

    // Build third part: baseString + sum string
    stringBuilder1(dest3, baseString, maxLen, 0);

    // Free temporary string if allocated (destructor likely stored in object)
    if (tempString != (char *)0x0) {
        (*(code *)this->deallocFunc)(tempString); // local_4 is uninitialized; replace with plausible member
    }
}