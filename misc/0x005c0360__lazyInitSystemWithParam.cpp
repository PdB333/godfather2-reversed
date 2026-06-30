// FUNC_NAME: lazyInitSystemWithParam
void FUN_005c0360(int param) {
    int iVar2;
    if (param == 0) {
        iVar2 = 0;
    } else {
        iVar2 = param + 4; // Offset to a member field (+0x4)
    }
    // Global handle for the system
    extern int g_systemHandle;
    if (g_systemHandle == 0) {
        // Allocate system memory (size 200, flags 0)
        int allocResult = func_memAlloc(200, 0);
        if (allocResult != 0) {
            g_systemHandle = func_constructSystem(); // Returns initialized handle
            func_systemReset();
            func_processSystem(iVar2);
            return;
        }
        // Allocation failed, reset global and call reset
        g_systemHandle = 0;
        func_systemReset();
    }
    func_processSystem(iVar2);
}

extern int func_memAlloc(int size, int flags);
extern int func_constructSystem(void);
extern void func_systemReset(void);
extern void func_processSystem(int param);