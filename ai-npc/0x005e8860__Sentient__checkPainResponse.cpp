// FUNC_NAME: Sentient::checkPainResponse
void Sentient::checkPainResponse(void) {
    int distVal;
    int someGlobal;
    
    // +0x26c: pointer to some data (maybe a script or behavior)
    if (*(int *)(this + 0x26c) != 0) {
        // +0x281: flag for first pain reaction (flinch)
        if (*(char *)(this + 0x281) == '\0') {
            // +0x484: another pointer or condition (maybe hit this frame)
            if (*(int *)(this + 0x484) != 0) {
                // Call a global function pointer at offset 0x68 from some global object (DAT_01223510)
                // Pass something at +0x1cc (likely a target or position)
                // This likely returns a distance or time value
                distVal = (**(code **)(*DAT_01223510 + 0x68))(*(undefined4 *)(this + 0x1cc));
                someGlobal = DAT_0122350c;
                // Check distance against threshold at +0x270
                if ((-1 < distVal) && (*(int *)(this + 0x270) <= distVal)) {
                    // Set first reaction played flag
                    *(char *)(this + 0x281) = 1;
                    // Play animation/sound ID 6 using some manager (DAT_0122350c) and parameter at +0x27c
                    FUN_005e25a0(someGlobal, *(undefined4 *)(this + 0x27c), 6);
                    return;
                }
            }
        }
        else {
            // +0x274: second threshold (maybe time since first reaction)
            // +0x282: flag for second pain reaction (stagger)
            if ((-1 < *(int *)(this + 0x274)) && (*(char *)(this + 0x282) == '\0')) {
                distVal = FUN_005e9780();
                someGlobal = DAT_0122350c;
                if ((-1 < distVal) && (*(int *)(this + 0x274) <= distVal)) {
                    *(char *)(this + 0x282) = 1;
                    // Play animation/sound ID 7
                    FUN_005e25a0(someGlobal, *(undefined4 *)(this + 0x27c), 7);
                }
            }
        }
    }
    return;
}