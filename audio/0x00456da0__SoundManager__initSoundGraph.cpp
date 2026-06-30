// FUNC_NAME: SoundManager::initSoundGraph
// Function address: 0x00456da0
// Role: Initialize the audio graph for the game's sound system, setting up buses, submixes, and routing for music stems.

#include <cstdint>

// Constants for audio bus types (fourCC codes)
static const uint32_t kBusSnare = 0x536e5031;     // "SnP1"
static const uint32_t kBusMasterChannel = 0x4d436830; // "MCh0"
static const uint32_t kBusReverbSend = 0x52737030;    // "Rsp0"
static const uint32_t kBusReverbReturn = 0x526f7530;  // "Rou0"
static const uint32_t kBusSub = 0x53756230;           // "Sub0"
static const uint32_t kBusGainFactor = 0x47614630;    // "GaF0"
static const uint32_t kBusSend = 0x53656e30;          // "Sen0"
static const uint32_t kBusDelay = 0x44656c30;         // "Del0"
static const uint32_t kBusReverbMaster = 0x524d3130;  // "RM10"

// External functions (from game engine, EARS)
extern void FUN_00ab5fb0(int, int);               // Probably sound system init
extern void FUN_00abd570();                        // Probably sound system update init
extern int FUN_004d3fe0(int size);                 // Memory allocation
extern void FUN_00c9eac0();                        // Audio engine startup
extern void FUN_00ca3ee0();                        // Check if audio hardware present
extern uint32_t FUN_00c9cd50(uint32_t fourCC);     // Resolve audio bus ID by fourCC
extern uint32_t FUN_00cada50();                    // Get default bus ID
extern uint32_t FUN_00c9ceb0(uint32_t id);         // Clone bus ID
extern uint32_t FUN_00ca9d60();                    // Get another default bus
extern int FUN_00c9cba0(int engine, uint32_t busID, uint32_t* outBuffer); // Set bus graph
extern int FUN_00ca55a0(int engine, int busType, int numInputs, void* graphDesc, int); // Create audio bus
extern void FUN_00c9cbe0(int engine, uint32_t busID, int, uint32_t* outBuffer); // Get bus parameter
extern void FUN_00c9cd40(int, uint32_t* paramSet); // Set audio bus parameters
extern uint32_t FUN_00c9ebd0();                    // Get current time / sample position
extern void FUN_00c9eae0();                        // Commit sound changes

// External data globals (assumed constants)
extern uint32_t DAT_0110ac04;          // Default bus volume
extern uint32_t DAT_00e2eff4;          // Default bus pan
extern uint32_t DAT_00e2b1a4;          // Default bus parameters (null/zero)
extern uint32_t DAT_00e2dd14;          // Default bus format
extern uint32_t DAT_00e44578;          // Conversion constant for pan offset
extern uint32_t DAT_00e2b04c;          // Pan value for right channel
extern uint32_t DAT_00e445ac;          // Default bus parameters for master
extern uint32_t DAT_00e2d99c;          // Some audio parameter (volume?)
extern uint32_t DAT_00e2b198;          // Another default parameter
extern uint32_t DAT_00e31a78[];        // String "MultiStreamSubmixA"
extern void* PTR_FUN_00e31a94;         // Vtable pointer for this class

// Structure for audio bus graph description
struct AudioBusDesc {
    uint32_t* busPtr;      // Pointer to bus ID/object
    uint32_t busID;        // Bus type ID
    uint8_t channelCount;  // Number of channels (usually 1 or 2)
    uint8_t _pad[3];
    uint32_t inputBusID;   // Input bus ID
};

