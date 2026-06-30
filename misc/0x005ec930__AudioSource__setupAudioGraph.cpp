// FUNC_NAME: AudioSource::setupAudioGraph
// Function at 0x005ec930: Sets up the audio processing graph for a sound source.
// Iterates over 5 generic stream slots, creates a chain of audio nodes (SndPlayer, Rechannel, Resample, Lowpass, AuxSends, Panner, SendToMaster),
// and connects aux sends to the appropriate audio bus buffers.

#include <cstdint>

// Forward declarations for EARS engine functions (assumed)
uint32_t hashString(const char* str); // FUN_00c9cd50
void* getNamedObject(const char* name); // FUN_004dafd0
void pushNamedObject(const char* name); // FUN_004d3d90
void beginAudioGraph(); // FUN_00c9eac0
void endAudioGraph(); // FUN_00c9eae0
void pushAudioNodeName(const char* name); // FUN_005e9ba0
void* createAudioNode(uint32_t typeId); // FUN_00c9cba0
int createAudioStream(void* audioSystem, int param1, int param2, int param3, int param4); // FUN_00ca55a0
void* getAudioNodeByName(const char* name, int* outParam); // FUN_005e9d90
void connectAudioNodes(void* audioSystem, void* sourceNode, int param, uint32_t* buffer); // FUN_00c9cbe0
void setAudioNodeParameter(int param, uint32_t* buffer); // FUN_00c9cd40

class AudioSource {
public:
    // Offsets (relative to this):
    // +0x56c: some handle (e.g., audio system handle)
    // +0x580: another handle (e.g., audio system handle)
    // +0x39c: pointer to AuxSend1 buffer
    // +0x3cc: pointer to AuxSend2 buffer
    // +0x3fc: pointer to AuxSend3 buffer
    // +0x42c: pointer to SendToMaster buffer
    // +0x???: array of 5 generic stream slots (each 12 bytes)
    //   Slot structure (12 bytes):
    //   +0: streamId (int)
    //   +4: some flag (int)
    //   +8: type (int, expected 0x10)
    //   +0xc: next slot? Actually loop increments by 0xc

