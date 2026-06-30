// FUNC_NAME: ModuleManager::getOrCreateSingleton
#include <cstddef>

// Forward declarations (actual implementations elsewhere)
extern int* FUN_005bb3a0(); // Returns some manager context
extern int FUN_005a86f0(void* (*constructor)(void*, int)); // Allocates and constructs
extern void FUN_0059c690(); // Likely debug log or initialization

// Static singleton pointers (initialized to NULL by default)
static int* g_singletonModule1 = nullptr; // DAT_012055e0
static int* g_singletonModule2 = nullptr; // DAT_012055e4
static int* g_singletonModule3 = nullptr; // DAT_012055e8

// Allocator function pointer type (matches FUN_005a86f0 pattern)
typedef void* (*ConstructorFunc)(void*);

// Helper to allocate and construct a singleton
static inline int* createSingleton(ConstructorFunc constructor)
{
    int* instance = static_cast<int*>((*reinterpret_cast<void* (**)(int, int)>)(0x0119caf0))(0x50, 0));
    if (instance == nullptr)
        return nullptr;
    instance = reinterpret_cast<int*>(FUN_005a86f0(reinterpret_cast<void* (*)(void*, int)>(constructor)));
    FUN_0059c690();
    return instance;
}

int ModuleManager::getOrCreateSingleton(int param_1)
{
    if (param_1 != 0)
    {
        // Scan the string at param_1 (ignored, possibly for debug)
        char* str = reinterpret_cast<char*>(param_1);
        while (*str++);

        int* context = FUN_005bb3a0();
        if (context != nullptr)
        {
            int typeId = *(context + 1); // offset +4

            if (typeId == 1)
            {
                if (g_singletonModule1 == nullptr)
                    g_singletonModule1 = createSingleton(FUN_005bb470);
                return reinterpret_cast<int>(g_singletonModule1);
            }
            else if (typeId == 2)
            {
                if (g_singletonModule2 == nullptr)
                    g_singletonModule2 = createSingleton(FUN_005bb580);
                return reinterpret_cast<int>(g_singletonModule2);
            }
            else if (typeId == 3)
            {
                if (g_singletonModule3 == nullptr)
                    g_singletonModule3 = createSingleton(FUN_005bb5c0);
                return reinterpret_cast<int>(g_singletonModule3);
            }
        }
    }
    return 0;
}