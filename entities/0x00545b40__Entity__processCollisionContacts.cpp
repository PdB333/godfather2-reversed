// FUNC_NAME: Entity::processCollisionContacts

// Reconstructed C++ for function at 0x00545b40
// This function processes collision contacts for an Entity object.
// It checks if the entity is active, then either updates its transform
// based on velocity (if static) or handles dynamic collision response.
// It iterates over a list of contacts and triggers collision callbacks.

#include <cstdint>

// Forward declarations
struct Entity;
struct ContactInfo;

// Constants
constexpr float kEpsilon = 0.0f; // DAT_00e2b05c likely 0.0f
constexpr uint32_t kAllocFlag = 0x2001;

// External functions (declared elsewhere)
extern float sqrtf(float x); // FUN_00414a80
extern void* allocateContactBuffer(uint32_t flag); // FUN_004af8c0
extern void pushTransform(Entity* entity); // FUN_009f17c0
extern void someInitFunction(); // FUN_0055da50
extern bool checkSomething(int* stack); // FUN_009f1be0
extern void doSomethingElse(); // FUN_009f2000
extern void transformMatrixMultiply(float* out, float* a, float* b); // FUN_00470d00
extern void freeContactBuffer(void* buffer, uint32_t size, uint32_t tag); // FUN_00aa26e0

// Structure for a 4x4 matrix (16 floats)
struct Matrix4x4 {
    float m[16];
};

// Structure for a contact entry (size 0x30 = 48 bytes)
struct ContactEntry {
    uint8_t pad0[0x10];          // +0x00: unknown
    uint8_t contactSide;         // +0x10: side/type byte (used with +0x10 offset)
    uint8_t pad1[7];             // +0x11: padding
    Entity* entityA;             // +0x20: first entity in contact
    Entity* entityB;             // +0x28: second entity in contact
    // Total size 0x30
};

// Entity class (partial, only fields used)
struct Entity {
    // vtable pointer at +0x00
    // Virtual method at +0x198 (408) - returns bool (isActive?)
    // Virtual method at +0xC8 (200) - collision callback

    uint8_t pad0[0x34];          // +0x04 to +0x33
    Matrix4x4 worldTransform;    // +0x34 (16 floats)
    uint8_t pad1[0x2E8 - 0x74]; // +0x74 to +0x2E7
    Entity* rigidBody;           // +0x2E8 (param_1[0xba])
    uint8_t pad2[0x360 - 0x2EC];// +0x2EC to +0x35F
    int32_t isStatic;            // +0x360 (param_1[0xd8])
    ContactInfo* contactList;    // +0x364 (param_1[0xd9])
    uint8_t pad3[0x378 - 0x368];// +0x368 to +0x377
    Entity* someOther;           // +0x378 (param_1[0xde])
};

// ContactInfo structure (list of contacts)
struct ContactInfo {
    int32_t count;               // +0x00: number of contacts
    ContactEntry entries[1];     // variable length
};

