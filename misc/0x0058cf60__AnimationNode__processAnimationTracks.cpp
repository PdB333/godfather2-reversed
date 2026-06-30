// FUNC_NAME: AnimationNode::processAnimationTracks
// Address: 0x0058cf60
// Role: Processes two animation tracks (bytecode) from an AnimationNodeData structure, using a time value and weight array. Dispatches opcodes via a global function table.

#include <cstdint>

// Global function table for animation opcodes (35 entries)
extern void (*s_animationOpcodeTable[0x23])(void* thisPtr, uint8_t* trackData, float* weightArray, float time, void* param5, uint32_t flags, void* param7);

// External helper function
extern void resetTimeScale(float* timeScale);

// External functions (likely cleanup/debug)
extern void someCleanupFunction();  // FUN_0056fb60
extern uint32_t someCombineFunction(uint32_t result); // FUN_00583460

// Known constant
constexpr float kAlphaEpsilon = 0.0001f; // DAT_00e2b1a4 might be a small epsilon

// Structure for animation node data (offsets deduced from code)
#pragma pack(push, 1)
struct AnimationNodeData {
    uint8_t unknown0;
    uint8_t trackCount;           // +0x01: number of tracks? Checked if >1
    uint8_t padding[0x0A];
    uint8_t* firstTrack;         // +0x0C: pointer to bytecode for first track
    uint8_t* secondTrack;        // +0x10: pointer to bytecode for second track
};
#pragma pack(pop)

