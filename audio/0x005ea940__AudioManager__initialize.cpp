// FUNC_NAME: AudioManager::initialize
// Address: 0x005ea940 - Initialization of the audio manager system. Sets up audio engine, submixes, DSP effects, mastering, and streaming.

#include <cstdint>

// Forward declarations for known types
class AudioEngine;         // The main audio engine (created via FUN_00ca6240)
class AudioDataSource;     // Reference-counted audio data source
class StreamManager;       // Streaming audio handler

// Known constants
const uint32_t kSubmixFourCC_Sub0 = 0x53756230; // 'Sub0'
const uint32_t kSubmixFourCC_HI20 = 0x48493230; // 'HI20'
const uint32_t kSubmixFourCC_Co10 = 0x436f3130; // 'Co10'
const uint32_t kSubmixFourCC_Gai0 = 0x47616930; // 'Gai0'
const uint32_t kSubmixFourCC_Dac0 = 0x44616330; // 'Dac0'

class AudioManager {
public:
    // Offset 0x10f: pointer to submix bus list (array of structs with 0xc byte entries)
    // Offset 0x110: count of submix buses
    // Offset 0x115: mastering configuration pointer
    // Offset 0x15a: AudioDataSource* (shared pointer wrapper)
    // Offset 0x157: parent audio data source
    // Offset 0x158: working audio data source (from param_3+0x1c)
    // Offset 0x159: another source from param_3+0x20
    // Offset 0x10a, 0x10b: audio output objects (probably left/right channels)
    // Offset 0x15c: stream manager pointer (from FUN_00ca51e0)
    // Offset 0x160: AudioEngine*
    // Offset 0x15b: mixer from engine
    // Offset 0x162: bool initialized flag
    // Offset 0x2070: array of 5 mutex/entry structures (size 0x10 each? Actually 3 ints + byte)
    // Offset 0x20d0: array of 14 channel objects (size 0x5C each)

