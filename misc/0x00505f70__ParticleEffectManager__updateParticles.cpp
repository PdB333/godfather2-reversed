// FUNC_NAME: ParticleEffectManager::updateParticles
// Address: 0x00505f70
// Role: Updates all active particle effects, including culling, vertex buffer allocation, and screen-space position calculation.

#include <cstdint>

// Forward declarations
class ParticleNode;
class AttachedObject; // object with vtable pointer

// Engine global constants (these are rough guesses based on usage)
extern float DAT_00e2b1a4; // screen width or max coordinate
extern float DAT_00e2b04c; // scale factor
extern float DAT_00e2eff4; // some min/max threshold
extern float DAT_00e2cd54; // another threshold
extern float DAT_00e44578; // offset factor
extern uint32_t DAT_01218e40; // screen width (int)
extern uint32_t DAT_01218e42; // screen height (int)
extern float DAT_01218e44; // width multiplier
extern float DAT_01218e48; // height multiplier

// Global state flags and addresses
extern uint32_t DAT_0121a290;
extern uint32_t* DAT_012058e8; // pointer to some structure
extern uint32_t DAT_0121a374;
extern uint32_t DAT_0121a370;
extern uint32_t DAT_0121a200;
extern uint32_t DAT_0121a204;
extern int DAT_012058d0, DAT_012058d4; // min/max values
extern int DAT_00f15988, DAT_00f1598c; // clamp targets
extern int _DAT_011f3a30, _DAT_011f39f4, _DAT_011f3a10, _DAT_011f3a3c, _DAT_011f3a38, _DAT_011f3a14, _DAT_011f3a44;
extern int _DAT_011f3c78, _DAT_011f3cd0;
extern int DAT_0121a310, DAT_0121a314, DAT_0121a318;
extern uint32_t DAT_012058f0;

// Extern functions (assumed signatures)
int* FUN_00505c90(uint32_t param); // returns context pointer
void FUN_004e3a70(); // unknown
void FUN_0060a460(uint32_t param);
void FUN_00536550();
float* FUN_0060cd00(int a0, int a1, int a2, int a3, int a4); // allocate particle vertex data
void FUN_0060cde0(); // free particle vertex data?
void FUN_00618d40();
void FUN_00417cf0(int a0, int a1, int a2);

// Globals used as array indices (likely audio/effect slot arrays)
extern char DAT_011eb8fc[]; // array indexed by DAT_0121a204 * 0x10
extern uint32_t DAT_011d912c[]; // array indexed by uVar9
extern float DAT_00e2b118; // some constant used in loop
extern float DAT_00e4493c; // another constant

struct ParticleNode {
    ParticleNode* next;      // +0x00
    int type;                // +0x04 (not directly used, maybe for classification)
    float x;                 // +0x08
    float y;                 // +0x0C
    float halfWidth;         // +0x10
    float halfHeight;        // +0x14
    float depth;             // +0x18
    // padding or other fields (offsets 0x1C to 0x20)
    AttachedObject* attachedObject; // +0x20 (pointer to object with vtable)
    int particleSpeed;       // +0x24 (velocity or alpha)
    int particleLifetime;    // +0x28 (remaining life or frame)
    int lastUpdateFrame;     // +0x2C (frame counter when last updated)
    uint8_t visibilityFlag;  // +0x1E (actually at offset 0x1E, not contiguous in struct, but placed here for clarity)
    // ... other fields to match size
};

struct ParticleContext {
    int frameCount;          // +0x04? (used as local_44)
    ParticleNode* nodeList;  // +0x00 (head of list)
};

