// FUNC_NAME: GodfatherGameManager::initGameplaySystems
void __fastcall GodfatherGameManager::initGameplaySystems(int this)
{
    // Initialize base gameplay systems
    FUN_005c1740();
    
    // Initialize gameplay timer with 100ms interval (0x64 = 100)
    // +0x64 = gameplay timer interval
    // +0xf0 = another timer interval (240ms)
    FUN_005c01d0(&DAT_00d8f974, this + 100, 0, 0, 0, 1);  // Timer 1: 100ms
    FUN_005c01d0(&DAT_00d8f96c, this + 0xf0, 6, 0, 0, 1); // Timer 2: 240ms, priority 6
}