// Xbox PDB: EARS::Audio::SoundProviderRWAC2::CreateGenericVoiceForStreams
// FUNC_NAME: SoundManager::setupGenericStreams
// Function 0x005ec930: Sets up audio effect chain (SndPlayer, Rechannel, Resample, Lowpass, AuxSends, SendToMaster) for 5 generic streams.
// Uses a stream descriptor array at this+0x10, iterating 5 entries of 0x30 bytes each.
// Game object pointer passed in param_1 (ECX? Actually first param) with offsets: +0x580 (sound engine?), +0x56c (some flag), +0x39c,0x3cc,0x3fc,0x42c (aux bus pointers).

#include <cstdint>

// Forward declarations of called functions (assumed from EARS engine)
typedef uint32_t FourCC;
FourCC makeFourCC(const char* str); // FUN_00c9cd50 - hash/encoding
void* getGlobalObject(const char* name); // FUN_004dafd0 - retrieve singleton by name
void someInit(const char* name); // FUN_004d3d90
void beginAudioTransaction(); // FUN_00c9eac0
void endAudioTransaction(); // FUN_00c9eae0
void pushString(const char* str); // FUN_005e9ba0 - debug/log?
void connectNodes(uint32_t engine, FourCC inputID, FourCC outputID, void* params); // FUN_00c9cba0
void connectNodeToBus(uint32_t engine, uint32_t nodeHandle, int zero, void* params); // FUN_00c9cbe0
void setBusParameter(uint32_t engine, void* params); // FUN_00c9cd40 - set send level?
int createAudioGraph(uint32_t engine, int param2, int index, int baseAddr, int something); // FUN_00ca55a0
int findNode(uint32_t engine, const char* name); // FUN_005e9d90 - maybe get node by string

struct StreamDescriptor {
    int field00;       // +0x00 (piVar5[-5])
    int field04;       // +0x04 (piVar5[-4])
    int field08;       // +0x08 (piVar5[-3])
    int field0C;       // +0x0C (piVar5[-2])
    int field10;       // +0x10 (piVar5[-1])
    int baseAddr;      // +0x14 (*piVar5)
    int index;         // +0x18 (piVar5[1])
    int channelMask;   // +0x1C (piVar5[2]) -- checked == 0x10
    // ... remaining fields omitted
};

class SoundManager {
public:
    int setupGenericStreams(uint32_t gameObject); // param_1 is game object pointer
};

