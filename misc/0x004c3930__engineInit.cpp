// FUNC_NAME: engineInit
// Address: 0x004c3930
// Role: Game engine initialization, calls two subsystem setup routines.
void engineInit(void)
{
    initAudio();      // 0x004977b0 - likely audio subsystem init
    initRenderer();   // 0x00497ad0 - likely rendering subsystem init
}