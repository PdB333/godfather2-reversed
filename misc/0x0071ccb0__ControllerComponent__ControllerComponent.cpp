// FUNC_NAME: ControllerComponent::ControllerComponent

#include <cstdint>

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

// External globals
extern int* g_pManager;            // DAT_0112ad38
extern int* g_pDefaultInstance;    // DAT_00d61e0c

// External function: registers component with manager, returns some ID
extern int RegisterComponent(Vec3* position, int* manager); // FUN_004265d0

class ControllerComponent {
public:
    // Offsets:
    //   +0x00: vtable (void*) - initially zeroed
    //   +0x04: field_4 (int) - zeroed
    //   +0x08: field_8 (int) - zeroed
    //   +0x0C: componentId (int) - returned from RegisterComponent
    //   +0x10: manager (int*) - set to g_pManager
    //   +0x14: field_14 (int) - zeroed
    //   +0x18: field_18 (int) - zeroed
    //   +0x1C: defaultInstance (int*) - set to g_pDefaultInstance
    int* vtable;
    int field_4;
    int field_8;
    int componentId;
    int* manager;
    int field_14;
    int field_18;
    int* defaultInstance;

    // __thiscall constructor
    ControllerComponent() {
        Vec3 zero = { 0, 0, 0 };
        int* mgr = g_pManager;

        componentId = RegisterComponent(&zero, mgr);
        manager = mgr;

        // Call virtual function from manager's vtable at offset +8
        // (assumes manager points to a vtable pointer)
        (*(void(__thiscall**)(void))(*mgr + 8))();

        int* defInst = g_pDefaultInstance;
        vtable = 0;
        field_4 = 0;
        field_8 = 0;
        field_14 = 0;
        field_18 = 0;
        defaultInstance = defInst;
    }
};