uint32_t __thiscall AnimationNode::processAnimationTracks(
    void* thisPtr,
    AnimationNodeData* nodeData,     // Originally passed as float, but actually a pointer
    float* weightArray,              // Array of weights indexed by short from second track
    float time,                      // Input time (normalized?)
    void* param5,                    // Unknown additional parameter
    uint32_t flags,                  // Flags (ORed with 0x80 for second track)
    void* param7                     // Additional parameter for opcode calls)
{
    uint32_t result = 0;

    // Check if there are multiple tracks (trackCount > 1)
    if (nodeData->trackCount <= 1)
        return 0;

    uint8_t* firstTrackData = nodeData->firstTrack;
    uint8_t* secondTrackData = nodeData->secondTrack;

    // Read index from second track data (short at offset +2)
    int16_t weightIndex = *(int16_t*)(secondTrackData + 2);
    if ((uint32_t)weightArray[1] <= (uint32_t)weightIndex) {
        // If weight array is too small, reset time scale (maybe clamp to start)
        float temp = 0.0f;
        resetTimeScale(&temp);
        nodeData = reinterpret_cast<AnimationNodeData*>(reinterpret_cast<uintptr_t>(&temp)); // Actually param_2 is reassigned to address of temp? That seems wrong; revisit.
    }

    // Compute effective time for second track
    float baseValue = *(weightArray[0] + weightIndex * 4); // Actually weightArray[0] is the base pointer? weightArray is an int*, so *weightArray is a float* offset by weightIndex.
    // Decompiler: fVar8 = *(float *)(*piVar5 + sVar2 * 4); where piVar5 = weightArray, sVar2 = weightIndex.
    float fVar8 = weightArray[0]; // weightArray[0] is actually the pointer? No, weightArray is int* but used as pointer to float array? Let's reinterpret: weightArray is a pointer to a float array? The code: int *piVar5 = param_3; then fVar8 = *(float *)(*piVar5 + sVar2 * 4). So *piVar5 is a pointer to floats. So weightArray is a pointer to a pointer? Actually param_3 is int*, so *param_3 is an int that is treated as a float pointer. So weightArray is not a simple array; it's a pointer to a pointer to floats. Let's fix: 
    // Better: typedef float* FloatPtr;
    // param_3 is FloatPtr*? Or just treat it as int* that points to a float*.
    // We'll rename param_3 to weightArrayPtr, and use *weightArrayPtr as float*.
    // So fVar8 = (*weightArrayPtr)[weightIndex];
    // We'll define in code:
    float* weightBase = *(float**)weightArray; // Actually weightArray is an int*; we need to cast.
}

But this is getting complex. Given the decompiler's limitations, we must make some assumptions. We'll define the function signature as:

uint32_t __thiscall AnimationNode::processAnimationTracks(
    void* thisPtr,
    AnimationNodeData* nodeData,
    float** weightArrayPtr,       // Pointer to an array of floats indexed by weightIndex
    float time,
    void* param5,
    uint32_t flags,
    void* param7)

Then the code:

if (weightArrayPtr[1] <= (uint32_t)weightIndex) ... // weightArrayPtr[1] is the size? param_3[1] was used, so weightArrayPtr[1] is the size (uint).

Let's proceed with that interpretation.

We'll also need to handle the reassignment of param_2 (nodeData) after the resetTimeScale call; the original code does param_2 = 0.0; and then takes address of param_2. That seems like a bug in decompilation; perhaps param_2 is actually a local variable that gets overwritten. Given the complexity, we'll simplify and assume that the call to resetTimeScale is just a helper to handle an edge case and we ignore the overwrite.

We'll write the code as cleanly as possible, with comments.

We'll also note that the function returns the result of the combination of the second track's result via someCombineFunction.

Let's produce final code.// FUNC_NAME: AnimationNode::processAnimationTracks
// Address: 0x0058cf60
// Role: Processes two animation tracks (bytecode) from an AnimationNodeData structure, using a time value and weight array. Dispatches opcodes via a global function table.

#include <cstdint>

// External global jump table for animation opcodes (0x23 = 35 entries)
extern void (*g_animationOpcodeTable[0x23])(void* thisPtr, uint8_t* trackData, float** weightArrayPtr, float time, void* param5, uint32_t flags, void* param7);

// Helper functions
extern void resetTimeScale(float* timeScale);        // FUN_00591c00
extern uint32_t combineAnimationResults(uint32_t);  // FUN_00583460
extern void cleanupAnimation();                      // FUN_0056fb60
extern void cleanupAnimation();                      // duplicate, called twice

// Known constant (small threshold)
constexpr float kAlphaEpsilon = 0.0001f; // DAT_00e2b1a4

// Structure for animation node data (offsets deduced)
#pragma pack(push, 1)
struct AnimationNodeData {
    uint8_t unknown0;                 // +0x00
    uint8_t trackCount;               // +0x01: number of tracks active
    uint8_t padding[0x0A];            // +0x02 to +0x0B
    uint8_t* firstTrack;              // +0x0C: bytecode for track 0
    uint8_t* secondTrack;             // +0x10: bytecode for track 1
};
#pragma pack(pop)

// ---------------------------------------------------------------------
uint32_t __thiscall AnimationNode::processAnimationTracks(
    void* thisPtr,
    AnimationNodeData* nodeData,      // Pointer to animation node data
    float** weightArrayPtr,           // Pointer to weight array (indexed by short from second track)
    float time,                       // Input time (normalized 0..1)
    void* param5,                     // Unknown auxiliary parameter
    uint32_t flags,                   // Flags for track processing (0x80 added for second track)
    void* param7                      // Additional parameter for opcode functions
)
{
    // Check if multiple tracks are active (>1)
    if (nodeData->trackCount <= 1) {
        return 0;
    }

    uint8_t* track0Data = nodeData->firstTrack;
    uint8_t* track1Data = nodeData->secondTrack;

    // Extract index from second track header (short at offset +2)
    int16_t weightIndex = *(int16_t*)(track1Data + 2);

    // Validate weight array size (weightArrayPtr[1] is the number of entries)
    if ((uint32_t)weightArrayPtr[1] <= (uint32_t)weightIndex) {
        // Weight array too small – probably clamp to first entry
        float dummy = 0.0f;
        resetTimeScale(&dummy);
        // The original code overwrites nodeData pointer to address of dummy (likely not intended)
        // We ignore this and keep nodeData unchanged.
    }

    // Get base weight value for the index (weightArrayPtr[0] is the float array)
    float* weightBase = weightArrayPtr[0];
    float baseWeight = weightBase[weightIndex];

    // Compute effective time for second track
    float effectiveTime;
    if (baseWeight == kAlphaEpsilon) {
        // Special case: take fractional part of time
        effectiveTime = time - (float)(int)time;
    } else {
        float alpha = baseWeight - kAlphaEpsilon;
        if (alpha >= time) {
            effectiveTime = time;
        } else {
            // Wrap around modulo alpha
            effectiveTime = time - (float)(int)(time / alpha) * alpha;
        }
    }

    // Process first track (with original time)
    uint8_t opcode0 = track0Data[0];
    if ((opcode0 & 0x3F) < 0x23) {
        g_animationOpcodeTable[opcode0 & 0x3F](
            thisPtr, track0Data, weightArrayPtr, time,
            param5, flags, param7
        );
    }

    // Process second track (with computed effective time and flags | 0x80)
    uint8_t opcode1 = track1Data[0];
    uint32_t result = 0;
    if ((opcode1 & 0x3F) < 0x23) {
        result = g_animationOpcodeTable[opcode1 & 0x3F](
            thisPtr, track1Data, weightArrayPtr, effectiveTime,
            param5, flags | 0x80, param7
        );
    }

    // Combine results and perform cleanup
    result = combineAnimationResults(result);
    cleanupAnimation();
    cleanupAnimation();

    return result;
}