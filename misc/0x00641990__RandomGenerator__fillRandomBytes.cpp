// FUNC_NAME: RandomGenerator::fillRandomBytes
void __thiscall RandomGenerator::fillRandomBytes(int count)
{
    // Check if random generator is initialized (flag at +0x0c)
    if (*(int*)(this + 0x0c) == 0) {
        int result = FUN_006385a0(); // e.g., checkSystemTimeForSeed()
        if (result != 0) {
            FUN_00641890(); // e.g., initializeSeed()
            return;
        }
    }
    else if (count != 0) {
        // Buffer pointer is passed in EAX (likely this->m_buffer for performance)
        byte* buffer = (byte*)(in_EAX + 3); // Destination buffer base + 3
        do {
            count--;
            int inner = 4;
            byte* dest = buffer;
            do {
                byte randByte = FUN_006418b0(); // Get next random byte
                *dest = randByte;
                dest--;
                inner--;
            } while (inner != 0);
            buffer += 4;
        } while (count != 0);
    }
}