// FUNC_NAME: SoundManager::initializeVoiceGraphs
// Address: 0x005ee6e0
// Sets up the DSP graph for all 128 voice slots.
// Each voice gets a chain: SndPlayer -> Rechannel -> Resample -> Gainfader -> GeneralPurposeLowpass -> AuxSend1/2/3 -> SendToMaster.
// The aux sends are connected to the corresponding buses stored in this object.

#include <cstddef>
#include <cstdint>

// Forward declarations of engine functions (names guessed from context)
void* allocateMemory(const char* poolName);
void pushStackContext();
void popStackContext();
uint32_t createNode(const char* nodeType);  // Returns node's four‑character code
uint32_t getNodeId(uint32_t fourCC);       // Returns a node ID from a FourCC code
void connectNodes(uint32_t graphHandle, uint32_t sourceNodeID, int destPort, uint32_t destNodeID);
void setBusSend(uint32_t param, uint32_t busHandleOrValue);
uint32_t getBusHandle(uint32_t graphHandle, uint32_t nodeID, int port);
uint32_t buildGraph(uint32_t graphHandle, int unk, int numNodes, void* nodeList, int unk2);
uint32_t findGraphNode(uint32_t graphHandle, const char* nodeName);
void freeMemory(void* ptr);

class SoundManager {
public:
    // Offsets from this pointer (0x00)
    uint32_t field_0x56c;        // +0x56c : pointer to something (maybe output graph?)
    uint32_t field_0x580;        // +0x580 : graph handle (sound engine context)
    uint32_t field_0x39c;        // +0x39c : pointer to bus pointer for AuxSend1
    uint32_t field_0x3cc;        // +0x3cc : pointer to bus pointer for AuxSend2
    uint32_t field_0x3fc;        // +0x3fc : pointer to bus pointer for AuxSend3
    uint32_t field_0x42c;        // +0x42c : pointer to bus pointer for SendToMaster
    // Voice state arrays start at +0x674
    // Each voice slot occupies 0x3e*4 = 0xF8 bytes? Actually piVar5 steps by 0x3e (62) ints = 0xF8 per slot.
    // Let's define a voice state struct (inferred)
    struct VoiceState {
        uint32_t slotIndex;      // offset 0 (piVar5[0])
        uint32_t nodeListPtr;    // offset -1 (piVar5[-1]) pointer to allocated node list
        uint32_t nodeCount;      // offset 1 (piVar5[1]) number of nodes?
        uint32_t graphHandle;    // offset -6 (piVar5[-6]) result of buildGraph
        uint32_t something;      // offset -5 (piVar5[-5]) = graphHandle + 0x50
        uint32_t allocHandle;    // offset 5 (piVar5[5]) from allocateMemory("RAMGENERIC")
    };
};
static_assert(offsetof(SoundManager, field_0x56c) == 0x56c, "field offset mismatch");
// Note: These fields are in the original object, not in the literal class definition.

// The function uses a pointer into the voice state array at this + 0x674.
// The loop iterates 0x80 = 128 times.

