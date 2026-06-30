// FUNC_NAME: Engine::initialize
// Address: 0x004a59c0
// Role: Initializes the engine subsystem. Calls global initialization and then initializes a sub-component at offset 0x20.

class Engine {
public:
    void __thiscall initialize();
private:
    // Unknown members 0x00–0x1F
    char _padding[0x20];
    // Subsystem object at +0x20
    void* _subsystem; // size unknown; placeholder
};

// External helper functions (from 0x004a4ce0, 0x004bd160)
extern void engineGlobalsInit(void);
extern void subsystemInit(void* subsystem);

void Engine::initialize() {
    engineGlobalsInit();
    subsystemInit(reinterpret_cast<char*>(this) + 0x20);
}