// FUNC_NAME: StimulusManager::constructor
StimulusManager* __fastcall StimulusManager::constructor(StimulusManager* this)
{
    // Store global singleton reference
    gStimulusManager = this;

    // Initialize base vtable pointer (offset +0x0)
    this->vtable = (void**)&PTR_FUN_00d624f8;

    // Set derived vtable pointer (offset +0x4) – overwrites initial assignment
    this->derivedVtable = (void**)&PTR_LAB_00d624e8;

    // Constructor body
    this->field_8 = 1;       // +0x08: likely count or flag
    this->field_C = 0;       // +0x0C
    this->field_10 = 0;      // +0x10
    this->field_14 = 0;      // +0x14
    this->field_18 = 0;      // +0x18
    this->field_1C = 0;      // +0x1C
    this->field_20 = 0;      // +0x20
    this->field_24 = 0;      // +0x24

    // Core system initialization
    initStimulusSystem();           // FUN_00729180
    allocateStimulusSlots(20);      // FUN_00729630(0x14 – probably 20 slots)

    // Register the message types and subscribe
    registerString(&sStimulusDataType, "StimulusData*");          // FUN_00408240
    registerString(&sMsgHandleStimulus, "iMsgHandleStimulus");    // FUN_00408240

    if (sMsgHandleStimulus != 0) {
        // Subscribe to stimulus messages with flag 0x8000 (likely eBroadcast or priority)
        subscribeToMessage(this + 1, &sMsgHandleStimulus, 0x8000); // FUN_00408900
    }

    return this;
}