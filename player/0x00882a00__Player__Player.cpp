// FUNC_NAME: Player::Player
// Address: 0x00882a00
// Role: Constructor for Player class, sets up vtable pointers, links to parent entity, sets flags

#include <cstdint>

class Entity; // forward declaration
class Player;

// Constants for offsets (relative to this)
#define OFFSET_PARENT_SUB_PTR   0x48  // param_1[0x12]
#define OFFSET_VTABLE2          0x50  // param_1[0x14]
#define OFFSET_VTABLE3          0x5C  // param_1[0x17]
#define OFFSET_FLAG1            0x54  // param_1[0x15]
#define OFFSET_NODE_NEXT        0x60  // param_1[0x18]
#define OFFSET_NODE_PREV        0x64  // param_1[0x19]
#define OFFSET_PARENT_ENTITY    0x68  // param_1[0x1a]
#define OFFSET_FLAGS            0x78  // param_1[0x1e]
#define OFFSET_SOME_VALUE       0x80  // param_1[0x20]

// External function declarations (assumed)
int Entity::Entity(int param1, int param2);  // base constructor
int* getSomeManager(DAT_01131018); // unknown function returning pointer to manager
void setSomeComponentFlag(void* ptr, int flag); // FUN_009aefd0

// Global pointers (from data reference)
extern int* gSomeGlobal1;  // DAT_00d76e70
extern int* gSomeManager1; // DAT_01131018
extern int* gSomeManager2; // DAT_01131084

// Vtable pointers (from data labels)
extern void* VTABLE_PLAYER_MAIN; // &PTR_LAB_00d76eb4
extern void* VTABLE_PLAYER_2;    // &PTR_FUN_00d76ea0
extern void* VTABLE_PLAYER_3;    // &PTR_LAB_00d76e9c
extern void* VTABLE_INITIAL_2;   // &PTR_LAB_00d58278
extern void* VTABLE_PURECALL;    // &PTR___purecall_00d76e98

// Reconstructed constructor
Player* __thiscall Player::Player(int creationParam1, int creationParam2)
{
    // Call base class constructor (likely Entity)
    Entity::Entity(creationParam1, creationParam2);

    // Set up vtable pointers for multiple inheritance
    this->offset34(OFFSET_VTABLE3) = VTABLE_PURECALL;    // param_1[0x17] = &PTR___purecall_00d76e98
    this->offset28(OFFSET_VTABLE2) = VTABLE_INITIAL_2;   // param_1[0x14] = &PTR_LAB_00d58278
    this->mainVtable = VTABLE_PLAYER_MAIN;                // *param_1 = &PTR_LAB_00d76eb4
    this->offset28(OFFSET_VTABLE2) = VTABLE_PLAYER_2;    // param_1[0x14] = &PTR_FUN_00d76ea0
    this->offset34(OFFSET_VTABLE3) = VTABLE_PLAYER_3;    // param_1[0x17] = &PTR_LAB_00d76e9c

    // Initialize other fields
    this->offset28(OFFSET_FLAG1) = 0;                     // param_1[0x15] = 0
    this->offset40(OFFSET_PARENT_ENTITY) = 0;             // param_1[0x1a] = 0
    this->offset60(OFFSET_FLAGS) = 0;                     // param_1[0x1e] = 0
    this->offset64(OFFSET_SOME_VALUE) = gSomeGlobal1;    // param_1[0x20] = DAT_00d76e70

    // Compute parent entity pointer if applicable
    int* parentSubPtr = reinterpret_cast<int*>(this->offset36(OFFSET_PARENT_SUB_PTR)); // param_1[0x12]
    int* parentEntityBase = nullptr;
    if (parentSubPtr != nullptr) {
        parentEntityBase = parentSubPtr - 0x48;  // iVar3 = param_1[0x12] - 0x48
    }
    this->offset40(OFFSET_PARENT_ENTITY) = parentEntityBase; // param_1[0x1a] = iVar3

    // Set flag in parent entity if it exists
    if (parentEntityBase != nullptr) {
        uint32_t* flagsPtr = reinterpret_cast<uint32_t*>(parentEntityBase + 0xc88);
        if ((*flagsPtr | 2) != *flagsPtr) {
            // Call virtual function on parent's vtable
            (**(code**)(*(int*)(parentEntityBase + 0x58) + 0x28))(0x10);
            *flagsPtr |= 2;
        }
    }

    // Check global manager and set component flag
    if (this->offset40(OFFSET_PARENT_ENTITY) != 0) {
        int* manager1 = reinterpret_cast<int*>(getSomeManager(gSomeManager1)); // FUN_0043b870(DAT_01131018)
        if (manager1 != nullptr) {
            setSomeComponentFlag(this->offset28(OFFSET_VTABLE2), 0x8000); // FUN_009aefd0(param_1+0x14, 0x8000)
        }
    }

    // Set flags on this object
    this->offset60(OFFSET_FLAGS) |= 8; // param_1[0x1e] = param_1[0x1e] | 8

    // Link this object into a doubly linked list of the parent entity
    if (this->offset40(OFFSET_PARENT_ENTITY) != 0) {
        int* manager2 = reinterpret_cast<int*>(getSomeManager(gSomeManager2)); // FUN_0043b870(DAT_01131084)
        if (manager2 != nullptr) {
            // Insert at head of list: parentEntity->listHead and parentEntity->listTail
            this->offset44(OFFSET_NODE_PREV) = reinterpret_cast<int*>(manager2 + 0x1c); // param_1[0x19] = *(manager2+0x1c)
            int* listNextPtr = this->offset42(OFFSET_NODE_NEXT); // piVar1 = param_1+0x18
            *listNextPtr = manager2 + 0x18;                       // *piVar1 = manager2+0x18
            *(int**)(manager2 + 0x1c) = listNextPtr;              // *(manager2+0x1c) = piVar1
            *(int**)(this->offset44(OFFSET_NODE_PREV)) = listNextPtr; // *(param_1[0x19]) = piVar1
        }
    }

    return this;
}

// Helper functions to access fields by int* offsets (for readability, not optimal)
inline int*& offset28(int* base, int offset) { return *(int**)((char*)base + offset); }
inline int& offset34(int* base, int offset) { return *(int*)((char*)base + offset); }
inline int*& offset40(int* base, int offset) { return *(int**)((char*)base + offset); }
inline int*& offset42(int* base, int offset) { return *(int**)((char*)base + offset); }
inline int*& offset44(int* base, int offset) { return *(int**)((char*)base + offset); }
inline int& offset60(int* base, int offset) { return *(int*)((char*)base + offset); }
inline int& offset64(int* base, int offset) { return *(int*)((char*)base + offset); }