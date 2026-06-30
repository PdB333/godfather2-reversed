//FUNC_NAME: RandomGenerator::fillRandomUint32
void __thiscall RandomGenerator::fillRandomUint32(uint32_t* outValue)
{
    // Check if random generator is initialized (field at +0x0C)
    if (this->m_initialized == 0) {
        // Attempt to initialize the random generator
        int initResult = initializeRandom(); // FUN_006385a0
        if (initResult != 0) {
            // Reset random state after successful initialization
            resetRandomState(); // FUN_00641890
            return;
        }
    } else {
        // Fill 4 bytes (32-bit value) at outValue with random bytes
        uint8_t* writePtr = reinterpret_cast<uint8_t*>(outValue) + 3;
        int remaining = 4;
        do {
            *writePtr = getRandomByte(); // FUN_006418b0
            writePtr--;
            remaining--;
        } while (remaining != 0);
    }
}