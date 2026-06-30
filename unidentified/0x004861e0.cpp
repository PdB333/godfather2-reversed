// FUN_004861e0: MessageSystem::initialize or constructor-like init
void MessageSystem::initialize()
{
    // +0x04: set to 1 (some flag)
    this->field4 = 1;
    // +0x08: set to 0 (reference count?)
    this->field8 = 0;
    // +0x0C: first vtable pointer? (note: later overwritten to another pointer)
    this->fieldC = &PTR_LAB_00e337b0;
    // +0x00: vtable pointer (function table)
    this->vtable = &PTR_FUN_00e3379c;
    // +0x0C: overwritten to another pointer (maybe second vtable or a different field)
    this->fieldC = &PTR_LAB_00e337ac;
    // Store global singleton reference
    _DAT_01223498 = this;
    // Zero out fields at +0x10, +0x14, +0x18
    this->field10 = 0;
    this->field14 = 0;
    this->field18 = 0;

    // Register known message types by hashing their names
    uint msgId;
    msgId = hashString("iMsgPrePresentationThreadCommandDispatch");
    registerMessageID(DAT_0120ecb0, msgId);
    msgId = hashString("iMsgPostPresentationThreadCommandDispatch");
    registerMessageID(DAT_0120ecb8, msgId);
    msgId = hashString("iMsgPostSimulation");
    registerMessageID(DAT_0120eca8, msgId);
    msgId = hashString("iMsgStreamBeginUnload");
    registerMessageID(DAT_01206778, msgId);
    msgId = hashString("iMsgStreamUnloading");
    registerMessageID(DAT_012067b4, msgId);

    // Handle the "iMsgStreamBeginUnload" registration if already present
    if (DAT_01206778 != 0)
    {
        _DAT_0120677c = _DAT_0120677c + 1;
        int handlerPtr = acquireMessageHandler(); // returns pointer to some handler object
        if (handlerPtr == 0)
        {
            releaseMessageHandler(&DAT_01206778, 0);
        }
        else
        {
            // Increment a 15-bit field at offset 0x14 with overflow protection
            ushort oldVal = *(ushort *)(handlerPtr + 0x14);
            // Pattern: ((oldVal * 2) >> 1) + 1 XOR oldVal, mask to 0x7fff, XOR with oldVal
            ushort newVal = oldVal ^ ((oldVal & 0x7fff) + 1);
            // Equivalent to: if bit15 is set, clear it and increment lower 15 bits; else just increment lower 15 bits.
            // This handles wrap-around without using the high bit.
            *(ushort *)(handlerPtr + 0x14) = newVal;
        }
    }
    // Handle the "iMsgStreamUnloading" registration if already present
    if (DAT_012067b4 != 0)
    {
        _DAT_012067b8 = _DAT_012067b8 + 1;
        int handlerPtr = acquireMessageHandler();
        if (handlerPtr == 0)
        {
            releaseMessageHandler(&DAT_012067b4, 0);
        }
        else
        {
            ushort oldVal = *(ushort *)(handlerPtr + 0x14);
            ushort newVal = oldVal ^ ((oldVal & 0x7fff) + 1);
            *(ushort *)(handlerPtr + 0x14) = newVal;
        }
    }
    // If post-presentation and post-simulation messages are registered, process them
    if (DAT_0120ecb8 != 0)
    {
        processOrDispatch(); // likely dispatches or handles pending messages
    }
    if (DAT_0120eca8 != 0)
    {
        processOrDispatch();
    }
    return;
}