int SoundManager::initializeVoiceGraphs() {
    if ((field_0x580 == 0) || (field_0x56c == 0)) {
        return 1;
    }

    // piVar5 points to the start of the voice state array (this + 0x674)
    VoiceState* voice = reinterpret_cast<VoiceState*>(reinterpret_cast<uintptr_t>(this) + 0x674);

    for (int i = 0; i < 128; i++) {
        // Allocate a generic memory block for this voice
        voice->allocHandle = reinterpret_cast<uint32_t>(allocateMemory("RAMGENERIC"));

        // If the number of nodes is less than 0x10, we have an error? (perhaps we need to reinit something)
        if (voice->nodeCount < 0x10) {
            pushStackContext();
            popStackContext();
        }

        // Begin building the DSP node chain for this voice
        // The node list is a flat array of node descriptors; each descriptor seems to be:
        //   - 4 bytes: something? (offset -8 from nodeListPtr? or nodeListPtr + slotIndex*0xc?)
        // The pattern: piVar5[-1] (nodeListPtr) + slotIndex*0xc - 8
        // The slotIndex is voice->slotIndex.
        // We'll abstract as functions addNodeToChain().

        // Add SndPlayer node (FourCC "SnP1")
        addNode(voice, "SndPlayer", 0x536e5031, 6);  // type byte = 6

        // Add Rechannel node (FourCC "Rch0")
        addNode(voice, "Rechannel", 0x52636830, 2);

        // Add Resample node (FourCC "Rsp0")
        addNode(voice, "Resample", 0x52737030, 2);

        // Add Gainfader node (FourCC "Gaf0")
        addNode(voice, "Gainfader", 0x47614630, 2);

        // Add GeneralPurposeLowpass node (FourCC "LI20")
        addNode(voice, "GeneralPurposeLowpass", 0x4c493230, 2);

        // Add AuxSend1 node (FourCC "Sen0")
        addNode(voice, "AuxSend1", 0x53656e30, 2);

        // Add AuxSend2 node (FourCC "Sen0")
        addNode(voice, "AuxSend2", 0x53656e30, 2);

        // Add AuxSend3 node (FourCC "Sen0")
        addNode(voice, "AuxSend3", 0x53656e30, 2);

        // Add an unknown node (FourCC from DAT_00e3f8e4) – probably "Pn21"? Actually 0x506e3231 = "Pn21"?
        addNode(voice, "UnknownNode", 0x506e3231, 6);  // type 6
        // Also connect it to the graph? The code then calls connectNodes and sets bus.

        // Add SendToMaster node (FourCC "Sen0")
        addNode(voice, "SendToMaster", 0x53656e30, 6);

        // Finalize the graph for this voice
        uint32_t graphHandle = buildGraph(field_0x580, 0, voice->slotIndex, voice->nodeListPtr, 0);
        voice->graphHandle = graphHandle;
        voice->something = (graphHandle != 0) ? graphHandle + 0x50 : 0;

        if (graphHandle == 0) {
            // Build failed – free resources and reset
            voice->slotIndex = 0;
            freeMemory(reinterpret_cast<void*>(voice->nodeListPtr));
            voice->nodeListPtr = 0;
            voice->nodeCount = 0;
            voice->something = 0;
        } else {
            // Connect the bus sends for each aux and master send
            connectAuxSend(voice, "AuxSend1", this->field_0x39c);
            connectAuxSend(voice, "AuxSend2", this->field_0x3cc);
            connectAuxSend(voice, "AuxSend3", this->field_0x3fc);
            connectAuxSend(voice, "SendToMaster", this->field_0x42c);
        }

        // Move to next voice slot (each slot is 0x3e ints = 0xF8 bytes)
        voice = reinterpret_cast<VoiceState*>(reinterpret_cast<uintptr_t>(voice) + 0xF8);
    }
    return 1;
}

// Helper functions (not part of the original, but reconstructed for clarity)
void SoundManager::addNode(VoiceState* voice, const char* name, uint32_t fourCC, uint8_t type) {
    // The original code: For each node:
    //   FUN_005e9ba0(name);  // probably creates a node descriptor in a temp context
    //   uint32_t nodeId = getNodeId(fourCC);
    //   Then write to the node list: (nodeListPtr + slotIndex*0xc - 8) = nodeId;
    //                            (nodeListPtr + slotIndex*0xc - 12) = 0;
    //                            (nodeListPtr + slotIndex*0xc - 4) = type;
    //   nodeListPtr is voice->nodeListPtr, slotIndex is voice->slotIndex.
    // For simplicity we skip the exact memory layout.
    createNode(name);
    uint32_t nodeId = getNodeId(fourCC);
    // Write to node list...
    // ...
}

void SoundManager::connectAuxSend(VoiceState* voice, const char* nodeName, uint32_t busPointerOffset) {
    // Find the node in the graph
    uint32_t nodeHandle = findGraphNode(field_0x580, nodeName);
    if (nodeHandle != 0) {
        // Check if the node is of type "Sen0" (FourCC 0x53656e30)
        uint32_t* nodeTypePtr = reinterpret_cast<uint32_t*>(nodeHandle + 0x28); // +0x28 might store FourCC
        if (*nodeTypePtr == 0x53656e30) {
            uint32_t* busPtrPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + busPointerOffset);
            if (busPtrPtr != nullptr && *busPtrPtr != 0) {
                uint32_t busHandle;
                getBusHandle(field_0x580, nodeHandle + 0x10, 0, &busHandle);
                busHandle = *busPtrPtr;  // set the bus handle from the stored bus pointer
                setBusSend(0, &busHandle);
            }
        }
    }
}