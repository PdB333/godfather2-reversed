// FUNC_NAME: F2FManager::initialize

F2FManager* __thiscall F2FManager::initialize(F2FManager* this, uint someParam)
{
    int* allocPtr;
    undefined4 local_c[3];

    // Store self in global singleton
    gF2FManager = this;

    // Set up vtable pointers (multiple tiers)
    this->vtable1 = &PTR_FUN_00e2f19c;          // +0x04
    this->field_02 = 1;                         // +0x08
    this->field_03 = 0;                         // +0x0c
    this->vtable2 = &PTR_LAB_00e30fe0;          // +0x10
    this->baseVtable = &PTR_FUN_00d609dc;       // +0x00
    this->vtable1 = &PTR_LAB_00d609cc;          // +0x04 override
    this->vtable2 = &PTR_LAB_00d609bc;          // +0x10 override

    // Clear local array
    local_c[0] = 0;
    local_c[1] = 0;
    local_c[2] = 0;

    // Allocate internal object
    allocPtr = (int*)FUN_004dddd0();
    this->internalObj = FUN_004265d0(local_c, allocPtr);
    this->allocPtr = allocPtr;
    // Call a virtual on the allocated object
    (*(code**)(*allocPtr + 8))();

    // Initialize additional fields
    this->field_06 = 0;   // +0x18
    this->field_05 = 0;   // +0x14
    this->field_07 = 0;   // +0x1c
    this->field_10 = 0;   // +0x28
    this->field_11 = 0;   // +0x2c
    this->field_12 = 0;   // +0x30

    // Sub-init functions
    FUN_006f8370();
    FUN_006f8060();

    // Register message strings for face-to-face events
    msgAudioF2FFailure       = FUN_00408240(&msgIdAudioF2FFailure,       "iMsgAudioF2FFailure");
    msgAudioF2FSuccess       = FUN_00408240(&msgIdAudioF2FSuccess,       "iMsgAudioF2FSuccess");
    msgF2FSuccessCompletion  = FUN_00408240(&msgIdF2FSuccessCompletion,  "iMsgF2FSuccessCompletion");
    msgFirstSuccessPolice    = FUN_00408240(&msgIdFirstPolice,           "iMsgFirstSuccessWithPoliceChief");
    msgFirstSuccessBribe     = FUN_00408240(&msgIdFirstBribe,            "iMsgFirstSuccessWithBribeOfficer");
    msgFirstSuccessPayable   = FUN_00408240(&msgIdFirstPayable,          "iMsgFirstSuccessWithPayable");
    msgFirstSuccessMerchant  = FUN_00408240(&msgIdFirstMerchant,         "iMsgFirstSuccessWithMerchant");
    msgFirstSuccessMerchant2 = FUN_00408240(&msgIdFirstMerchant2,        "iMsgFirstSuccessWithMerchant");
    msgFirstSuccessRacket    = FUN_00408240(&msgIdFirstRacket,           "iMsgFirstSuccessWithRacketOwner");
    msgFirstSuccessFBI       = FUN_00408240(&msgIdFirstFBI,              "iMsgFirstSuccessWithFBI");
    msgFirstSuccessQuack     = FUN_00408240(&msgIdFirstQuack,            "iMsgFirstSuccessWithQuack");
    msgFirstSuccessSnitch    = FUN_00408240(&msgIdFirstSnitch,           "iMsgFirstSuccessWithSnitch");
    msgFirstSuccessBribeLite = FUN_00408240(&msgIdFirstBribeLite,        "iMsgFirstSuccessWithBribeLite");
    msgFirstSuccessCrew      = FUN_00408240(&msgIdFirstCrew,             "iMsgFirstSuccessWithCrew");
    msgFirstSuccessDetective = FUN_00408240(&msgIdFirstDetective,        "iMsgFirstSuccessWithDetective");

    // Register completion message with notification system
    if (msgF2FSuccessCompletion != 0) {
        FUN_00408900(this + 1, &msgF2FSuccessCompletion, 0x8000);
    }

    // Register for message with hash 0x25920c72
    FUN_00463980(0x25920c72, &this->vtable2, someParam);

    return this;
}