void Entity::processCollisionContacts() {
    // Check if entity is active via virtual call at +0x198
    bool isActive = (**(bool (__thiscall**)(Entity*))(*(uint32_t*)this + 0x198))();
    if (!isActive) {
        return;
    }

    int32_t staticFlag = this->isStatic; // param_1[0xd8]
    Matrix4x4 localTransform; // aiStack_1f0
    Matrix4x4 scaledTransform; // aiStack_260

    // Copy current world transform to local
    localTransform = this->worldTransform;

    // Some constant (likely identity or zero)
    uint32_t someConstant = DAT_00e2b1a4; // unknown

    if (staticFlag == 0) {
        // Non-static: compute velocity magnitude and scale transform
        Entity* rigidBody = this->rigidBody; // param_1[0xba]
        if (rigidBody) {
            // Get velocity vector from rigidBody at +0x1A0 (3 floats)
            float vx = *(float*)((uint8_t*)rigidBody + 0x1A0);
            float vy = *(float*)((uint8_t*)rigidBody + 0x1A4);
            float vz = *(float*)((uint8_t*)rigidBody + 0x1A8);
            float speedSq = vx*vx + vy*vy + vz*vz;
            float speed = sqrtf(speedSq); // FUN_00414a80

            // Scale the transform's translation by speed
            // The transform is stored as 16 floats; translation is at indices 12,13,14
            scaledTransform = this->worldTransform;
            scaledTransform.m[12] *= speed;
            scaledTransform.m[13] *= speed;
            scaledTransform.m[14] *= speed;
            // Note: The original code uses float10 and casts, but we simplify.
        }
    } else {
        // Static: do some initialization
        // Check something via stack manipulation
        int stackVar; // uStack_284
        char* checkResult = (char*)FUN_009f1be0((int)&stackVar + 3);
        if (*checkResult == '\0') {
            Entity* someOther = this->someOther; // param_1[0xde]
            if (someOther) {
                float someFloat = *(float*)(*(uint32_t*)((uint8_t*)someOther + 0x18) + 0x14);
                if (someFloat != kEpsilon) {
                    // Do something else
                    FUN_009f2000();
                }
            }
        }
        // Call some init functions
        FUN_0055da50();
        // Multiply local transform by something (maybe identity)
        FUN_00470d00((float*)&localTransform);
    }

    // If there is a contact list
    if (this->contactList) {
        ContactInfo* contacts = this->contactList; // param_1[0xd9]
        int32_t contactCount = contacts->count; // DAT_00e445dc

        // Prepare parameters for callback
        // Build a structure on stack for the callback
        struct CallbackParams {
            void* vtable;          // +0x00: points to PTR_LAB_00e397fc
            uint32_t flags;        // +0x04
            uint32_t unknown1;     // +0x08
            uint32_t unknown2;     // +0x0C
            Matrix4x4* transform;  // +0x10
            float someFloat;       // +0x14
            int* someInt;          // +0x18
            uint32_t unknown3;     // +0x1C
            uint32_t unknown4;     // +0x20
            uint32_t unknown5;     // +0x24
            uint32_t unknown6;     // +0x28
            uint32_t unknown7;     // +0x2C
        };

        CallbackParams params;
        params.vtable = &PTR_LAB_00e397fc; // some vtable
        params.flags = 0x80000008;
        params.unknown1 = 0;
        params.unknown2 = 0;
        params.transform = &scaledTransform; // or localTransform depending on path
        params.someFloat = 0.0f;
        params.someInt = nullptr;
        params.unknown3 = someConstant;
        params.unknown4 = someConstant;
        params.unknown5 = 0;
        params.unknown6 = 0;
        params.unknown7 = 0;

        // Push transform for the rigid body (param_1[0xba] + 0xe0)
        pushTransform(this->rigidBody); // FUN_009f17c0

        // Call virtual method on contactList at +0x34 (52) to process contacts?
        // Actually the code calls (**(code**)(*param_1[0xd9] + 0x34))(...)
        // So contactList has its own vtable with method at +0x34
        typedef void (__thiscall* ContactProcessFunc)(ContactInfo*, CallbackParams*, Matrix4x4**, void**, void**);
        ContactProcessFunc processFunc = *(ContactProcessFunc*)(*(uint32_t*)contacts + 0x34);
        processFunc(contacts, &params, &scaledTransform.m[12], &params.vtable, &params.vtable);

        // Now iterate over contacts
        if (contactCount > 0) {
            for (int i = 0; i < contactCount; i++) {
                ContactEntry* entry = &contacts->entries[i];
                Entity* entityA = entry->entityA; // +0x20
                Entity* entityB = entry->entityB; // +0x28
                uint8_t contactSide = entry->contactSide; // +0x10

                Entity* localEntity = nullptr;
                Entity* otherEntity = nullptr;

                // Check entityA validity
                if (entityA) {
                    uint8_t* ptr = (uint8_t*)entityA;
                    if (*(char*)(ptr + 0x10) + ptr != 0) { // some validity check
                        // Allocate buffer for entityA
                        if (allocateContactBuffer(kAllocFlag)) {
                            localEntity = entityA;
                        }
                    }
                }

                // Check entityB validity
                if (entityB) {
                    uint8_t* ptr = (uint8_t*)entityB;
                    if (*(char*)(ptr + 0x10) + ptr != 0) {
                        if (allocateContactBuffer(kAllocFlag)) {
                            otherEntity = entityB;
                        }
                    }
                }

                // If both entities are valid and different
                if (localEntity && otherEntity && localEntity != otherEntity) {
                    // Determine which one is 'this' and call collision callback
                    if (localEntity == this) {
                        // this is entityA, so callback on entityB
                        uint8_t side = *(uint8_t*)((uint8_t*)entityA + 0x18); // side from entityA
                        auto callback = (void (__thiscall*)(Entity*, int, int))(*(uint32_t*)otherEntity + 0xC8);
                        callback(otherEntity, (int)side, (int)entry);
                    } else if (otherEntity == this) {
                        // this is entityB, so callback on entityA
                        uint8_t side = *(uint8_t*)((uint8_t*)entityB + 0x18); // side from entityB
                        auto callback = (void (__thiscall*)(Entity*, int, int))(*(uint32_t*)localEntity + 0xC8);
                        callback(localEntity, (int)side, (int)entry);
                    }
                }
            }
        }

        // Free the contact buffer if needed
        if ((int32_t)params.flags >= 0) {
            TlsGetValue(DAT_01139810); // thread-local storage
            freeContactBuffer(&params.vtable, (params.flags & 0x3FFFFFFF) * 0x30, 0x17);
        }
    }
}