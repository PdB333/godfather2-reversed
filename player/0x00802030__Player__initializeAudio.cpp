// FUNC_NAME: Player::initializeAudio
void __fastcall Player::initializeAudio(int this) {
    int *pManager;
    float10 fVar;
    
    // Check if bit 20 (0x100000) at offset 0x8e0 is already set
    if ((*(uint *)(this + 0x8e0) >> 0x14 & 1) == 0) {
        // Call virtual function at vtable+0x28 (likely allocate or create) with argument 0x20
        (**(code **)(*(int *)(this + 0x58) + 0x28))(0x20);
    }
    // Set bit 20 at offset 0x8e0 (flag to prevent re-entry)
    *(uint *)(this + 0x8e0) = *(uint *)(this + 0x8e0) | 0x100000;
    
    // Get singleton manager from global pointer
    pManager = (int *)getAudioManager(DAT_01131018);
    if (pManager != (int *)0x0) {
        // Call virtual function at +0x2c (getter returning float)
        fVar = (float10)(**(code **)(*pManager + 0x2c))();
        // Call virtual function at +0x3c (setter with float argument)
        (**(code **)(*pManager + 0x3c))((float)fVar);
    }
    return;
}