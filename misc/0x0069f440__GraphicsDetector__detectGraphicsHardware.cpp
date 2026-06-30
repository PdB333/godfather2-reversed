// FUNC_NAME: GraphicsDetector::detectGraphicsHardware
int GraphicsDetector::detectGraphicsHardware(void)
{
    char cVar1;
    int iVar2;
    char *pcVar3;
    char *pcVar4;
    CHAR *pCVar5;
    DWORD iDevNum;
    char *pcVar6;
    bool bVar7;
    int local_1c4;
    int local_1c0;
    _DISPLAY_DEVICEA displayDevice; // +0x1a8 size

    // Check for known incompatible configurations
    FUN_0049bee0(); // likely checkOSVersion or similar
    iVar2 = FUN_0049bc90(); // likely checkCPUFeatures
    if ((((iVar2 != 0) && (cVar1 = FUN_0049c210(), cVar1 != '\0')) && (local_1c0 == 0xf)) &&
       (local_1c4 == 0)) {
        return 2; // Return code for "unsupported but can run"
    }
    
    displayDevice.cb = 0x1a8; // sizeof(DISPLAY_DEVICEA)
    iDevNum = 0;
    iVar2 = EnumDisplayDevicesA((LPCSTR)0x0, 0, &displayDevice, 0);
    
    do {
        if (iVar2 == 0) {
            // No more display devices - check for specific configurations
            iVar2 = FUN_0060f480(); // likely checkGraphicsAPI
            if (iVar2 == 0) {
                return 3; // Return code for "no suitable graphics"
            }
            iVar2 = FUN_0060f480();
            if (iVar2 != 1) {
                iVar2 = FUN_0060f480();
                if ((iVar2 == 3) && (cVar1 = FUN_00608200(), cVar1 == '\0')) {
                    return 2; // Return code for "unsupported but can run"
                }
                return 4; // Return code for "unknown configuration"
            }
            return 2; // Return code for "unsupported but can run"
        }
        
        iDevNum = iDevNum + 1;
        
        // Check if this is a primary display device (StateFlags bit 2 = 0x04)
        if (((byte)displayDevice.StateFlags & 4) != 0) {
            pcVar3 = _strstr(displayDevice.DeviceID, "VEN_");
            _strstr(displayDevice.DeviceID, "DEV_");
            
            // Null-terminate at each '&' in DeviceID to extract vendor/device IDs
            for (pcVar4 = _strchr(displayDevice.DeviceID, 0x26); pcVar4 != (char *)0x0;
                pcVar4 = _strchr(pcVar4 + 1, 0x26)) {
                *pcVar4 = '\0';
            }
            
            pCVar5 = displayDevice.DeviceString;
            do {
                cVar1 = *pCVar5;
                pCVar5 = pCVar5 + 1;
            } while (cVar1 != '\0');
            pCVar5 = pCVar5 - (int)(displayDevice.DeviceString + 1); // length of DeviceString
            
            // Check for NVIDIA GPU (VEN_10DE)
            iVar2 = 5;
            bVar7 = true;
            pcVar4 = "10DE";
            pcVar6 = pcVar3 + 4;
            do {
                if (iVar2 == 0) break;
                iVar2 = iVar2 + -1;
                bVar7 = *pcVar4 == *pcVar6;
                pcVar4 = pcVar4 + 1;
                pcVar6 = pcVar6 + 1;
            } while (bVar7);
            
            if (bVar7) {
                // NVIDIA GPU detected - check if it's a GeForce
                pcVar4 = "NVIDIA GeForce ";
                do {
                    pcVar3 = pcVar4;
                    pcVar4 = pcVar3 + 1;
                } while (*pcVar3 != '\0');
                
                if ((pcVar3 + -0xd5d014 < pCVar5) &&
                   (iVar2 = __strnicmp(displayDevice.DeviceString, "NVIDIA GeForce ", (size_t)(pcVar3 + -0xd5d018)), iVar2 == 0)) {
                    cVar1 = FUN_0069f3b0(); // likely checkShaderModel or similar
joined_r0x0069f702:
                    if (cVar1 != '\0') {
                        return 2; // Return code for "unsupported but can run"
                    }
                }
            }
            else {
                // Check for AMD/ATI GPU (VEN_1002)
                iVar2 = 5;
                bVar7 = true;
                pcVar4 = "1002";
                pcVar3 = pcVar3 + 4;
                do {
                    if (iVar2 == 0) break;
                    iVar2 = iVar2 + -1;
                    bVar7 = *pcVar4 == *pcVar3;
                    pcVar4 = pcVar4 + 1;
                    pcVar3 = pcVar3 + 1;
                } while (bVar7);
                
                if (bVar7) {
                    // AMD/ATI GPU detected - check for Radeon X or HD series
                    pcVar4 = "ATI Radeon X";
                    do {
                        pcVar3 = pcVar4;
                        pcVar4 = pcVar3 + 1;
                    } while (*pcVar3 != '\0');
                    
                    pcVar4 = "ATI Radeon X";
                    do {
                        pcVar6 = pcVar4;
                        pcVar4 = pcVar6 + 1;
                    } while (*pcVar6 != '\0');
                    
                    if ((pcVar6 + -0xd5cffc < pCVar5) &&
                       (iVar2 = __strnicmp(displayDevice.DeviceString, "ATI Radeon X", (size_t)(pcVar3 + -0xd5d000)), iVar2 == 0)) {
                        return 2; // Return code for "unsupported but can run"
                    }
                    
                    pcVar4 = "?ATI Radeon HD ";
                    do {
                        pcVar4 = pcVar4 + 1;
                    } while (*pcVar4 != '\0');
                    
                    pcVar3 = "?ATI Radeon HD ";
                    do {
                        pcVar3 = pcVar3 + 1;
                    } while (*pcVar3 != '\0');
                    
                    if ((pcVar3 + -0xd5cfec < pCVar5) &&
                       (iVar2 = __strnicmp(displayDevice.DeviceString, "ATI Radeon HD ", (size_t)(pcVar4 + -0xd5cff0)), iVar2 == 0)) {
                        cVar1 = FUN_0069f3b0(); // likely checkShaderModel or similar
                        goto joined_r0x0069f702;
                    }
                }
            }
        }
        
        iVar2 = EnumDisplayDevicesA((LPCSTR)0x0, iDevNum, &displayDevice, 0);
    } while(true);
}