void __thiscall ParticleEffectManager::updateParticles(uint32_t thisPtr) {
    float fVar1, fVar2, fVar3;
    float fVar10, fVar11, fVar12, fVar13, fVar14;
    uint32_t uVar9;
    int iVar5;
    ParticleNode* currentNode;
    float screenPosX, screenPosY;
    float widthScale, heightScale;
    float fStack_3c, fStack_40, fStack_34, fStack_30, fStack_2c;
    float vertexData[20]; // temporary, but used as local buffer for allocation

    ParticleContext* context = (ParticleContext*)FUN_00505c90(thisPtr);
    int currentFrame = context->frameCount;
    currentNode = context->nodeList;
    context->frameCount = currentFrame + 1;

    if (currentNode != nullptr) {
        // First, set up some global state
        FUN_004e3a70();
        DAT_0121a204 = DAT_0121a374;
        DAT_0121a200 = DAT_0121a370;

        // Check if a specific state matches
        if (DAT_012058e8 == (uint32_t*)&DAT_0121a1f0) { // address of global
            FUN_0060a460(DAT_0121a374);
            FUN_0060a460(DAT_0121a200);
        }

        // Set and clamp various global parameters for rendering
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;

        if (DAT_012058d0 < 7) DAT_012058d0 = 7;
        if (7 < DAT_00f15988) DAT_00f15988 = 7;
        _DAT_011f39f4 = 1;

        if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
        if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
        _DAT_011f3a10 = 0;

        if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 5;

        if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
        _DAT_011f3a38 = 0;

        if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
        _DAT_011f3a14 = 0;

        if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
        if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
        _DAT_011f3a44 = 0;

        if (DAT_012058d4 < 0xa8) DAT_012058d4 = 0xa8;
        if (0xa7 < DAT_00f1598c) DAT_00f1598c = 0xa8;
        _DAT_011f3c78 = 0;

        if (DAT_012058d4 < 0xbe) DAT_012058d4 = 0xbe;
        if (0xbd < DAT_00f1598c) DAT_00f1598c = 0xbe;
        _DAT_011f3cd0 = 0;

        FUN_00536550(); // unknown setup

        // Loop over all particle nodes in the linked list
        do {
            screenPosX = 0.0f;

            // Determine if we need to read new input from the attached object
            if (currentNode->lastUpdateFrame == 0 || (currentFrame - currentNode->lastUpdateFrame) < 2) {
                // Attempt to read data from the attached object's vtable (index 7 -> method at +0x1c)
                iVar5 = (*(int (**)(void*, float*, int, int))(*(uint32_t**)currentNode->attachedObject)[7])(
                    currentNode->attachedObject, &screenPosX, 4, 0);
                if (iVar5 == 0 || (iVar5 != 1 && iVar5 != -1)) {
                    goto LAB_005061fa; // skip
                }
            } else {
                // For older particles, read with non-blocking flag
                do {
                    iVar5 = (*(int (**)(void*, float*, int, int))(*(uint32_t**)currentNode->attachedObject)[7])(
                        currentNode->attachedObject, &screenPosX, 4, 1);
                    if (iVar5 == 0) break;
                } while (iVar5 != 1 && iVar5 != -1);
LAB_005061fa:
                currentNode->lastUpdateFrame = currentFrame;
                screenPosX = screenPosX * (currentNode->visibilityFlag); // multiply by visibility byte

                fStack_3c = currentNode->halfWidth;
                // Check if particle is within screen bounds
                if ((currentNode->x + fStack_3c < 0.0f) || (currentNode->x - fStack_3c > (float)(int)DAT_01218e40)) {
                    currentNode->visibilityFlag = 0;
                } else {
                    if ((currentNode->y + currentNode->halfHeight < 0.0f) || (currentNode->y - currentNode->halfHeight > (float)(int)DAT_01218e42)) {
                        currentNode->visibilityFlag = 0;
                    } else {
                        currentNode->visibilityFlag = 1;
                    }
                }

                fStack_40 = currentNode->halfHeight;
                // Allocate vertex data for this particle (5 float4? Or 4 floats per vertex, 4 vertices = 16 floats)
                float* vertexBuffer = FUN_0060cd00(5, 4, 0, 1, 0);
                if (vertexBuffer == nullptr) {
                    fVar12 = 0.0f;
                    currentNode->particleSpeed = 0;
                } else {
                    // Lock the attached object (vtable index 6)
                    (*(void (**)(void*, int))(*(uint32_t**)currentNode->attachedObject)[6])(currentNode->attachedObject, 2);
                    float fConst1 = DAT_00e2b1a4;
                    float fScale = DAT_00e2b04c;
                    float* writePtr = vertexBuffer + 2;
                    int vi = 0;
                    // Fill 4 vertices with screen-space coordinates
                    do {
                        // Each vertex: x, y, z, w (or depth)
                        writePtr[-2] = ((DAT_00e4493c * currentFrame + currentNode->x) * DAT_01218e44 * fScale - fConst1);
                        writePtr[-1] = ((DAT_00e4493c * screenPosX - currentNode->y) * DAT_01218e48 * fScale + fConst1);
                        *writePtr = currentNode->depth;
                        writePtr[1] = fConst1; // probably w or some constant
                        vi++;
                        writePtr += 4;
                    } while (vi < 4);

                    // Extract some min/max from the vertex data (likely for sorting or culling)
                    float v0z = vertexBuffer[0]; // first vertex's z? Actually vertexBuffer[0] is x of first vertex, but they treat as fStack_40
                    fStack_40 = *vertexBuffer;
                    fVar12 = DAT_00e2eff4;
                    if (DAT_00e2eff4 < fStack_40 && fVar12 = fStack_40, fConst1 <= fStack_40) {
                        fVar12 = fConst1;
                    }
                    float v12z = vertexBuffer[12]; // fourth vertex's z?
                    float fVar13 = DAT_00e2eff4;
                    if (DAT_00e2eff4 < v12z && fVar13 = v12z, fConst1 <= v12z) {
                        fVar13 = fConst1;
                    }
                    float v1z = vertexBuffer[1];
                    float fVar14 = DAT_00e2eff4;
                    if (DAT_00e2eff4 < v1z && fVar14 = v1z, fConst1 <= v1z) {
                        fVar14 = fConst1;
                    }
                    float v13z = vertexBuffer[13];
                    float fVar10 = DAT_00e2eff4;
                    if (DAT_00e2eff4 < v13z && fVar10 = fConst1, v13z < fConst1) {
                        fVar10 = v13z;
                    }
                    fStack_30 = (fVar13 - fVar12) / (v12z - fStack_40);
                    fStack_34 = (fVar10 - fVar14) / (v13z - v1z);

                    FUN_0060cde0(); // free/cleanup? (maybe deallocate temporary)

                    // Unlock the attached object
                    (*(void (**)(void*, int))(*(uint32_t**)currentNode->attachedObject)[6])(currentNode->attachedObject, 1);

                    fVar3 = DAT_00e2b1a4;
                    fVar12 = DAT_00e2b04c;
                    float lifetime = (float)currentNode->particleLifetime;
                    if (lifetime <= DAT_00e2cd54) {
                        fVar11 = 0.0f;
                    } else {
                        fStack_30 = (float)(int)screenPosX;
                        if ((int)screenPosX < 0) {
                            fStack_30 += DAT_00e44578;
                        }
                        fStack_30 = fStack_30 / lifetime;
                        fVar11 = fStack_30 * DAT_00e2b04c;
                        if (fVar11 <= 0.0f) {
                            fVar11 = 0.0f;
                        } else if (DAT_00e2b1a4 <= fVar11) {
                            fVar11 = DAT_00e2b1a4;
                        }
                    }
                    currentNode->particleSpeed = (int)fVar11;
                    fVar11 = fVar3 - (float)currentNode->particleSpeed;
                    currentNode->particleSpeed = (int)(fVar3 - fVar11 * fVar11);
                    // Final calculation (used for some attenuation)
                    fVar12 = fStack_40 * fVar12 * fStack_3c * fVar12 * fStack_2c * (float)DAT_00e2b118;
                }
                currentNode->particleLifetime = (int)fVar12;
            }
            currentNode = currentNode->next;
        } while (currentNode != nullptr);

        // Post-update global state changes
        if (DAT_0121a290 != 0) {
            uVar9 = DAT_0121a290 & 0xff;
            if (DAT_011eb8fc[DAT_0121a204 * 16] != '\0') {
                uVar9 += 0x10;
            }
            FUN_00618d40();
            DAT_011d912c[uVar9] = 0;
        }

        // Clear some global pointers and flags
        DAT_012058e8 = nullptr;
        DAT_012058f0 = 0;
        DAT_0121a310 = 0;
        DAT_0121a314 = 0;
        DAT_0121a318 = 0;

        // Set some more rendering parameters (second batch)
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;

        if (DAT_012058d0 < 7) DAT_012058d0 = 7;
        if (7 < DAT_00f15988) DAT_00f15988 = 7;
        _DAT_011f39f4 = 1;

        if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
        if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
        _DAT_011f3a10 = 1;

        if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 7;

        if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
        _DAT_011f3a38 = 0;

        if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
        _DAT_011f3a14 = 0;

        if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
        if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
        _DAT_011f3a44 = 0;

        FUN_00417cf0(1, 5, 6);

        if (DAT_012058d4 < 0xa8) DAT_012058d4 = 0xa8;
        if (0xa7 < DAT_00f1598c) DAT_00f1598c = 0xa8;
        _DAT_011f3c78 = 0xf;

        if (DAT_012058d4 < 0xbe) DAT_012058d4 = 0xbe;
        if (0xbd < DAT_00f1598c) DAT_00f1598c = 0xbe;
        _DAT_011f3cd0 = 0xf;
    }

    // Clear the list head and type?
    context->nodeList = nullptr;
    context->type = 0;
}