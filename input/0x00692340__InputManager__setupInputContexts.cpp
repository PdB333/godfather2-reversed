// FUNC_NAME: InputManager::setupInputContexts
void InputManager::setupInputContexts()
{
    // This function initializes all input contexts (action maps, states, bindings).
    // It creates action maps and contexts for various game modes (Hand-to-Hand, Weapon, Driving, etc.)
    // and registers their action bindings.
    
    // --- "Hand to Hand" context ---
    ActionMap* handToHandMap = createActionMap(); // FUN_00499d60
    ActionContext* handToHandCtx = createActionContext("Hand to Hand", 1); // FUN_00495d90
    global_handToHandMap = handToHandMap; // DAT_01129bd8
    global_handToHandCtx = handToHandCtx; // DAT_01129bdc

    initContext(handToHandMap, handToHandCtx); // FUN_006905a0

    // Setup state machine for Hand-to-Hand
    int handToHandStateMachine = createStateMachine(0, &LAB_00691a50, 0, 3); // FUN_0049a700
    // vtable call: setStateMachineSize (offset 4)
    (**(code **)(*handToHandMap + 4))(0x2a, handToHandStateMachine);
    finalizeContext(handToHandCtx); // FUN_00691b50

    // Add action mappings for Hand-to-Hand
    addActionMapping(0x64ce24d7, handToHandCtx); // FUN_00690530
    bindActionToKey(0xed41087b, handToHandMap, 0x64ce24d7); // FUN_004979c0
    if (handToHandCtx) {
        bindActionToKey(0xed41087b, handToHandCtx, 0x64ce24d7);
    }

    addActionMapping(0x657a83a5, handToHandCtx);
    bindActionToKey(0xed41087b, handToHandMap, 0x657a83a5);
    if (handToHandCtx) {
        bindActionToKey(0xed41087b, handToHandCtx, 0x657a83a5);
    }

    // ... many more similar bindings for other action hashes
    // (0xa7879506, 0x776def75, 0x78467823, 0x17a26743, 0xebc77d43,
    //  0x6ef11ea8, 0xbe16155b, 0xc4aacd36..0xc4aacd3f)
    // Each follows the same pattern as above.
    bindActionToKey(0xed41087b, handToHandMap, 0xa7879506);
    bindActionToKey(0xed41087b, handToHandMap, 0x776def75);
    bindActionToKey(0xed41087b, handToHandMap, 0x78467823);
    bindActionToKey(0xed41087b, handToHandMap, 0x17a26743);
    if (handToHandCtx) {
        bindActionToKey(0xed41087b, handToHandCtx, 0x17a26743);
    }
    bindActionToKey(0xed41087b, handToHandMap, 0xebc77d43);
    if (handToHandCtx) {
        bindActionToKey(0xed41087b, handToHandCtx, 0xebc77d43);
    }
    bindActionToKey(0xed41087b, handToHandMap, 0x6ef11ea8);
    if (handToHandCtx) {
        bindActionToKey(0xed41087b, handToHandCtx, 0x6ef11ea8);
    }
    bindActionToKey(0xed41087b, handToHandMap, 0xbe16155b);
    if (handToHandCtx) {
        bindActionToKey(0xed41087b, handToHandCtx, 0xbe16155b);
    }
    // Bind 0xc4aacd36..0xc4aacd3f (10 actions)
    for (uint i = 0x36; i <= 0x3f; ++i) {
        bindActionToKey(0xed41087b, handToHandMap, 0xc4aacd00 | i);
    }

    // Setup additional states for Hand-to-Hand
    int stateHandle1 = createState(3, 0, &LAB_00690ce0, 0, 3); // FUN_0049a700
    (**(code **)(*handToHandMap + 4))(0x20, stateHandle1);
    bindActionToButton(0xed41087b, handToHandMap, 0x20); // FUN_00497960

    if (handToHandCtx) {
        uint64 contextState = getContextState(); // FUN_00496470
        setStateMachine(contextState, &LAB_00690d80, 0); // FUN_00496780
        (**(code **)(*handToHandCtx + 4))(0x10, contextState);
        bindActionToButton(0xed41087b, handToHandCtx, 0x10);
    }

    // Register action states
    addActionMapping(0x2938c6cc, handToHandCtx);
    addActionMapping(0x3ddc7637, handToHandCtx);
    {
        int stateVal1 = getActionStateValue(global_someState, 0); // FUN_00496830
        (**(code **)(*handToHandCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_someState, 0); // FUN_00496880
        (**(code **)(*handToHandCtx + 0x18))(3, stateVal2);
    }

    // --- "Weapon" context ---
    ActionMap* weaponMap = createActionMap();
    ActionContext* weaponCtx = createActionContext("Weapon", 1);
    global_weaponMap = weaponMap; // DAT_01129be0
    global_weaponCtx = weaponCtx; // DAT_01129be4
    initContext(weaponMap, weaponCtx);

    int weaponStateMachine = createStateMachine(0, &LAB_00691a50, 0, 3);
    (**(code **)(*weaponMap + 4))(0x2a, weaponStateMachine);
    finalizeContext(weaponCtx);

    // Add action mappings for Weapon
    addActionMapping(0x62b07722, weaponCtx);
    addActionMapping(0xd177df7c, weaponCtx);
    addActionMapping(0x54a314df, weaponCtx);

    {
        int stateVal1 = getActionStateValue(global_someState, 0);
        (**(code **)(*weaponCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_someState, 0);
        (**(code **)(*weaponCtx + 0x18))(3, stateVal2);
    }

    // --- "Weapon Wheel - HandToHand" context ---
    ActionMap* weaponWheelH2HMap = createActionMap();
    ActionContext* weaponWheelH2HCtx = createActionContext("Weapon Wheel - HandToHand", 1);
    global_weaponWheelH2HMap = weaponWheelH2HMap; // DAT_01129be8
    global_weaponWheelH2HCtx = weaponWheelH2HCtx; // DAT_01129bec
    // Create a separate setup function for this (FUN_00692010) which likely registers sub-actions
    setupWeaponWheel(weaponWheelH2HMap, weaponWheelH2HCtx); // FUN_00692010

    // --- "Weapon Wheel - Weapon" context ---
    ActionMap* weaponWheelWeaponMap = createActionMap();
    ActionContext* weaponWheelWeaponCtx = createActionContext("Weapon Wheel - Weapon", 1);
    global_weaponWheelWeaponMap = weaponWheelWeaponMap; // DAT_01129bf0
    global_weaponWheelWeaponCtx = weaponWheelWeaponCtx; // DAT_01129bf4
    setupWeaponWheel(weaponWheelWeaponMap, weaponWheelWeaponCtx);

    // --- "Driving" context ---
    ActionMap* drivingMap = createActionMap();
    ActionContext* drivingCtx = createActionContext("Driving", 1);
    global_drivingMap = drivingMap; // DAT_01129bf8
    global_drivingCtx = drivingCtx; // DAT_01129bfc
    if (drivingMap) {
        // Initialize driving-specific bindings
        int drivingState0 = allocateActionSlot(0);
        (**(code **)(*drivingMap + 4))(10, drivingState0); // set size 10
        bindActionToButton(0x3210a0c6, drivingMap, 10);

        int drivingState1 = allocateActionSlot(0);
        (**(code **)(*drivingMap + 4))(8, drivingState1);
        bindActionToButton(0xec486385, drivingMap, 8);

        int drivingState2 = allocateActionSlot(0);
        (**(code **)(*drivingMap + 4))(0x10, drivingState2);
        bindActionToButton(0x9f425b6d, drivingMap, 0x10);

        int drivingState3 = allocateActionSlot(0);
        (**(code **)(*drivingMap + 4))(0x12, drivingState3);
        bindActionToButton(0xded909d6, drivingMap, 0x12);
    }

    // Add action mappings for Driving
    addActionMapping(0x66e0c2b3, drivingCtx);
    addActionMapping(0xb4a5136c, drivingCtx);
    addActionMapping(0xa08a43df, drivingCtx);
    addActionMapping(0x5855e99b, drivingCtx);

    if (drivingMap) {
        // More driving bindings
        int drivingState4 = allocateActionSlot(0);
        (**(code **)(*drivingMap + 4))(0xd, drivingState4);
        bindActionToButton(0x1d8e854d, drivingMap, 0xd);

        int drivingState5 = allocateActionSlot(0);
        (**(code **)(*drivingMap + 4))(0xc, drivingState5);
        bindActionToButton(0xc1e9c75, drivingMap, 0xc);
    }

    addActionMapping(0xf2448c6, drivingCtx);
    addActionMapping(0xc072d9d7, drivingCtx);
    addActionMapping(0x6af3511e, drivingCtx);
    addActionMapping(0xc9694699, drivingCtx);
    addActionMapping(0x5182bba0, drivingCtx);

    if (drivingMap) {
        // Additional driving state machine setup
        int extraState = createStateMachine(3, 0, &LAB_00690d20, 0, 3);
        (**(code **)(*drivingMap + 4))(0x15, extraState);
        bindActionToButton(0x5dd81de3, drivingMap, 0x15);
    }

    if (drivingCtx) {
        uint64 ctxState = getContextState();
        setStateMachine(ctxState, &LAB_00690dc0, 0);
        (**(code **)(*drivingCtx + 4))(0x10, ctxState);
        bindActionToButton(0x5dd81de3, drivingCtx, 0x10);
    }

    // Register default action IDs
    {
        int defaultAction1 = getDefaultAction1(); // FUN_0049a850
        (**(code **)(*drivingMap + 0x18))(0, defaultAction1); // vtable offset 0x18
        int defaultAction2 = getDefaultAction2(); // FUN_0049a860
        (**(code **)(*drivingMap + 0x18))(1, defaultAction2);
    }

    // Register action states for Driving context
    {
        int stateVal1 = getActionStateValue(global_drivingState, 0);
        (**(code **)(*drivingCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_drivingState, 0);
        (**(code **)(*drivingCtx + 0x18))(3, stateVal2);
    }

    // --- "MultiplayerDonsCamera" context ---
    ActionMap* mpDonsCamMap = createActionMap();
    ActionContext* mpDonsCamCtx = createActionContext("MultiplayerDonsCamera", 1);
    global_mpDonsCamMap = mpDonsCamMap; // DAT_01129c00
    global_mpDonsCamCtx = mpDonsCamCtx; // DAT_01129c04
    initContext(mpDonsCamMap, mpDonsCamCtx);

    if (mpDonsCamMap) {
        int state0 = allocateActionSlot(0);
        (**(code **)(*mpDonsCamMap + 4))(0xd, state0);
        bindActionToButton(0x1d8e854d, mpDonsCamMap, 0xd);
        int state1 = allocateActionSlot(0);
        (**(code **)(*mpDonsCamMap + 4))(0xc, state1);
        bindActionToButton(0xc1e9c75, mpDonsCamMap, 0xc);
    }

    addActionMapping(0xb14e178e, mpDonsCamCtx);
    addActionMapping(0x4296e28d, mpDonsCamCtx);
    addActionMapping(0x36d50d68, mpDonsCamCtx);
    addActionMapping(0x4238f65a, mpDonsCamCtx);

    if (mpDonsCamMap) {
        int state2 = allocateActionSlot(0);
        (**(code **)(*mpDonsCamMap + 4))(7, state2);
        bindActionToButton(0x424a9b6b, mpDonsCamMap, 7);
        int state3 = allocateActionSlot(0);
        (**(code **)(*mpDonsCamMap + 4))(5, state3);
        bindActionToButton(0x424a9b6c, mpDonsCamMap, 5);
        int state4 = allocateActionSlot(0);
        (**(code **)(*mpDonsCamMap + 4))(6, state4);
        bindActionToButton(0x424a9b6d, mpDonsCamMap, 6);
        int state5 = allocateActionSlot(0);
        (**(code **)(*mpDonsCamMap + 4))(4, state5);
        bindActionToButton(0x424a9b6e, mpDonsCamMap, 4);
    }

    // Register action states for MultiplayerDonsCamera
    {
        int stateVal1 = getActionStateValue(global_mpCamState, 0);
        (**(code **)(*mpDonsCamCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_mpCamState, 0);
        (**(code **)(*mpDonsCamCtx + 0x18))(3, stateVal2);
    }

    // --- "MultiplayerDonsFixedCamera" context ---
    ActionMap* mpDonsFixedMap = createActionMap();
    ActionContext* mpDonsFixedCtx = createActionContext("MultiplayerDonsFixedCamera", 1);
    global_mpDonsFixedMap = mpDonsFixedMap; // DAT_01129c08
    global_mpDonsFixedCtx = mpDonsFixedCtx; // DAT_01129c0c
    addActionMapping(0xc4417112, mpDonsFixedCtx);

    if (mpDonsFixedMap) {
        int state0 = allocateActionSlot(0);
        (**(code **)(*mpDonsFixedMap + 4))(0xd, state0);
        bindActionToButton(0x1d8e854d, mpDonsFixedMap, 0xd);
        int state1 = allocateActionSlot(0);
        (**(code **)(*mpDonsFixedMap + 4))(0xc, state1);
        bindActionToButton(0xc1e9c75, mpDonsFixedMap, 0xc);
        int state2 = allocateActionSlot(0);
        (**(code **)(*mpDonsFixedMap + 4))(4, state2);
        bindActionToButton(0xa08a43df, mpDonsFixedMap, 4);
    }

    // Register action states for MultiplayerDonsFixedCamera
    {
        int stateVal1 = getActionStateValue(global_mpFixedState, 0);
        (**(code **)(*mpDonsFixedCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_mpFixedState, 0);
        (**(code **)(*mpDonsFixedCtx + 0x18))(3, stateVal2);
    }

    // --- "MultiplayerDonsFollowCamera" context ---
    ActionMap* mpDonsFollowMap = createActionMap();
    ActionContext* mpDonsFollowCtx = createActionContext("MultiplayerDonsFollowCamera", 1);
    global_mpDonsFollowMap = mpDonsFollowMap; // DAT_01129c10
    global_mpDonsFollowCtx = mpDonsFollowCtx; // DAT_01129c14
    addActionMapping(0xc4417112, mpDonsFollowCtx);

    if (mpDonsFollowMap) {
        int state0 = allocateActionSlot(0);
        (**(code **)(*mpDonsFollowMap + 4))(0xd, state0);
        bindActionToButton(0x1d8e854d, mpDonsFollowMap, 0xd);
        int state1 = allocateActionSlot(0);
        (**(code **)(*mpDonsFollowMap + 4))(0xc, state1);
        bindActionToButton(0xc1e9c75, mpDonsFollowMap, 0xc);
    }

    // Register action states for MultiplayerDonsFollowCamera
    {
        int stateVal1 = getActionStateValue(global_mpFollowState, 0);
        (**(code **)(*mpDonsFollowCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_mpFollowState, 0);
        (**(code **)(*mpDonsFollowCtx + 0x18))(3, stateVal2);
    }

    // --- "Waypoint Wheel" context ---
    ActionMap* waypointWheelMap = createActionMap();
    ActionContext* waypointWheelCtx = createActionContext("Waypoint Wheel", 1);
    global_waypointWheelMap = waypointWheelMap; // DAT_01129c18
    global_waypointWheelCtx = waypointWheelCtx; // DAT_01129c1c
    initContext(waypointWheelMap, waypointWheelCtx);

    addActionMapping(0xb14e178e, waypointWheelCtx);

    if (waypointWheelMap) {
        int state0 = allocateActionSlot(0);
        (**(code **)(*waypointWheelMap + 4))(0xc, state0);
        bindActionToButton(0xc1e9c75, waypointWheelMap, 0xc);
        int state1 = allocateActionSlot(0);
        (**(code **)(*waypointWheelMap + 4))(0xd, state1);
        bindActionToButton(0x1d8e854d, waypointWheelMap, 0xd);
    }

    // Register action states for Waypoint Wheel
    {
        int stateVal1 = getActionStateValue(global_waypointState, 0);
        (**(code **)(*waypointWheelCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_waypointState, 0);
        (**(code **)(*waypointWheelCtx + 0x18))(3, stateVal2);
    }

    // --- "Face 2 Face" context ---
    ActionMap* f2fMap = createActionMap();
    ActionContext* f2fCtx = createActionContext("Face 2 Face", 1);
    global_f2fMap = f2fMap; // DAT_01129c28
    global_f2fCtx = f2fCtx; // DAT_01129c2c
    initContext(f2fMap, f2fCtx);

    int f2fStateMachine = createStateMachine(0, &LAB_00691a50, 0, 3);
    (**(code **)(*f2fMap + 4))(0x2a, f2fStateMachine);
    // Additional F2F state machine setup
    int f2fState0 = allocateActionSlot(0);
    (**(code **)(*f2fMap + 4))(0xd, f2fState0);
    bindActionToButton(0x1d8e854d, f2fMap, 0xd);

    addActionMapping(0x2938c6cc, f2fCtx);
    addActionMapping(0x3ddc7637, f2fCtx);

    int extraF2FState = createStateMachine(0, &LAB_00690ce0, 0, 3);
    (**(code **)(*f2fMap + 4))(0x20, extraF2FState);
    bindActionToButton(0xed41087b, f2fMap, 0x20);

    if (f2fCtx) {
        uint64 f2fCtxState = getContextState();
        setStateMachine(f2fCtxState, &LAB_00690d80, 0);
        (**(code **)(*f2fCtx + 4))(0x10, f2fCtxState);
        bindActionToButton(0xed41087b, f2fCtx, 0x10);
    }

    // Register action states for Face2Face
    {
        int stateVal1 = getActionStateValue(global_f2fState, 0);
        (**(code **)(*f2fCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_f2fState, 0);
        (**(code **)(*f2fCtx + 0x18))(3, stateVal2);
    }

    // --- "Face 2 Face Dialog" sub-context ---
    ActionMap* f2fDialogMap = createActionMap();
    ActionContext* f2fDialogCtx = createActionContext("Face 2 Face Dialog", 1);
    global_f2fDialogMap = f2fDialogMap; // DAT_01129c30
    global_f2fDialogCtx = f2fDialogCtx; // DAT_01129c34

    if (f2fDialogMap) {
        // Bind multiple dialog actions
        bindActionToKey(f2fDialogMap, 0xb0bda83a, 0x8c036aab);
        int state0 = allocateActionSlot(0);
        (**(code **)(*f2fDialogMap + 4))(0, state0);
        bindActionToButton(0xb0bda83a, f2fDialogMap, 0);
        bindActionToButton(0x8c036aab, f2fDialogMap, 0);

        bindActionToKey(f2fDialogMap, 0xe1fe5cc1, 0x46e7afe1);
        int state1 = allocateActionSlot(0);
        (**(code **)(*f2fDialogMap + 4))(1, state1);
        bindActionToButton(0xe1fe5cc1, f2fDialogMap, 1);
        bindActionToButton(0x46e7afe1, f2fDialogMap, 1);

        bindActionToKey(f2fDialogMap, 0x51374386, 0x1a271621);
        int state2 = allocateActionSlot(0);
        (**(code **)(*f2fDialogMap + 4))(2, state2);
        bindActionToButton(0x51374386, f2fDialogMap, 2);
        bindActionToButton(0x1a271621, f2fDialogMap, 2);

        bindActionToKey(f2fDialogMap, 0x923727fd, 0xd7d6fc22);
        int state3 = allocateActionSlot(0);
        (**(code **)(*f2fDialogMap + 4))(3, state3);
        bindActionToButton(0x923727fd, f2fDialogMap, 3);
        bindActionToButton(0xd7d6fc22, f2fDialogMap, 3);

        int stateD = allocateActionSlot(0);
        (**(code **)(*f2fDialogMap + 4))(0xd, stateD);
        bindActionToButton(0x1d8e854d, f2fDialogMap, 0xd);
    }

    // Register default actions for Face2Face dialog
    {
        int defaultAction1 = getDefaultAction1();
        (**(code **)(*f2fDialogMap + 0x18))(0, defaultAction1);
        int defaultAction2 = getDefaultAction2();
        (**(code **)(*f2fDialogMap + 0x18))(1, defaultAction2);
    }

    // --- "Front End" context ---
    ActionMap* frontEndMap = createActionMap();
    ActionContext* frontEndCtx = createActionContext("Front End", 1);
    global_frontEndMap = frontEndMap; // DAT_01129c20
    global_frontEndCtx = frontEndCtx; // DAT_01129c24

    // Set up front-end action slots with specific sizes
    int slot1 = allocateActionSlot(0xf); (**(code **)(*frontEndMap + 4))(0xc, slot1);
    int slot2 = allocateActionSlot(0x1e); (**(code **)(*frontEndMap + 4))(0x10, slot2);
    int slot3 = allocateActionSlot(0x20); (**(code **)(*frontEndMap + 4))(0x12, slot3);
    int slot4 = allocateActionSlot(0x11); (**(code **)(*frontEndMap + 4))(0x11, slot4);
    int slot5 = allocateActionSlot(0x1f); (**(code **)(*frontEndMap + 4))(0x13, slot5);
    // More front-end slots with specific bound values
    int slotA = allocateActionSlot(200); (**(code **)(*frontEndMap + 4))(0, slotA);
    int slotB = allocateActionSlot(0xd0); (**(code **)(*frontEndMap + 4))(1, slotB);
    int slotC = allocateActionSlot(0xcb); (**(code **)(*frontEndMap + 4))(2, slotC);
    int slotD = allocateActionSlot(0xcd); (**(code **)(*frontEndMap + 4))(3, slotD);
    int slotE = allocateActionSlot(0x33); (**(code **)(*frontEndMap + 4))(9, slotE);
    int slotF = allocateActionSlot(0x34); (**(code **)(*frontEndMap + 4))(0xb, slotF);
    int slotG = allocateActionRange(0x1c, 0x9c); (**(code **)(*frontEndMap + 4))(5, slotG);
    int slotH = allocateActionSlot(1); (**(code **)(*frontEndMap + 4))(7, slotH);
    int slotI = allocateActionRange(0x2d, 0x2f); (**(code **)(*frontEndMap + 4))(6, slotI);
    int slotJ = createActionWithFlags(0xd3, 0x53, &LAB_00690ac0, 0, 3); (**(code **)(*frontEndMap + 4))(0x15, slotJ);

    // --- "Pause Map" context ---
    ActionMap* pauseMapMap = createActionMap();
    ActionContext* pauseMapCtx = createActionContext("Pause Map", 1);
    global_pauseMapMap = pauseMapMap; // DAT_01129c38
    global_pauseMapCtx = pauseMapCtx; // DAT_01129c3c
    if (pauseMapMap) {
        int pauseSlot = allocateActionSlot(0);
        (**(code **)(*pauseMapMap + 4))(0xc, pauseSlot);
        bindActionToButton(0xc1e9c75, pauseMapMap, 0xc);
    }

    // Register actions for Pause Map
    int pauseSlot2 = allocateActionSlot(0x33); (**(code **)(*pauseMapMap + 4))(9, pauseSlot2);
    int pauseSlot3 = allocateActionSlot(0x34); (**(code **)(*pauseMapMap + 4))(0xb, pauseSlot3);
    int pauseSlot4 = allocateActionSlot(0); (**(code **)(*pauseMapMap + 4))(0x11, pauseSlot4);
    bindActionToButton(0x8c036aab, pauseMapMap, 0x11);
    int pauseSlot5 = allocateActionSlot(0); (**(code **)(*pauseMapMap + 4))(0x13, pauseSlot5);
    bindActionToButton(0x46e7afe1, pauseMapMap, 0x13);
    int pauseSlot6 = allocateActionSlot(0); (**(code **)(*pauseMapMap + 4))(0x10, pauseSlot6);
    bindActionToButton(0x1a271621, pauseMapMap, 0x10);
    int pauseSlot7 = allocateActionSlot(0); (**(code **)(*pauseMapMap + 4))(0x12, pauseSlot7);
    bindActionToButton(0xd7d6fc22, pauseMapMap, 0x12);
    int pauseSlot8 = allocateActionSlot(200); (**(code **)(*pauseMapMap + 4))(0, pauseSlot8);
    int pauseSlot9 = allocateActionSlot(0xd0); (**(code **)(*pauseMapMap + 4))(1, pauseSlot9);
    int pauseSlot10 = allocateActionSlot(0xcd); (**(code **)(*pauseMapMap + 4))(3, pauseSlot10);
    int pauseSlot11 = allocateActionSlot(0xcb); (**(code **)(*pauseMapMap + 4))(2, pauseSlot11);
    int pauseSlot12 = allocateActionSlot(1); (**(code **)(*pauseMapMap + 4))(7, pauseSlot12);
    int pauseSlot13 = createActionWithParams(0x39, 0x1c, 0x9c, 0, 0xff, 0, 0, 3); (**(code **)(*pauseMapMap + 4))(5, pauseSlot13);
    int pauseSlot14 = allocateActionSlot(0x10); (**(code **)(*pauseMapMap + 4))(4, pauseSlot14);
    int pauseSlot15 = allocateActionSlot(0x12); (**(code **)(*pauseMapMap + 4))(6, pauseSlot15);

    // Register default actions for Pause Map
    {
        int default1 = getDefaultAction1();
        (**(code **)(*pauseMapMap + 0x18))(0, default1);
        int default2 = getDefaultAction2();
        (**(code **)(*pauseMapMap + 0x18))(1, default2);
    }

    // Additional bindings for Pause Map
    int pauseSlot16 = allocateActionSlot(0); (**(code **)(*pauseMapMap + 4))(10, pauseSlot16);
    bindActionToButton(0x5d4e479f, pauseMapMap, 10);
    int pauseSlot17 = allocateActionSlot(0); (**(code **)(*pauseMapMap + 4))(8, pauseSlot17);
    bindActionToButton(0x388a33a7, pauseMapMap, 8);

    // Register action states for Pause Map context
    {
        int stateVal1 = getActionStateValue(global_pauseState, 0);
        (**(code **)(*pauseMapCtx + 0x18))(2, stateVal1);
        int stateVal2 = getActionStateValue2(global_pauseState, 0);
        (**(code **)(*pauseMapCtx + 0x18))(3, stateVal2);
    }

    // --- "In Game Video" context ---
    ActionMap* inGameVideoMap = createActionMap();
    ActionContext* inGameVideoCtx = createActionContext("In Game Video", 1);
    global_inGameVideoMap = inGameVideoMap; // DAT_01129c40
    global_inGameVideoCtx = inGameVideoCtx; // DAT_01129c44
    int videoSlot = createActionWithParams(1, 0x1c, 0x9c, 0, 0xff, 0, 0, 3);
    (**(code **)(*inGameVideoMap + 4))(5, videoSlot);

    // No return; function ends
}