// Xbox PDB: EA::Jobs::JobThreadParameters::JobThreadParameters
// FUNC_NAME: Application::init
// Function address: 0x0068d010
// Role: Main engine initialization - sets up memory manager, loads settings, processes command-line args, creates window

bool Application::init() {
    char cVar1;
    bool bFullscreen;
    bool bVSync;
    int iVar6;
    uint uVar12;
    uint uVar13;
    long lVar10, lVar11;
    char *pcVar8, *pcVar9;
    long windowHeight, windowWidth;
    undefined4 local_44[2];
    undefined4 local_3c, local_38;
    undefined4 local_30, local_2c, local_28;
    undefined4 local_1c, local_18, local_14, local_10;
    char *local_8;
    bool result = false;

    // Initialize subsystems
    FUN_0040cf00();  // likely initMemoryPool
    FUN_0040cee0();  // likely initThreading
    uVar4 = FUN_00697cb0();  // getConfigManager
    FUN_006998d0(uVar4);     // setConfigManager
    uVar4 = FUN_0069bb60("settings.txt", 1, 0, 0);  // openSettingsFile
    uVar5 = FUN_00697ca0();  // getPlatformManager
    FUN_0069b9e0(0, 1, uVar5); // configurePlatform
    FUN_00697ea0(uVar4);     // closeSettingsFile
    FUN_00698760();          // initDeviceManager

    // Allocate memory for some system
    iVar6 = FUN_009c8e50(0x54);  // allocateMemory(0x54)
    if (iVar6 != 0) {
        FUN_00401130();  // initMemoryAllocator
    }

    FUN_004949c0();  // initGraphics
    FUN_00494cf0();  // initWindow
    FUN_0056a960(FUN_009c8be0, &LAB_009c8c20, FUN_009c8c00); // installExceptionHandler

    iVar6 = DAT_01223378;  // global system memory
    FUN_00401200(0xd);     // initMemoryPoolType
    *(undefined4 *)(iVar6 + 0x48) = 0; // zero out field

    // Allocate a large heap
    uVar4 = FUN_009c88c0(0x100000);  // allocateVirtualMemory(1MB)
    cVar1 = FUN_00401210(uVar4);     // registerMemoryPool
    if (cVar1 != '\0') {
        FUN_0040cf30(&DAT_00e2f044); // initJobThread
        FUN_00494d50(0x140000, 0x10000, 0x200); // createWindow(1280x1024?)
        uVar4 = FUN_0040cf60();      // getThreadPool
        FUN_0067c050(uVar4);         // setThreadPool

        // Create job manager thread
        DAT_01129b00 = FUN_009c89c0(); // createJobManager
        if (DAT_01129b00 == 0) {
            iVar6 = 0;
        } else {
            iVar6 = DAT_01129b00 + 4;
        }
        FUN_00ab86d0(iVar6);        // initJobManager
        FUN_00abd1c0(0x10, 0x10);   // createThreadPool(16, 16)

        FUN_00459020(&DAT_01129b80); // initCriticalSection
        FUN_00ab5450();             // startJobThread

        // Setup job thread parameters
        local_18 = local_30;
        local_14 = local_2c;
        local_10 = local_28;
        local_c = 0x3f;             // priority?
        local_8 = "Job Manager - Job Thread";
        local_4 = 0;
        local_1c = 0;
        FUN_00abac60(local_44, &local_1c); // setThreadStartInfo

        // Set thread stack size
        local_3c = 0x800;  // 2KB?
        local_38 = 0x200;  // 512B?

        if (DAT_01129b00 == 0) {
            iVar6 = 0;
        } else {
            iVar6 = DAT_01129b00 + 4;
        }
        uVar4 = FUN_00495010();      // getThreadFunc
        FUN_004950b0(iVar6, 2, &local_3c, uVar4); // createThread

        // Try to run main loop; if fails, clean up
        iVar6 = FUN_0069daf0();      // runMainLoop
        if (iVar6 != 0) {
            FUN_0069d5c0(iVar6);     // shutdownMainLoop
            FUN_00459020(0);         // deleteCriticalSection
            FUN_00ababe0(0, 0, 0xffffffff); // terminateThread
            FUN_00ab9490();          // cleanupJobManager
            thunk_FUN_004d03b0();    // cleanupAudio
            FUN_00401330();          // freeMemory
            FUN_00494d00();          // destroyWindow
            FUN_00494ac0();          // shutdownGraphics
            FUN_0067bf30();          // cleanupCommandLine
            FUN_0040cf00();          // deinitMemoryPool
            FUN_0040cef0();          // deinitThreading
            return false;
        }

        // Read window settings from config
        local_44[0] = FUN_0069bcc0("Window.State", 0);    // getWindowState
        bVSync = FUN_0069bc30("Window.VSync", false);      // getVSync
        bFullscreen = FUN_0069bc30("Window.Fullscreen", true); // getFullscreen
        uVar4 = FUN_0069bcc0("Window.Left", 0);             // windowLeft
        uVar5 = FUN_0069bcc0("Window.Top", 0);             // windowTop
        windowWidth = FUN_0069bcc0("Window.Width", 0x400); // default 1024
        windowHeight = FUN_0069bcc0("Window.Height", 0x300); // default 768
        FUN_0069bcc0("Window.Bright", 0);                   // brightness
        uVar7 = FUN_0069bcc0("Window.Hz", 0x3c);           // refresh rate 60Hz
        FUN_0060e9c0(uVar7);                                // setRefreshRate

        // Process command-line arguments
        int numArgs = FUN_0067bf10(); // getCommandLineArgsCount
        if (numArgs != 0) {
            uVar13 = 1;
            do {
                pcVar8 = (char *)FUN_0067bf20(uVar13 - 1); // getCommandLineArg(index)
                if (pcVar8 == nullptr) {
                    iVar6 = 1;
                } else {
                    iVar6 = __stricmp(pcVar8, "-fullscreen");
                }
                if (iVar6 == 0) {
                    bFullscreen = true;
                } else {
                    if (pcVar8 == nullptr) {
                        iVar6 = 1;
                    } else {
                        iVar6 = __stricmp(pcVar8, "-windowed");
                    }
                    if (iVar6 == 0) {
                        bFullscreen = false;
                    } else {
                        if (pcVar8 == nullptr) {
                            iVar6 = 1;
                        } else {
                            iVar6 = __stricmp(pcVar8, "-vsync");
                        }
                        if (iVar6 == 0) {
                            bVSync = true;
                        } else {
                            if (pcVar8 == nullptr) {
                                iVar6 = 1;
                            } else {
                                iVar6 = __stricmp(pcVar8, "-novsync");
                            }
                            if (iVar6 == 0) {
                                bVSync = false;
                            } else {
                                if (pcVar8 == nullptr) {
                                    iVar6 = 1;
                                } else {
                                    iVar6 = __stricmp(pcVar8, "-resolution");
                                }
                                if (iVar6 == 0) {
                                    uVar12 = FUN_0067bf10(); // getCommandLineArgsCount
                                    if (uVar13 + 1 < uVar12) {
                                        pcVar8 = (char *)FUN_0067bf20(uVar13);
                                        pcVar9 = (char *)FUN_0067bf20(uVar13 + 1);
                                        lVar10 = _atol(pcVar8);
                                        lVar11 = _atol(pcVar9);
                                        if (lVar10 > 0 && lVar11 > 0) {
                                            windowWidth = lVar10;
                                            windowHeight = lVar11;
                                        }
                                    }
                                } else {
                                    iVar6 = FUN_0068cff0(); // checkDebugMode?
                                    if (iVar6 == 0) {
                                        uVar12 = FUN_0067bf10();
                                        if (uVar13 < uVar12) {
                                            pcVar8 = (char *)FUN_0067bf20(uVar13);
                                            lVar10 = _atol(pcVar8);
                                            FUN_0060f380(lVar10); // setDebugLevel?
                                        }
                                    } else {
                                        iVar6 = FUN_0068cff0();
                                        if (iVar6 == 0) {
                                            uVar12 = FUN_0067bf10();
                                            if (uVar13 < uVar12) {
                                                pcVar8 = (char *)FUN_0067bf20(uVar13);
                                                // Copy debug player name
                                                pcVar9 = s_debugPlayer01_00e50224; // "debugPlayer01"
                                                do {
                                                    cVar1 = *pcVar8;
                                                    *pcVar9 = cVar1;
                                                    pcVar8++;
                                                    pcVar9++;
                                                } while (cVar1 != '\0');
                                            }
                                        } else {
                                            iVar6 = FUN_0068cff0();
                                            if (iVar6 == 0) {
                                                FUN_0040f9c0(1); // enableDebugMode?
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                uVar12 = FUN_0067bf10(); // getCommandLineArgsCount
                bool continueLoop = uVar13 < uVar12;
                uVar13++;
            } while (continueLoop);
        }

        // Apply window settings
        FUN_0060e680(bVSync);                                        // setVSync
        FUN_0069e3e0(bFullscreen, local_44[0], uVar4, uVar5, windowWidth, windowHeight); // createWindowEx
        FUN_0068bd30();  // initInputManager
        FUN_0068ab50();  // initAudioManager
        FUN_0069d380(0, 0); // initNetworkManager
        FUN_0069eb40();  // initScriptEngine
        FUN_0061e7a0(DAT_00e5021c); // initGameEngine? (global string)
        result = true;
    }
    return result;
}