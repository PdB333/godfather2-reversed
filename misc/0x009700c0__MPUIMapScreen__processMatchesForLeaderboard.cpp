// FUNC_NAME: MPUIMapScreen::processMatchesForLeaderboard
void __fastcall MPUIMapScreen::processMatchesForLeaderboard(int thisPtr)
{
  int iVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined8 uVar7;
  uint local_1c;
  undefined8 local_10;
  
  local_10 = CONCAT44(local_10._4_4_,(undefined4)local_10);
  if (((DAT_0112b9b4 != 0) &&
      (iVar5 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *(int *)(DAT_0112b9b4 + 0x34) * 4),
      local_10 = CONCAT44(local_10._4_4_,(undefined4)local_10), *(int *)(thisPtr + 0x17c) != 0)) &&
     (local_10 = CONCAT44(local_10._4_4_,(undefined4)local_10), iVar5 != 0)) {
    // Sort leaderboard entries if more than 1
    if (1 < *(uint *)(thisPtr + 0x17c)) {
      _qsort(*(void **)(thisPtr + 0x178), *(uint *)(thisPtr + 0x17c), 4,
             (_PtFuncCompare *)&LAB_00963510);  // comparison function
    }
    local_1c = 0;
    if (*(int *)(thisPtr + 0x17c) != 0) {
      do {
        uVar3 = FUN_00964d50(*(int *)(*(int *)(thisPtr + 0x178) + local_1c * 4) + 0x4d);  // get something from match info
        if (uVar3 == 0) {
          DAT_011307fc = uVar3;  // unknown global
          FUN_009c8f10(DAT_011307f8);  // free something
          DAT_011307f8 = 0;
          DAT_01130800 = 0;
          iVar4 = FUN_00963f80(*(undefined4 *)(*(int *)(local_1c * 4 + *(int *)(thisPtr + 0x178)) + 0x10));  // get leaderboard data
          if (iVar4 != 0) {
            uVar3 = *(uint *)(iVar4 + 8);
            uVar6 = 0;
            if (uVar3 != 0) {
              do {
                iVar1 = *(int *)(*(int *)(iVar4 + 4) + uVar6 * 4);
                if (iVar1 != 0) {
                  uVar7 = FUN_0095c290(iVar1 + 0x17c, iVar1 + 0x180);  // create pair
                  local_10 = uVar7;
                  FUN_0095e000(&local_10);  // process pair
                }
                uVar6 = uVar6 + 1;
              } while (uVar6 < uVar3);
            }
          }
          iVar4 = *(int *)(*(int *)(thisPtr + 0x178) + local_1c * 4);
          if (*(uint *)(iVar4 + 8) < DAT_011307fc) {
            cVar2 = FUN_00962d10(*(undefined4 *)(iVar5 + 0x34), *(undefined4 *)(iVar4 + 0x14));  // check match rank
            if (cVar2 != '\0') {
              iVar5 = *(int *)(*(int *)(thisPtr + 0x178) + local_1c * 4);
              *(undefined4 *)(thisPtr + 0x19c) = *(undefined4 *)(iVar5 + 0x100);  // +0x100 = player name
              *(undefined4 *)(thisPtr + 0x1a0) = *(undefined4 *)(iVar5 + 0xfc);   // +0xfc = player score
              *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) | 2;        // +0x6f4 = flags (bit 1 = showing leaderboard)
              FUN_0096f920(*(undefined4 *)(thisPtr + 0x1a0), *(undefined4 *)(thisPtr + 0x19c));  // update leaderboard display
              *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xffffefff;
              return;
            }
          }
        }
        local_1c = local_1c + 1;
      } while (local_1c < *(uint *)(thisPtr + 0x17c));
    }
  }
  // No match found - show "no matches found" menu
  iVar5 = FUN_009c8e50(0xf0);  // allocate menu object
  if (iVar5 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = FUN_00982280(0);  // initialize menu
  }
  FUN_00981eb0("$mp_no_matches_found");  // load localization string
  *(undefined4 *)(iVar5 + 0xc) = 3;     // +0xc = menu type (3 = info dialog)
  *(code **)(iVar5 + 0x14) = FUN_00982b30;  // +0x14 = callback function
  FUN_00982e10();  // show menu
  FUN_0096a1e0();  // play UI sound
  FUN_00970400(0); // reset something
  FUN_005a04a0("ShowMenu", 0, &DAT_00d8cdec, 0);  // show the menu via Lua
  FUN_005a04a0("HighlightSelected", 0, &DAT_00d8cdec, 0);  // highlight current selection
  *(undefined4 *)(DAT_0112b9b4 + 0x34) = 0xffffffff;  // clear player index
  *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xffffefff;
  return;
}