// Xbox PDB: EARS::Modules::CommonNPC::CommonNPC
// FUNC_NAME: StimulusManager::StimulusManager

// Function address: 0x0072ac90
// Constructor for the StimulusManager class.
// Registers message handlers for "iMsgHandleStimulus" and "iMsgStimulusReceived",
// sets up multiple vtable pointers (multiple inheritance), and fills debug guards.

StimulusManager::StimulusManager(uint32_t param_2) {
    // Base class initializer (likely a core manager base)
    BaseManagerConstructor(param_2, 0);  // FUN_007326f0

    // Install vtable pointers at various offsets (multiple base classes / interfaces)
    *(void**)this = &PTR_FUN_00d626d8;                    // +0x00: primary vtable
    *(void**)(this + 0x0f) = &PTR_LAB_00d626c8;           // +0x3C: message-handling sub-object vtable
    *(void**)(this + 0x12) = &PTR_LAB_00d626c4;           // +0x48
    *(void**)(this + 0x14) = &PTR_LAB_00d626c0;           // +0x50
    *(void**)(this + 0x15) = &PTR_LAB_00d62660;           // +0x54
    *(void**)(this + 0x16) = &PTR_LAB_00d625f8;           // +0x58
    *(void**)(this + 0xe4) = &PTR_LAB_00d625d8;           // +0x390
    *(void**)(this + 0xe5) = &PTR_FUN_00d625c4;           // +0x394 (function pointer)
    *(void**)(this + 0xe8) = &PTR_FUN_00d625bc;           // +0x3A0 (function pointer)
    *(void**)(this + 0x7cc) = &PTR_LAB_00d625b4;          // +0x1F30

    // Additional initialization (maybe static data or memory pool)
    StaticDataInit();  // FUN_00700040

    // Write debug signatures to detect memory corruption
    // These are at offsets 0x26C0..0x26EF (9b0 * 4 = 0x26C0)
    *(uint32_t*)(this + 0x9b0) = 0xBADBADBA;
    *(uint32_t*)(this + 0x9b1) = 0xBEEFBEEF;
    *(uint32_t*)(this + 0x9b2) = 0xEAC15A55;
    *(uint32_t*)(this + 0x9b3) = 0x91100911;
    *(uint32_t*)(this + 0x9b4) = 0xBADBADBA;
    *(uint32_t*)(this + 0x9b5) = 0xBEEFBEEF;
    *(uint32_t*)(this + 0x9b6) = 0xEAC15A55;
    *(uint32_t*)(this + 0x9b7) = 0x91100911;
    *(uint32_t*)(this + 0x9b8) = 0xBADBADBA;
    *(uint32_t*)(this + 0x9b9) = 0xBEEFBEEF;
    *(uint32_t*)(this + 0x9ba) = 0xEAC15A55;
    *(uint32_t*)(this + 0x9bb) = 0x91100911;

    // Clear some fields after the guards
    *(uint32_t*)(this + 0x9bc) = 0;   // +0x26F0
    *(uint32_t*)(this + 0x9bd) = 0;   // +0x26F4
    *(uint32_t*)(this + 0x9be) = 0;   // +0x26F8
    *(uint32_t*)(this + 0x9c3) = 0;   // +0x270C

    // Register message type IDs from string names
    g_iMsgHandleStimulusId = RegisterMessageString("iMsgHandleStimulus");   // FUN_00408240 -> &DAT_0112ad8c
    g_iMsgStimulusReceivedId = RegisterMessageString("iMsgStimulusReceived"); // FUN_00408240 -> &DAT_0112ad84

    // Subscribe this object's message-handling sub-object (offset +0x0f) to those messages
    if (g_iMsgHandleStimulusId != 0) {
        SubscribeToMessage(this + 0x0f, &g_iMsgHandleStimulusId, 0x8000); // FUN_00408900
    }
    // Note: second subscription uses a different global (DAT_0112ad7c) which is set elsewhere
    if (g_msgIdOtherStimulus != 0) {
        SubscribeToMessage(this + 0x0f, &g_msgIdOtherStimulus, 0x8000);
    }

    // Finalize constructor (post‑init)
    PostConstructorInit();  // FUN_0072a9f0
}