// FUNC_00445910: SimGroup::constructInternal
void __fastcall SimGroup::constructInternal(SimGroup *this)
{
    // local variables (used for stack buffer)
    void *localBuffer;
    uint32_t magic;           // 0x2a7ed975
    void (*initFunc)();       // FUN_00447820
    // other locals removed due to being unused

    // Setup vtable pointers (likely for SimGroup or helper object)
    this->vtable = &PTR_FUN_00e311b4;     // +0x00: class vtable
    this->field0x0c = &PTR_LAB_00e311c4; // +0x0C: maybe secondary vtable
    this->field0x14 = &PTR_LAB_00e311d0; // +0x14: vtable override (changed later)

    // Prepare stack buffer: local variable addresses passed to registration
    localBuffer = this;
    magic = 0x2a7ed975;
    initFunc = FUN_00447820; // likely a static initialization function

    // Register this object with the engine?
    FUN_00486cd0(DAT_01223380, &localBuffer); // DAT_01223380 is likely a global register

    // Initialize global singletons (mutex, etc.)
    FUN_00408310(&DAT_0120e93c);
    FUN_004086d0(&DAT_01206760);
    FUN_004086d0(&DAT_0120678c);
    FUN_004086d0(&DAT_01206780);
    FUN_004086d0(&DAT_01206778);

    // Register the class name "SimGroup" with the engine's type system
    FUN_0049c7f0("SimGroup");

    // One-time initialization for the entire SimGroup system
    if ((DAT_01226f54 & 1) == 0)
    {
        DAT_01226f54 |= 1;
        FUN_00484b10(); // Initialize SimGroup subsystem
        _atexit((void (*)())&LAB_00d50760); // Register atexit cleanup
    }

    // Further subsystem initialization
    FUN_00484000();
    FUN_00447fe0();

    // Clear internal buffer (size stored at this[0x1d], buffer at this[0x1c])
    this->field0x78 = 0;
    _memset((void *)this->field0x70, 0, this->field0x74 * 4);

    // Call virtual methods on internal objects stored at field offsets
    // this[0xb5] = offset 0x2D4 (pointer to another object)
    (*(void (**)())(**(int **)(this->field0x2D4) + 0xC))(); // +0xC method on object A

    // this[0x30] = offset 0xC0 (pointer to another object)
    (*(void (**)(void *, int))(**(int **)(this->field0xC0) + 4))(this->field0xB0, 0); // method at vtable+4
    if (this->field0xBC != 0)
    {
        (*(void (**)(void *, int))(**(int **)(this->field0xC0) + 4))(this->field0xBC, 0);
    }
    (*(void (**)())(**(int **)(this->field0xC0) + 0xC))(); // method at vtable+0xC

    // Free two memory blocks (likely attached resources)
    FUN_009c8f10(this->field0x80); // +0x80
    FUN_009c8f10(this->field0x70); // +0x70

    // Call a cleanup/method on SimGroup itself
    FUN_00448590();

    // Free another block
    FUN_009c8f10(this->field0x48); // +0x48

    // Override vtable entry (switch to a "default" or "clean" state)
    this->field0x14 = &PTR_LAB_00e311d4; // +0x14 changed

    // Reset global flag
    DAT_01223410 = 0;

    // Final cleanup
    FUN_0049c640();
    FUN_004083d0();
}