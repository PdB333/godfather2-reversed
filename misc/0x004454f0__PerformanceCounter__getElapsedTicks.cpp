// FUNC_NAME: PerformanceCounter::getElapsedTicks
class PerformanceCounter {
    uint32_t lowPart;   // +0x00
    uint32_t highPart;  // +0x04
public:
    uint64_t getElapsedTicks() {
        LARGE_INTEGER current;
        QueryPerformanceCounter(&current);

        // Calculate (current - stored base) as a 64-bit unsigned difference
        uint32_t borrow = (current.LowPart < lowPart) ? 1 : 0;
        uint64_t elapsed = (uint64_t)(current.LowPart - lowPart)
                         | ((uint64_t)(current.HighPart - highPart - borrow) << 32);
        return elapsed;
    }
};