void __thiscall SoundManager::initSoundGraph(char* nameCounter) {
    // Initialize member fields
    this->vtable = (void*)&PTR_FUN_00e31a94;
    this->field_0x04 = 1;
    this->field_0x08 = 0;

    // Default bus parameter values (volume, pan, etc.)
    this->busVolume = DAT_0110ac04;
    this->busPan = DAT_00e2eff4;
    this->defaultParam = DAT_00e2b1a4;

    this->field_0xD0 = 3;    // +0xD0: number of streams?
    this->field_0xD4 = 0;
    this->field_0xD8 = 0;
    this->field_0xDC = 0;
    this->busMasterVolume = DAT_0110ac04; // +0xE0
    this->field_0xE4 = 0;
    this->field_0xE8 = DAT_00e2b1a4;
    this->field_0xEC = DAT_00e2b1a4;
    this->field_0xF0 = DAT_00e2b1a4;
    this->field_0xF4 = DAT_00e2b1a4;
    this->field_0xF8 = 1;
    this->field_0xFC = 0;
    this->vtable = (void*)&PTR_FUN_00e31a94;
    this->field_0xCC = 3;
    this->field_0xD0 = 0;
    this->field_0xD4 = 0;
    this->field_0xD8 = 0;
    this->field_0xDC = DAT_0110ac04;
    this->field_0xE0 = 0;
    this->field_0xE4 = DAT_00e2eff4;
    this->field_0xE8 = 0;
    this->field_0xF8 = DAT_00e2b1a4;
    this->field_0xFC = 0;
    this->field_0x100 = 0;
    this->field_0x104 = 0;
    this->field_0x108 = 0;
    this->field_0x10C = 0;
    this->field_0x110 = 0;
    this->field_0x114 = 0;
    this->field_0x118 = DAT_00e2eff4;
    this->field_0x11C = 0;
    this->field_0x120 = 0;
    this->field_0x124 = 0;
    this->field_0x128 = 0;
    this->field_0x12C = 0;
    this->field_0x130 = 0;
    this->field_0x134 = 0;
    this->field_0x138 = 0;
    this->field_0x13C = 0;
    this->field_0x140 = 0;
    this->field_0x144 = 0;
    this->field_0x148 = 0;
    this->field_0x14C = 0;
    this->field_0x150 = 0;
    this->field_0x154 = 0;
    this->field_0x158 = 0;
    this->field_0x15C = 0;
    this->field_0x160 = 0;
    this->field_0x164 = 0;
    this->field_0x168 = 0;
    this->field_0x16C = 0;
    this->field_0x170 = 0;
    this->field_0x174 = 0;
    this->field_0x178 = 0;
    this->field_0x17C = 0;
    this->field_0x180 = 0;
    this->field_0x184 = 0;
    this->field_0x188 = 0;
    this->field_0x18C = 0;
    this->field_0x190 = 0;
    this->field_0x194 = 0;
    this->field_0x198 = 0;
    this->field_0x19C = 0;
    this->field_0x1A0 = 0;
    this->field_0x1A4 = 0;
    this->field_0x1A8 = 0;
    this->field_0x1AC = 0;
    this->field_0x1B0 = 0;
    this->field_0x1B4 = 0;
    this->field_0x1B8 = 0;
    this->field_0x1BC = 0;
    this->field_0x1C0 = 0;
    this->field_0x1C4 = 0;
    this->field_0x1C8 = 0;
    this->field_0x1CC = 0;
    this->field_0x1D0 = 0;
    this->field_0x1D4 = 0;
    this->field_0x1D8 = 0;

    // Initialize audio engine
    FUN_00ab5fb0(0, 1);  // Initialize sound subsystem
    this->field_0x1DC = 0;
    this->field_0x1E0 = 0;
    this->field_0x1E4 = 0;
    this->field_0x1E8 = 0;
    this->field_0x1EC = 0;
    this->field_0x1F0 = 0;
    this->field_0x1F4 = 0;
    this->field_0x1F8 = DAT_00e2eff4;
    this->field_0x1FC = 0;
    this->field_0x200 = 0;
    this->field_0x204 = 0;
    this->field_0x208 = 0;
    this->field_0x20C = 0;
    this->field_0x210 = 0;
    this->field_0x214 = 0;
    this->field_0x218 = 0;
    this->field_0x21C = 0;
    this->field_0x220 = 0;
    this->field_0x224 = 0;
    this->field_0x228 = 0;
    this->field_0x22C = 0;
    this->field_0x230 = 0;
    this->field_0x234 = 0;
    this->field_0x238 = 0;
    this->field_0x23C = 0;
    this->field_0x240 = 3;  // audio mode?
    this->field_0x244 = 0;
    this->field_0x248 = 0;
    this->field_0x24C = 0;
    this->field_0x250 = 0;
    this->field_0x254 = 0x20;
    this->field_0x258 = 0;
    this->field_0x25C = 0;
    this->field_0x260 = 0;
    this->field_0x264 = 0;
    this->field_0x268 = 0;

    // Allocate buffers for audio graph
    FUN_004d3fe0(0x104);  // Allocate memory for bus objects
    FUN_004d3fe0(0x104);  // Allocate another

    // If audio engine is active, set up the graph
    int engine = DAT_01143360;  // Global audio engine handle
    if (engine != 0) {
        FUN_00c9eac0();  // Start audio engine
        if (*(int*)(engine + 0x28) == 0) {
            FUN_00ca3ee0();  // Initialize audio hardware
        }

        // Resolve bus IDs by fourCC
        uint32_t busSnare = FUN_00c9cd50(kBusSnare);          // +0x???
        uint32_t busMasterChannel = FUN_00c9cd50(kBusMasterChannel); // +0x???
        uint32_t busReverbSend = FUN_00c9cd50(kBusReverbSend);
        uint32_t busReverbReturn = FUN_00c9cd50(kBusReverbReturn);
        uint32_t busSub = FUN_00c9cd50(kBusSub);
        uint32_t busGainFactor = FUN_00c9cd50(kBusGainFactor);
        uint32_t busSend = FUN_00c9cd50(kBusSend);
        uint32_t busDelay = FUN_00c9cd50(kBusDelay);
        uint32_t busReverbMaster = FUN_00c9cd50(kBusReverbMaster);

        // Ensure required buses exist, create defaults if not
        if (busReverbReturn == 0) {
            uint32_t defaultBus = FUN_00cada50();
            busReverbReturn = FUN_00c9ceb0(defaultBus);
        }
        if (busMasterChannel == 0) {
            uint32_t defaultBus = FUN_00ca9d60();
            busMasterChannel = FUN_00c9ceb0(defaultBus);
        }

        // Setup the first bus graph (master output)
        uint32_t graphBuffer[4];  // Used for graph descriptions
        FUN_00c9cba0(engine, busSnare, graphBuffer);
        
        AudioBusDesc busDesc;
        busDesc.busPtr = graphBuffer;
        busDesc.busID = busSnare;
        busDesc.channelCount = 8;  // 8 channels
        busDesc._pad[0] = 0;
        busDesc.inputBusID = busMasterChannel;  // Input from master channel
        
        // Prepare a graph with 8 slots
        struct {
            int field0;
            uint32_t inputBus;
            uint8_t channelCount;
            uint8_t _pad[3];
        } graphSlots[8];
        for (int i = 0; i < 8; i++) {
            graphSlots[i].field0 = 0;
            graphSlots[i].inputBus = busMasterChannel;
            graphSlots[i].channelCount = 8;
        }

        // Create the master bus (bus index 3 in object)
        int masterBus = FUN_00ca55a0(engine, 0, 0x0B, &busDesc, 0);
        this->masterBusID = masterBus;
        this->masterBusID2 = masterBus + 0x50;  // +0x50 offset for related object

        // Second bus graph for the music stem streams (8 stereo pairs)
        char stemName[] = "MultiStreamSubmixA";  // Base name for stream submixes
        char* namePtr = stemName;
        // Calculate end of string (to append letters)
        while (*namePtr != '\0') namePtr++;
        // Save pointer for later name modifications
        char* nameEnd = namePtr - 1;  // Points to the position before null

        // Setup second bus graph (for stereo stems)
        uint32_t stemGraph[2];
        FUN_00c9cba0(engine, busSub, stemGraph);
        
        AudioBusDesc stemDesc;
        stemDesc.busPtr = stemGraph;
        stemDesc.busID = busSub;
        stemDesc.channelCount = 1;
        stemDesc._pad[0] = 0;
        stemDesc.inputBusID = busReverbReturn;

        // Create 8 stereo submix buses for music stems
        for (int i = 0; i < 8; i++) {
            // Generate unique name "MultiStreamSubmixA", "MultiStreamSubmixB", etc.
            char letter = *nameCounter;
            *nameEnd = letter + 'A';  // Replace last char with letter
            (*nameCounter)++;         // Increment counter for next time

            // Create the submix bus
            int stemBus = FUN_00ca55a0(engine, 1, 4, &stemDesc, 0);
            this->stemBusIDs[i*2] = stemBus;    // +0x???
            this->stemBusIDs[i*2+1] = stemBus + 0x50;

            // Set volume/pan for this submix
            uint32_t paramBuffer[4];
            FUN_00c9cbe0(engine, busReverbReturn, 0, paramBuffer);
            paramBuffer[0] = *(uint32_t*)(stemBus + 0x50);  // Get handle
            float pan = (float)i;  // Pan based on index
            if (i < 0) pan += DAT_00e44578;  // Convert negative (not reached)
            paramBuffer[2] = pan;
            paramBuffer[3] = 0.0f;
            FUN_00c9cd40(0, paramBuffer);
        }
        // Set the name pointer back to original? (Seems this loop modifies the string in place)

        // Create two more buses for reverb send(?) 
        AudioBusDesc reverbDesc;
        reverbDesc.busPtr = stemGraph;
        reverbDesc.busID = busSub;
        reverbDesc.channelCount = 1;
        reverbDesc._pad[0] = 0;
        reverbDesc.inputBusID = busReverbReturn + 0x50;  // Some offset

        for (int i = 0; i < 2; i++) {
            char letter = *nameCounter;
            *nameEnd = letter + 'A';
            (*nameCounter)++;

            int reverbBus = FUN_00ca55a0(engine, 2, 4, &reverbDesc, 0);
            this->reverbBusIDs[i*2] = reverbBus;    // +0x???
            this->reverbBusIDs[i*2+1] = reverbBus + 0x50;
        }

        // Create a master reverb bus (index 0x2F)
        char letter = *nameCounter;
        *nameEnd = letter + 'A';
        (*nameCounter)++;

        AudioBusDesc masterReverbDesc;
        masterReverbDesc.busPtr = stemGraph;
        masterReverbDesc.busID = busSub;
        masterReverbDesc.channelCount = 6;  // 6 channels?
        masterReverbDesc._pad[0] = 0;
        masterReverbDesc.inputBusID = busGainFactor;  // Connect to gain factor bus

        int masterReverbBus = FUN_00ca55a0(engine, 3, 3, &masterReverbDesc, 0);
        this->masterReverbBusID = masterReverbBus;
        this->masterReverbBusID2 = masterReverbBus + 0x50;

        // Now configure pan/volume for the 8 stereo stems (again? maybe finalize routing)
        for (int i = 0; i < 8; i++) {
            // Get a parameter buffer
            uint32_t paramBuffer[4];
            FUN_00c9cbe0(engine, busSend, 0, paramBuffer);
            paramBuffer[0] = *(uint32_t*)(this->stemBusIDs[(i & 1) + 10]); // Pick odd/even?
            // Actually the code: unaff_ESI[((local_18c & 1) + 10) * 4] - that's offset into array
            // Assuming stemBusIDs is at offset 0x28? Hard to reconstruct perfectly.
            FUN_00c9cd40(0, paramBuffer);

            // Set volume/pan for the stereo pair
            uint32_t volParam[4];
            FUN_00c9cbe0(engine, busReverbReturn, 0, volParam);
            volParam[0] = *(uint32_t*)(this->masterReverbBusID2); // +0x30
            volParam[1] = 0.0f;
            volParam[2] = 0.0f;
            if (i & 1) {
                volParam[2] = DAT_00e2b04c;  // Pan right
            }
            volParam[3] = 0.0f;
            FUN_00c9cd40(0, volParam);
        }

        // Set master volume for the whole system
        uint32_t masterVolParam[4];
        FUN_00c9cbe0(engine, busMasterChannel, 0, masterVolParam);
        masterVolParam[0] = *(uint32_t*)(this->masterReverbBusID2);
        masterVolParam[1] = 0.0f;
        masterVolParam[2] = (float)DAT_00e2d99c;  // Volume value
        masterVolParam[3] = 0.0f;
        FUN_00c9cd40(0, masterVolParam);

        // Finalize: set a parameter to current time/sample
        uint32_t timeParam[2];
        FUN_00c9cbe0(engine, *(uint32_t*)(*(int*)(this->masterReverbBusID2 + 8) + 0x10), 0, timeParam);
        timeParam[0] = FUN_00c9ebd0();  // Current sample position
        FUN_00c9cd40(0, timeParam);

        FUN_00c9eae0();  // Commit changes
    }
}