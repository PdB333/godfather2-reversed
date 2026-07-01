// FUNC_NAME: MultiplayerDonUI::setupDonLobbyScreen
void MultiplayerDonUI::setupDonLobbyScreen(void)
{
  int *vtable;
  int result[3];
  code *callback;
  
  vtable = DAT_01130048;  // some vtable pointer, e.g., UI framework
  
  FUN_004d3bc0("$mp_online_sort_method");  // localized string lookup
  FUN_004d3e20(result);  // get UI element handle or callback
  if (result[0] != 0) {
    (*callback)(result[0]);  // invoke callback if valid
  }
  
  FUN_00986250(5);  // set number of sort methods / options (5)
  FUN_004d3bc0("$mp_online_donlobby_title_host");  // "Host"
  FUN_00986550(0);  // set option 0
  FUN_004d3bc0("$mp_online_join_in");  // "Join In"
  FUN_00986550(1);  // set option 1
  FUN_004d3bc0("$mp_online_join_max");  // "Max Players"
  FUN_00986550(2);  // set option 2
  FUN_004d3bc0("$mp_online_game_mode");  // "Game Mode"
  FUN_00986550(3);  // set option 3
  FUN_004d3bc0("$mp_online_map");  // "Map"
  FUN_00986550(4);  // set option 4
  
  FUN_00986240(*(undefined4 *)(DAT_01129930 + 0x110));  // set current selection from some state
                    /* WARNING: Could not recover jumptable at 0x00966085. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*vtable + 0x28))();  // call virtual function at vtable+0x28, likely update UI
  return;
}