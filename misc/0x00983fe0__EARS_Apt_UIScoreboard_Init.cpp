// Xbox PDB: EARS_Apt_UIScoreboard_Init
// FUNC_NAME: UIScoreboard::init
void __fastcall UIScoreboard::init(int this)
{
    // Initialize the scoreboard UI system
    FUN_005c1740(); // Likely base UI initialization
    
    // Register various UI elements with their properties
    // Each call registers a UI element at a specific offset in the object
    FUN_005c01d0(&DAT_00d87b2c, this + 0x6c, 2, 0, 0, 1); // +0x6c: element type 2
    FUN_005c01d0(&DAT_00d90a6c, this + 0x70, 1, 0, 0, 1); // +0x70: element type 1
    FUN_005c01d0(&DAT_00d90a64, this + 0x74, 1, &LAB_00983fc0, 0, 0); // +0x74: element type 1 with callback
    FUN_005c01d0(&DAT_00d88e58, this + 0x78, 1, 0, 0, 1); // +0x78: element type 1
    FUN_005c01d0(&DAT_00d86468, this + 0x8c, 6, 0, 0, 1); // +0x8c: element type 6
    FUN_005c01d0(&DAT_00d90a5c, this + 0xa0, 6, 0, 0, 1); // +0xa0: element type 6
    FUN_005c01d0(&DAT_00d90a54, this + 0xa4, 0, 0, 0, 1); // +0xa4: element type 0
    FUN_005c01d0(&DAT_00d878bc, this + 0xa8, 1, 0, 0, 1); // +0xa8: element type 1
    FUN_005c01d0(&DAT_00d90a4c, this + 0xac, 2, 0, 0, 1); // +0xac: element type 2
    FUN_005c01d0(&DAT_00d90a44, this + 0xad, 2, 0, 0, 1); // +0xad: element type 2
    FUN_005c01d0(&DAT_00d90a3c, this + 0xb0, 1, 0, 0, 1); // +0xb0: element type 1
    FUN_005c01d0(&DAT_00d85730, this + 0xd0, 1, 0, 0, 1); // +0xd0: element type 1
    FUN_005c01d0(&DAT_00d90a34, this + 0xb4, 1, 0, 0, 1); // +0xb4: element type 1
    FUN_005c01d0(&DAT_00d90a2c, this + 0xd4, 1, 0, 0, 1); // +0xd4: element type 1
    FUN_005c01d0(&DAT_00d90a24, this + 0xc4, 1, 0, 0, 1); // +0xc4: element type 1
    FUN_005c01d0(&DAT_00d856e8, this + 0x5c, 1, 0, 0, 1); // +0x5c: element type 1
    FUN_005c01d0(&DAT_00d90a1c, this + 0xce, 2, 0, 0, 1); // +0xce: element type 2
    
    // Register timer update and hide delayed callbacks
    FUN_00408240(this + 0xe0, "UIScoreboard_TimerUpdate_Internal"); // +0xe0: timer update callback
    FUN_00408240(this + 0xe8, "UIScoreboard_HideDelayed_Internal"); // +0xe8: hide delayed callback
    
    // Register VoIP message handlers
    FUN_00408240(&DAT_0112edf4, "iMsgVoipBroadcastStart"); // VoIP broadcast start message
    FUN_00408240(&DAT_0112ef7c, "iMsgVoipBroadcastStop");  // VoIP broadcast stop message
    
    // Subscribe to the VoIP messages
    FUN_00408680(&DAT_0112edf4); // Subscribe to broadcast start
    FUN_00408680(&DAT_0112ef7c); // Subscribe to broadcast stop
    FUN_00408680(&DAT_0112ee7c); // Subscribe to another VoIP message
    
    return;
}