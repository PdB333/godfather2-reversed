// FUNC_NAME: Animated::startTimer

void __thiscall Animated::startTimer(int this)
{
    int timerData[2]; // unknown structure: [0]=ptr, [1]=int, then a byte?
    char localByte;

    if ( *(char *)(this + 0x9a) == '\0' )
    {
        timerData[0] = *(int *)(this + 0x60);
        if ( timerData[0] != 0 )
        {
            timerData[1] = 0;
            localByte = 0;
            startTimer(&timerData, 0); // FUN_00408a00
        }
    }
    *(char *)(this + 0x9a) = 1; // mark timer as started
}