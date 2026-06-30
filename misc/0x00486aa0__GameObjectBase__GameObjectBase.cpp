// FUNC_NAME: GameObjectBase::GameObjectBase

extern void* PTR_FUN_00e337b8;  // vtable for base class
extern void* PTR_LAB_00e337bc;  // vtable for derived class (this)
extern int g_initializedFlag;   // DAT_01223380 - shared global flag

class GameObjectBase {
public:
    void** vtable; // +0x00

    GameObjectBase(byte param_2);
    virtual ~GameObjectBase(); // destructor (not shown)

private:
    void baseInitialize(); // FUN_004872d0 - base class setup
    void cleanup();        // FUN_009c8eb0 - destructor or cleanup call
};

GameObjectBase::GameObjectBase(byte param_2) {
    // Install base class vtable first
    this->vtable = &PTR_FUN_00e337b8;

    // Call base class initializer
    this->baseInitialize();

    // Overwrite with derived class vtable (this class's own vtable)
    this->vtable = &PTR_LAB_00e337bc;

    // Reset global initialization flag
    g_initializedFlag = 0;

    // If bit 0 of param_2 is set, call cleanup (used for immediate destruction)
    if (param_2 & 1) {
        this->cleanup();
    }
}