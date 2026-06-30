// FUNC_NAME: initializeEngine
// Function at 0x0060d520: Core engine initialization that registers three system interfaces and calls various subsystem initializers.
// The function takes three interface pointers, stores them globally, increments their reference counts via vtable offset 0x8 (likely AddRef),
// then runs a sequence of init functions. param_2 can be null.
void initializeEngine(void* system1, void* system2, void* system3)
{
    // Global pointers to keep references alive
    extern void* g_pSystem1;  // +0x01205868
    extern void* g_pSystem2;  // +0x0120586c
    extern void* g_pSystem3;  // +0x01205870

    // External globals used later
    extern int g_someColorConstant; // 0x00e2b1a4
    extern unsigned char g_initFlagByte; // 0x01205759
    extern int g_anotherFlag; // 0x01205474

    // Store system interfaces and call their AddRef (virtual function at offset 8)
    g_pSystem1 = system1;
    (*(void (**)(void))((int*)system1[0] + 2))(system1); // AddRef, assuming vtable at +8

    if (system2 != 0)
    {
        g_pSystem2 = system2;
        (*(void (**)(void))((int*)system2[0] + 2))(system2);
    }

    g_pSystem3 = system3;
    (*(void (**)(void))((int*)system3[0] + 2))(system3);

    // Initialize various engine subsystems
    initNetwork();        // FUN_00607990
    initGraphics();       // FUN_006132c0
    initInput();          // FUN_006060a0
    initSound();          // FUN_0061ad30

    g_initFlagByte = 0;   // Clear initialization flag

    initEntitySystem();   // FUN_00608f10

    // Build a color struct on stack (r,g,b?) and pass to renderer setter
    struct { int a; int b; int c; } clearColor; // Stack allocation
    clearColor.a = g_someColorConstant;
    clearColor.b = g_someColorConstant;
    clearColor.c = 0;
    setRendererClearColor(&clearColor); // FUN_00609090

    initScripting();      // FUN_00611c20
    initCamera();         // FUN_004d21e0

    g_anotherFlag = 0;    // Clear another flag

    initPhysics();        // FUN_004c7b40
    initUI();             // FUN_00606110
}