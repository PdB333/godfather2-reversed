// Xbox PDB: main
// FUNC_NAME: gameMainLoop
// Function address: 0x0068aeb0
// This is the main game entry point that initializes subsystems, registers loop callbacks,
// and runs the main loop with frontend-to-game transition logic.

#include <cstdlib> // for exit

// Forward declarations for internal functions
void memoryInit(int zero);                     // 0x00483a40
void systemInit();                             // 0x00609900
bool checkLicense();                           // 0x009c89c0
int* getLicenseObject();                       // 0x009c9120
void releaseLicenseObject(int* obj);           // 0x009c8f70
void registerMainLoop(const char* loopName, void* data); // 0x00683360 (overloaded)
void registerMainLoop(unsigned int loopId, void* data);  // 0x00683360 (overloaded)
unsigned int getStringId(const char* str);     // 0x00683280
void setCurrentLoop(unsigned int loopId);      // 0x0067c390
void setActiveLoop(unsigned int loopId);       // 0x0067c590
void unregisterLoop(unsigned int loopId);      // 0x006834d0
bool isApplicationActive();                    // 0x00439fa0
void sleepMs(int ms);                          // 0x00ab4b40
char checkContinueLoop();                      // 0x00683450 (returns non-zero to continue)
bool initFramework();                          // 0x0068d010
void initGameObject();                         // 0x0068ac80
void initFrontendToGameTransition();           // 0x0060b610
void shutdown();                               // 0x00607c30

// Global variables (addresses from Ghidra)
extern int* g_licenseObject;                   // DAT_01129a74
extern char g_transitionFlag;                  // DAT_01129a70
extern char g_transitionDone;                  // DAT_01129a71

// Vtable pointer for the main loop object (from PTR_LAB_00d5a21c)
extern void* g_mainObjectVtable;

// Stack-based object used for initial registration of loops
struct MainLoopData {
    void* vtable;          // +0x00: pointer to vtable
    unsigned int id;       // +0x04: loop ID
    unsigned int pad1;     // +0x08
    unsigned int pad2;     // +0x0C
    unsigned int pad3;     // +0x10
    unsigned int pad4;     // +0x14
    unsigned int pad5;     // +0x18
    unsigned int pad6;     // +0x1C
    unsigned int pad7;     // +0x20
};

