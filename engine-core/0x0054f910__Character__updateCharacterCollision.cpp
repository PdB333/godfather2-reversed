// FUNC_NAME: Character::updateCharacterCollision

#include <windows.h> // for TlsGetValue, LPVOID, etc.

// External functions (declared elsewhere)
extern void updateAcceleration(Character* self, float dt); // FUN_0054efb0
extern int doCheapCast(Character* self, float* out_pos, float* out_vel, byte* out_collisionFlags, int* out_hitCount, int* out_contactNormal); // FUN_0054d3e0
extern int getObjectFromHandle(int handle); // FUN_004afca0
extern int getWorldObject(); // FUN_00421430
extern int getObjectFromCell(int handle); // FUN_0054c0e0
extern void releaseObject(int handle); // FUN_0044b210
extern void setPosition(float* pos, int unknown); // FUN_009f1820
extern void handleCollisionFlag(Character* self); // FUN_0054f520

// Global constants
extern float COLLISION_DOT_THRESHOLD; // DAT_00e2cd54
extern int SOME_OBJECT_FLAG; // DAT_01205224
extern DWORD TLS_INDEX; // DAT_01139830
extern int GLOBAL_VALUES[4]; // DAT_01139820, etc.

// Profile block helper (simplified)
inline void profileEvent(const char* name, int& start, int& end) {
    // In real code, this would write to TLS buffer.
    // Here we just ignore for reconstruction.
}

