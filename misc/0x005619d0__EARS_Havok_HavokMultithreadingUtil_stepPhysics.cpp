// Xbox PDB: EARS::Havok::HavokMultithreadingUtil::stepPhysics
// FUNC_NAME: GameTickManager::processTimestep
void GameTickManager::processTimestep(int timestepMs)
{
    // Get TLS buffer for profiling/tracing
    LPVOID tlsBuffer = TlsGetValue(DAT_01139830);
    undefined4 *profileSlot = *(undefined4 **)((int)tlsBuffer + 4);
    undefined4 *profileEnd = *(undefined4 **)((int)tlsBuffer + 0xc);
    
    // Push profile marker if space available
    if (profileSlot < profileEnd) {
        *profileSlot = "MiTimestep";
        profileSlot[1] = timestepMs;
        *(undefined4 **)((int)tlsBuffer + 4) = profileSlot + 2;
    }
    
    // Store timestep in member variable (+0x134)
    *(int *)(unaff_ESI + 0x134) = timestepMs;
    
    // Process game tick
    FUN_009e5d60();  // Begin tick processing
    FUN_009e5d20(*(undefined4 *)(unaff_ES I + 0x134));  // Process tick with timestep
    FUN_00aad120(*(undefined4 *)(unaff_ESI + 4));  // Process subsystems (count at +0x04)
    
    int i = 0;
    int param = 0;
    FUN_009e5d40(&param);  // Get some parameter
    FUN_009e66f0();  // End tick processing
    
    // Process each subsystem
    if (0 < *(int *)(unaff_ESI + 4)) {
        do {
            FUN_00aad110();  // Process single subsystem
            i = i + 1;
        } while (i < *(int *)(unaff_ESI + 4));
    }
}