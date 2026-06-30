// Address: 0x0041f120 - Busy wait delay loop, spins for a count stored in global variable (DAT_01205370). Likely a short micro-delay or placeholder.
void delayLoop(void)
{
    uint iterationCount = 0;
    // DAT_01205370 is a global variable indicating number of iterations to wait.
    if (DAT_01205370 != 0) {
        do {
            iterationCount = iterationCount + 1;
        } while (iterationCount < DAT_01205370);
    }
    return;
}