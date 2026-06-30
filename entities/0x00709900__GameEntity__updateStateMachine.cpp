// FUNC_NAME: GameEntity::updateStateMachine

#include <cstdlib>

// Based on observed offsets from decompiled code (0x00709900)
// This function appears to be a state machine update for a game entity,
// handling placement/spawning logic with random orientation and debug output.

class GameEntity {
public:
    // Virtual table at offset 0x00
    // Vtable indices used: 0x1c, 0x20, 0x5c, 0x70, 0x7c, 0x10 (on child)

    // Fields (offsets in bytes, param_1 is int* so multiply by 4)
    // +0x1B0 (0x6c) - some object pointer (e.g., a spawn data or owner)
    // +0x1D4 (0x75) - byte flags
    // +0x1B4 (0x6d) - int counter/flags?
    // +0x1D0 (0x74) - 32-bit flags (bit13 used)
    // +0x1E0 (0x78) - pointer to something (collision?)
    // +0x214 (0x85) - pointer to another object (e.g., a node or parent) +48 offset?
    // +0x1F0 (0x7c) - vector XYZ (x, y, z, w) for position/velocity
    // +0x200 (0x80) - another vector? 0x81,0x82,0x83
    // +0x274 (0x9d) - some integer
    // +0x290 (0xa4) - flag/integer (0 means not active?)
    // +0x158 (0x56) - next state function pointer (returned at end)

    // External global constants
    static constexpr float kOne = 1.0f;      // _DAT_00d5780c (likely 1.0)
    static constexpr float kAngleScale = 0.0f; // DAT_00e445c8 (likely PI/180 or similar, placeholder)

    void* __thiscall operator new(size_t);
    void operator delete(void*);

    // Virtual functions (assumed via vtable)
    virtual void someFunc1(float* matrix);      // vtable +0x1c
    virtual void someFunc2();                    // vtable +0x7c
    virtual void someFunc3(float* matrix);      // vtable +0x20
    virtual int  someFunc4(int param, int handle); // vtable +0x5c
    virtual void someFunc5();                    // vtable +0x70
};

// External functions (actual names unknown, placeholder)
extern void baseConstructor(void* thisPtr);          // FUN_00855780
extern void debugLog(int a, int b, int c);        // FUN_009f4240 (2,1,0)
extern void adjustMatrixFromEuler(float* matrix, float* euler); // FUN_009f4c40
extern void placeEntity(float* transform);         // FUN_009f2000
extern void generateRandomDirection(float& outX, float& outY); // FUN_00b99e20, FUN_00b99fcb
extern void releaseObject(int* ptr);              // FUN_004daf90
extern void setState(int newStateId);             // FUN_0043c490 (second param 6)
extern void resetFlags(int* obj);                 // FUN_00708f80
extern void collisionCheck(int* obj);             // FUN_009e7450
extern void cleanup(void*);                       // FUN_007073c0
extern void createTransform(float* out, int* src); // FUN_00707d10, FUN_007080f0

// Global references (actual names unknown)
extern float g_constant_1; // _DAT_00d5780c (likely 1.0f)
extern float g_angleFactor; // DAT_00e445c8 (likely DEG2RAD or similar)

// State labels (addresses of functions for state machine)
extern void __cdecl state_handleA(void* thisPtr); // LAB_00707620
extern void __cdecl state_handleB(void* thisPtr); // LAB_00707ff0

