// Xbox PDB: EARS_Apt_UIFrontend_ShowLoadFailedPopup
// FUNC_NAME: GameUIManager::showPauseOrRetryScreen
// Function address: 0x00933c30
// This function initializes and displays a pause/retry dialog (used for multiplayer or single-player pause menu).
// It checks global flags for online saved game not loaded, allocates a menu object, sets up button text accordingly,
// and attaches a callback (if provided) for post-initialization actions.

void __thiscall GameUIManager::showPauseOrRetryScreen(void* this, char isRetry)
{
  int menuObj;
  char* textKey;
  int textParam;
  undefined1* callback;
  code* callbackFunc;

  // Initialize the parent (this) object – likely a screen or menu manager.
  FUN_004d3bc0(this);

  // If the global "online saved game not loaded" flag is set and conditions are met, display warning.
  if (((DAT_01130590 & 0x402) != 0) ||
     (((DAT_01223484 != 0 &&
       (*(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0)) &&
      (DAT_01223484 != -0x28)))) {
    FUN_004d4300(" $mp_online_saved_game_not_loaded");
  }

  // Allocate a new menu object (0xF0 bytes).
  menuObj = FUN_009c8e50(0xf0);
  if (menuObj == 0) {
    menuObj = 0;
  }
  else {
    // Call constructor on the allocated memory.
    menuObj = FUN_00982280(0);
  }

  // Initialize field at +0x0C (likely a flag or counter) to 0.
  *(undefined4 *)(menuObj + 0xc) = 0;

  // If no callback was provided, use default string.
  callback = local_10;
  if (local_10 == (undefined1 *)0x0) {
    callback = &DAT_0120546e; // global default string
  }
  FUN_00981eb0(callback); // set up some resource/string

  // Choose button text and parameter based on isRetry flag.
  if (isRetry == '\0') {
    textParam = 0xffffffff;
    textKey = "$pause_button_continue";
  }
  else {
    textParam = 0;
    textKey = "$fe_main_retry";
  }
  FUN_00981e70(textKey, 1, textParam); // set button text with localized string

  // Store a function pointer (likely a VTable or callback) at +0x14.
  *(undefined1 **)(menuObj + 0x14) = &LAB_00932a20;

  // Render/update the UI (maybe redraw or activate).
  FUN_00982e10();

  // If a callback was originally provided, invoke it.
  if (local_10 != (undefined1 *)0x0) {
    (*local_4)(local_10);
  }
  return;
}