    int setupAudioGraph() {
        int thisPtr = reinterpret_cast<int>(this);
        int iVar1 = thisPtr;
        uint32_t uVar2;
        int* in_EAX; // pointer to generic streams structure
        int* puVar3;
        int iVar4;
        int* piVar5;
        int local_30;
        uint32_t local_28[2];
        uint32_t local_20[2];
        uint32_t local_18[2];
        uint32_t local_10;
        uint32_t local_8;

        // Get the generic streams object
        in_EAX = (int*)getNamedObject("GENERIC_STREAMS");
        *in_EAX = (int)in_EAX; // self-reference? Possibly a bug or intentional
        pushNamedObject("GENERIC_STREAMS");

        // Initialize 5 slots at offsets 0x10, 0x1c, 0x28, 0x34, 0x40 (each 12 bytes apart)
        puVar3 = in_EAX + 0x10; // offset 0x10 in bytes = 4 ints
        iVar4 = 5;
        do {
            *puVar3 = *in_EAX; // copy the self-reference
            puVar3 = puVar3 + 0xc; // advance 12 bytes (3 ints)
            iVar4 = iVar4 - 1;
        } while (iVar4 != 0);

        // piVar5 points to the third slot? Actually in_EAX+10 (int offset 10 = byte 40)
        piVar5 = in_EAX + 10;
        local_30 = 5;
        do {
            // Check if slot is empty (piVar5[-5] == 0) and audio system handles are valid
            if ((((piVar5[-5] == 0) && (*(int*)(iVar1 + 0x580) != 0)) && (*(int*)(iVar1 + 0x56c) != 0)) &&
                (piVar5[2] == 0x10)) {
                beginAudioGraph();
                pushAudioNodeName("SndPlayer");
                int param_1 = *piVar5 + -0xc + piVar5[1] * 0xc; // calculate offset into slot? Actually *piVar5 is the slot base, piVar5[1] is index?
                uVar2 = hashString("SnP1"); // 0x536e5031
                *(uint32_t*)(param_1 + 4) = uVar2;
                uVar2 = hashString("SnP1");
                createAudioNode(*(uint32_t*)(iVar1 + 0x580), uVar2, local_20);
                local_20[0] = DAT_00e2dd14; // some global data
                *(uint32_t**)(*piVar5 + -0xc + piVar5[1] * 0xc) = local_20;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6; // type flag?

                pushAudioNodeName("Rechannel");
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("Rch0"); // 0x52636830
                *(uint32_t*)(param_1 + 4) = uVar2;
                *(uint32_t*)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                pushAudioNodeName("Resample");
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("Rsp0"); // 0x52737030
                *(uint32_t*)(param_1 + 4) = uVar2;
                *(uint32_t*)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                pushAudioNodeName("GeneralPurposeLowpass");
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("LI20"); // 0x4c493230
                *(uint32_t*)(param_1 + 4) = uVar2;
                *(uint32_t*)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                pushAudioNodeName("AuxSend1");
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("Sen0"); // 0x53656e30
                *(uint32_t*)(param_1 + 4) = uVar2;
                *(uint32_t*)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                pushAudioNodeName("AuxSend2");
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("Sen0");
                *(uint32_t*)(param_1 + 4) = uVar2;
                *(uint32_t*)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                pushAudioNodeName("AuxSend3");
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("Sen0");
                *(uint32_t*)(param_1 + 4) = uVar2;
                *(uint32_t*)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                pushAudioNodeName("Pn21"); // from DAT_00e3f8e4, likely "Pn21"
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("Pn21"); // 0x506e3231
                puVar3 = local_18;
                *(uint32_t*)(param_1 + 4) = uVar2;
                uVar2 = hashString("Pn21");
                createAudioNode(*(uint32_t*)(iVar1 + 0x580), uVar2, puVar3);
                local_8 = 0;
                local_18[0] = DAT_0110ae38; // some global
                local_10 = DAT_00e44720; // some global
                *(uint32_t**)(*piVar5 + -0xc + piVar5[1] * 0xc) = local_18;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                pushAudioNodeName("SendToMaster");
                param_1 = *piVar5 + -0xc + piVar5[1] * 0xc;
                uVar2 = hashString("Sen0");
                *(uint32_t*)(param_1 + 4) = uVar2;
                *(uint32_t*)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
                *(uint8_t*)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;

                // Create the audio stream
                iVar4 = createAudioStream(*(uint32_t*)(iVar1 + 0x580), 0, piVar5[1], *piVar5, 0);
                piVar5[-5] = iVar4; // store stream ID
                piVar5[-4] = iVar4 + 0x50; // some offset

                if ((iVar4 != 0) && (iVar4 + 0x50 != 0)) {
                    // Connect AuxSend1 to buffer at +0x39c
                    puVar3 = &param_1;
                    param_1 = 0;
                    uVar2 = getNamedObject("AuxSend1", puVar3);
                    iVar4 = getAudioNodeByName(uVar2, puVar3);
                    if (((iVar4 != 0) &&
                        ((*(int*)(param_1 + 0x28) == 0x53656e30 && (*(int**)(iVar1 + 0x39c) != (int*)0x0)))) &&
                        (**(int**)(iVar1 + 0x39c) != 0)) {
                        connectAudioNodes(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(iVar4 + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x39c);
                        setAudioNodeParameter(0, local_28);
                    }

                    // Connect AuxSend2 to buffer at +0x3cc
                    puVar3 = &param_1;
                    uVar2 = getNamedObject("AuxSend2", puVar3);
                    iVar4 = getAudioNodeByName(uVar2, puVar3);
                    if ((((iVar4 != 0) && (*(int*)(param_1 + 0x28) == 0x53656e30)) &&
                        (*(int**)(iVar1 + 0x3cc) != (int*)0x0)) && (**(int**)(iVar1 + 0x3cc) != 0)) {
                        connectAudioNodes(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(iVar4 + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x3cc);
                        setAudioNodeParameter(0, local_28);
                    }

                    // Connect AuxSend3 to buffer at +0x3fc
                    puVar3 = &param_1;
                    uVar2 = getNamedObject("AuxSend3", puVar3);
                    iVar4 = getAudioNodeByName(uVar2, puVar3);
                    if (((iVar4 != 0) && (*(int*)(param_1 + 0x28) == 0x53656e30)) &&
                        ((*(int**)(iVar1 + 0x3fc) != (int*)0x0 && (**(int**)(iVar1 + 0x3fc) != 0)))) {
                        connectAudioNodes(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(iVar4 + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x3fc);
                        setAudioNodeParameter(0, local_28);
                    }

                    // Connect SendToMaster to buffer at +0x42c
                    puVar3 = &param_1;
                    uVar2 = getNamedObject("SendToMaster", puVar3);
                    iVar4 = getAudioNodeByName(uVar2, puVar3);
                    if ((iVar4 != 0) && (*(int*)(param_1 + 0x28) == 0x53656e30)) {
                        connectAudioNodes(*(uint32_t*)(iVar1 + 0x580), *(uint32_t*)(iVar4 + 0x10), 0, local_28);
                        local_28[0] = **(uint32_t**)(iVar1 + 0x42c);
                        setAudioNodeParameter(0, local_28);
                    }
                }
                endAudioGraph();
            }
            piVar5 = piVar5 + 0xc; // move to next slot
            local_30 = local_30 - 1;
        } while (local_30 != 0);
        return 1;
    }
};