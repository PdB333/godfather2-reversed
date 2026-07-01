//FUNC_NAME: SelectSlotManager::SelectSlotManager
// Function address: 0x008a0640
// Constructor for the radial menu / select slot manager.
// Initializes linked lists, vectors, message strings, and sub-objects.

#include <cstdint>

// Forward declarations for external functions
void initSubObject1(); // 0x0089e820
void initSubObject2(); // 0x0089eb80
void setString(uint32_t* strObj, const char* text); // 0x00408240
void registerMessage(uint32_t* strObj); // 0x00408680
void initSelectSlotList(SelectSlotManager* this); // 0x00898d40

// Static string objects (global data)
extern uint32_t DAT_01130278; // "iMsgSelectslotNone"
extern uint32_t DAT_01130300; // "iMsgSelectslotLeft"
extern uint32_t DAT_011303c0; // "iMsgSelectslotTopLeft"
extern uint32_t DAT_011301c8; // "iMsgSelectslotTop"
extern uint32_t DAT_01130280; // "iMsgSelectslotTopRight"
extern uint32_t DAT_011301a0; // "iMsgSelectslotRight"
extern uint32_t DAT_011304e0; // "iMsgSelectslotBottomRight"
extern uint32_t DAT_01130490; // "iMsgSelectslotBottom"
extern uint32_t DAT_011304c0; // "iMsgSelectslotBottomLeft"
extern uint32_t DAT_011304b8; // "iMsgSelectslotPadDown"
extern uint32_t DAT_01130250; // "iMsgSelectslotPadUp"
extern uint32_t DAT_011302d8; // "iMsgSelectslotPadRight"

// Vtable symbols (external)
extern void* PTR_FUN_00e2f19c;
extern void* PTR_FUN_00d78830;
extern void* PTR_LAB_00d78820;

// Structure for a circular doubly linked list sentinel node
struct ListNode {
    ListNode* next;
    ListNode* prev;
};

// Main class
struct SelectSlotManager {
    // +0x00: vtable pointer (base)
    void* vtable0;
    // +0x04: vtable pointer (derived) / also first list sentinel? Actually vtable then list
    void* vtable1;
    // +0x08: some integer
    int32_t field_08;
    // +0x0C: some integer
    int32_t field_0C;
    // +0x10: first list sentinel (8 bytes)
    ListNode list1;
    // +0x18: padding? Actually list1 occupies 8 bytes, so next at +0x18? But offsets are in words.
    // Let's recalc: param_1[4] is offset 16 bytes, so list1 starts at +0x10.
    // Then param_1[7] is offset 28 bytes, so list2 at +0x1C? Wait, param_1 is int*, so index 7 is byte offset 28.
    // So list2 at +0x1C (28). But we have 5 lists at indices 4,7,10,13,16 -> bytes 16,28,40,52,64.
    // So list1 at +0x10, list2 at +0x1C, list3 at +0x28, list4 at +0x34, list5 at +0x40.
    ListNode list2; // +0x1C
    ListNode list3; // +0x28
    ListNode list4; // +0x34
    ListNode list5; // +0x40
    // +0x4C: first array of 3 vectors (each 3 floats) at param_1+0x15 (index 21 -> byte 84)
    // Actually index 21 is byte 84, so after list5 (ends at +0x48), there is padding? We'll place array1 at +0x54? Let's compute properly.
    // param_1+0x15 = param_1 + 21*4 = 84 bytes. So array1 starts at offset 84.
    // Similarly array2 at param_1+0x21 = 33*4 = 132 bytes.
    // We'll define arrays as float[3][3] or similar.
    float array1[3][3]; // +0x54 (84)
    // After array1 (9 floats = 36 bytes) ends at +0x78 (120). Then there is a gap until array2 at +0x84 (132).
    float array2[3][3]; // +0x84 (132)
    // Then fields at indices 0x2b (43*4=172), 0x2c (176), 0x2d (180), 0x2e (184), 0x2f (188), 0x30 (192), 0x31 (196), 0x32 (200), 0x33 (204), 0x34 (208)
    // Also bytes at 0xd1 (209), 0xd2 (210), 0xd3 (211)
    int32_t field_2b; // +0xAC (172)
    int32_t field_2c; // +0xB0 (176)
    int32_t field_2d; // +0xB4 (180)
    int32_t field_2e; // +0xB8 (184)
    int32_t field_2f; // +0xBC (188)
    int32_t field_30; // +0xC0 (192)
    int32_t field_31; // +0xC4 (196)
    int32_t field_32; // +0xC8 (200)
    int32_t field_33; // +0xCC (204)
    uint8_t byte_34; // +0xD0 (208) - actually param_1+0x34 is index 52? Wait, param_1 is int*, so param_1+0x34 is offset 0x34*4 = 0xD0 bytes. So byte at +0xD0.
    uint8_t byte_d1; // +0xD1 (209)
    uint8_t byte_d2; // +0xD2 (210)
    uint8_t byte_d3; // +0xD3 (211)
};

