// FUNC_NAME: AudioManager::setAudioParameter
void __thiscall AudioManager::setAudioParameter(uint param_1, int param_2, const char* param_3)
{
    bool bVar1;
    bool bVar2;
    char cVar3;
    undefined4 uVar4;
    undefined4* puVar5;
    undefined4 local_18;
    undefined1* local_14;
    undefined1 local_10;
    undefined1 local_c[4];
    int local_8[2];

    cVar3 = AudioManager::isAudioEnabled();
    if (cVar3 == '\0') {
        return;
    }
    bVar2 = false;
    bVar1 = false;
    uVar4 = 0;
    puVar5 = (undefined4*)0x0;
    switch(param_2) {
    case 0:
        puVar5 = (undefined4*)(param_1 + 0x2e9c);
        break;
    case 1:
        puVar5 = (undefined4*)(param_1 + 0x2ea4);
        break;
    case 2:
        puVar5 = (undefined4*)(param_1 + 0x2eb4);
        break;
    case 3:
        puVar5 = (undefined4*)(param_1 + 0x2eac);
        break;
    case 4:
        puVar5 = (undefined4*)(param_1 + 0x2ebc);
        break;
    case 5:
        puVar5 = (undefined4*)(param_1 + 0x2ec4);
        break;
    case 6:
        puVar5 = (undefined4*)(param_1 + 0x2ecc);
        break;
    case 7:
        puVar5 = (undefined4*)(param_1 + 0x2ed4);
        break;
    case 8:
        puVar5 = (undefined4*)(param_1 + 0x2edc);
        break;
    case 9:
        puVar5 = (undefined4*)(param_1 + 0x2ee4);
        break;
    case 10:
        puVar5 = (undefined4*)(param_1 + 0x2eec);
        break;
    case 0xb:
        puVar5 = (undefined4*)(param_1 + 0x2ef4);
        goto LAB_0079f18b;
    case 0xc:
        puVar5 = (undefined4*)(param_1 + 0x2efc);
        break;
    case 0xd:
        puVar5 = (undefined4*)(param_1 + 0x2f04);
        break;
    case 0xe:
        puVar5 = (undefined4*)(param_1 + 0x2f0c);
        break;
    case 0xf:
        puVar5 = (undefined4*)(param_1 + 0x2f14);
        break;
    case 0x10:
        puVar5 = (undefined4*)(param_1 + 0x2f6c);
        break;
    case 0x11:
        puVar5 = (undefined4*)(param_1 + 0x2f74);
        break;
    case 0x12:
        puVar5 = (undefined4*)(param_1 + 0x2f7c);
        break;
    case 0x13:
        puVar5 = (undefined4*)(param_1 + 0x2f84);
        break;
    case 0x14:
        puVar5 = (undefined4*)(param_1 + 0x2f8c);
        break;
    case 0x15:
        puVar5 = (undefined4*)(param_1 + 0x2f94);
        break;
    case 0x16:
        puVar5 = (undefined4*)(param_1 + 0x2f9c);
        break;
    case 0x17:
        puVar5 = (undefined4*)(param_1 + 0x2fa4);
        break;
    case 0x18:
        puVar5 = (undefined4*)(param_1 + 0x2f1c);
        break;
    case 0x19:
        puVar5 = (undefined4*)(param_1 + 0x2f24);
        break;
    case 0x1a:
        puVar5 = (undefined4*)(param_1 + 0x2f2c);
        break;
    case 0x1b:
        puVar5 = (undefined4*)(param_1 + 0x2f34);
        break;
    case 0x1c:
        puVar5 = (undefined4*)(param_1 + 0x2f3c);
        break;
    case 0x1d:
        puVar5 = (undefined4*)(param_1 + 0x2f44);
        break;
    case 0x1e:
        puVar5 = (undefined4*)(param_1 + 0x2f4c);
        goto LAB_0079f1a7;
    case 0x1f:
        puVar5 = (undefined4*)(param_1 + 0x2f54);
        goto LAB_0079f18b;
    case 0x20:
        puVar5 = (undefined4*)(param_1 + 0x2f5c);
        goto LAB_0079f18b;
    case 0x21:
        puVar5 = (undefined4*)(param_1 + 0x2f64);
LAB_0079f18b:
        uVar4 = param_3;  // param_3 used as string pointer for these cases
        bVar2 = true;
        break;
    case 0x22:
        puVar5 = (undefined4*)(param_1 + 0x2fbc);
        goto LAB_0079f1a7;
    case 0x23:
        puVar5 = (undefined4*)(param_1 + 0x2ff4);
        goto LAB_0079f1a7;
    case 0x24:
        puVar5 = (undefined4*)(param_1 + 0x3024);
        goto LAB_0079f1a7;
    case 0x25:
        puVar5 = (undefined4*)(param_1 + 0x3034);
        goto LAB_0079f1a7;
    case 0x26:
        puVar5 = (undefined4*)(param_1 + 0x3014);
        goto LAB_0079f1a7;
    case 0x27:
        puVar5 = (undefined4*)(param_1 + 0x2ffc);
        goto LAB_0079f1a7;
    case 0x28:
        puVar5 = (undefined4*)(param_1 + 0x3004);
        goto LAB_0079f1a7;
    case 0x29:
        puVar5 = (undefined4*)(param_1 + 0x300c);
        goto LAB_0079f1a7;
    case 0x2a:
        puVar5 = (undefined4*)(param_1 + 0x2fc4);
        goto LAB_0079f1a7;
    case 0x2b:
        puVar5 = (undefined4*)(param_1 + 0x2fe4);
        goto LAB_0079f1a7;
    case 0x2c:
        puVar5 = (undefined4*)(param_1 + 0x2fdc);
        goto LAB_0079f1a7;
    case 0x2d:
        puVar5 = (undefined4*)(param_1 + 0x2fd4);
        goto LAB_0079f1a7;
    case 0x2e:
        puVar5 = (undefined4*)(param_1 + 0x302c);
        goto LAB_0079f1a7;
    case 0x2f:
        puVar5 = (undefined4*)(param_1 + 0x2fac);
        goto LAB_0079f1a7;
    case 0x30:
        puVar5 = (undefined4*)(param_1 + 0x2fcc);
        goto LAB_0079f1a7;
    case 0x31:
        puVar5 = (undefined4*)(param_1 + 0x2fec);
        goto LAB_0079f1a7;
    case 0x32:
        puVar5 = (undefined4*)(param_1 + 0x303c);
        goto LAB_0079f1a7;
    case 0x33:
        puVar5 = (undefined4*)(param_1 + 0x3044);
        goto LAB_0079f1a7;
    case 0x34:
        puVar5 = (undefined4*)(param_1 + 0x304c);
        goto LAB_0079f1a7;
    case 0x35:
        puVar5 = (undefined4*)(param_1 + 0x3054);
        goto LAB_0079f1a7;
    }
    bVar1 = bVar2;
    if ((0 < DAT_0112b9d0) || (0 < DAT_0112ba0c)) { // global audio enable flags?
LAB_0079f1a7:
        if (puVar5 != (undefined4*)0x0) {
            if (bVar1) {
                // String parameter: copy the string and parse it
                AudioManager::copyString(uVar4);
                local_18 = *puVar5; // original value at offset
                local_14 = local_c; // buffer
                local_10 = 0;
                AudioManager::stringToIntOrPath(&local_18, 0); // parse or convert
                if (local_8[0] != 0) {
                    AudioManager::freeMemory(local_8);
                    return;
                }
            }
            else {
                // Non-string parameter: set value directly (perhaps float or bool)
                FUN_007fff40(puVar5);
            }
        }
    }
    return;
}