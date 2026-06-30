// FUNC_NAME: AudioDataManager::AudioDataManager
#include <cstdlib> // For malloc (if needed)

class AudioDataManager {
public:
    // Constructor
    AudioDataManager();

    // Static function pointers (set in constructor)
    static void (*g_pFunc1)();  // 0x005cf110
    static void (*g_pFunc2)();  // 0x005cf130
    static void (*g_pFunc3)();  // 0x005cf140

private:
    int field_0;      // +0x00
    int field_4;      // +0x04
    int field_8;      // +0x08
    void* subObject;  // +0x0C (allocated subobject of size 0x1AC)
    int field_4C;     // +0x4C (offset 0x13)
    int field_50;     // +0x50 (offset 0x14)
};

// Global allocation function pointer (likely operator new or custom allocator)
extern void* (*g_pAllocator)(size_t size, int flags); // DAT_0119caf0

// External functions
void __cdecl FUN_005ce310();    // Base initialization
void* __cdecl FUN_00670170();   // Construct subobject (returns pointer)

// Static function definitions (placeholders for actual implementations)
void func0x005cf110();
void func0x005cf130();
void func0x005cf140();

// Static pointer initializations
void (*AudioDataManager::g_pFunc1)() = nullptr;
void (*AudioDataManager::g_pFunc2)() = nullptr;
void (*AudioDataManager::g_pFunc3)() = nullptr;

// Constructor
void __thiscall AudioDataManager::AudioDataManager()
{
    // Clear initial fields
    this->field_0 = 0;
    this->field_4 = 0;
    this->field_8 = 0;

    // Call base initialization
    FUN_005ce310();

    // Clear more fields
    this->field_4C = 0;   // offset 0x4C (0x13 * 4)
    this->field_50 = 0;   // offset 0x50 (0x14 * 4)

    // Set global function pointers (likely static members or vtables)
    g_pFunc1 = &func0x005cf110;  // DAT_01206690
    g_pFunc2 = &func0x005cf130;  // DAT_01206694
    g_pFunc3 = &func0x005cf140;  // _DAT_01206698

    // Allocate subobject of size 0x1AC (428 bytes)
    void* allocResult = g_pAllocator(0x1AC, 0);
    if (allocResult != nullptr) {
        // Construct subobject and store pointer
        this->subObject = FUN_00670170();
    }
    else {
        this->subObject = nullptr;
    }
}