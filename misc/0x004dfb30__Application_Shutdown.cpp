// FUNC_NAME: Application_Shutdown

// Global state variables
extern int g_shutdownState;          // 0x01194540 - shutdown progress flag (0 = idle, 2 = shutting down)
extern class Subsystem* g_subsystem1; // 0x012234c8 - e.g., input subsytem
extern class Subsystem* g_subsystem2; // 0x012234d0 - e.g., audio subsytem
extern class Subsystem* g_subsystem3; // 0x012234cc - e.g., network subsytem
extern class Subsystem* g_subsystem4; // 0x012234c4 - e.g., render subsytem
extern class Application* g_app;      // 0x01194538 - main application singleton

extern class ResourceManager* g_rendererManager; // 0x012054c8
extern class ResourceManager* g_audioManager;   // 0x012054c4
extern class ResourceManager* g_resourceManager; // 0x012054c0

// Helper function declarations
void ShutdownSubsystem(void);        // FUN_004dfff0
void DestroyRenderer(void);         // FUN_004e0e10
void FreeResource(void* handle);    // FUN_009c8f10
void FreeMemory(void* ptr);         // FUN_009c8eb0
void DestroyAudio(void);            // FUN_004e0bb0

// Base class for subsystems with a virtual shutdown(int)
class Subsystem {
public:
    virtual void Shutdown(int reason) = 0;
};

// Resource manager class (opaque pointer)
class ResourceManager {
public:
    // ...
};

void Application_Shutdown(void)
{
    // Mark shutdown in progress
    g_shutdownState = 2;

    // Notify subsystems to shut down
    if (g_subsystem1 != nullptr) {
        g_subsystem1->Shutdown(1);
    }
    if (g_subsystem2 != nullptr) {
        g_subsystem2->Shutdown(1);
    }
    if (g_subsystem3 != nullptr) {
        g_subsystem3->Shutdown(1);
    }

    // Generic subsystem shutdown
    ShutdownSubsystem();

    if (g_subsystem4 != nullptr) {
        g_subsystem4->Shutdown(1);
    }

    // Destroy renderer manager
    if (g_rendererManager != nullptr) {
        DestroyRenderer();
        FreeResource(*((void**)g_rendererManager)); // release handle (e.g., renderer resource)
        FreeMemory(g_rendererManager);
        g_rendererManager = nullptr;
    }

    // Destroy audio manager
    if (g_audioManager != nullptr) {
        DestroyAudio();
        FreeResource(*((void**)g_audioManager));
        FreeMemory(g_audioManager);
        g_audioManager = nullptr;
    }

    // Destroy resource manager
    if (g_resourceManager != nullptr) {
        if (*((int*)g_resourceManager) != 0) {
            FreeResource((void*)*((int*)g_resourceManager));
        }
        FreeMemory(g_resourceManager);
        g_resourceManager = nullptr;
    }

    // Finalise shutdown state
    g_shutdownState = 0;

    // Call application's destructor (vtable index 0x0C)
    g_app->Shutdown();   // corresponds to (**(code **)(*g_app + 0x0C))()
    g_app = nullptr;
}