void __thiscall Character::updateCharacterCollision(float dt)
{
    float velX, velY, velZ, velW; // velocity components (might also be delta)
    float newVelX, newVelY, newVelZ, newVelW;
    float displacementX, displacementY, displacementZ, displacementW;
    float castResultPos[4]; // collision test result position (x,y,z,w)
    float castVelX, castVelY, castVelZ, castVelW; // velocity from cast
    int collisionHitCount; // number of collisions found
    int contactNormal; // some contact normal or surface id
    int objectHandle; // handle to collided object
    int worldObjectHandle; // handle to world object
    float dotProduct;
    int somethingFlag;
    float accelX, accelY, accelZ, accelW; // acceleration from external forces
    byte collisionFlags; // from cheap cast
    float unusedFloat;
    int unusedInt;

    if (*(int*)(this + 0xe8) == 0) {
        // --- Normal cheaper collision update ---
        // Profile start
        LPVOID tlsData = TlsGetValue(TLS_INDEX);
        int* counter = (int*)((char*)tlsData + 4);
        int* maxCounter = (int*)((char*)tlsData + 12);
        if (counter < maxCounter) {
            *counter = (int)"LtCheaper Character Collision";
            counter[3] = (int)"StPre Cheap Cast";
            counter[1] = (int)__rdtsc();
            counter += 4;
            *(int**)((char*)tlsData + 4) = counter;
        }

        // Get current velocity (from previous frame? stored elsewhere)
        velX = *(float*)(this + 100); // +0x64? Actually offset 100 decimal = 0x64, but decomp says +100 (int) -> +0x64? Check: (this+100) is used, but later +0x68, +0x6c, etc. Inconsistent. Likely +0x64 is something else. Actually decomp says "*(float *)(in_EAX + 100)" => 100 decimal = 0x64. But earlier offsets: +0x68, +0x6c. So 100 is int, not hex. So it's +0x64. But then later values from +0x68,+0x6c,+0x70,+0x74,+0x78,+0x7c. So velX is from +0x64, but then used as accumulator? Let's revisit.
        // Actually the decompiled: fStack_b0 = *(float *)(in_EAX + 100); -> 100 decimal = 0x64. Then later fStack_ac = *(float *)(in_EAX + 0x68), etc. So velX is at +0x64, velY at +0x68, velZ at +0x6c, and there is a fourth? But later used fStack_a4 from +0x7c. So there might be a 4-component velocity (maybe with delta time or mass?).
        // To maintain consistency with later code, I'll keep offsets as given.
        newVelX = *(float*)(this + 0x64); // +100 decimal = 0x64
        newVelY = *(float*)(this + 0x68);
        newVelZ = *(float*)(this + 0x6c);
        newVelW = 0.0f;

        // If bit0 of flag at +0xe4 is not set, integrate external acceleration
        if ((*(byte*)(this + 0xe4) & 1) == 0) {
            updateAcceleration(this, dt); // adds to velocity? Actually it modifies current velocity? The function modifies the velocity fields? Decompiled: FUN_0054efb0(param_1); then fStack_ac = *(float *)(in_EAX + 0x74) + fStack_ac; etc. So it adds stored delta? So updateAcceleration likely sets some internal acceleration delta.
            newVelX += *(float*)(this + 0x70); // +0x70 is added to velX
            newVelY += *(float*)(this + 0x74);
            newVelZ += *(float*)(this + 0x78);
            newVelW += *(float*)(this + 0x7c); // possibly a separate component
        }

        // If bit8 of flag is not set, compute displacement = velocity * dt
        if ((*(int*)(this + 0xe4) & 0x100) == 0) {
            displacementX = newVelX * dt;
            displacementY = newVelY * dt;
            displacementZ = newVelZ * dt;
            displacementW = newVelW * dt;
        } else {
            displacementX = displacementY = displacementZ = displacementW = 0.0f;
        }

        // Prepare cheap cast parameters
        int unusedParam = 0xffffffff;
        int someOtherParam = 0xffffffff;
        int profileGlobal = *(int*)0x00e2b1a4; // some global
        int unused = 0;
        int someFlag = 0;
        float something = 0.0f;
        int contactCount = 0;
        int contactNormalOut = 0;
        int castFlags = 0xfe16702f; // constant, maybe indicates type of cast

        // Perform cheap cast (collision detection)
        doCheapCast(*(int*)(*(int*)(this + 0x14) + 0x30), &castResultPos[0], &something, (byte*)&collisionFlags, &contactCount, &contactNormalOut);
        // Note: the decompiled passes various stack addresses; I'll approximate.

        // Profile end
        LPVOID tlsData2 = TlsGetValue(TLS_INDEX);
        int* counter2 = (int*)((char*)tlsData2 + 4);
        if (counter2 < (int*)((char*)tlsData2 + 12)) {
            *counter2 = (int)"StPost Cheap Cast";
            counter2[1] = (int)__rdtsc();
            counter2 += 3;
            *(int**)((char*)tlsData2 + 4) = counter2;
        }

        // Process cheap cast results
        if (someFlag == 0) {
            // No collision detected? Use original position/velocity
            castResultPos[0] = *(float*)(this + 0x90); // original? but +0x90 might be previous position?
            castResultPos[1] = *(float*)(this + 0x94);
            castResultPos[2] = *(float*)(this + 0x98);
            castResultPos[3] = *(float*)(this + 0x9c);
            collisionFlags = 0;
            *(byte*)&collisionFlags = 0; // set to 0?
            objectHandle = 0;
        } else {
            // Collision found, use result
            // castResultPos is already set from doCheapCast output?
            // The decompiled shows fStack_90 = fStack_70; etc. So it's using output of doCheapCast.
            castResultPos[0] = someFloatFromCast;
            castResultPos[1] = someFloatFromCast;
            castResultPos[2] = someFloatFromCast;
            castResultPos[3] = someFloatFromCast; // Actually it's uStack_64 which is maybe extra data
            collisionFlags = 1; // indicates collision?
            // Then get object handle
            objectHandle = getObjectFromHandle(someFlag);
            if (objectHandle == 0) {
                int* objPtr = (int*)getObjectFromCell(&something, someFlag);
                castFlags = *objPtr; // some data
            } else {
                int* objPtr = (int*)getWorldObject();
                castFlags = *objPtr;
            }
        }

        // Copy some global values (maybe gravity or environment)
        int globalVals[4];
        globalVals[0] = *(int*)0x01139820;
        globalVals[1] = *(int*)0x01139824;
        globalVals[2] = *(int*)0x01139828;
        globalVals[3] = *(int*)0x0113982c;

        // If flag bit8 is set, store cast result to character
        if ((*(int*)(this + 0xe4) & 0x100) != 0) {
            *(byte*)(this + 0x30) = collisionFlags; // some status byte?
            *(byte*)(this + 0x31) = *(byte*)&collisionFlags; // second byte?
            *(float*)(this + 0x40) = castResultPos[0];
            *(float*)(this + 0x44) = castResultPos[1];
            *(float*)(this + 0x48) = castResultPos[2];
            *(float*)(this + 0x4c) = castResultPos[3];
            *(int*)(this + 0x50) = globalVals[0];
            *(int*)(this + 0x54) = globalVals[1];
            *(int*)(this + 0x58) = globalVals[2];
            *(int*)(this + 0x5c) = globalVals[3];
            *(int*)(this + 0xd0) = contactNormalOut;
            *(int*)(this + 0xcc) = contactCount;
            *(int*)(this + 0x60) = castFlags;
            releaseObject(objectHandle);
        }

        // Check dot product of current projection (?) against threshold
        dotProduct = *(float*)(this + 0x90) * castResultPos[0] +
                     *(float*)(this + 0x94) * castResultPos[1] +
                     *(float*)(this + 0x98) * castResultPos[2];
        if (dotProduct <= COLLISION_DOT_THRESHOLD) {
            if (*(int*)(this + 0xa4) == 0) {
                *(int*)(this + 0xa4) = SOME_OBJECT_FLAG;
            }
        } else {
            // Update movement: set velocity to something?
            int sceneNode = *(int*)(this + 0x14);
            *(float*)(sceneNode + 0x10) = newVelX;
            *(float*)(sceneNode + 0x14) = newVelY;
            *(float*)(sceneNode + 0x18) = newVelZ;
            *(float*)(sceneNode + 0x1c) = newVelW;

            int transformPtr = *(int*)(*(int*)(*(int*)(this + 0x14) + 0x30) + 0x18);
            displacementX = newVelX * dt + *(float*)(transformPtr + 0x30);
            displacementY = newVelY * dt + *(float*)(transformPtr + 0x34);
            displacementZ = newVelZ * dt + *(float*)(transformPtr + 0x38);
            displacementW = newVelW * dt + *(float*)(transformPtr + 0x3c); // maybe a time offset?

            // If collision object handle is non-zero and bit0 not set, use cast result velocity
            if ((objectHandle != 0) && ((*(byte*)(this + 0xe4) & 1) == 0)) {
                displacementY = something; // fStack_dc from earlier? Actually the decompiled sets local_cc = fStack_dc (which is from cheap cast I think)
            }

            // Profile
            LPVOID tlsData3 = TlsGetValue(TLS_INDEX);
            int* counter3 = (int*)((char*)tlsData3 + 4);
            if (counter3 < (int*)((char*)tlsData3 + 12)) {
                *counter3 = (int)"StSet position";
                counter3[1] = (int)__rdtsc();
                counter3 += 3;
                *(int**)((char*)tlsData3 + 4) = counter3;
            }

            setPosition(&displacementX, 0);

            // Store result back to character (similar to earlier)
            *(byte*)(this + 0x30) = collisionFlags;
            *(byte*)(this + 0x31) = *(byte*)&collisionFlags;
            *(float*)(this + 0x40) = castResultPos[0];
            *(float*)(this + 0x44) = castResultPos[1];
            *(float*)(this + 0x48) = castResultPos[2];
            *(float*)(this + 0x4c) = castResultPos[3];
            *(int*)(this + 0x50) = globalVals[0];
            *(int*)(this + 0x54) = globalVals[1];
            *(int*)(this + 0x58) = globalVals[2];
            *(int*)(this + 0x5c) = globalVals[3];
            *(int*)(this + 0xcc) = contactCount;
            *(int*)(this + 0xd0) = contactNormalOut;
            *(int*)(this + 0x60) = castFlags;
            releaseObject(objectHandle);

            *(int*)(this + 0xa4) = 0;
        }

        // Check another flag at +0x30 (if zero, set something, else clear)
        if (*(char*)(this + 0x30) == '\0') {
            if (*(int*)(this + 0xb0) == 0) {
                *(int*)(this + 0xb0) = SOME_OBJECT_FLAG;
            }
        } else {
            *(int*)(this + 0xb0) = 0;
        }

        // If bit9 of flag is set, call additional handler
        if ((*(int*)(this + 0xe4) & 0x200) != 0) {
            handleCollisionFlag(this);
        }

        // Clear bit8
        *(int*)(this + 0xe4) &= ~0x100;

        // Final profile (maybe end marker)
        LPVOID tlsDataEnd = TlsGetValue(TLS_INDEX);
        int* counterEnd = (int*)((char*)tlsDataEnd + 4);
        if (counterEnd < (int*)((char*)tlsDataEnd + 12)) {
            *counterEnd = (int)"LtCheaper Character Collision End"; // placeholder
            counterEnd[1] = (int)__rdtsc();
            counterEnd += 3;
            *(int**)((char*)tlsDataEnd + 4) = counterEnd;
        }

    } else {
        // --- Simple update path (disabled cheaper collision?) ---
        int sceneNode = *(int*)(this + 0x14);
        float velX2 = *(float*)(this + 0x64); // +100 decimal again
        float velY2 = *(float*)(this + 0x68);
        float velZ2 = *(float*)(this + 0x6c);
        float velW2 = *(float*)(this + 0x7c); // some constant

        *(float*)(sceneNode + 0x10) = velX2;
        *(float*)(sceneNode + 0x14) = velY2;
        *(float*)(sceneNode + 0x18) = velZ2;
        *(float*)(sceneNode + 0x1c) = velW2;

        int transformPtr = *(int*)(*(int*)(*(int*)(this + 0x14) + 0x30) + 0x18);
        displacementX = velX2 * dt + *(float*)(transformPtr + 0x30);
        displacementY = velY2 * dt + *(float*)(transformPtr + 0x34);
        displacementZ = velZ2 * dt + *(float*)(transformPtr + 0x38);
        displacementW = *(float*)(transformPtr + 0x3c) + dt; // note: only dt added to w component

        setPosition(&displacementX, 0);
    }

    return;
}