// Global pointer set at start
SelectSlotManager* g_selectSlotManager = nullptr; // DAT_01129914

SelectSlotManager* __fastcall SelectSlotManager::SelectSlotManager(SelectSlotManager* this)
{
    // Store global pointer
    g_selectSlotManager = this;

    // Set vtable pointers (base and derived)
    this->vtable1 = &PTR_FUN_00e2f19c; // +0x04
    this->field_08 = 1;                // +0x08
    this->field_0C = 0;                // +0x0C
    this->vtable0 = &PTR_FUN_00d78830; // +0x00
    this->vtable1 = &PTR_LAB_00d78820; // +0x04 (overwrites previous)

    // Initialize 5 circular doubly linked lists (sentinel nodes)
    // Each list: next and prev point to itself
    this->list1.next = &this->list1;
    this->list1.prev = &this->list1;
    // list2 at +0x1C
    this->list2.next = &this->list2;
    this->list2.prev = &this->list2;
    // list3 at +0x28
    this->list3.next = &this->list3;
    this->list3.prev = &this->list3;
    // list4 at +0x34
    this->list4.next = &this->list4;
    this->list4.prev = &this->list4;
    // list5 at +0x40
    this->list5.next = &this->list5;
    this->list5.prev = &this->list5;

    // Initialize first array of 3 vectors (3x3 floats) to zero
    for (int i = 0; i < 3; i++) {
        this->array1[i][0] = 0.0f;
        this->array1[i][1] = 0.0f;
        this->array1[i][2] = 0.0f;
    }

    // Call sub-constructor 1
    initSubObject1(); // 0x0089e820

    // Initialize second array of 3 vectors to zero
    for (int i = 0; i < 3; i++) {
        this->array2[i][0] = 0.0f;
        this->array2[i][1] = 0.0f;
        this->array2[i][2] = 0.0f;
    }

    // Call sub-constructor 2
    initSubObject2(); // 0x0089eb80

    // Zero out many fields
    this->field_2b = 0;
    this->field_2c = 0;
    this->field_2d = 0;
    this->field_2e = 0;
    this->field_30 = 0;
    this->field_31 = 0;
    this->field_32 = 0;
    this->field_2f = 0;
    this->byte_34 = 0;
    this->byte_d1 = 0;
    this->byte_d2 = 0;
    this->field_33 = 0;
    this->byte_d3 = 0;

    // Assign message strings to static String objects
    setString(&DAT_01130278, "iMsgSelectslotNone");
    setString(&DAT_01130300, "iMsgSelectslotLeft");
    setString(&DAT_011303c0, "iMsgSelectslotTopLeft");
    setString(&DAT_011301c8, "iMsgSelectslotTop");
    setString(&DAT_01130280, "iMsgSelectslotTopRight");
    setString(&DAT_011301a0, "iMsgSelectslotRight");
    setString(&DAT_011304e0, "iMsgSelectslotBottomRight");
    setString(&DAT_01130490, "iMsgSelectslotBottom");
    setString(&DAT_011304c0, "iMsgSelectslotBottomLeft");
    setString(&DAT_011304b8, "iMsgSelectslotPadDown");
    setString(&DAT_01130250, "iMsgSelectslotPadUp");
    setString(&DAT_011302d8, "iMsgSelectslotPadRight");

    // Initialize the select slot list (sub-object at offset 4? Actually param_1+1)
    initSelectSlotList(this + 1); // 0x00898d40

    // Register each message string (possibly add to a global list)
    registerMessage(&DAT_01130278);
    registerMessage(&DAT_01130300);
    registerMessage(&DAT_011303c0);
    registerMessage(&DAT_011301c8);
    registerMessage(&DAT_01130280);
    registerMessage(&DAT_011301a0);
    registerMessage(&DAT_011304e0);
    registerMessage(&DAT_01130490);
    registerMessage(&DAT_011304c0);
    registerMessage(&DAT_011304b8);
    registerMessage(&DAT_01130250);
    registerMessage(&DAT_011302d8);

    return this;
}