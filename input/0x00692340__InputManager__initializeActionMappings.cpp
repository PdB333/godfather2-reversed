// FUNC_NAME: InputManager::initializeActionMappings
void InputManager::initializeActionMappings(void)

{
  int iVar1;
  int *handToHandManager;
  int *handToHandActionMap;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined1 *puStack_c4;
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  int *piStack_b4;
  undefined1 auStack_b0 [8];
  undefined1 auStack_a8 [8];
  undefined1 auStack_a0 [8];
  undefined8 uStack_98;
  undefined1 auStack_90 [8];
  char *pcStack_88;
  undefined1 auStack_84 [8];
  int *piStack_7c;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined8 uStack_6c;
  int *piStack_64;
  undefined8 uStack_60;
  int *piStack_58;
  undefined4 uStack_54;
  int *piStack_50;
  undefined8 uStack_4c;
  undefined8 uStack_44;
  undefined4 uStack_3c;
  int *piStack_38;
  undefined8 uStack_34;
  int *piStack_2c;
  undefined8 uStack_28;
  undefined1 auStack_20 [8];
  undefined4 uStack_18;
  
  uStack_18 = 0x69234b;
  handToHandManager = (int *)createActionManager(); // FUN_00499d60 - creates action manager
  uStack_18 = 1;
  auStack_20._4_4_ = "Hand to Hand";
  auStack_20._0_4_ = 0x692359;
  handToHandActionMap = (int *)createActionMap(); // FUN_00495d90 - creates action map
  uStack_18 = 0x69236f;
  DAT_01129bd8 = handToHandManager;
  DAT_01129bdc = handToHandActionMap;
  initializeActionMap(); // FUN_006905a0 - initializes the action map
  uStack_18 = 3;
  auStack_20._4_4_ = 0x692376;
  auStack_20._4_4_ = getActionMapName(); // FUN_00691a70 - gets action map name
  auStack_20._0_4_ = &LAB_00691a50;
  uStack_28._4_4_ = (int *)0x0;
  uStack_28._0_4_ = (int *)0x692383;
  join_0x00000008_0x00000000_ = createActionGroup(); // FUN_0049a700 - creates action group
  auStack_20._0_4_ = 0x2a; // 42 actions
  uStack_28._4_4_ = (int *)0x692393;
  (**(code **)(*handToHandManager + 4))(); // setActionCount
  uStack_28._0_4_ = (int *)0x692399;
  uStack_28._4_4_ = handToHandActionMap;
  setActionMapName(); // FUN_00691b50 - sets action map name
  piStack_2c = (int *)0x6367ea84;
  uStack_34._4_4_ = (int *)0x6923ab;
  uStack_28._0_4_ = handToHandActionMap;
  bindAction(); // FUN_00690530 - binds action to key
  uStack_28._4_4_ = (int *)0x64ce24d7;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6923c4;
  piStack_2c = handToHandManager;
  setActionKey(); // FUN_004979c0 - sets action key binding
  if (handToHandActionMap != (int *)0x0) {
    uStack_28._4_4_ = (int *)0x64ce24d7;
    uStack_28._0_4_ = (int *)0xed41087b;
    uStack_34._4_4_ = (int *)0x6923de;
    piStack_2c = handToHandActionMap;
    setActionKey();
  }
  uStack_28._4_4_ = (int *)0x657a83a5;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6923f4;
  piStack_2c = handToHandManager;
  setActionKey();
  if (handToHandActionMap != (int *)0x0) {
    uStack_28._4_4_ = (int *)0x657a83a5;
    uStack_28._0_4_ = (int *)0xed41087b;
    uStack_34._4_4_ = (int *)0x69240e;
    piStack_2c = handToHandActionMap;
    setActionKey();
  }
  uStack_28._4_4_ = (int *)0xa7879506;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692424;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0x776def75;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x69243a;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0x78467823;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692450;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0x17a26743;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692466;
  piStack_2c = handToHandManager;
  setActionKey();
  if (handToHandActionMap != (int *)0x0) {
    uStack_28._4_4_ = (int *)0x17a26743;
    uStack_28._0_4_ = (int *)0xed41087b;
    uStack_34._4_4_ = (int *)0x692480;
    piStack_2c = handToHandActionMap;
    setActionKey();
  }
  uStack_28._4_4_ = (int *)0xebc77d43;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692496;
  piStack_2c = handToHandManager;
  setActionKey();
  if (handToHandActionMap != (int *)0x0) {
    uStack_28._4_4_ = (int *)0xebc77d43;
    uStack_28._0_4_ = (int *)0xed41087b;
    uStack_34._4_4_ = (int *)0x6924b0;
    piStack_2c = handToHandActionMap;
    setActionKey();
  }
  uStack_28._4_4_ = (int *)0x6ef11ea8;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6924c6;
  piStack_2c = handToHandManager;
  setActionKey();
  if (handToHandActionMap != (int *)0x0) {
    uStack_28._4_4_ = (int *)0x6ef11ea8;
    uStack_28._0_4_ = (int *)0xed41087b;
    uStack_34._4_4_ = (int *)0x6924e0;
    piStack_2c = handToHandActionMap;
    setActionKey();
  }
  uStack_28._4_4_ = (int *)0xbe16155b;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6924f6;
  piStack_2c = handToHandManager;
  setActionKey();
  if (handToHandActionMap != (int *)0x0) {
    uStack_28._4_4_ = (int *)0xbe16155b;
    uStack_28._0_4_ = (int *)0xed41087b;
    uStack_34._4_4_ = (int *)0x692510;
    piStack_2c = handToHandActionMap;
    setActionKey();
  }
  uStack_28._4_4_ = (int *)0xc4aacd36;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692526;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd37;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x69253c;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd38;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692552;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd39;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692568;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd3a;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x69257e;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd3b;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x692594;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd3c;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6925aa;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd3d;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6925c0;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd3e;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6925d6;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0xc4aacd3f;
  uStack_28._0_4_ = (int *)0xed41087b;
  uStack_34._4_4_ = (int *)0x6925ec;
  piStack_2c = handToHandManager;
  setActionKey();
  uStack_28._4_4_ = (int *)0x3;
  uStack_28._0_4_ = (int *)0x0;
  piStack_2c = (int *)&LAB_00690ce0;
  uStack_34._4_4_ = (int *)0x0;
  uStack_34._0_4_ = (int *)0x692605;
  uStack_28 = createActionGroup();
  piStack_2c = (int *)0x20;
  uStack_34._4_4_ = (int *)0x692621;
  (**(code **)(*handToHandManager + 4))(); // setActionCount
  uStack_34._4_4_ = (int *)0x20;
  piStack_38 = (int *)0xed41087b;
  uStack_3c = 0x692634;
  uStack_34._0_4_ = handToHandManager;
  setActionKey();
  if (handToHandActionMap != (int *)0x0) {
    uStack_34._4_4_ = (int *)0x69263d;
    uVar5 = getActionMapName();
    uStack_34._4_4_ = (int *)0x0;
    piStack_38 = (int *)auStack_20;
    uStack_34._0_4_ = (int *)&LAB_00690d80;
    uStack_3c = 0x69265f;
    auStack_20 = (undefined1  [8])uVar5;
    setActionMapName();
    piStack_38 = (int *)0x10;
    uStack_3c = 0x692677;
    uStack_34 = auStack_20;
    (**(code **)(*handToHandActionMap + 4))(); // setActionCount
    uStack_34._4_4_ = (int *)0x10;
    piStack_38 = (int *)0xed41087b;
    uStack_3c = 0x69268a;
    uStack_34._0_4_ = handToHandActionMap;
    setActionKey();
  }
  uStack_34._0_4_ = (int *)0x2938c6cc;
  piStack_38 = (int *)0x69269c;
  uStack_34._4_4_ = handToHandActionMap;
  bindAction();
  uStack_3c = 0x3ddc7637;
  uStack_44._4_4_ = 0x6926ae;
  piStack_38 = handToHandActionMap;
  bindAction();
  iVar1 = *handToHandActionMap;
  uStack_34._4_4_ = (int *)0x0;
  uStack_34._0_4_ = (int *)_DAT_00d5ca64;
  piStack_38 = (int *)0x6926c7;
  uStack_34._4_4_ = (int *)getActionId(); // FUN_00496830
  uStack_34._0_4_ = (int *)0x2;
  piStack_38 = (int *)0x6926d3;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  piStack_38 = (int *)0x0;
  uStack_3c = _DAT_00d5ca64;
  uStack_44._4_4_ = 0x6926e9;
  piStack_38 = (int *)getActionId();
  uStack_3c = 3;
  uStack_44._4_4_ = 0x6926f5;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  
  // Weapon action map setup
  uStack_44._4_4_ = 0x6926fa;
  handToHandManager = (int *)createActionManager();
  uStack_44._4_4_ = 1;
  uStack_44._0_4_ = "Weapon";
  uStack_4c._4_4_ = (undefined1 *)0x692708;
  handToHandActionMap = (int *)createActionMap();
  uStack_44._4_4_ = 0x69271e;
  _DAT_01129be0 = handToHandManager;
  _DAT_01129be4 = handToHandActionMap;
  initializeActionMap();
  uStack_44._4_4_ = 3;
  uStack_44._0_4_ = "PhP\x1ai";
  uStack_44._0_4_ = (char *)getActionMapName();
  uStack_4c._4_4_ = &LAB_00691a50;
  uStack_4c._0_4_ = (int *)0x0;
  piStack_50 = (int *)0x692732;
  uStack_44 = createActionGroup();
  uStack_4c._4_4_ = (undefined1 *)0x2a;
  uStack_4c._0_4_ = (int *)0x692742;
  (**(code **)(*handToHandManager + 4))(); // setActionCount
  piStack_50 = (int *)0x692748;
  uStack_4c._0_4_ = handToHandActionMap;
  setActionMapName();
  uStack_54 = 0x62b07722;
  piStack_58 = (int *)0x69275a;
  piStack_50 = handToHandActionMap;
  bindAction();
  uStack_60._4_4_ = (int *)0xd177df7c;
  uStack_60._0_4_ = (char *)0x69276c;
  piStack_58 = handToHandActionMap;
  bindAction();
  piStack_64 = (int *)0x54a314df;
  uStack_6c._4_4_ = 0x69277e;
  uStack_60._0_4_ = (char *)handToHandActionMap;
  bindAction();
  iVar1 = *handToHandActionMap;
  uStack_4c._0_4_ = (int *)0x0;
  piStack_50 = (int *)_DAT_00d5ca64;
  uStack_54 = 0x692797;
  uStack_4c._0_4_ = (int *)getActionId();
  piStack_50 = (int *)0x2;
  uStack_54 = 0x6927a3;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  uStack_54 = 0;
  piStack_58 = (int *)_DAT_00d5ca64;
  uStack_60._4_4_ = (int *)0x6927b9;
  uStack_54 = getActionId();
  piStack_58 = (int *)0x3;
  uStack_60._4_4_ = (int *)0x6927c5;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  
  // Weapon Wheel - HandToHand
  uStack_60._4_4_ = (int *)0x6927ca;
  uVar4 = createActionManager();
  uStack_60._4_4_ = (int *)0x1;
  uStack_60._0_4_ = "Weapon Wheel - HandToHand";
  piStack_64 = (int *)0x6927d8;
  _DAT_01129bec = createActionMap();
  piStack_64 = (int *)0x3;
  uStack_70 = 0x6927ec;
  _DAT_01129be8 = uVar4;
  uStack_6c._0_4_ = (int *)uVar4;
  uStack_6c._4_4_ = _DAT_01129bec;
  initializeWeaponWheel(); // FUN_00692010
  uStack_70 = 0x6927f1;
  uVar4 = createActionManager();
  uStack_70 = 1;
  uStack_78._4_4_ = "Weapon Wheel - Weapon";
  uStack_78._0_4_ = (int *)0x6927ff;
  _DAT_01129bf4 = createActionMap();
  uStack_78._0_4_ = (int *)0x4;
  auStack_84._0_4_ = 0x692813;
  _DAT_01129bf0 = uVar4;
  auStack_84._4_4_ = uVar4;
  piStack_7c = (int *)_DAT_01129bf4;
  initializeWeaponWheel();
  
  // Driving action map
  auStack_84._0_4_ = 0x692818;
  handToHandManager = (int *)createActionManager();
  auStack_84._0_4_ = 1;
  pcStack_88 = "Driving";
  auStack_90._4_4_ = 0x692826;
  handToHandActionMap = (int *)createActionMap();
  _DAT_01129bf8 = handToHandManager;
  _DAT_01129bfc = handToHandActionMap;
  if (handToHandManager != (int *)0x0) {
    uStack_60._4_4_ = (int *)0x0;
    uStack_60._0_4_ = (char *)0x692846;
    uStack_60 = createActionGroup();
    piStack_64 = (int *)0xa;
    uStack_6c._4_4_ = 0x692856;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_6c._4_4_ = 10;
    uStack_70 = 0x3210a0c6;
    uStack_78._4_4_ = "j";
    uStack_6c._0_4_ = handToHandManager;
    setActionKey();
    uStack_6c._4_4_ = 0;
    uStack_6c._0_4_ = (int *)0x692870;
    uStack_6c = createActionGroup();
    uStack_70 = 8;
    uStack_78._4_4_ = (char *)0x692880;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_78._4_4_ = (char *)0x8;
    piStack_7c = (int *)0xec486385;
    auStack_84._4_4_ = 0x692893;
    uStack_78._0_4_ = handToHandManager;
    setActionKey();
    uStack_78._4_4_ = (char *)0x0;
    uStack_78._0_4_ = (int *)0x69289a;
    uStack_78 = createActionGroup();
    piStack_7c = (int *)0x10;
    auStack_84._4_4_ = 0x6928aa;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    auStack_84._4_4_ = 0x10;
    pcStack_88 = (char *)0x9f425b6d;
    auStack_90._4_4_ = 0x6928bd;
    auStack_84._0_4_ = handToHandManager;
    setActionKey();
    auStack_84._4_4_ = 0;
    auStack_84._0_4_ = 0x6928c4;
    auStack_84 = (undefined1  [8])createActionGroup();
    pcStack_88 = (char *)0x12;
    auStack_90._4_4_ = 0x6928d4;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_60._4_4_ = (int *)0x12;
    piStack_64 = (int *)0xded909d6;
    uStack_6c._4_4_ = 0x6928e7;
    uStack_60._0_4_ = (char *)handToHandManager;
    setActionKey();
  }
  uStack_60._0_4_ = (char *)0x66e0c2b3;
  piStack_64 = (int *)0x6928f9;
  uStack_60._4_4_ = handToHandActionMap;
  bindAction();
  uStack_6c._4_4_ = 0xb4a5136c;
  uStack_6c._0_4_ = (int *)0x69290b;
  piStack_64 = handToHandActionMap;
  bindAction();
  uStack_70 = 0xa08a43df;
  uStack_78._4_4_ = (char *)0x69291d;
  uStack_6c._0_4_ = handToHandActionMap;
  bindAction();
  uStack_78._0_4_ = (int *)0x5855e99b;
  piStack_7c = (int *)0x69292f;
  uStack_78._4_4_ = (char *)handToHandActionMap;
  bindAction();
  if (handToHandManager != (int *)0x0) {
    uStack_60._4_4_ = (int *)0x0;
    uStack_60._0_4_ = (char *)0x69293d;
    uStack_60 = createActionGroup();
    piStack_64 = (int *)0xd;
    uStack_6c._4_4_ = 0x69294d;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_6c._4_4_ = 0xd;
    uStack_70 = 0x1d8e854d;
    uStack_78._4_4_ = "j";
    uStack_6c._0_4_ = handToHandManager;
    setActionKey();
    uStack_6c._4_4_ = 0;
    uStack_6c._0_4_ = (int *)0x692967;
    uStack_6c = createActionGroup();
    uStack_70 = 0xc;
    uStack_78._4_4_ = (char *)0x692977;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_60._4_4_ = (int *)0xc;
    piStack_64 = (int *)0xc1e9c75;
    uStack_6c._4_4_ = 0x69298a;
    uStack_60._0_4_ = (char *)handToHandManager;
    setActionKey();
  }
  uStack_60._0_4_ = (char *)0xf2448c6;
  piStack_64 = (int *)0x692999;
  uStack_60._4_4_ = handToHandActionMap;
  bindAction();
  uStack_6c._4_4_ = 0xc072d9d7;
  uStack_6c._0_4_ = (int *)0x6929ab;
  piStack_64 = handToHandActionMap;
  bindAction();
  uStack_70 = 0x6af3511e;
  uStack_78._4_4_ = (char *)0x6929bd;
  uStack_6c._0_4_ = handToHandActionMap;
  bindAction();
  uStack_78._0_4_ = (int *)0xc9694699;
  piStack_7c = (int *)0x6929cf;
  uStack_78._4_4_ = (char *)handToHandActionMap;
  bindAction();
  auStack_84._4_4_ = 0x5182bba0;
  auStack_84._0_4_ = 0x6929e1;
  piStack_7c = handToHandActionMap;
  bindAction();
  if (handToHandManager != (int *)0x0) {
    uStack_60._4_4_ = (int *)0x3;
    uStack_60._0_4_ = (char *)0x0;
    piStack_64 = (int *)&LAB_00690d20;
    uStack_6c._4_4_ = 0;
    uStack_6c._0_4_ = (int *)0x692a01;
    uStack_60 = createActionGroup();
    piStack_64 = (int *)0x15;
    uStack_6c._4_4_ = 0x692a1d;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_60._4_4_ = (int *)0x15;
    piStack_64 = (int *)0x5dd81de3;
    uStack_6c._4_4_ = 0x692a30;
    uStack_60._0_4_ = (char *)handToHandManager;
    setActionKey();
  }
  if (handToHandActionMap != (int *)0x0) {
    uStack_60._4_4_ = (int *)0x692a39;
    uStack_4c = getActionMapName();
    uStack_60._4_4_ = (int *)0x0;
    piStack_64 = (int *)&uStack_4c;
    uStack_60._0_4_ = &LAB_00690dc0;
    uStack_6c._4_4_ = 0x692a5b;
    setActionMapName();
    piStack_64 = (int *)0x10;
    uStack_6c._4_4_ = 0x692a73;
    uStack_60 = uStack_4c;
    (**(code **)(*handToHandActionMap + 4))(); // setActionCount
    uStack_60._4_4_ = (int *)0x10;
    piStack_64 = (int *)0x5dd81de3;
    uStack_6c._4_4_ = 0x692a86;
    uStack_60._0_4_ = (char *)handToHandActionMap;
    setActionKey();
  }
  iVar1 = *handToHandManager;
  uStack_60._4_4_ = (int *)0x692a90;
  uStack_60._4_4_ = (int *)getDefaultActionId(); // FUN_0049a850
  uStack_60._0_4_ = (char *)0x0;
  piStack_64 = (int *)0x692a99;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandManager;
  piStack_64 = (int *)0x692aa3;
  piStack_64 = (int *)getDefaultActionId2(); // FUN_0049a860
  uStack_6c._4_4_ = 1;
  uStack_6c._0_4_ = (int *)0x692aac;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  uStack_6c._0_4_ = (int *)0x0;
  uStack_70 = _DAT_00d5ca1c;
  uStack_78._4_4_ = (char *)0x692ac2;
  uStack_6c._0_4_ = (int *)getActionId();
  uStack_70 = 2;
  uStack_78._4_4_ = (char *)0x692ace;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  uStack_78._4_4_ = (char *)0x0;
  uStack_78._0_4_ = (int *)DAT_00d5ca18;
  piStack_7c = (int *)0x692ae4;
  uStack_78._4_4_ = (char *)getActionId();
  uStack_78._0_4_ = (int *)0x3;
  piStack_7c = (int *)0x692af0;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  
  // MultiplayerDonsCamera action map
  piStack_7c = (int *)0x692af5;
  handToHandManager = (int *)createActionManager();
  piStack_7c = (int *)0x1;
  auStack_84._4_4_ = "MultiplayerDonsCamera";
  auStack_84._0_4_ = 0x692b03;
  handToHandActionMap = (int *)createActionMap();
  piStack_7c = (int *)0x692b19;
  _DAT_01129c00 = handToHandManager;
  _DAT_01129c04 = handToHandActionMap;
  initializeActionMap();
  if (handToHandManager != (int *)0x0) {
    piStack_7c = (int *)0x0;
    auStack_84._4_4_ = 0x692b24;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_84._0_4_ = 0xd;
    pcStack_88 = (char *)0x692b34;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    pcStack_88 = (char *)0xd;
    auStack_90._0_4_ = 0x1d8e854d;
    uStack_98._4_4_ = (int *)0x692b47;
    auStack_90._4_4_ = handToHandManager;
    setActionKey();
    pcStack_88 = (char *)0x0;
    auStack_90._4_4_ = 0x692b4e;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_90._0_4_ = 0xc;
    uStack_98._4_4_ = (int *)0x692b5e;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    piStack_7c = (int *)0xc;
    auStack_84._0_4_ = 0xc1e9c75;
    pcStack_88 = (char *)0x692b71;
    auStack_84._4_4_ = handToHandManager;
    setActionKey();
  }
  auStack_84._4_4_ = 0xb14e178e;
  auStack_84._0_4_ = 0x692b83;
  piStack_7c = handToHandActionMap;
  bindAction();
  pcStack_88 = (char *)0x4296e28d;
  auStack_90._4_4_ = 0x692b95;
  auStack_84._0_4_ = handToHandActionMap;
  bindAction();
  auStack_90._0_4_ = 0x36d50d68;
  uStack_98._4_4_ = (int *)0x692ba7;
  auStack_90._4_4_ = handToHandActionMap;
  bindAction();
  uStack_98._0_4_ = (int *)0x4238f65a;
  auStack_a0._4_4_ = 0x692bb9;
  uStack_98._4_4_ = handToHandActionMap;
  bindAction();
  if (handToHandManager != (int *)0x0) {
    piStack_7c = (int *)0x0;
    auStack_84._4_4_ = 0x692bcb;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_84._0_4_ = 7;
    pcStack_88 = (char *)0x692bdb;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    pcStack_88 = (char *)0x7;
    auStack_90._0_4_ = 0x424a9b6b;
    uStack_98._4_4_ = (int *)0x692bee;
    auStack_90._4_4_ = handToHandManager;
    setActionKey();
    pcStack_88 = (char *)0x0;
    auStack_90._4_4_ = 0x692bf5;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_90._0_4_ = 5;
    uStack_98._4_4_ = (int *)0x692c05;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_98._4_4_ = (int *)0x5;
    auStack_a0._4_4_ = 0x424a9b6c;
    auStack_a0._0_4_ = 0x692c18;
    uStack_98._0_4_ = handToHandManager;
    setActionKey();
    uStack_98._4_4_ = (int *)0x0;
    uStack_98._0_4_ = (int *)0x692c1f;
    uStack_98 = createActionGroup();
    auStack_a0._4_4_ = 6;
    auStack_a0._0_4_ = 0x692c2f;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    auStack_a0._0_4_ = 6;
    auStack_a8._0_4_ = 0x424a9b6d;
    auStack_b0._4_4_ = 0x692c42;
    auStack_a8._4_4_ = handToHandManager;
    setActionKey();
    auStack_a0._0_4_ = 0;
    auStack_a8._4_4_ = 0x692c49;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_a8._0_4_ = 4;
    auStack_b0._4_4_ = 0x692c59;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    piStack_7c = (int *)0x4;
    auStack_84._0_4_ = 0x424a9b6e;
    pcStack_88 = (char *)0x692c6c;
    auStack_84._4_4_ = handToHandManager;
    setActionKey();
  }
  iVar1 = *handToHandActionMap;
  piStack_7c = (int *)0x0;
  auStack_84._4_4_ = _DAT_00d5c9fc;
  auStack_84._0_4_ = 0x692c82;
  piStack_7c = (int *)getActionId();
  auStack_84._4_4_ = 2;
  auStack_84._0_4_ = 0x692c8e;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  auStack_84._0_4_ = 0;
  pcStack_88 = (char *)_DAT_00d5c9fc;
  auStack_90._4_4_ = 0x692ca4;
  auStack_84._0_4_ = getActionId();
  pcStack_88 = (char *)0x3;
  auStack_90._4_4_ = 0x692cb0;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  
  // MultiplayerDonsFixedCamera action map
  auStack_90._4_4_ = 0x692cb5;
  handToHandManager = (int *)createActionManager();
  auStack_90._4_4_ = 1;
  auStack_90._0_4_ = "MultiplayerDonsFixedCamera";
  uStack_98._4_4_ = (int *)0x692cc3;
  handToHandActionMap = (int *)createActionMap();
  uStack_98._0_4_ = (int *)0xc4417112;
  auStack_a0._4_4_ = 0x692ce3;
  _DAT_01129c08 = handToHandManager;
  _DAT_01129c0c = handToHandActionMap;
  uStack_98._4_4_ = handToHandActionMap;
  bindAction();
  if (handToHandManager != (int *)0x0) {
    auStack_90._4_4_ = 0;
    auStack_90._0_4_ = 0x692cf1;
    auStack_90 = (undefined1  [8])createActionGroup();
    uStack_98._4_4_ = (int *)0xd;
    uStack_98._0_4_ = (int *)0x692d01;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_98._0_4_ = (int *)0xd;
    auStack_a0._0_4_ = 0x1d8e854d;
    auStack_a8._4_4_ = 0x692d14;
    auStack_a0._4_4_ = handToHandManager;
    setActionKey();
    uStack_98._0_4_ = (int *)0x0;
    auStack_a0._4_4_ = 0x692d1b;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_a0._0_4_ = 0xc;
    auStack_a8._4_4_ = 0x692d2b;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    auStack_a8._4_4_ = 0xc;
    auStack_b0._4_4_ = 0xc1e9c75;
    auStack_b0._0_4_ = 0x692d3e;
    auStack_a8._0_4_ = handToHandManager;
    setActionKey();
    auStack_a8._4_4_ = 0;
    auStack_a8._0_4_ = 0x692d45;
    auStack_a8 = (undefined1  [8])createActionGroup();
    auStack_b0._4_4_ = 4;
    auStack_b0._0_4_ = 0x692d55;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    auStack_90._4_4_ = 4;
    uStack_98._4_4_ = (int *)0xa08a43df;
    uStack_98._0_4_ = (int *)0x692d68;
    auStack_90._0_4_ = handToHandManager;
    setActionKey();
  }
  iVar1 = *handToHandActionMap;
  auStack_90._4_4_ = 0;
  auStack_90._0_4_ = _DAT_00d5c9fc;
  uStack_98._4_4_ = (int *)0x692d7e;
  auStack_90._4_4_ = getActionId();
  auStack_90._0_4_ = 2;
  uStack_98._4_4_ = (int *)0x692d8a;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  uStack_98._4_4_ = (int *)0x0;
  uStack_98._0_4_ = (int *)_DAT_00d5c9fc;
  auStack_a0._4_4_ = 0x692da0;
  uStack_98._4_4_ = (int *)getActionId();
  uStack_98._0_4_ = (int *)0x3;
  auStack_a0._4_4_ = 0x692dac;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  
  // MultiplayerDonsFollowCamera action map
  auStack_a0._4_4_ = 0x692db1;
  handToHandManager = (int *)createActionManager();
  auStack_a0._4_4_ = 1;
  auStack_a0._0_4_ = "MultiplayerDonsFollowCamera";
  auStack_a8._4_4_ = 0x692dbf;
  handToHandActionMap = (int *)createActionMap();
  auStack_a8._0_4_ = 0xc4417112;
  auStack_b0._4_4_ = 0x692ddf;
  _DAT_01129c10 = handToHandManager;
  _DAT_01129c14 = handToHandActionMap;
  auStack_a8._4_4_ = handToHandActionMap;
  bindAction();
  if (handToHandManager != (int *)0x0) {
    auStack_a0._4_4_ = 0;
    auStack_a0._0_4_ = 0x692ded;
    auStack_a0 = (undefined1  [8])createActionGroup();
    auStack_a8._4_4_ = 0xd;
    auStack_a8._0_4_ = 0x692dfd;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    auStack_a8._0_4_ = 0xd;
    auStack_b0._0_4_ = 0x1d8e854d;
    piStack_b4 = (int *)0x692e10;
    auStack_b0._4_4_ = handToHandManager;
    setActionKey();
    auStack_a8._0_4_ = 0;
    auStack_b0._4_4_ = 0x692e17;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_b0._0_4_ = 0xc;
    piStack_b4 = (int *)0x692e27;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    auStack_a0._4_4_ = 0xc;
    auStack_a8._4_4_ = 0xc1e9c75;
    auStack_a8._0_4_ = 0x692e3a;
    auStack_a0._0_4_ = handToHandManager;
    setActionKey();
  }
  iVar1 = *handToHandActionMap;
  auStack_a0._4_4_ = 0;
  auStack_a0._0_4_ = _DAT_00d5ca64;
  auStack_a8._4_4_ = 0x692e50;
  auStack_a0._4_4_ = getActionId();
  auStack_a0._0_4_ = 2;
  auStack_a8._4_4_ = 0x692e5c;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  auStack_a8._4_4_ = 0;
  auStack_a8._0_4_ = _DAT_00d5ca64;
  auStack_b0._4_4_ = 0x692e72;
  auStack_a8._4_4_ = getActionId();
  auStack_a8._0_4_ = 3;
  auStack_b0._4_4_ = 0x692e7e;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  
  // Waypoint Wheel action map
  auStack_b0._4_4_ = 0x692e83;
  handToHandManager = (int *)createActionManager();
  auStack_b0._4_4_ = 1;
  auStack_b0._0_4_ = "Waypoint Wheel";
  piStack_b4 = (int *)0x692e91;
  handToHandActionMap = (int *)createActionMap();
  piStack_b4 = (int *)0x692ea4;
  _DAT_01129c18 = handToHandManager;
  _DAT_01129c1c = handToHandActionMap;
  initializeActionMap();
  uStack_b8 = 0xb14e178e;
  auStack_c0._4_4_ = 0x692eb6;
  piStack_b4 = handToHandActionMap;
  bindAction();
  if (handToHandManager != (int *)0x0) {
    auStack_b0._4_4_ = 0;
    auStack_b0._0_4_ = 0x692ec4;
    auStack_b0 = (undefined1  [8])createActionGroup();
    piStack_b4 = (int *)0xc;
    uStack_b8 = 0x692ed4;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    uStack_b8 = 0xc;
    auStack_c0._0_4_ = 0xc1e9c75;
    puStack_c4 = (undefined1 *)0x692ee7;
    auStack_c0._4_4_ = handToHandManager;
    setActionKey();
    uStack_b8 = 0;
    auStack_c0._4_4_ = 0x692eee;
    join_0x00000008_0x00000000_ = createActionGroup();
    auStack_c0._0_4_ = 0xd;
    puStack_c4 = (undefined1 *)0x692efe;
    (**(code **)(*handToHandManager + 4))(); // setActionCount
    auStack_b0._4_4_ = 0xd;
    piStack_b4 = (int *)0x1d8e854d;
    uStack_b8 = 0x692f11;
    auStack_b0._0_4_ = handToHandManager;
    setActionKey();
  }
  iVar1 = *handToHandActionMap;
  auStack_b0._4_4_ = 0;
  auStack_b0._0_4_ = _DAT_00d5c968;
  piStack_b4 = (int *)0x692f27;
  auStack_b0._4_4_ = getActionId();
  auStack_b0._0_4_ = 2;
  piStack_b4 = (int *)0x692f33;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  iVar1 = *handToHandActionMap;
  piStack_b4 = (int *)0x0;
  uStack_b8 = _DAT_00d5c968;
  auStack_c0._4_4_ = 0x692f49;
  piStack_b4 = (int *)getActionId();
  uStack_b8 = 3;
  auStack_c0._4_4_ = 0x692f55;
  (**(code **)(iVar1 + 0x18))(); // setActionMapping
  
  // Face 2 Face action map
  auStack_c0._4_4_ = 0x692f5a;
  handToHandManager = (int *)createActionManager();
  auStack_c0._4_4_ = 1;
  auStack_c0._0_4_ = "Face 2 Face";
  puStack_c4 = (undefined1 *)0x692f68;
  handToHandActionMap = (int *)createActionMap();
  auStack_c0._4_4_ = 0x692f7e;
  _DAT_01129c28 = handToHandManager;
  _DAT_01129c2c = handToHandActionMap;
  initializeActionMap();
  auStack_c0._4_4_ = 3;
  auStack_c0._0_4_ = 0x692f85;
  auStack_c0._0_4_ = getActionMapName();
  puStack_c4 = &LAB_00691a50;
  uStack_c8 = 0;
  auStack_d0._4_4_ = 0x692f92;
  auStack_c0 = (undefined1  [8])createActionGroup();
  puStack_c4 = (undefined1 *)0x2a;
  uStack_c8 = 0x692fa2;
  (**(code **)(*handToHandManager + 4))(); // setActionCount
  uStack_c8 = 0;
  auStack_d0._4_4_ = 0x692fa9;
  join_0x00000008_0x00000000_ = createActionGroup();
  auStack_d0._0_4_ = 0xd;
  (**(code **)(*handToHandManager + 4))(); // setActionCount
  setActionKey(0x1d8e854d,handToHandManager,0xd);
  bindAction(0x2938c6cc,handToHandActionMap);
  bindAction(0x3ddc7637,handToHandActionMap);
  uVar5 = createActionGroup(0,&LAB_00690ce0,0,3);
  (**(code **)(*handToHandManager + 4))(0x20,uVar5);
  setActionKey(0xed41087b,handToHandManager,0x20);
  if (handToHandActionMap != (int *)0x0) {
    uVar5 = getActionMapName();
    auStack_d0 = (undefined1  [8])uVar5;
    setActionMapName(auStack_d0,&LAB_00690d80,0);
    (**(code **)(*handToHandActionMap + 4))(0x10,auStack_d0);
    setActionKey(0xed41087b,handToHandActionMap,0x10);
  }
  iVar1 = *handToHandActionMap;
  uVar4 = getActionId(_DAT_00d5ca64,0);
  (**(code **)(iVar1 + 0x18))(2,uVar4);
  iVar1 = *handToHandActionMap;
  uVar4 = getActionId(_DAT_00d5ca64,0);
  (**(code **)(iVar1 + 0x18))(3,uVar4);
  handToHandManager = (int *)createActionManager();
  _DAT_01129c34 = createActionMap("Face 2 Face Dialog",1);
  _DAT_01129c30 = handToHandManager;
  if (handToHandManager != (int *)0x0) {
    setActionKey(handToHandManager,0xb0bda83a,0x8c036aab);
    uVar5 = createActionGroup(0);
    (**(code **)(*handToHandManager + 4))(0,uVar5);
    setActionKey(0xb0bda83a,handToHandManager,0);
    setActionKey(0x8c036aab,handToHandManager,0);
    setActionKey(handToHandManager,0xe1fe5cc1,0x46e7afe1);
    uVar5 = createActionGroup(0);
    (**(code **)(*handToHandManager + 4))(1,uVar5);
    setActionKey(0xe1fe5cc1,handToHandManager,1);
    setActionKey(0x46e7afe1,handToHandManager,1);
    setActionKey(handToHandManager,0x51374386,0x1a271621);
    uVar5 = createActionGroup(0);
    (**(code **)(*handToHandManager + 4))(2,uVar5);
    setActionKey(0x51374386,handToHandManager,2);
    setActionKey(0x1a271621,handToHandManager,2);
    setActionKey(handToHandManager,0x923727fd,0xd7d6fc22);
    uVar5 = createActionGroup(0);
    (**(code **)(*handToHandManager + 4))(3,uVar5);
    setActionKey(0x923727fd,handToHandManager,3);
    setActionKey(0xd7d6fc22,handToHandManager,3);
    uVar5 = createActionGroup(0);
    (**(code **)(*handToHandManager + 4))(0xd,uVar5);
    setActionKey(0x1d8e854d,handToHandManager,0xd);
  }
  iVar1 = *handToHandManager;
  uVar4 = getDefaultActionId();
  (**(code **)(iVar1 + 0x18))(0,uVar4);
  iVar1 = *handToHandManager;
  uVar4 = getDefaultActionId2();
  (**(code **)(iVar1 + 0x18))(1,uVar4);
  handToHandManager = (int *)createActionManager();
  _DAT_01129c24 = createActionMap("Front End",1);
  iVar1 = *handToHandManager;
  _DAT_01129c20 = handToHandManager;
  uVar5 = createActionGroup(0xf);
  (**(code **)(iVar1 + 4))(0xc,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x1e);
  (**(code **)(iVar1 + 4))(0x10,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x20);
  (**(code **)(iVar1 + 4))(0x12,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x11);
  (**(code **)(iVar1 + 4))(0x11,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x1f);
  (**(code **)(iVar1 + 4))(0x13,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(200);
  (**(code **)(iVar1 + 4))(0,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0xd0);
  (**(code **)(iVar1 + 4))(1,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0xcb);
  (**(code **)(iVar1 + 4))(2,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0xcd);
  (**(code **)(iVar1 + 4))(3,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x33);
  (**(code **)(iVar1 + 4))(9,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x34);
  (**(code **)(iVar1 + 4))(0xb,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroupWithRange(0x1c,0x9c);
  (**(code **)(iVar1 + 4))(5,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(1);
  (**(code **)(iVar1 + 4))(7,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroupWithRange(0x2d,0x2f);
  (**(code **)(iVar1 + 4))(6,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroupWithCallback(0xd3,0x53,&LAB_00690ac0,0,3);
  (**(code **)(iVar1 + 4))(0x15,uVar5);
  
  // Pause Map action map
  handToHandManager = (int *)createActionManager();
  handToHandActionMap = (int *)createActionMap("Pause Map",1);
  _DAT_01129c38 = handToHandManager;
  _DAT_01129c3c = handToHandActionMap;
  if (handToHandManager != (int *)0x0) {
    uVar5 = createActionGroup(0);
    (**(code **)(*handToHandManager + 4))(0xc,uVar5);
    setActionKey(0xc1e9c75,handToHandManager,0xc);
  }
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x33);
  (**(code **)(iVar1 + 4))(9,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x34);
  (**(code **)(iVar1 + 4))(0xb,uVar5);
  uVar5 = createActionGroup(0);
  (**(code **)(*handToHandManager + 4))(0x11,uVar5);
  setActionKey(0x8c036aab,handToHandManager,0x11);
  uVar5 = createActionGroup(0);
  (**(code **)(*handToHandManager + 4))(0x13,uVar5);
  setActionKey(0x46e7afe1,handToHandManager,0x13);
  uVar5 = createActionGroup(0);
  (**(code **)(*handToHandManager + 4))(0x10,uVar5);
  setActionKey(0x1a271621,handToHandManager,0x10);
  uVar5 = createActionGroup(0);
  (**(code **)(*handToHandManager + 4))(0x12,uVar5);
  setActionKey(0xd7d6fc22,handToHandManager,0x12);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(200);
  (**(code **)(iVar1 + 4))(0,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0xd0);
  (**(code **)(iVar1 + 4))(1,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0xcd);
  (**(code **)(iVar1 + 4))(3,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0xcb);
  (**(code **)(iVar1 + 4))(2,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(1);
  (**(code **)(iVar1 + 4))(7,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroupWithColor(0x39,0x1c,0x9c,0,0xff,0,0,3);
  (**(code **)(iVar1 + 4))(5,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x10);
  (**(code **)(iVar1 + 4))(4,uVar5);
  iVar1 = *handToHandManager;
  uVar5 = createActionGroup(0x12);
  (**(code **)(iVar1 + 4))(6,uVar5);
  iVar1 = *handToHandManager;
  uVar4 = getDefaultActionId();
  (**(code **)(iVar1 + 0x18))(0,uVar4);
  iVar1 = *handToHandManager;
  uVar4 = getDefaultActionId2();
  (**(code **)(iVar1 + 0x18))(1,uVar4);
  uVar5 = createActionGroup(0);
  (**(code **)(*handToHandManager + 4))(10,uVar5);
  setActionKey(0x5d4e479f,handToHandManager,10);
  uVar5 = createActionGroup(0);
  (**(code **)(*handToHandManager + 4))(8,uVar5);
  setActionKey(0x388a33a7,handToHandManager,8);
  iVar1 = *handToHandActionMap;
  uVar4 = getActionId(DAT_00d5779c,0);
  (**(code **)(iVar1 + 0x18))(2,uVar4);
  iVar1 = *handToHandActionMap;
  uVar4 = getActionId(DAT_00d5779c,0);
  (**(code **)(iVar1 + 0x18))(3,uVar4);
  
  // In Game Video action map
  handToHandManager = (int *)createActionManager();
  _DAT_01129c44 = createActionMap("In Game Video",1);
  iVar1 = *handToHandManager;
  _DAT_01129c40 = handToHandManager;
  uVar5 = createActionGroupWithColor(1,0x1c,0x9c,0,0xff,0,0,3);
  (**(code **)(iVar1 + 4))(5,uVar5);
  return;
}