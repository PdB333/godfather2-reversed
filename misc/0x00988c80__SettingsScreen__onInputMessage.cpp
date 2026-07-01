// FUNC_NAME: SettingsScreen::onInputMessage
bool __thiscall SettingsScreen::onInputMessage(int thisPtr, const char* inputPath)
{
    bool bVar1;
    int iVar2;
    char cVar3;
    const char* pbVar4;
    uint uVar5, uVar6, uVar7;
    int iVar8;
    const char* pbVar9;
    char* pcVar10;
    bool bVar11;
    EA::SIMD::Vec3 localVec; // +0x0c
    char localStr[64];

    // +0x50: bool m_isDropdownVisible?   +0x51: bool m_isCaretActive?
    if (*(char*)(thisPtr + 0x50) == '\0') {
        iVar8 = 0x1e;
        bVar11 = true;
        pbVar4 = "/syss/buttons/button_0/button";
        pbVar9 = inputPath;
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *pbVar9;
            pbVar4++;
            pbVar9++;
        } while (bVar11);
        if (bVar11) {
            // Button 0 pressed (e.g., "A" button)
            playSound(); // FUN_00988260
            localVec = DAT_011302e8;  // some constant vector/color
            localVec.y = 0;
            localVec.z = 0;
            FUN_00408a00(&localVec, 0);  // set something (maybe UI effect)
            return true;
        }

        // Check button_1 (e.g., "B" button)
        iVar8 = 0x1e;
        bVar11 = true;
        pbVar4 = "/syss/buttons/button_1/button";
        pbVar9 = inputPath;
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *pbVar9;
            pbVar4++;
            pbVar9++;
        } while (bVar11);
        if (bVar11) {
            uVar5 = getAnalogLeftStickX(); // FUN_0060e9e0
            uVar6 = getAnalogLeftStickY(); // FUN_0060e9f0
            uVar7 = getAnalogRightStickX(); // FUN_0060e9d0
            iVar8 = *(int*)(thisPtr + 0x70); // m_prevLeftTrigger?
            iVar2 = *(int*)(thisPtr + 0x78); // m_prevRightTrigger?
            if ((*(char*)(thisPtr + 0x10d) != '\0') &&
                (((((uVar5 & 0xffff) != *(uint*)(thisPtr + 0x114) ||   // m_lastAnalogLeftX
                    ((uVar6 & 0xffff) != *(uint*)(thisPtr + 0x110))) || // m_lastAnalogLeftY
                   ((uVar7 & 0xffff) != *(uint*)(thisPtr + 0x118))) || // m_lastAnalogRightX
                  ((cVar3 = isButtonHeld(/*some button*/), (iVar8 == 0) != (bool)cVar3 ) ||  // FUN_0060e860
                   (cVar3 = isButtonHeld(/*other button*/), (iVar2 != 0) != (bool)cVar3 )))))) { // FUN_0060e690
                *(char*)(thisPtr + 0x10e) = 1;  // m_flagInputChanged
                updateUI(); // FUN_009886e0
                return true;
            }
            resetInputState(); // FUN_009881d0
            (*(code**)(*DAT_011305b0 + 0x2c))();  // vtable call (maybe close menu)
            return true;
        }

        // Check button_2 (e.g., "X" button)
        iVar8 = 0x1e;
        bVar11 = true;
        pbVar4 = "/syss/buttons/button_2/button";
        pbVar9 = inputPath;
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *pbVar9;
            pbVar4++;
            pbVar9++;
        } while (bVar11);
        if (bVar11) {
            *(char*)(thisPtr + 0x10c) = 0; // m_flagSomething
            *(char*)(thisPtr + 0x10d) = 0;
            resetToDefaults(); // FUN_00988070
            updateUI(); // FUN_009886e0
            return true;
        }

        // Check selector_left for current control index (m_controlIndex at +0x54)
        FUN_00910160(localStr, "/syss/content/control_%d/select/selector_left",
                     *(int*)(thisPtr + 0x54));
        pbVar4 = localStr;
        pbVar9 = inputPath;
        do {
            bVar1 = *pbVar4;
            bVar11 = bVar1 < *pbVar9;
            if (bVar1 != *pbVar9) {
                iVar8 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                goto LAB_00988f06;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar4[1];
            bVar11 = bVar1 < pbVar9[1];
            if (bVar1 != pbVar9[1]) goto LAB_00988f01;
            pbVar4 += 2;
            pbVar9 += 2;
        } while (bVar1 != 0);
        iVar8 = 0;
LAB_00988f06:
        if (iVar8 == 0) {
            if (*(char*)(thisPtr + 0x50) != '\0') {
                return true;
            }
            executeMenuAction("MoveLeft", &DAT_00d90fa8, &DAT_011304d8, &DAT_011302c0);
            return true;
        }

        // Check selector_right
        FUN_00910160(localStr, "/syss/content/control_%d/select/selector_right",
                     *(int*)(thisPtr + 0x54));
        pbVar4 = localStr;
        pbVar9 = inputPath;
        do {
            bVar1 = *pbVar4;
            bVar11 = bVar1 < *pbVar9;
            if (bVar1 != *pbVar9) {
                iVar8 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                goto LAB_00988f85;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar4[1];
            bVar11 = bVar1 < pbVar9[1];
            if (bVar1 != pbVar9[1]) goto LAB_00988f80;
            pbVar4 += 2;
            pbVar9 += 2;
        } while (bVar1 != 0);
        iVar8 = 0;
LAB_00988f85:
        if (iVar8 == 0) {
            if (*(char*)(thisPtr + 0x50) != '\0') {
                return true;
            }
            executeMenuAction("MoveRight", &DAT_00d90fa8, &DAT_011304d8, &DAT_011302c0);
            return true;
        }

        // Check option for control_0 (generic)
        iVar8 = 0x1f;
        bVar11 = true;
        pbVar4 = "/syss/content/control_0/option";
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *inputPath;
            pbVar4++;
            inputPath++;
        } while (bVar11);
        if (!bVar11) {
            return false;
        }
        if (*(int*)(thisPtr + 0x58) != 1) { // m_optionIndex? Only handle if index == 1
            return true;
        }
    } else {
        // Dropdown is visible (m_isDropdownVisible == true)
        if (*(char*)(thisPtr + 0x51) != '\0') {
            *(char*)(thisPtr + 0x51) = 0; // m_isCaretActive? Clear it
            return true;
        }

        // Check caret_up
        iVar8 = 0x3c;
        bVar11 = true;
        pbVar4 = "/syss/content/control_0/dropbox/dropdown/scrollbar/caret_up";
        pbVar9 = inputPath;
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *pbVar9;
            pbVar4++;
            pbVar9++;
        } while (bVar11);
        if (bVar11) {
            return true;
        }

        // Check caret_down
        iVar8 = 0x3e;
        bVar11 = true;
        pbVar4 = "/syss/content/control_0/dropbox/dropdown/scrollbar/caret_down";
        pbVar9 = inputPath;
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *pbVar9;
            pbVar4++;
            pbVar9++;
        } while (bVar11);
        if (bVar11) {
            return true;
        }

        // Check scrollbar handle (hspt)
        iVar8 = 0x38;
        bVar11 = true;
        pbVar4 = "/syss/content/control_0/dropbox/dropdown/scrollbar/hspt";
        pbVar9 = inputPath;
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *pbVar9;
            pbVar4++;
            pbVar9++;
        } while (bVar11);
        if (bVar11) {
            return true;
        }

        // Check slider handle
        iVar8 = 0x3f;
        bVar11 = true;
        pbVar4 = "/syss/content/control_0/dropbox/dropdown/scrollbar/slider/hspt";
        pbVar9 = inputPath;
        do {
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pbVar4 == *pbVar9;
            pbVar4++;
            pbVar9++;
        } while (bVar11);
        if (bVar11) {
            return true;
        }

        // Check track (note: leading '?' omitted in compare? Actually pcVar10 starts with "?/syss/...")
        pcVar10 = "?/syss/content/control_0/dropbox/dropdown/scrollbar/track/hspt";
        iVar8 = 0x3e;
        bVar11 = true;
        pbVar4 = inputPath;
        do {
            pcVar10++;  // skip '?' then compare?
            if (iVar8 == 0) break;
            iVar8--;
            bVar11 = *pcVar10 == *pbVar4;
            pbVar4++;
        } while (bVar11);
        if (bVar11) {
            return true;
        }

        // Check specific dropbox item path
        FUN_00910160(localStr, "/syss/content/control_%d/dropbox/item_%d/item",
                     *(int*)(thisPtr + 0x54),  // m_controlIndex
                     *(int*)(thisPtr + 0x5c)); // m_dropboxItemIndex
        pbVar4 = localStr;
        do {
            bVar1 = *pbVar4;
            bVar11 = bVar1 < *inputPath;
            if (bVar1 != *inputPath) {
                iVar8 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                goto LAB_00988d65;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar4[1];
            bVar11 = bVar1 < inputPath[1];
            if (bVar1 != inputPath[1]) goto LAB_00988d60;
            pbVar4 += 2;
            inputPath += 2;
        } while (bVar1 != 0);
        iVar8 = 0;
LAB_00988d65:
        if (iVar8 != 0) {
            updateUI(); // FUN_009886e0
            return true;
        }
    }

    // Fallback: maybe close or confirm something
    finalizeAction(); // FUN_00988990
    return true;
}