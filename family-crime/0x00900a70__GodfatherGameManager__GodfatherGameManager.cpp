// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

void __fastcall GodfatherGameManager::GodfatherGameManager(int *this)
{
    int subPtr;

    // Set virtual function table pointers (multiple inheritance)
    this[0] = (int)&PTR_FUN_00d817e8;             // +0x00: primary vtable
    this[0xf] = (int)&PTR_LAB_00d817d8;           // +0x3C: secondary vtable
    this[0x12] = (int)&PTR_LAB_00d817d4;          // +0x48
    this[0x14] = (int)&PTR_LAB_00d817d0;          // +0x50
    this[0x15] = (int)&PTR_LAB_00d81770;          // +0x54
    this[0x16] = (int)&PTR_LAB_00d81708;          // +0x58

    // Initialize substructures (likely container/list objects at +0x188, +0x190, etc.)
    initializeContainer(&DAT_012069d4);           // global static container? Or this+?
    initializeContainer(&this[0x62]);             // +0x188: container init
    resetContainer(&this[0x62]);                 // +0x188: reset/clear
    initializeContainer(&this[100]);             // +0x190: container init
    resetContainer(&this[100]);                  // +0x190: reset/clear
    resetContainer(&this[0x66]);                 // +0x198
    resetContainer(&this[0x68]);                 // +0x1A0
    resetContainer(&this[0x6a]);                 // +0x1A8

    // If pointer at +0x184 is non-null, release related resources
    if (this[0x61] != 0) {
        destroyAudioManager();                   // FUN_009008a0
        destroyStreamManager();                  // FUN_009f01a0
        this[0x61] = 0;
    }

    // Check flags at +0x180 (bitmask 0x3000) - dead code due to contradictory condition
    if (((*(ushort *)(this + 0x60) & 0x3000) != 0) && ((*(ushort *)(this + 0x60) & 0x3000) == 0)) {
        (**(code **)(*this + 0x18))();           // call virtual function at vtable+0x18 (0x1C? offset)
    }

    // If pointer at +0x1D0 is non-null, release that resource
    subPtr = this[0x74];
    if (subPtr != 0) {
        deleteResource();                         // FUN_00900430
        deleteResource();                         // FUN_00900430
        releaseResource(subPtr);                  // FUN_009c8eb0
    }

    // Final initialization steps
    finalizeLogging();                            // FUN_00903a40
    finalizeMemoryTracker();                      // FUN_0046ea20
}