    byte initialize(void* parentData, int32_t config) {
        // param_1 = this, param_2 = parentData, param_3 = config
        // config is a pointer to a struct with fields at offsets 0x10, 0x1c, 0x20, 0x28

        FUN_005efad0(0x40); // Possibly start reference counting or allocate memory
        FUN_005efc20(4);    // Set alignment or size

        this->parentAudioSource = (AudioDataSource*)parentData;
        if (parentData) {
            (*(void(__thiscall**)(AudioDataSource*))(*(uint32_t*)parentData + 8))(); // AddRef
        }

        // Determine the working audio source from config
        int32_t* sourcePtr = *(int32_t**)(config + 0x1c);
        this->workingAudioSource = (AudioDataSource*)sourcePtr;
        if (sourcePtr == nullptr) {
            this->workingAudioSource = this->parentAudioSource;
        }
        if (this->workingAudioSource) {
            (*(void(__thiscall**)(AudioDataSource*))(*(uint32_t*)this->workingAudioSource + 8))(); // AddRef
        }

        int32_t* anotherSource = *(int32_t**)(config + 0x20);
        this->extraAudioSource = (AudioDataSource*)anotherSource;
        if (anotherSource) {
            (*(void(__thiscall**)(AudioDataSource*))(*(uint32_t*)anotherSource + 8))(); // AddRef
        }

        if (this->parentAudioSource == nullptr) {
            return 1; // Early exit if no parent
        }

        // Allocate a shared pointer wrapper (AudioDataSource?)
        uint32_t* wrapper = (uint32_t*)FUN_009c8e50(8);
        if (wrapper) {
            // Initialize wrapper: first set vtable to PTR_FUN_00e36f1c, then store working source
            wrapper[0] = &PTR_FUN_00e36f1c; // vtable for raw pointer
            wrapper[1] = (uint32_t)this->workingAudioSource;
            if (this->workingAudioSource) {
                (*(void(__thiscall**)(AudioDataSource*))(*(uint32_t*)this->workingAudioSource + 8))(); // AddRef
            }
            // Change vtable to actual shared pointer class
            wrapper[0] = &PTR_FUN_00e3fb8c;
        }
        this->sharedAudioSource = (AudioDataSource*)wrapper;

        // Create audio engine with chunk size 0x20000
        AudioEngine* engine = (AudioEngine*)FUN_00ca6240(this->sharedAudioSource, 0x20000);
        this->audioEngine = engine;
        *(uint32_t*)((uint32_t)engine + 0xcc) = DAT_00e44594; // Some engine parameter

        FUN_00c9eac0(); // Initialize audio engine internal

        // Get mixer from engine
        uint32_t mixer = *(uint32_t*)((uint32_t)engine + 0x28);
        if (mixer == 0) {
            FUN_00ca3ee0(); // Create a default mixer
            mixer = *(uint32_t*)((uint32_t)engine + 0x28);
        }
        this->mixer = (void*)mixer;

        // Register various DSP processing nodes
        if (this->mixer) {
            FUN_00c9ceb0(FUN_00caeb90()); // Register node1
            FUN_00c9ceb0(FUN_00ca76d0()); // Register node2
            FUN_00c9ceb0(FUN_00ca7ee0()); // etc.
            // ... many more registrations
            FUN_00c9ceb0(FUN_00ca9f50());
        }

        // Initialize another system (maybe physics or scripting)
        void* system = FUN_00ca3e90();
        if (system) {
            void* subSystem = FUN_00cc7220();
            FUN_00c96910(subSystem);
        }

        // Setup mastering configuration
        this->masteringConfig = (void*)FUN_004dafd0("MASTERING");

        // Finalize preliminary setup
        FUN_005ef9a0();
        FUN_005ef890();

        // Create and configure submix buses
        // Submix1: 'Sub0' (Submix)
        createSubmix("Submix1", kSubmixFourCC_Sub0, 6); // flags = 6 (0b110)
        // Submix2: Highpass 'HI20' with flags 6
        createSubmix("Highpass", kSubmixFourCC_HI20, 6);
        // Submix3: MasterCompressor 'Co10' with flags 6
        createSubmix("MasterCompressor", kSubmixFourCC_Co10, 6);
        // Submix4: PostCompressionGain 'Gai0' with flags 6
        createSubmix("PostCompressionGain", kSubmixFourCC_Gai0, 6);
        // Submix5: (name from DAT_00e3f95c) 'Dac0' with flags 0
        createSubmix(&DAT_00e3f95c, kSubmixFourCC_Dac0, 0);

        // Create two audio output objects from engine
        this->audioOutputLeft = (uint32_t)FUN_00ca55a0((uint32_t)this->audioEngine, 0xff, this->submixCount, this->submixList, 0);
        this->audioOutputRight = this->audioOutputLeft + 0x50; // Right channel offset

        // Handle de-emphasis or Dac0 parameter if mastering is active
        if (FUN_005e9d10()) {
            char result = (*(byte(__thiscall**)(AudioManager*, void*))this->vtable[0x34])(this, *(void**)(config + 0x28));
            if (result == 0) {
                result = (*(byte(__thiscall**)(AudioManager*, int))this->vtable[0x34])(this, 0);
            }
            if (result != 0) {
                // Set Dac0 parameter (de-emphasis?)
                uint8_t paramData[12];
                FUN_00c9cbe0((uint32_t)this->audioEngine, kSubmixFourCC_Dac0, 4, paramData);
                FUN_00c9cd40(4, paramData); // Apply parameter
            }
        }

        // Set master volume to stored value
        if (FUN_005e9d10()) {
            FUN_00ca4e90(0, DAT_00e2afb8);
        }

        // Initialize streaming (if enabled)
        if (FUN_005e9d10()) {
            void* streamMgr = FUN_00c9ebc0(); // Create stream manager
            FUN_00cd77c0(streamMgr); // Initialize streaming
        }

        // Initialize sub-components
        bool b1 = initComponent1(this);
        bool b2 = initComponent2(this);
        bool b3 = initComponent3(this);

        // Register additional processing
        FUN_00c96910(FUN_00ca3e90(FUN_00cd2b70())); // Register a global effect
        FUN_00c96910(FUN_00ca3e90(FUN_00cd2bb0())); // Register another effect

        // Store streaming source size from config
        this->streamSourceSize = *(uint32_t*)(config + 0x10);

        // Create stream manager with hash constant
        this->streamManager = (StreamManager*)FUN_00ca51e0(0x2ea8fb98, 5, this->streamSourceSize, 10, (uint32_t)this->audioEngine, (uint32_t)this->sharedAudioSource, 0x1000);

        // Finalize initialization
        FUN_00cd7750(*(uint32_t*)this->somePointer); // Dereference and setup
        FUN_00c9eae0(); // Finish engine setup
        FUN_005eef50(this); // Final init step

        this->isInitialized = 1; // Mark initialized

        // Initialize 5 slot structures (for locking or job queues) starting at offset 0x2070
        // Each slot is 4 ints (16 bytes) + a byte? 
        for (int i = 0; i < 5; i++) {
            uint32_t* slot = (uint32_t*)(this->subslotArray + i * 4); // each slot 4 ints? Actually offset pattern: piVar13+2 is byte, piVar13[-1], piVar13[0], piVar13[1]
            // But from assembly: piVar13+2 = byte, piVar13[-1]=int, piVar13[0]=int, piVar13[1]=int
            // So each slot is 3 ints + byte? Might be 0x10 bytes. However loop increments piVar13 by 4 (int steps), so each iteration moves 4 ints. But the accesses suggest a structure with int[3] and a byte at the end.
            slot[2] = 0; // Clear byte
            LOCK();      // Some lock macro
            slot[-1] = 0;
            UNLOCK();
            slot[0] = 0;
            slot[1] = 0;
        }

        // Initialize 14 channel objects (size 0x5C each) starting at offset 0x20d0
        for (int i = 0; i < 14; i++) {
            AudioChannel* channel = (AudioChannel*)((uint32_t)this + 0x20d0 + i * 0x5C);
            FUN_005ea0d0(); // Initialize the channel object
            channel->field_0   = 0; // first int
            channel->field_C   = 0; // offset 0xC? Actually puVar14[-2] and [-1] are zero
            channel->field_10  = 0; // offset 0x10?
            channel->flags |= 1;    // Set bit 0
        }

        // Final sub-init functions
        bool b4 = initComponent4(this);
        bool b5 = initComponent5(this);
        bool b6 = initComponent6(this);
        bool b7 = initComponent7(this);
        bool b8 = initComponent8(this);

        // Return success if all components initialized
        return (b1 & b2 & b3 & b4 & b5 & b6 & b7 & b8) != 0;
    }

private:
    // Internal helper to create a submix bus
    void createSubmix(const char* name, uint32_t fourcc, byte flags) {
        // Stores entry into submix list
        uint32_t index = this->submixCount;
        uint32_t* list = this->submixList;
        // Write fourcc at list + index*0xc - 8
        *(uint32_t*)((uint32_t)list + index * 0xc - 8) = fourcc;
        // Set name pointer? Actually writes name pointer at list + index*0xc - 0xc
        *(uint32_t*)((uint32_t)list + index * 0xc - 0xc) = (uint32_t)name;
        // Set flags at list + index*0xc - 4
        *(byte*)((uint32_t)list + index * 0xc - 4) = flags;
        this->submixCount++;
    }

