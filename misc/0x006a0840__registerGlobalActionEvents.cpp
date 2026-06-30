// FUNC_NAME: registerGlobalActionEvents

void registerGlobalActionEvents(void)
{
    // Registers a large number of action events into the game event system.
    // Each block: get a base ID, build an action struct with parameters, then register it with a hash.
    // Parameters to buildEventAction: (actionType, extra, r, g, b, a, unk1, unk2, baseId, flag)
    // The hash constants likely correspond to specific event names/IDs.

    uint32_t baseId;
    uint32_t flag;
    void* action;

    // --- Action type 0x11 (maybe "punch" or "attack") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x11, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x8c036aab, action, baseId, flag);

    // --- Action type 0x1f (maybe "shoot" or "aim") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x1f, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x46e7afe1, action, baseId, flag);

    // --- Action type 0x1e (maybe "reload") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x1e, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x1a271621, action, baseId, flag);

    // --- Action type 0x20 (maybe "melee") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x20, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xd7d6fc22, action, baseId, flag);

    // --- Action type 0x12 (maybe "block") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x12, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xa08a43df, action, baseId, flag);

    // --- Action type 0x38 (maybe "special move") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x38, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x776def75, action, baseId, flag);

    // --- Action type 0x2a (maybe "interact") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x2a, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x78467823, action, baseId, flag);

    // --- Action type 0x1d with extra 0x9d (maybe "extortion") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x1d, 0x9d, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x17a26743, action, baseId, flag);

    // --- Player-specific actions (index 0, 1) ---
    baseId = getPlayerBaseId(0, 0xff);  // player slot 0
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x2938c6cc, action, baseId, flag);

    baseId = getPlayerBaseId(1, 0xff);  // player slot 1
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x3ddc7637, action, baseId, flag);

    // --- Action type 0x10 (maybe "pickup") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x10, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x6367ea84, action, baseId, flag);

    // --- Action type 0x39 (maybe "ability") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xed41087b, action, baseId, flag);

    // --- Action type 0x21 repeated (maybe "use item" twice) ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x21, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xa7879506, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x21, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xf0c639eb, action, baseId, flag);

    // --- Action type 0x2e (maybe "crouch") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x2e, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x657a83a5, action, baseId, flag);

    // --- Action type 0x2f (maybe "sprint") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x2f, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x64ce24d7, action, baseId, flag);

    // --- Action type 0xf with flag=0 (maybe "stealth") ---
    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0xf, 0, 0, 0, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0xc1e9c75, action, baseId, flag);

    // --- Player-specific with extra parameters ---
    baseId = getPlayerBaseId(0xff, 4);  // family slot 4
    flag = 1;
    action = buildEventAction(0x2c, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x6ef11ea8, action, baseId, flag);

    baseId = getPlayerBaseId(0xff, 3);  // family slot 3
    flag = 1;
    action = buildEventAction(0x2d, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xbe16155b, action, baseId, flag);

    // --- Inventory/item actions (0-10) with flag=0 ---
    for (int itemIdx = 2; itemIdx <= 10; itemIdx++) {
        baseId = getBaseId();
        flag = 0;
        action = buildEventAction(itemIdx, 0, 0, 0, 0xff, 0, 0, 3, baseId, 0);
        // Hash based on item index: 0xc4aacd37 + (itemIdx - 2) for 2..10
        uint32_t hash = 0xc4aacd37 + (itemIdx - 2);
        registerEventAction(hash, action, baseId, flag);
    }
    // Special case: itemIdx = 0xb (11) gets hash 0xc4aacd36
    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0xb, 0, 0, 0, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0xc4aacd36, action, baseId, flag);

    // --- Another player/family specific ---
    baseId = getPlayerBaseId(0xff, 2);  // family slot 2
    flag = 1;
    action = buildEventAction(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xebc77d43, action, baseId, flag);

    // --- Action type 0x13 (maybe "dodge") ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x13, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x62b07722, action, baseId, flag);

    // --- Player-specific actions again (index 0, 1) with different hashes ---
    baseId = getPlayerBaseId(0, 0xff);
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x54a314df, action, baseId, flag);

    baseId = getPlayerBaseId(1, 0xff);
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xd177df7c, action, baseId, flag);

    // --- Repeat of many earlier actions with different hashes (maybe alternate states) ---
    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x11, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x3210a0c6, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x1f, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xec486385, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x1e, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x9f425b6d, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x20, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xded909d6, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x2a, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x66e0c2b3, action, baseId, flag);

    baseId = getPlayerBaseId(0, 0xff);
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x5dd81de3, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x1d, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xb4a5136c, action, baseId, flag);

    baseId = getPlayerBaseId(0xff, 2);
    flag = 1;
    action = buildEventAction(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x5855e99b, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x2c, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xf2448c6, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x10, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xc072d9d7, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x2e, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x6af3511e, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x21, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xc9694699, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x2f, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x5182bba0, action, baseId, flag);

    // --- Actions with specific RGB values (maybe highlight colors) ---
    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0xff, 0xff, 200, 0x48, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0xb0bda83a, action, baseId, flag);

    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0xff, 0xff, 0xd0, 0x50, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0xe1fe5cc1, action, baseId, flag);

    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0xff, 0xff, 0xcb, 0x4b, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0x51374386, action, baseId, flag);

    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0xff, 0xff, 0xcd, 0x4d, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0x923727fd, action, baseId, flag);

    // --- More item/UI actions ---
    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(1, 0, 0, 0, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0x1d8e854d, action, baseId, flag);

    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0x1c, 0x9c, 0, 0, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0x318300a5, action, baseId, flag);

    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(1, 0, 0, 0, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0xd4c6db97, action, baseId, flag);

    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(0x39, 0, 0, 0, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0x5d4e479f, action, baseId, flag);

    baseId = getBaseId();
    flag = 0;
    action = buildEventAction(199, 0, 0, 0, 0xff, 0, 0, 3, baseId, 0);
    registerEventAction(0x388a33a7, action, baseId, flag);

    // --- Another batch with family/player-specific ---
    baseId = getPlayerBaseId(0xff, 2);
    flag = 1;
    action = buildEventAction(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xb14e178e, action, baseId, flag);

    baseId = getPlayerBaseId(0, 0xff);
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x4296e28d, action, baseId, flag);

    baseId = getPlayerBaseId(1, 0xff);
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x36d50d68, action, baseId, flag);

    baseId = getBaseId();
    flag = 1;
    action = buildEventAction(0x38, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0x4238f65a, action, baseId, flag);

    // --- Equipment/item actions for slots 2..5 ---
    for (int equipSlot = 2; equipSlot <= 5; equipSlot++) {
        baseId = getBaseId();
        flag = 1;
        action = buildEventAction(equipSlot, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
        uint32_t hash = 0x424a9b6b + (equipSlot - 2);
        registerEventAction(hash, action, baseId, flag);
    }

    // --- Last player-specific ---
    baseId = getPlayerBaseId(1, 0xff);
    flag = 1;
    action = buildEventAction(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, baseId, 1);
    registerEventAction(0xc4417112, action, baseId, flag);

    return;
}