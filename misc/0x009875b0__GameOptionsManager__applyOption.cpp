// FUNC_NAME: GameOptionsManager::applyOption
void __fastcall GameOptionsManager::applyOption(int this) {
  int iVar1;
  float fVar2;
  undefined4 uVar3;

  if (*(int *)(this + 0x58) == 0) {
    // Sound options tab
    iVar1 = *(int *)(this + 0x54); // Option type
    *(undefined1 *)(this + 0x10c) = 1;
    if (iVar1 == 0) {
      // Music volume
      if (*(int *)(this + 0xb0) != *(int *)(this + 0x68)) {
        setMusicMute(DAT_011304d8, 0);
      }
      iVar1 = *(int *)(this + 0x68);
      fVar2 = (float)iVar1;
      *(int *)(this + 0xb0) = iVar1;
      if (iVar1 < 0) {
        fVar2 = fVar2 + DAT_00e44578; // Handle negative values (wrap-around)
      }
      setMusicVolume(fVar2 * DAT_00d58cbc); // Multiply by scaling factor
      return;
    }
    if (iVar1 == 1) {
      // SFX volume
      if (*(int *)(this + 0xb4) != *(int *)(this + 0x68)) {
        setSfxMute(DAT_011304d8, 0);
      }
      iVar1 = *(int *)(this + 0x68);
      fVar2 = (float)iVar1;
      *(int *)(this + 0xb4) = iVar1;
      if (iVar1 < 0) {
        fVar2 = fVar2 + DAT_00e44578;
      }
      setSfxVolume(fVar2 * DAT_00d58cbc);
      return;
    }
    if (iVar1 == 2) {
      // Subtitles toggle
      *(int *)(this + 0xb8) = *(int *)(this + 0x68);
      setSubtitlesEnabled(*(int *)(this + 0x68) == 1);
      return;
    }
    if (iVar1 == 3) {
      // Some other sound option
      setSoundSetting(*(undefined4 *)(this + 0x68));
      return;
    }
  }
  else if (*(int *)(this + 0x58) == 1) {
    // Gameplay options tab
    *(undefined1 *)(this + 0x10d) = 1;
    iVar1 = *(int *)(this + 0x54);
    if (iVar1 == 0) {
      // Aiming style
      *(undefined4 *)(this + 0x6c) = *(undefined4 *)(this + 0x68);
      return;
    }
    if (iVar1 == 1) {
      // Free aim toggle
      if (*(int *)(this + 0x70) != *(int *)(this + 0x68)) {
        if (*(int *)(this + 0x68) == 0) {
          luaCall("EnableSelection", 0, DAT_00d90fa8, 1, DAT_00d796d4);
          *(undefined4 *)(this + 0x70) = *(undefined4 *)(this + 0x68);
          return;
        }
        luaCall("DisableSelection", 0, DAT_00d90fa8, 1, DAT_00d796d4);
        *(undefined4 *)(this + 0x70) = *(undefined4 *)(this + 0x68);
        return;
      }
    }
    else {
      if (iVar1 == 2) {
        // Auto-aim toggle
        if (*(int *)(this + 0x74) != *(int *)(this + 0x68)) {
          setAutoAimMute(DAT_011304d8, 0);
        }
        *(undefined4 *)(this + 0x74) = *(undefined4 *)(this + 0x68);
        setAutoAimEnabled(*(undefined4 *)(this + 0x68));
        return;
      }
      if (iVar1 == 3) {
        // Vibration toggle
        *(undefined4 *)(this + 0x78) = *(undefined4 *)(this + 0x68);
        return;
      }
      if (iVar1 == 4) {
        // Difficulty setting
        iVar1 = *(int *)(this + 0x68);
        if (*(int *)(this + 0x7c) != iVar1) {
          if (iVar1 == 0) {
            uVar3 = 2; // Easy
          }
          else if (iVar1 == 1) {
            uVar3 = 3; // Medium
          }
          else {
            if (iVar1 != 2) {
              // Hard (or custom)
              setAdvancedOptions(1);
              luaCall("EnableAdvancedOptions", 0, DAT_00d90fa8, 0);
              *(undefined4 *)(this + 0x7c) = *(undefined4 *)(this + 0x68);
              return;
            }
            uVar3 = 4; // Hard
          }
          setAdvancedOptions(uVar3);
          luaCall("DisableAdvancedOptions", 0, DAT_00d90fa8, 0);
          *(undefined4 *)(this + 0x7c) = *(undefined4 *)(this + 0x68);
          return;
        }
      }
      else {
        if (iVar1 == 5) {
          // Advanced option 0
          *(undefined4 *)(this + 0x80) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(0, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 6) {
          // Advanced option 1
          *(undefined4 *)(this + 0x84) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(1, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 7) {
          // Advanced option 2
          *(undefined4 *)(this + 0x88) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(2, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 8) {
          // Advanced option 3
          *(undefined4 *)(this + 0x8c) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(3, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 9) {
          // Advanced option 4
          *(undefined4 *)(this + 0x90) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(4, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 10) {
          // Advanced option 5
          *(undefined4 *)(this + 0x94) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(5, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 0xb) {
          // Advanced option 7
          *(undefined4 *)(this + 0x98) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(7, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 0xc) {
          // Advanced option 6
          *(undefined4 *)(this + 0x9c) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(6, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 0xd) {
          // Advanced option 9
          *(undefined4 *)(this + 0xa0) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(9, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 0xe) {
          // Advanced option 8
          *(undefined4 *)(this + 0xa4) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(8, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 0xf) {
          // Advanced option 10
          *(undefined4 *)(this + 0xa8) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(10, *(undefined4 *)(this + 0x68));
          return;
        }
        if (iVar1 == 0x10) {
          // Advanced option 11
          *(undefined4 *)(this + 0xac) = *(undefined4 *)(this + 0x68);
          setAdvancedOption(0xb, *(undefined4 *)(this + 0x68));
        }
      }
    }
  }
  return;
}