// FUNC_NAME: staticInitializer_audioAndStream
// Address: 0x00688a10
// Role: Static initialization of audio and stream systems (EA EARS engine)
// This function is a compiler-generated static initializer that ensures
// two subsystems are initialized exactly once, with destructors registered via atexit.

static uint32 s_initializationFlags = 0; // global guard, +0x01129a3c

void initializeAudioAndStreamSubsystems()
{
    // Initialize audio subsystem if not already done
    if ((s_initializationFlags & 1) == 0)
    {
        s_initializationFlags |= 1;
        initializeAudioSystem();          // FUN_00482440 – likely AudioDataManager::initialize()
        atexit(destroyAudioSystem);       // LAB_00d51490 – destructor stub
    }

    // Initialize stream subsystem if not already done
    if ((s_initializationFlags & 2) == 0)
    {
        s_initializationFlags |= 2;
        initializeStreamSystem();         // FUN_005be4f0 – likely StreamManager::initialize()
        atexit(destroyStreamSystem);      // LAB_00d51480 – destructor stub
    }
}