    // Members (offsets relative to "this")
    void* unknown; // placeholder
    void* parentAudioSource;         // +0x157 * 4? Actually these are int offsets, so need to multiply by 4
    void* workingAudioSource;        // +0x158
    void* extraAudioSource;          // +0x159
    void* sharedAudioSource;         // +0x15a
    void* audioEngine;               // +0x160
    void* mixer;                     // +0x15b
    uint32_t audioOutputLeft;        // +0x10a
    uint32_t audioOutputRight;       // +0x10b
    void* masteringConfig;           // +0x115
    uint32_t* submixList;            // +0x10f
    uint32_t submixCount;            // +0x110
    uint32_t streamSourceSize;       // +0x2421
    StreamManager* streamManager;    // +0x15c
    byte isInitialized;              // +0x162 (byte)
    // Slot array at +0x2070 (5 entries)
    // Channel array at +0x20d0 (14 entries of size 0x5C)
    // ... other members
};

// External functions used (from sound engine / EARS)
extern "C" {
    void FUN_005efad0(int);
    void FUN_005efc20(int);
    void* FUN_009c8e50(int size);
    AudioEngine* FUN_00ca6240(void* source, uint32_t chunkSize);
    void FUN_00c9eac0();
    void FUN_00ca3ee0();
    void* FUN_00caeb90();
    // ... many more
    void* FUN_004dafd0(const char*);
    void FUN_005ef9a0();
    void FUN_005ef890();
    void FUN_005e9ba0(const char*);
    uint32_t FUN_00c9cd50(uint32_t fourcc);
    void FUN_00c9cba0(uint32_t engine, uint32_t fourcc, char** name);
    uint32_t FUN_00ca55a0(uint32_t engine, uint32_t priority, uint32_t count, uint32_t* list, int unknown);
    void FUN_00c9cbe0(uint32_t engine, uint32_t fourcc, uint32_t dataSize, void* data);
    void FUN_00c9cd40(uint32_t dataSize, void* data);
    void FUN_00ca4e90(int, float);
    void* FUN_00c9ebc0();
    void FUN_00cd77c0(void*);
    bool FUN_005ecf00(AudioManager*);
    bool FUN_005ed150(AudioManager*);
    bool FUN_005ed2d0(AudioManager*);
    void* FUN_00cd2b70();
    void* FUN_00cd2bb0();
    void FUN_00c96910(void*);
    void* FUN_00ca3e90(void*);
    StreamManager* FUN_00ca51e0(uint32_t hash, int, uint32_t, int, uint32_t engine, uint32_t source, uint32_t size);
    void FUN_00cd7750(uint32_t);
    void FUN_00c9eae0();
    void FUN_005eef50(AudioManager*);
    bool FUN_005e9d10();
    void FUN_00c9ceb0(void*);
    void* FUN_00ca76d0();
    void* FUN_00ca7ee0();
    // ... etc
    void FUN_005ea0d0();
    bool FUN_005ee6e0(AudioManager*);
    bool FUN_005ec930(AudioManager*);
    bool FUN_005ed560(AudioManager*);
    bool FUN_005eda70(AudioManager*);
    bool FUN_005ee090(AudioManager*);
}

extern uint32_t DAT_00e44594;
extern float DAT_00e2afb8;
extern const char DAT_00e3f95c[]; // Some name with 'Dac0'?
extern const void* PTR_FUN_00e36f1c;
extern const void* PTR_FUN_00e3fb8c;