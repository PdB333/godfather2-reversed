// FUNC_NAME: Animated::Animated
// Function address: 0x006da325
// Constructor for Animated class. Initializes vtable, linked list node, float data, and inserts into global list.

#include <cstdint>

// Forward declarations
void FUN_004daf90(int* listHead); // Remove node from linked list
void FUN_006da2b0(); // Base class constructor or additional init

// Global constants (from data references)
extern uint32_t DAT_00d5780c; // Some global value
extern uint32_t DAT_00d5cf70; // Another global value
extern void* PTR_FUN_00d5f5b0; // Vtable pointer for Animated

class Animated {
public:
    // Vtable pointer at +0x00
    void* vtable;
    // +0x04: some integer (maybe ID or handle)
    int field_04;
    // +0x08: byte flag
    char field_08;
    // +0x0C: padding? Actually byte at +0x08, then +0x09? Wait, offset 2 words = 8 bytes, so field_08 is at byte offset 8? But param_1[2] is at offset 8 bytes, but it's a char, so it's at +0x08. Then param_1[3] is at +0x0C (int). So structure:
    // +0x00: vtable
    // +0x04: int field_04
    // +0x08: char field_08
    // +0x0C: int field_0C (initialized to 0xFF)
    // +0x10: int* next (linked list)
    // +0x14: int* prev (linked list)
    // +0x18: int field_18? Actually param_1[4] is at +0x10, param_1[5] at +0x14, param_1[8] at +0x20, etc. So offsets:
    // +0x00: vtable
    // +0x04: int field_04
    // +0x08: char field_08
    // +0x0C: int field_0C
    // +0x10: int* next
    // +0x14: int* prev
    // +0x18: int field_18? (param_1[6]? Actually param_1[6] is not used, so skip)
    // +0x1C: int field_1C? (param_1[7] not used)
    // +0x20: float field_20 (param_1[8])
    // +0x24: uint32_t field_24 (param_1[9]) = DAT_00d5780c
    // +0x28: uint32_t field_28 (param_1[10]) = DAT_00d5cf70
    // +0x2C: uint32_t field_2C (param_1[0xB]) = same
    // +0x30: float field_30 (param_1[0xC]) = in_XMM1_Da
    // +0x34: float field_34 (param_1[0xD]) = same
    // +0x38: float field_38 (param_1[0xE]) = same
    // +0x3C: float field_3C (param_1[0xF]) = same
    // +0x40: int field_40 (param_1[0x10]) = unaff_EBX
    // +0x44: int field_44? (param_1[0x11] not used)
    // ...
    // +0x50: uint32_t field_50 (param_1[0x14]) = copy of field_24
    // +0x54: uint32_t field_54 (param_1[0x15]) = DAT_00d5780c
    // +0x58: float field_58 (param_1[0x16]) = in_XMM1_Da
    // Total size at least 0x5C bytes.

    // Constructor
    void* __fastcall Animated(
        int param_edx,          // in_EAX (second parameter in EDX)
        int param_ebx,          // unaff_EBX (third parameter in EBX)
        float param_xmm0,       // in_XMM0_Da
        float param_xmm1,       // in_XMM1_Da
        bool zeroFlag           // in_ZF (from previous comparison)
    ) {
        // Initialize fields
        this->field_04 = param_ebx;
        this->field_08 = (char)param_ebx;
        this->field_0C = 0xFF;
        this->vtable = &PTR_FUN_00d5f5b0;
        this->next = (int*)param_ebx;
        this->prev = (int*)param_ebx;
        this->field_20 = param_xmm0;
        this->field_24 = DAT_00d5780c;
        this->field_28 = DAT_00d5cf70;
        this->field_2C = DAT_00d5cf70;
        this->field_30 = param_xmm1;
        this->field_34 = param_xmm1;
        this->field_38 = param_xmm1;
        this->field_3C = param_xmm1;
        this->field_40 = param_ebx;

        // Linked list insertion
        int* listHead = &this->next; // piVar1 = param_1 + 4
        int newHead;
        if (zeroFlag) {
            newHead = 0;
        } else {
            newHead = param_edx + 0x48; // in_EAX + 0x48
        }

        if (*listHead != newHead) {
            if (*listHead != (int*)param_ebx) {
                FUN_004daf90(listHead); // Remove old head
                param_xmm1 = 0.0f;
            }
            *listHead = (int*)newHead;
            if (newHead != 0) {
                this->prev = *(int**)(newHead + 4); // param_1[5] = *(iVar3+4)
                *(int**)(newHead + 4) = listHead; // *(iVar3+4) = piVar1
            }
        }

        // Call base constructor or additional init
        FUN_006da2b0();

        // Final assignments
        this->field_50 = this->field_24; // copy of DAT_00d5780c
        this->field_08 = (char)param_ebx;
        this->field_54 = DAT_00d5780c;
        this->field_58 = param_xmm1;

        return this;
    }
};