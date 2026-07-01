// FUNC_NAME: ScrollManager::initScroll
void __thiscall ScrollManager::initScroll(int this, unsigned int* outValue)
{
    // Global dynamic array of 64-bit scroll seeds
    static unsigned long long* sScrollArray = nullptr; // DAT_011307f8
    static int sScrollCount = 0;                       // DAT_011307fc
    static int sScrollCapacity = 0;                    // DAT_01130800

    // Reset the global array
    sScrollCount = 0;
    freeScrollArray(sScrollArray); // FUN_009c8f10
    sScrollArray = nullptr;
    sScrollCapacity = 0;

    // Generate and store 5 scroll seeds (pairs of 32-bit constants)
    unsigned int seedLow, seedHigh;
    unsigned long long newValue;

    // Seed pair 1
    seedLow = 0xa6b07719;
    seedHigh = 0xdaaa5987;
    newValue = generateScrollSeed(&seedHigh, &seedLow); // FUN_0095c290
    if (sScrollCount == sScrollCapacity) {
        int newCapacity = (sScrollCapacity == 0) ? 1 : sScrollCapacity * 2;
        resizeScrollArray(newCapacity); // FUN_0095c7f0
    }
    unsigned long long* slot = &sScrollArray[sScrollCount];
    sScrollCount++;
    if (slot != nullptr) {
        *slot = newValue;
    }

    // Seed pair 2
    seedLow = 0xb4167e93;
    seedHigh = 0x2efecf8d;
    newValue = generateScrollSeed(&seedHigh, &seedLow);
    if (sScrollCount == sScrollCapacity) {
        int newCapacity = (sScrollCapacity == 0) ? 1 : sScrollCapacity * 2;
        resizeScrollArray(newCapacity);
    }
    slot = &sScrollArray[sScrollCount];
    sScrollCount++;
    if (slot != nullptr) {
        *slot = newValue;
    }

    // Seed pair 3
    seedLow = 0xf62e4080;
    seedHigh = 0x7116917a;
    newValue = generateScrollSeed(&seedHigh, &seedLow);
    if (sScrollCount == sScrollCapacity) {
        int newCapacity = (sScrollCapacity == 0) ? 1 : sScrollCapacity * 2;
        resizeScrollArray(newCapacity);
    }
    slot = &sScrollArray[sScrollCount];
    sScrollCount++;
    if (slot != nullptr) {
        *slot = newValue;
    }

    // Seed pair 4
    seedLow = 0xc23e7eff;
    seedHigh = 0x3d26cff9;
    newValue = generateScrollSeed(&seedHigh, &seedLow);
    if (sScrollCount == sScrollCapacity) {
        int newCapacity = (sScrollCapacity == 0) ? 1 : sScrollCapacity * 2;
        resizeScrollArray(newCapacity);
    }
    slot = &sScrollArray[sScrollCount];
    sScrollCount++;
    if (slot != nullptr) {
        *slot = newValue;
    }

    // Seed pair 5
    seedLow = 0xcadaa53c;
    seedHigh = 0x45c2f636;
    newValue = generateScrollSeed(&seedHigh, &seedLow);
    if (sScrollCount == sScrollCapacity) {
        int newCapacity = (sScrollCapacity == 0) ? 1 : sScrollCapacity * 2;
        resizeScrollArray(newCapacity);
    }
    slot = &sScrollArray[sScrollCount];
    sScrollCount++;
    if (slot != nullptr) {
        *slot = newValue;
    }

    // Output a value from the object (offset +0xA8)
    *outValue = *(unsigned int*)(this + 0xA8);

    // Log initialization
    debugPrint("InitScroll", 0, &DAT_00d8cdec, 0); // FUN_005a04a0
}