void gameMainLoop() {
    memoryInit(0);
    systemInit();

    // Check license
    int licenseOk = checkLicense();
    if (licenseOk == 0) {
        int* licenseObj = getLicenseObject();
        // Call vtable[2] (some license method)
        void* vtable = *(void**)licenseObj;
        void (*licenseFunc)(int*) = (void (*)(int*))((void**)vtable)[2];
        licenseFunc(licenseObj);
        releaseLicenseObject(licenseObj);
    }

    // Prepare stack data for loop registration
    unsigned int loopIdInitOnce = 0;           // local_248
    unsigned int pad0 = 0;                     // local_23c
    unsigned int pad1 = 0;                     // local_238
    unsigned int pad2 = 0;                     // local_234

    // Function pointers for loop callbacks (from decompiled constants)
    void* initOnceCallback = (void*)0x009ce820;     // local_24c
    void* gameLoopCallback = (void*)0x009d0420;     // local_244
    void* frontendLoopCallback = (void*)0x009d01a0; // local_240

    // Register first callback (initOnce? actually just sets some global? see FUN_004839f0)
    // This call seems to initialize something with the first callback.
    // The decompiled shows: FUN_004839f0(&local_24c); which takes address of struct.
    // We'll represent it as a struct pointer.
    struct LoopRegistration {
        void* callbackInitOnce;
        void* callbackGame;
        void* callbackFrontend;
        unsigned int id;
        unsigned int pad[4];
    };
    LoopRegistration reg;
    reg.callbackInitOnce = initOnceCallback;
    reg.callbackGame = gameLoopCallback;
    reg.callbackFrontend = frontendLoopCallback;
    reg.id = 0;
    // FUN_004839f0 likely processes this registration
    // This function is poorly named, but we can leave it as a placeholder.
    // It probably stores or initializes the callback table.
    // We'll call it processMainLoopRegistration for now.
    // address 0x004839f0 is used.
    auto processMainLoopRegistration = (void (*)(LoopRegistration*))0x004839f0;
    processMainLoopRegistration(&reg);

    // Another init
    auto func_00412c50 = (void (*)())0x00412c50;
    func_00412c50();

    // Check framework init
    bool frameworkReady = initFramework();
    if (frameworkReady) {
        // Setup stack-based main loop object
        void* stackObject[35]; // appuStack_208, 35 pointers
        char stackBuffer1[44]; // auStack_17c
        char stackBuffer2[336]; // auStack_150

        // Set vtable pointer
        stackObject[0] = &g_mainObjectVtable; // PTR_LAB_00d5a21c

        // Initialize game object (likely creates the main game singleton)
        initGameObject(); // FUN_0068ac80

        // Register loops
        unsigned int gameLoopId = getStringId("GameMainLoop");
        MainLoopData mainLoopData;
        mainLoopData.vtable = &g_mainObjectVtable; // PTR_FUN_00d5a1f8
        mainLoopData.id = 0;
        mainLoopData.pad1 = 0;
        mainLoopData.pad2 = 0;
        mainLoopData.pad3 = 0;
        mainLoopData.pad4 = 0;
        mainLoopData.pad5 = 0;
        mainLoopData.pad6 = 0;
        mainLoopData.pad7 = 0;

        unsigned int initOnceLoopId = getStringId("InitOnceMainLoop");
        registerMainLoop(initOnceLoopId, &mainLoopData);

        setCurrentLoop(gameLoopId);

        registerMainLoop(gameLoopId, &stackBuffer2); // auStack_150 as data

        setActiveLoop(gameLoopId);

        unsigned int frontendLoopId = getStringId("FrontendMainLoop");
        registerMainLoop(frontendLoopId, &stackBuffer1); // auStack_17c as data

        unregisterLoop(initOnceLoopId);

        // Main loop
        char continueFlag;
        do {
            if (isApplicationActive()) {
                continueFlag = checkContinueLoop(); // returns non-zero to continue
            } else {
                // Application not active, sleep/idle
                sleepMs(0); // wait for message or yield
                continueFlag = 1; // not sure, decompiled sets local_24c to 0 and calls FUN_00ab4b40(&local_24c)? Actually does: local_24c = 0; FUN_00ab4b40(&local_24c); That suggests a sleep with a timeout pointer.
                // Simplify as sleep(0)
                sleepMs(0);
                // Since original sets local_24c to null and passes address, we'll mimic but for clarity use sleepMs(0).
            }

            // Check frontend-to-game transition flag
            if (g_transitionFlag != 0) {
                if (g_transitionDone == 0) {
                    g_transitionDone = 1;
                    initFrontendToGameTransition(0);

                    // Check if current loop changed from frontend to game
                    void* oldLoopData = (void*)0; // not stored in decompiled
                    // Actually original code:
                    // ppuVar1 = DAT_0112980c[1]; (some global pointer)
                    // then checks if current loop is frontend
                    unsigned int curLoop = getStringId("GameMainLoop");
                    void* currentLoopData = (void*)getCurrentLoopData(curLoop); // FUN_006833d0 returns pointer
                    // Reconstructed logic:
                    void* ppuVar1 = *(void**)(g_mainObjectVtable + 4); // DAT_0112980c is a pointer to an array of pointers? Actually DAT_0112980c is a global pointer to array of pointers, and [1] is second element.
                    // We'll simplify: assume we have a function getCurrentLoopData that returns pointer.
                    auto getCurrentLoopData = (void* (*)(unsigned int))0x006833d0;
                    void* gameLoopData = getCurrentLoopData(gameLoopId);
                    if (ppuVar1 != gameLoopData) {
                        void* frontendLoopData = getCurrentLoopData(frontendLoopId);
                        if (ppuVar1 == frontendLoopData) {
                            // Switch from frontend to game
                            // FUN_0067c770 likely does the actual transition
                            auto switchLoop = (void (*)())0x0067c770;
                            switchLoop();
                        }
                    }
                }
                g_transitionFlag = 0;
            }
        } while (continueFlag != 0);

        // Shutdown
        shutdown(); // FUN_00607c30
        exit(0);
    }
    exit(0);
}