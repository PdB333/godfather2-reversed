// FUNC_NAME: spinDelay
void spinDelay(int cycles) {
    // Simple busy-wait loop that decrements cycles until zero.
    // Used for short timing delays or CPU cycle consumption.
    while (cycles > 0) {
        --cycles;
    }
}