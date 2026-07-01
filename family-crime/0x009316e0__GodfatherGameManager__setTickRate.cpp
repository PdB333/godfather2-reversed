// FUNC_NAME: GodfatherGameManager::setTickRate

// Function address: 0x009316e0
// Role: Called during initialization to configure the game loop timer.
// Stores a parameter at +0x5c and sets a global tick interval to 30.

extern void FUN_00983190(void);   // unknown subsystem initialization
extern void FUN_00931010(void);   // unknown timer start/finalize

extern int DAT_00e5672c;          // global tick interval (frames/milliseconds)

void __thiscall GodfatherGameManager::setTickRate(void* this, int param_2)
{
    FUN_00983190();
    *(int*)((int)this + 0x5c) = param_2;   // +0x5c: timer configuration value
    DAT_00e5672c = 0x1e;                     // set global interval to 30
    FUN_00931010();
}