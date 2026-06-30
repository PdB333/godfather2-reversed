// FUNC_NAME: EARS::Framework::initialize
// Address: 0x0068d010
// Role: Main game engine initialization - settings, memory, job system, window creation, subsystem init

bool EARS::Framework::initialize()
{
    char   cVar1;
    bool   bResult = false;
    bool   bVSync;
    bool   bFullscreen;
    int    iWindowState;
    int    iWindowLeft;
    int    iWindowTop;
    int    iWindowWidth  = 0x400; // 1024 default
    int    iWindowHeight = 0x300; // 768 default
    int    iHz;
    int    iCmdCount;
    uint   uCmdIndex;
    char*  pCmdArg;
    char*  pCmdArg2;
    long   lWidth;
    long   lHeight;
    void*  pAlloc1MB;
    int    iJobMgrPlus4;
    int    iSomeFlag;
    long   lTemp;

    // Initialize debug/assert system
    initCrashHandler();
    initDebugOutput();

    // Platform setup
    int platform = getPlatform();
    setPlatform(platform);

    // Read settings file
    int settingsHandle = openSettingsFile("settings.txt", 1, 0, 0);
    int settingsRoot = getSettingsRoot();
    readSettingsGroup(0, 1, settingsRoot);
    closeSettingsFile(settingsHandle);
    parseSettings();

    // Memory allocation attempt
    iSomeFlag = malloc(0x54);
    if (iSomeFlag != 0) {
        initMemoryAllocation();
    }

    initHeap();
    initMemoryManager();

    // Register debug handlers (assert, error, warning)
    registerDebugHandlers(assertHandler, errorHandler, warningHandler);

    // Set thread priority
    int* pConfig = g_appConfig;
    setThreadPriority(0xD);
    pConfig[0x48 / 4] = 0; // clear some config field at offset 0x48

    // Allocate 1MB block for engine
    pAlloc1MB = allocateMemory(0x100000);
    if (checkAllocation(pAlloc1MB) != '\0') {
        // Initialization proper
        setAppName(&g_appName);
        initHeapRegions(0x140000, 0x10000, 0x200);
        int sysInfo = getSystemInfo();
        setSystemInfo(sysInfo);

        // Job system initialization
        g_jobManager = createJobManager();
        if (g_jobManager == 0) {
            iJobMgrPlus4 = 0;
        } else {
            iJobMgrPlus4 = (int)g_jobManager + 4;
        }
        initJobThread(iJobMgrPlus4);
        initJobPool(0x10, 0x10);
        initializeCriticalSection(&g_jobManagerCriticalSection);
        startJobManager();

        // Worker thread creation
        int threadInfo[2]; // local_44, local_1c will be output
        int threadInit = 0; // local_1c
        char threadName[] = "Job Manager - Job Thread";
        int threadPriority = 0x3F; // local_c
        // local_18,14,10 uninitialized, set to zeros
        threadInfo[1] = threadPriority; // Actually this assignment is messy. Mimic original.

        // Ghidra: local_18 = local_30; etc. These are uninitialized. We'll ignore.
        createThread(&threadInfo, &threadInit);

        int threadStackSize = 0x800; // local_3c
        int threadInitFlags = 0x200; // local_38

        if (g_jobManager == 0) {
            iJobMgrPlus4 = 0;
        } else {
            iJobMgrPlus4 = (int)g_jobManager + 4;
        }
        void* threadProc = getJobThreadProc();
        startJobThread(iJobMgrPlus4, 2, &threadStackSize, threadProc);

        // Initialize game subsystems, returns non-zero on success
        if (initGameSubsystems()) {
            // Read window settings from .cfg
            iWindowState = readSettingInt("Window.State", 0);
            bVSync       = readSettingBool("Window.VSync", 0);
            bFullscreen  = readSettingBool("Window.Fullscreen", 1);
            iWindowLeft  = readSettingInt("Window.Left", 0);
            iWindowTop   = readSettingInt("Window.Top", 0);
            iWindowWidth = readSettingInt("Window.Width", 0x400);
            iWindowHeight= readSettingInt("Window.Height", 0x300);
            readSettingInt("Window.Bright", 0);
            iHz          = readSettingInt("Window.Hz", 0x3C);
            setRefreshRate(iHz);

            // Parse command line arguments
            iCmdCount = getCommandLineArgCount();
            uCmdIndex = 1;
            while (uCmdIndex < iCmdCount) {
                pCmdArg = getCommandLineArg(uCmdIndex - 1);
                if (pCmdArg == 0) {
                    if (0 == 1) {} // bogus
                    else if (__stricmp(pCmdArg, "-fullscreen") == 0) {
                        bFullscreen = true;
                    }
                    else if (__stricmp(pCmdArg, "-windowed") == 0) {
                        bFullscreen = false;
                    }
                    else if (__stricmp(pCmdArg, "-vsync") == 0) {
                        bVSync = true;
                    }
                    else if (__stricmp(pCmdArg, "-novsync") == 0) {
                        bVSync = false;
                    }
                    else if (__stricmp(pCmdArg, "-resolution") == 0) {
                        if (uCmdIndex + 1 < iCmdCount) {
                            pCmdArg  = getCommandLineArg(uCmdIndex);
                            pCmdArg2 = getCommandLineArg(uCmdIndex + 1);
                            lWidth  = _atol(pCmdArg);
                            lHeight = _atol(pCmdArg2);
                            if (lWidth > 0 && lHeight > 0) {
                                iWindowWidth  = (int)lWidth;
                                iWindowHeight = (int)lHeight;
                            }
                        }
                    }
                    else if (checkDebugCmd() == 0) {
                        if (uCmdIndex < iCmdCount) {
                            pCmdArg = getCommandLineArg(uCmdIndex);
                            long seed = _atol(pCmdArg);
                            setGameSeed(seed);
                        }
                    }
                    else if (checkDebugCmd() == 0) {
                        if (uCmdIndex < iCmdCount) {
                            pCmdArg = getCommandLineArg(uCmdIndex);
                            // Copy debug player name to global
                            strcpy(g_debugPlayer01_00e50224, pCmdArg);
                        }
                    }
                    else if (checkDebugCmd() == 0) {
                        setDebugMode(1);
                    }
                }
                uCmdIndex++;
            }

            // Apply window settings
            setVSync(bVSync);
            createWindow(bFullscreen, iWindowState, iWindowLeft, iWindowTop, iWindowWidth, iWindowHeight);

            // Initialize remaining systems
            initInputSystem();
            initAudioSystem();
            initNetworkSystem(false, false);
            initRenderingSystem();
            initSoundSystem(g_soundBank);

            bResult = true;
        } else {
            // Cleanup on initGameSubsystems failure
            cleanupGameSubsystems(/* handle */);
            initializeCriticalSection(0);
            closeThread(0, 0, 0xFFFFFFFF);
            destroyJobPool();
            shutdownMemoryManager();
            cleanupAfterError();
            shutdownHeap();
            shutdownHeap2();
            setSystemInfo(0);
            initCrashHandler();
            initDebugOutput2();
            return false;
        }
    }
    return bResult;
}