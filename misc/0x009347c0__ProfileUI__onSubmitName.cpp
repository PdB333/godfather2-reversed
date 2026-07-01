// FUNC_NAME: ProfileUI::onSubmitName
void ProfileUI::onSubmitName(int *param_1)
{
  char cVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  int aiStack_30 [3];
  code *pcStack_24;
  undefined2 *puStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  code *pcStack_14;
  int aiStack_10 [3];
  code *pcStack_4;
  
  // Call virtual function at vtable+0x2c (likely onSubmit or similar)
  (**(code **)(*param_1 + 0x2c))();

  // Get profile name string from this+0x1c->+0x10
  pcVar7 = *(char **)(param_1[0x1c] + 0x10);
  if (pcVar7 == (char *)0x0) {
    pcVar7 = &DAT_0120546e; // empty string constant
  }

  iVar5 = 0;
  pcVar6 = pcVar7;
  if (*pcVar7 != '\0') {
    // Count words in the name string
    do {
      iVar2 = _isspace((int)*pcVar6);
      if (iVar2 == 0) {
        iVar5 = iVar5 + 1;
      }
      pcVar6 = pcVar6 + 1;
    } while (*pcVar6 != '\0');

    // If there is at least one word (non-whitespace), check if name is valid
    if (iVar5 != 0) {
      cVar1 = FUN_00698a40(pcVar7); // IsAlphaNumeric check
      if (cVar1 != '\0') {
        // Name is valid alphanumeric
        // Parse the name string into some internal representation
        puStack_20 = (undefined2 *)0x0;
        uStack_18 = 0;
        uStack_1c = 0;
        FUN_004d3bc0(pcVar7); // likely ConvertStringToWide or ParseToken
        FUN_004dd9e0(aiStack_10, &puStack_20); // possibly Tokenize or AllocateWide
        if (aiStack_10[0] != 0) {
          (*pcStack_4)(aiStack_10[0]); // deallocator
        }

        puVar3 = puStack_20;
        if (puStack_20 == (undefined2 *)0x0) {
          puVar3 = &DAT_00e2df14; // fallback
        }
        FUN_0069aa10(puVar3); // SetProfileName or similar

        // Update player count: global = number of connected players - 1
        DAT_0113058c = *(ushort *)(DAT_0113056c + 4) - 1;

        FUN_006989e0(); // Refresh/update UI

        // Reset RNG seed? (stack array as RNG context)
        aiStack_30[0] = 0;
        aiStack_30[2] = 0;
        aiStack_30[1] = 0;

        uVar4 = FUN_00699280(aiStack_30); // Generate random number or seed
        cVar1 = FUN_009341d0(uVar4); // Check if valid
        if (cVar1 != '\0') {
          uVar4 = FUN_006987c0(aiStack_30); // Another random call
          cVar1 = FUN_009341d0(uVar4);
          if (cVar1 != '\0') {
            // Proceed with joining/creating game
            FUN_006a0580(); // Initialize game session?
            FUN_006906b0(); // Load menu assets?
            FUN_00497ad0(); // Show loading screen?
            iVar5 = DAT_01129928; // Global game state pointer
            DAT_00e56734 = 0;
            DAT_00e56735 = 1;
            DAT_00e5672c = 0xb; // some state ID
            *(undefined4 *)(DAT_01129928 + 0x60) = 0; // clear progress
            if ((DAT_01130590 & 1) == 0) {
              FUN_005c0d50(iVar5 + 0x14, &LAB_00931e00, 0); // Register callback
              DAT_01130590 = DAT_01130590 | 1; // set flag
            }
          }
        }

        if (aiStack_30[0] != 0) {
          (*pcStack_24)(aiStack_30[0]); // cleanup
        }
        if (puStack_20 != (undefined2 *)0x0) {
          (*pcStack_14)(puStack_20); // cleanup
        }
        return;
      }

      // Name exists in alphanumeric check failed (likely name in use or invalid)
      iVar5 = FUN_009c8e50(0xf0); // Allocate error dialog structure (size 0xf0)
      if (iVar5 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = FUN_00982280(0); // Create dialog object
      }
      *(undefined4 *)(iVar5 + 0xc) = 3; // Error type 3 (name in use)
      FUN_00981ec0("$ui_pro_name_inuse"); // Set title
      FUN_00981eb0("$ui_pro_name_inuse"); // Set message
      *(undefined1 **)(iVar5 + 0x14) = &LAB_009332b0; // Set callback for "OK" button
      FUN_00982e10(); // Show dialog
      return;
    }
  }

  // Name is empty or all whitespace
  iVar5 = FUN_009c8e50(0xf0); // Allocate error dialog
  if (iVar5 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = FUN_00982280(0);
  }
  *(undefined4 *)(iVar5 + 0xc) = 2; // Error type 2 (empty name)
  FUN_00981ec0("$ui_pro_name_empty");
  FUN_00981eb0("$ui_pro_name_empty");
  *(undefined1 **)(iVar5 + 0x14) = &LAB_009332b0; // Same OK callback
  FUN_00982e10(); // Show dialog
  return;
}