// Decompiled function: __thiscall void FUN_00709900(GameEntity* this, float* position, int eventType, char flag, float scale, int extraData)
void __thiscall GameEntity::updateStateMachine(float* position, int eventType, char flag, float scale, int extraData)
{
    // Call base class constructor pattern (may be part of update)
    baseConstructor(this);

    // Check byte at offset 0x75, bit 3 (0x08)
    if (((*(reinterpret_cast<unsigned char*>(this) + 0x75) >> 3) & 1) != 0) {
        // If a certain flag is set and some counter is non-zero
        if (*(reinterpret_cast<int*>(this) + 0x6d) != 0) {
            // Call cleanup? (FUN_00707c30)
            extern void cleanupSomething();
            cleanupSomething();
        }
    }

    // Main branch: check if spawn data exists (offset 0x6c) and a flag bit 13 (0x2000) is set
    if ((*(reinterpret_cast<int*>(this) + 0x6c) == 0) || 
        ((static_cast<unsigned int>(*(reinterpret_cast<int*>(this) + 0x74)) >> 0xd) & 1) == 0) 
    {
        // ----- PATH A: No spawn data or flag not set -----
        if (position == nullptr) {
            createTransform(reinterpret_cast<float*>(&matrixLocal), nullptr);
        } else {
            createTransform(reinterpret_cast<float*>(&matrixLocal), position);
        }

        // Call vtable functions on the local matrix
        this->someFunc1(&matrixLocal);   // vtable +0x1c
        this->someFunc2();               // vtable +0x7c

        // Build a 4x4 matrix (assuming column-major? 16 floats)
        float matrix[16];
        matrix[0]  = g_constant_1; matrix[1]  = 0.0f; matrix[2]  = 0.0f; matrix[3]  = 0.0f;
        matrix[4]  = 0.0f; matrix[5]  = 0.0f; matrix[6]  = 0.0f; matrix[7]  = 0.0f;
        matrix[8]  = 0.0f; matrix[9]  = 0.0f; matrix[10] = 0.0f; matrix[11] = 0.0f;
        matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = g_constant_1;

        // Call vtable +0x20 with matrix
        this->someFunc3(matrix);

        // Check collision pointer at offset 0x78
        int* collisionObj = reinterpret_cast<int*>(this) + 0x78; // pointer field
        if (*collisionObj != 0) {
            // Check second field of that object (offset 8? ints)
            if (*(reinterpret_cast<int*>(*collisionObj) + 2) == 0) {
                collisionCheck(reinterpret_cast<int*>(*collisionObj));
                cleanup();
            }
        }
        cleanup();
    }
    else {
        // ----- PATH B: Spawn data exists and flag is set -----
        this->someFunc2();   // vtable +0x7c

        // Debug log: event type 2,1,0
        extern void debugLog(int a, int b, int c);
        debugLog(2, 1, 0);

        if (position == nullptr) {
            // No position provided: use random placement
            float randomDir[4];
            createTransform(&randomDir[0], nullptr);

            // Extract some fields from randomDir (likely position)
            float posX = randomDir[0];
            float posY = randomDir[1];
            float posZ = randomDir[2];

            // Random angle for orientation
            int angleDeg = rand() % 360; // 0x168 = 360
            float angleRad = static_cast<float>(angleDeg) * g_angleFactor;

            // Convert angle to direction vector?
            float sinAngle, cosAngle;
            // Assume FUN_00b99e20 and FUN_00b99fcb compute sin/cos
            sinAngle = sinf(angleRad); // placeholder
            cosAngle = cosf(angleRad); // placeholder

            // Build placement transform
            float placeTransform[6]; // 2D? Actually it's 6 floats? Reconstruct
            // The code using stack variables: fStack_60, fStack_5c, fStack_58, etc.
            // We'll approximate with a 4x4 matrix again.
            float transform[16];
            transform[0] = cosAngle; transform[1] = sinAngle; // etc.
            // ... actually the code stores into fStack_60 etc. We'll skip exact.

            // Set extra data in transform
            // uStack_5c = extraData; (param_6)
            // fStack_58 = ? (cosAngle * something?)

            // Get spawn data object (param_1[0x6c])
            int* spawnData = reinterpret_cast<int*>(this) + 0x6c; // actually pointer, need to dereference
            int* actualSpawnData = reinterpret_cast<int*>(*spawnData);

            // Call a function on that spawnData's vtable +0x40
            // ( **(code **)(*(int *)(iVar2 + 0xd0) + 0x40) )(&fStack_60);
            // That means actualSpawnData[0xd0] (offset 0x340?) is a vtable, call +0x40
            reinterpret_cast<void (__thiscall*)(void*, float*)>(actualSpawnData[0xd0])(actualSpawnData, &transform[0]);

            // Then adjust matrix from the original position
            createTransform(reinterpret_cast<float*>(&randomDir), &transform[0]); // but param_2 is used
        }
        else {
            // Position provided
            // Copy position to local matrix
            float localMatrix[4];
            localMatrix[0] = position[0];
            localMatrix[1] = position[1];
            localMatrix[2] = position[2];
            localMatrix[3] = 0.0f; // W or padding

            adjustMatrixFromEuler(localMatrix, nullptr); // FUN_009f4c40

            if (flag == 0) {
                // No random offset, use exact position
                float placementTransform[4];
                placementTransform[0] = 0.0f;
                placementTransform[1] = extraData; // param_6
                placementTransform[2] = 0.0f;
                placementTransform[3] = 0; // padding

                // Call spawn function on spawnData
                int* spawnData = reinterpret_cast<int*>(this) + 0x6c;
                int* actualSpawnData = reinterpret_cast<int*>(*spawnData);
                reinterpret_cast<void (__thiscall*)(void*, float*)>(actualSpawnData[0xd0])(actualSpawnData, placementTransform);
            } else {
                // Apply random offset scaled by param_5
                int angleDeg = rand() % 360;
                float angleRad = static_cast<float>(angleDeg) * g_angleFactor;
                float sinAngle, cosAngle;
                sinAngle = sinf(angleRad); cosAngle = cosf(angleRad);

                float offsetX = cosAngle * scale;
                float offsetZ = sinAngle * scale; // assuming 2D horizontal

                // Build placement transform
                float placementTransform[4];
                placementTransform[0] = offsetX;
                placementTransform[1] = extraData;
                placementTransform[2] = offsetZ;
                placementTransform[3] = 0;

                int* spawnData = reinterpret_cast<int*>(this) + 0x6c;
                int* actualSpawnData = reinterpret_cast<int*>(*spawnData);
                reinterpret_cast<void (__thiscall*)(void*, float*)>(actualSpawnData[0xd0])(actualSpawnData, placementTransform);
            }
        }

        // Then adjust matrix from position (pass original position to FUN_007080f0)
        createTransform(position, reinterpret_cast<float*>(&localMatrix)); // param_2 used

        // Handle special event type 0x1ff (511) and reference to offset 0x85
        if ((eventType == 0x1ff) && (*(reinterpret_cast<int*>(this) + 0x85) != 0) && 
            (*(reinterpret_cast<int*>(this) + 0x85) != 0x48)) 
        {
            int* refObj = reinterpret_cast<int*>(this) + 0x85;
            if (*refObj == 0) {
                // This branch seems contradictory, but decompiler shows it.
                // Possibly it's: if (refObj[0] == 0) ... else ...
                // Use the parent's vtable +0x58
                int parentVtable = *(reinterpret_cast<int*>(this)); // vtable of this
                int handle = 0xffffffff;
                int result = parentVtable(&parentVtable, handle); // vtable+0x58? Actually it's weird.
                // vtable +0x58 is called on some object derived from refObj - 0x48?
                // Simplify: call a function on the referenced object's vtable +0x58
                int* otherObj = reinterpret_cast<int*>(*refObj - 0x48); // weird offset
                reinterpret_cast<int (__thiscall*)(void*, int)>(otherObj[0x58])(otherObj, handle);
            } else {
                // Similar but using this->vtable +0x5c
                this->someFunc4(eventType, 0xffffffff);
            }
        } else {
            this->someFunc4(eventType, 0xffffffff);
        }

        // Copy data from spawn data to this object
        int* spawnData = reinterpret_cast<int*>(this) + 0x6c;
        int* actualSpawnData = reinterpret_cast<int*>(*spawnData);
        *(reinterpret_cast<int*>(this) + 0x7c) = *(actualSpawnData + 0x110); // +0x440? ints
        *(reinterpret_cast<int*>(this) + 0x7d) = *(actualSpawnData + 0x114);
        *(reinterpret_cast<int*>(this) + 0x7e) = *(actualSpawnData + 0x118);
        *(reinterpret_cast<int*>(this) + 0x7f) = *(actualSpawnData + 0x11c);

        // Add g_constant_1 to one of the components (Y? position?)
        float yComponent = static_cast<float>(*(reinterpret_cast<int*>(this) + 0x7d)) + g_constant_1;
        *(reinterpret_cast<int*>(this) + 0x7c) = *(reinterpret_cast<int*>(this) + 0x7c);
        *(reinterpret_cast<int*>(this) + 0x7d) = static_cast<int>(yComponent);
        *(reinterpret_cast<int*>(this) + 0x7e) = *(reinterpret_cast<int*>(this) + 0x7e);
        *(reinterpret_cast<int*>(this) + 0x7f) = *(reinterpret_cast<int*>(this) + 0x7f);

        *(reinterpret_cast<int*>(this) + 0x80) = 0;
        *(reinterpret_cast<int*>(this) + 0x81) = 0;
        *(reinterpret_cast<int*>(this) + 0x82) = 0;
        *(reinterpret_cast<int*>(this) + 0x83) = 0;

        // Set flag bit 8 (0x100) at offset 0x74
        *(reinterpret_cast<int*>(this) + 0x74) |= 0x100;

        // Copy ebx value (unaff_EBX) to offset 0x9d (likely some register save)
        *(reinterpret_cast<int*>(this) + 0x9d) = 0; // Placeholder
    }

    // --- Common cleanup/release section ---
    int* refPtr = reinterpret_cast<int*>(this) + 0x85; // pointer field
    if ((*refPtr != 0) && (*refPtr != 0x48)) {
        // If the reference is not null and not 0x48, call vtable +0x10 on an object derived from it
        if (*refPtr == 0) {
            // Inconceivable case, but code exists
        } else {
            int* childObj = reinterpret_cast<int*>(*refPtr - 0x48);
            reinterpret_cast<void (__thiscall*)(void*, int)>(*childObj[0x10])(childObj, 0x383225a1); // some ID
        }
        // Release the reference
        if (*refPtr != 0) {
            releaseObject(refPtr);
            *refPtr = 0;
        }
        // Set state to 6
        extern void setState(void* obj, int state);
        setState(this, 6);
    }

    // Call vtable +0x70
    this->someFunc5();

    // Check flag at offset 0xa4 (290)
    if (*(reinterpret_cast<int*>(this) + 0xa4) == 0) {
        // Call some reset function
        extern void resetFlags(void* obj);
        resetFlags(reinterpret_cast<int*>(this) + 0xa0); // offset 0xa0 (3 ints?)
        // Clear bit 12 (0x1000) in flags at 0x74
        *(reinterpret_cast<int*>(this) + 0x74) &= ~0x1000;
    }

    // Check bit 1 (0x2) at offset 0x74
    if (((*(reinterpret_cast<int*>(this) + 0x74) >> 1) & 1) == 0) {
        // Return pointer to state handler A (LAB_00707620)
        *(reinterpret_cast<int*>(this) + 0x56) = reinterpret_cast<int>(&state_handleA);
        return;
    } else {
        // Return pointer to state handler B (LAB_00707ff0)
        *(reinterpret_cast<int*>(this) + 0x56) = reinterpret_cast<int>(&state_handleB);
        return;
    }
}