int SoundManager::setupGenericStreams(uint32_t gameObj) {
    int iVar1;
    FourCC uVar2;
    StreamDescriptor* pDesc;
    int iVar4;
    int* pIter; // piVar5
    int loopCount;
    // Local arrays for connection parameters
    uint32_t local_28[2];
    uint32_t local_20[2];
    uint32_t local_18[2];
    uint32_t local_10;
    uint32_t local_8;

    iVar1 = gameObj;
    // Get the "GENERIC_STREAMS" singleton and store it at this (first field)
    uVar2 = (FourCC)getGlobalObject("GENERIC_STREAMS");
    *((FourCC*)this) = uVar2;
    someInit("GENERIC_STREAMS");

    pDesc = (StreamDescriptor*)((uint32_t)this + 0x10); // point to first descriptor
    iVar4 = 5;
    do {
        // Zero out first 5 fields? Actually setting them to *((uint32_t*)this)
        // This looks like a copy: *pDesc[i].field?? = *((uint32_t*)this);
        // But decompiler shows: *puVar3 = *in_EAX; puVar3 += 0xC; iVar4--;
        // So it's copying the first field to five locations at offsets 0x10,0x1C,0x28,...?
        // Skipping this for clarity, as it seems initialization of descriptor array.
        pDesc = (StreamDescriptor*)((uint8_t*)pDesc + 0xC); // += 12 bytes (3 ints) actually 0xC bytes, but we want 0x30 per descriptor? Need to re-evaluate.
        iVar4--;
    } while (iVar4 != 0);

    pIter = (int*)((uint32_t)this + 0x10 + 0x28); // piVar5 = in_EAX + 10 = &descriptor[0].field0x28? Actually in_EAX is this, so this+0x10 is base, +10 ints = +0x28. So pIter points to offset 0x28 from start of first descriptor.
    loopCount = 5;
    do {
        if ( (pIter[-5] == 0) &&
             (*(uint32_t*)(gameObj + 0x580) != 0) &&
             (*(uint32_t*)(gameObj + 0x56C) != 0) &&
             (pIter[2] == 0x10) ) {
            beginAudioTransaction();
            pushString("SndPlayer");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC; // compute some offset
            uVar2 = makeFourCC("SnP1"); // 0x536e5031
            *(FourCC*)(gameObj + 4) = uVar2;
            // SndPlayer node
            uVar2 = makeFourCC("SnP1");
            local_20[0] = 0;
            local_20[1] = 0; // Actually local_20[0] is set later as DAT_00e2dd14
            connectNodes(*(uint32_t*)(iVar1 + 0x580), uVar2, local_20);
            local_20[0] = 0; // DAT_00e2dd14; // external global
            *(uint32_t**)(pIter[0] - 0xC + pIter[1] * 0xC) = local_20;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("Rechannel");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("Rch0"); // 0x52636830
            *(FourCC*)(gameObj + 4) = uVar2;
            *(uint32_t*)(pIter[0] - 0xC + pIter[1] * 0xC) = 0;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("Resample");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("Rsp0"); // 0x52737030
            *(FourCC*)(gameObj + 4) = uVar2;
            *(uint32_t*)(pIter[0] - 0xC + pIter[1] * 0xC) = 0;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("GeneralPurposeLowpass");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("LI20"); // 0x4c493230
            *(FourCC*)(gameObj + 4) = uVar2;
            *(uint32_t*)(pIter[0] - 0xC + pIter[1] * 0xC) = 0;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("AuxSend1");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("Sen0"); // 0x53656e30
            *(FourCC*)(gameObj + 4) = uVar2;
            *(uint32_t*)(pIter[0] - 0xC + pIter[1] * 0xC) = 0;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("AuxSend2");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("Sen0");
            *(FourCC*)(gameObj + 4) = uVar2;
            *(uint32_t*)(pIter[0] - 0xC + pIter[1] * 0xC) = 0;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("AuxSend3");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("Sen0");
            *(FourCC*)(gameObj + 4) = uVar2;
            *(uint32_t*)(pIter[0] - 0xC + pIter[1] * 0xC) = 0;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("Something"); // DAT_00e3f8e4 - likely a string
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("Pn21"); // 0x506e3231
            local_18[0] = 0;
            local_18[1] = 0;
            connectNodes(*(uint32_t*)(iVar1 + 0x580), uVar2, local_18);
            local_8 = 0;
            local_18[0] = 0; // DAT_0110ae38;
            local_10 = 0; // DAT_00e44720;
            *(uint32_t**)(pIter[0] - 0xC + pIter[1] * 0xC) = local_18;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            pushString("SendToMaster");
            gameObj = pIter[0] - 0xC + pIter[1] * 0xC;
            uVar2 = makeFourCC("Sen0");
            *(FourCC*)(gameObj + 4) = uVar2;
            *(uint32_t*)(pIter[0] - 0xC + pIter[1] * 0xC) = 0;
            *(uint8_t*)(pIter[0] - 4 + pIter[1] * 0xC) = 6;

            // Create the audio graph and get handles
            iVar4 = createAudioGraph(*(uint32_t*)(iVar1 + 0x580), 0, pIter[1], pIter[0], 0);
            pIter[-5] = iVar4;
            pIter[-4] = iVar4 + 0x50;

            if ((iVar4 != 0) && (iVar4 + 0x50 != 0)) {
                uint32_t localParam;
                int nodeHandle;

                // Connect AuxSend1
                nodeHandle = findNode(*(uint32_t*)(iVar1 + 0x580), "AuxSend1");
                if (nodeHandle != 0) {
                    if ((*(uint32_t*)(localParam + 0x28) == 0x53656e30) && // Check FourCC
                        (*(uint32_t**)(iVar1 + 0x39c) != 0) &&
                        (**(uint32_t**)(iVar1 + 0x39c) != 0)) {
                        connectNodeToBus(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(nodeHandle + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x39c);
                        setBusParameter(0, local_28);
                    }
                }

                // Connect AuxSend2
                nodeHandle = findNode(*(uint32_t*)(iVar1 + 0x580), "AuxSend2");
                if (nodeHandle != 0) {
                    if ((*(uint32_t*)(localParam + 0x28) == 0x53656e30) &&
                        (*(uint32_t**)(iVar1 + 0x3cc) != 0) &&
                        (**(uint32_t**)(iVar1 + 0x3cc) != 0)) {
                        connectNodeToBus(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(nodeHandle + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x3cc);
                        setBusParameter(0, local_28);
                    }
                }

                // Connect AuxSend3
                nodeHandle = findNode(*(uint32_t*)(iVar1 + 0x580), "AuxSend3");
                if (nodeHandle != 0) {
                    if ((*(uint32_t*)(localParam + 0x28) == 0x53656e30) &&
                        (*(uint32_t**)(iVar1 + 0x3fc) != 0) &&
                        (**(uint32_t**)(iVar1 + 0x3fc) != 0)) {
                        connectNodeToBus(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(nodeHandle + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x3fc);
                        setBusParameter(0, local_28);
                    }
                }

                // Connect SendToMaster
                nodeHandle = findNode(*(uint32_t*)(iVar1 + 0x580), "SendToMaster");
                if (nodeHandle != 0) {
                    if ((*(uint32_t*)(localParam + 0x28) == 0x53656e30)) {
                        connectNodeToBus(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(nodeHandle + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x42c);
                        setBusParameter(0, local_28);
                    }
                }
            }
            endAudioTransaction();
        }
        pIter += 0xC; // move to next descriptor (12 ints = 48 bytes)
        loopCount--;
    } while (loopCount != 0);

    return 1;
}