// FUNC_NAME: Entity::constructor
// This function appears to be a constructor for an Entity derived class,
// initializing numerous fields, allocating a sub-object (0x60 bytes),
// and inserting itself into a linked list. The specific class name is uncertain,
// but based on offset patterns and called functions, it resembles an EA EARS object.

#include <cstdint>

// Forward declarations for unknown functions
void FUN_004ac120(uint32_t, uint32_t);
uint32_t FUN_009c8e80(uint32_t size);
void FUN_009a61d0();
uint32_t FUN_0043b870(uint32_t);
uint32_t FUN_00800a90();          // Possibly returns a global object pointer
uint32_t FUN_0077dd80();
void FUN_00716420(uint32_t);
float FUN_00712ef0(uint32_t);
void FUN_009a4460(int32_t);
uint32_t *FUN_007ffdf0();        // Returns a linked list head node
void FUN_004daf90(int32_t *node);
char FUN_0076bbc0(int32_t);

// Global constants used
extern uint32_t DAT_00d5ccf8;
extern float DAT_00d5c454;
extern float DAT_00d5d934;
extern uint32_t DAT_0112afe8;
extern void *PTR_LAB_00d6492c;  // vtable pointer

// Hypothetical entity struct with field offsets
class Entity {
public:
    // +0x00 vtable pointer (set to &PTR_LAB_00d6492c)
    // +0x12 int32_t baseSize;  // size of base class? used in calculation
    // +0x15 int32_t unused1;
    // +0x16 uint32_t field_0x16; // initialized from DAT_00d5ccf8
    // +0x17 uint32_t field_0x17; // same value
    // +0x18 uint32_t flags;    // bit field flags
    // +0x1c int32_t field_0x1c; // set to 3
    // +0x1d int32_t field_0x1d; // zeroed
    // +0x1e uint32_t field_0x1e; // result of FUN_0043b870
    // +0x25 int32_t field_0x25; // zeroed
    // +0x26 int32_t *listNext; // linked list node (next)
    // +0x27 int32_t *listPrev; // linked list node (prev)
    // +0x28 uint32_t field_0x28; // set from list head's +8
    // +0x29 int32_t field_0x29; // zeroed
    // +0x2a int32_t field_0x2a; // zeroed
    // +0x2b int32_t field_0x2b; // zeroed
    // +0x2c void *subObject;   // pointer to allocated 0x60 byte buffer
    // +0x2d int32_t field_0x2d; // zeroed
    // +0x2e int32_t field_0x2e; // set to 8
    // +0x30 uint32_t flags2;   // ORed with 0x20000000
    // +0x36 float field_0x36;  // distance squared
    // +0x3b uint32_t field_0x3b; // read from subObject offset +0x5f0
    // +0x42 void *subObjectRef; // pointer to subObject (same as +0x2c)
    // +0x43 float maxDistance;  // initial float value
    // +0x44 int32_t field_0x44; // computed offset
};

// Constructor implementation
Entity *__thiscall Entity::constructor(Entity *this, uint32_t arg1, uint32_t arg2) {
    int32_t iVar4;
    char cVar2;
    uint32_t uVar3;
    int32_t *piVar1;
    int32_t *piVar5;
    float fVar7;

    // Call base class constructor with arguments
    FUN_004ac120(arg1, arg2);

    uVar3 = DAT_00d5ccf8;
    this->vtable = &PTR_LAB_00d6492c;           // +0x00
    // Direct offset assignments (using pointer arithmetic for clarity)
    this->field_0x16 = uVar3;                    // +0x16
    this->field_0x17 = uVar3;                    // +0x17
    this->flags = 0;                             // +0x18
    this->field_0x1d = 0;                        // +0x1d
    this->field_0x25 = 0;                        // +0x25
    piVar1 = &this->listNext;                    // +0x26
    *piVar1 = nullptr;                           // next
    this->listPrev = nullptr;                    // +0x27
    this->field_0x28 = 0;                        // +0x28
    this->field_0x29 = 0;                        // +0x29
    this->field_0x2a = 0;                        // +0x2a
    this->field_0x2b = 0;                        // +0x2b
    uVar3 = FUN_009c8e80(0x60);                  // allocate 0x60 bytes
    this->subObject = reinterpret_cast<void*>(uVar3); // +0x2c
    this->field_0x2d = 0;                        // +0x2d
    this->field_0x2e = 8;                        // +0x2e
    FUN_009a61d0();                              // unknown static init

    this->field_0x15 = 0;                        // +0x15
    this->flags = 0;                             // +0x18 again?
    if (this->baseSize == 0) {                   // +0x12
        iVar4 = 0;
    } else {
        iVar4 = this->baseSize - 0x48;
    }
    this->field_0x44 = iVar4;                    // +0x44

    // If baseSize is 0 or exactly 0x48, skip; else get something
    if ((this->baseSize == 0) || (this->baseSize == 0x48)) {
        uVar3 = 0;
    } else {
        uVar3 = FUN_0043b870(DAT_0112afe8);
    }
    this->field_0x1e = uVar3;                    // +0x1e

    iVar4 = FUN_00800a90();
    if (iVar4 != 0) {
        this->maxDistance = *reinterpret_cast<float*>(iVar4 + 0x34c); // +0x43
    }

    uVar3 = FUN_0077dd80();
    FUN_00716420(uVar3);
    float tempFloat = FUN_00712ef0(uVar3);
    if ((tempFloat < this->maxDistance) || (iVar4 == 0)) {
        this->maxDistance = tempFloat;
    }

    this->field_0x1c = 3;                        // +0x1c
    FUN_009a4460(this->field_0x44);              // +0x44

    fVar7 = this->maxDistance;                   // +0x43
    this->subObjectRef = &this->subObject;       // +0x42 (points to +0x2c)

    if (((this->flags >> 4) & 1) != 0) {
        fVar7 = fVar7 * DAT_00d5c454;
    }
    if (fVar7 < DAT_00d5d934) {
        fVar7 = DAT_00d5d934;
    }

    // Read from subObject + different offsets
    this->field_0x3b = *reinterpret_cast<uint32_t*>(this->field_0x44 + 0x5f0); // +0x3b
    this->flags2 |= 0x20000000;                  // +0x30
    this->field_0x36 = fVar7 * fVar7;            // +0x36

    piVar5 = reinterpret_cast<int32_t*>(FUN_007ffdf0());
    if (piVar1 != piVar5) {
        iVar4 = *piVar5;
        if (*piVar1 != iVar4) {
            if (*piVar1 != 0) {
                FUN_004daf90(piVar1);            // remove from list
            }
            *piVar1 = iVar4;
            if (iVar4 != 0) {
                this->listPrev = *reinterpret_cast<uint32_t*>(iVar4 + 4);
                *reinterpret_cast<int32_t**>(iVar4 + 4) = piVar1; // update prev pointer
            }
        }
    }
    this->field_0x28 = piVar5[2];                // +0x28

    cVar2 = FUN_0076bbc0(this->field_0x44);
    if (cVar2 != '\0') {
        this->flags |= 0x40;                     // +0x18 bit 6
    }

    return this;
}