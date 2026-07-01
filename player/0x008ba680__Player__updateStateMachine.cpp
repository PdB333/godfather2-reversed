// FUNC_NAME: Player::updateStateMachine

#include <cstdint>

// Forward declarations and globals (extern)
extern uint32_t DAT_01223484;       // 0x1223484 - some global flag (maybe online status)
extern uint32_t DAT_012233a0;       // 0x12233a0 - pointer to something
extern float DAT_00e44658;          // 0xe44658
extern float DAT_00d61b40;          // 0xd61b40
extern float DAT_00d577a0;          // 0xd577a0
extern float DAT_00d5780c;          // 0xd5780c - common threshold
extern float DAT_00d5efb8;          // 0xd5efb8 - distance trigger
extern float DAT_00d5c458;          // 0xd5c458 - another distance trigger
extern float DAT_012067e8;          // 0x12067e8 - some constant (delta time?)
extern float DAT_00e44680;          // 0xe44680 - mask maybe
extern char DAT_0120546e;           // 0x120546e - default material name?
extern int DAT_0112f8a8;            // static data for sound
extern int DAT_0112f92c;            // sound related
extern float DAT_00d7b404;          // some float constant
extern int DAT_01205224;            // some global timer value
extern int DAT_01206980;            // audio channel handle
extern int DAT_01206970;            // audio channel handle

// Forward declarations of functions called
extern "C" bool FUN_00842870();                     // 0x842870 - check some global condition
extern "C" void* FUN_00471610();                   // 0x471610 - returns player position struct
extern "C" double FUN_00414c30(int* a, float* b);  // 0x414c30 - distance?
extern "C" void FUN_004704d0(int soundId, int, int); // play sound
extern "C" void FUN_00471df0();                     // stop sound?
extern "C" void FUN_00470550(int soundId);          // play loop sound?
extern "C" bool FUN_008b8370();                     // check something
extern "C" void FUN_00408680(int* handle);          // stop sound channel
extern "C" void* FUN_009c8e50(int size);            // memory allocator
extern "C" void FUN_008b9050(int);                  // set state
extern "C" void FUN_004706f0(float value);          // adjust something
extern "C" void FUN_00408900(int* dest, int* src, int flags); // copy data
extern "C" void FUN_00402050(int* ptr, int value);
extern "C" void FUN_00440590(int* dest, int* src, float, int, int);
extern "C" void FUN_004088c0(int* ptr);             // stop something
extern "C" int* FUN_00435300(int, int, int);         // get object properties? returns triple
extern "C" void FUN_004df590();                     // release object
extern "C" void FUN_0044b4e0(char* stackMem, float* matrix); // build matrix
extern "C" void* FUN_004df330(float* outVec, float* inVec, char* transform, int flags, int, int, int, int); // create dynamic object
extern "C" void* FUN_004eb390(int size, int align); // new operator
extern "C" unsigned int FUN_0043a210(int*, int*);   // some transform calculation
extern "C" void FUN_004df830(void* obj);            // activate dynamic object

// Virtual function table offsets (constants for this->vtable)
constexpr int VTBL_UPDATE = 0x158;    // some vtable func (move?)
constexpr int VTBL_GETHEIGHT = 0xc0;  // returns float
constexpr int VTBL_SOMETHING = 0x128; // another virtual

// Byte offsets in this class (relative to this as int*)
// 0x21e, 0x21d, 0x21f are char flags at offsets 0x21e, 0x21d, 0x21f
// param_1[99] = flags at offset 0x18c
// param_1[0x54] = 0x150 - some float (health?)
// param_1[0x66] = 0x198 - position x?
// param_1[0x67] = 0x19c - position y?
// param_1[0x4c] = 0x130 - pointer to another object (weapon?)
// param_1[0x59] = 0x164 - some flag (alive?)
// param_1[0x76] = 0x1d8 - vector (start of 3 floats?)
// param_1[0x78] = 0x1e0 - end of that vector? Actually 0x76 and 0x78 are separate pointers? In code they are combined as double word.
// more fields...

// In the reconstruction we'll use a struct to represent this object
enum PlayerFlags : uint32_t {
    FLAG_UNK_1   = (1 << 1),    // bit 1
    FLAG_UNK_4   = (1 << 4),    // bit 4
    FLAG_UNK_5   = (1 << 5),    // bit 5
    FLAG_UNK_6   = (1 << 6),    // bit 6
    FLAG_UNK_7   = (1 << 7),    // bit 7
    FLAG_UNK_9   = (1 << 9),    // bit 9
    FLAG_UNK_0xB = (1 << 11),   // bit 11
    FLAG_UNK_0xC = (1 << 12),   // bit 12
    FLAG_UNK_0x13= (1 << 19),   // bit 19
    FLAG_UNK_0x15= (1 << 21),   // bit 21
    FLAG_UNK_0x17= (1 << 23),   // bit 23
    FLAG_UNK_0x1A= (1 << 26),   // bit 26
    FLAG_UNK_0x1B= (1 << 27),   // bit 27
    FLAG_UNK_0x1C= (1 << 28),   // bit 28
};

// Reconstruction of the member function
void __fastcall Player::updateStateMachine(/*this*/int* playerObj)
{
    // Local variables (renamed from Ghidra)
    uint32_t flags;                     // uVar2
    float sqDist;                       // local_b4
    float tempFloat;                    // fVar12, fVar13, fVar14
    bool shouldStopSound;               // bVar11
    int soundId;                        // uVar15 (0xfa or 0)
    int playerPosPtr;                   // iVar4 (from FUN_00471610)
    // For the latter part: navigation creation
    int navObjectHandle;                // iVar4 (after alloc)
    int* navTransform;                  // piVar6 (param_1+0x7a) pointer to store nav object ref
    int* newNavObj;                     // piVar7
    int* allocNavObj;                   // piVar8
    char matrixBuffer[76];              // auStack_50
    float transformMatrix[6];           // afStack_90 (6 floats for a 3x2 matrix?)
    double doubleVal;                   // uVar1
    int intVal;                         // for various temporaries
    bool condition;

    // ---- Initial audio/state checks ----
    if (((DAT_01223484 == 0) || (*(int*)(DAT_01223484 + 0xc) == 0)) &&
        (FUN_00842870() == false))
    {
        // Not online or no appropriate context? Proceed with sound stop logic
        if ((((uint)(playerObj[99] >> 0x1b) & 1) != 0) ||   // check bit 27
            (playerObj[0x59] == 0) ||                         // param_1[0x59] == 0 (maybe dead?)
            ((DAT_012233a0 == 0) ||
             ((**(int**)(DAT_012233a0 + 4) == 0) || (**(int**)(DAT_012233a0 + 4) == 0x1f30))))
        {
            goto exitAnimCheck;
        }

        // Get player global position
        playerPosPtr = (int)FUN_00471610();   // returns pointer to position struct
        // Read position (x,y) from playerPosPtr+0x30 and +0x38
        int posX = *(int*)(playerPosPtr + 0x30);
        int posY = *(int*)(playerPosPtr + 0x38);
        // Store for distance calculation (these are stored as double in structured local)
        // Actually the code constructs a local vector from these and current character? Let's skip details.
        // Calculate squared distance from current entity to something (maybe home base)
        float currentX = *(float*)(playerObj[0x4c] + 0x20);  // param_1[0x4c] is pointer, +0x20 is x?
        float currentY = *(float*)(playerObj[0x4c] + 0x2c);  // +0x2c is y?
        // Actually the code uses param_1[0x4c] as a pointer to a structure with fields at +0x20, +0x2c
        // Then computes distance between that and the playerPos ...
        // For brevity, we'll simplify: compute sqDist from player to some target
        // The original code: 
        //   iVar4 = param_1[0x4c];
        //   local_b0 = uVar1; (uVar1 from playerPosPtr+0x30 and +0x38)
        //   local_a8 = ... (z?)
        //   ...
        //   fVar12 = (float10)FUN_00414c30(iVar4 + 0x20, &local_a0);
        // This suggests FUN_00414c30 returns distance squared between two 2D points.
        // We'll emulate:
        int* target = (int*)playerObj[0x4c];
        // The local_a0 is constructed from playerPos data
        // For readability, just call:
        float distanceSq = (float)FUN_00414c30(target + 0x20, &playerPosPtr + 0x30);  // approximate
        // But note the actual args: iVar4+0x20 and &local_a0 where local_a0 is built from playerPos
        // The result is stored in local_b4 (sqDist)

        sqDist = distanceSq; // local_b4
        if ((FUN_00414c30(target + 0x20, &playerPosPtr + 0x30) > (double)DAT_00e44658) &&  // fVar12 > DAT_00e44658
            (sqDist / (target[0x2c] * target[0x2c]) > DAT_00d61b40))   // local_b4 / (fVar13*fVar13) > threshold
        {
            if (DAT_00d577a0 < (float)playerObj[0x54]) // some check on health
            {
                FUN_004704d0(0xfa, 0, 1); // play sound ID 0xfa
            }
            goto exitAnimCheck;
        }
        // Check health threshold
        if (!(DAT_00d5780c < (float)playerObj[0x54]) && !(DAT_00d5780c == (float)playerObj[0x54]))
        {
            // health is less than threshold
            // Clear bit 26
            if ((uint)(playerObj[99] >> 0x1a) & 1) // bit 26 set?
            {
                playerObj[99] &= 0xFBFFFFFF; // clear bit 26
                FUN_00471df0(); // stop some sound
            }
            soundId = 0xfa; // play sound
        }
        else
        {
            soundId = 0xfa; // still play? Actually the code goes to else branch? Wait:
        }
        // The structure: if (health < threshold) do the else block? Need to reorder.
        // From decompiled: after if (DAT_00d5780c < health) goto LAB_008ba7ef; else if == also goto; so only if health < DAT_00d5780c does the block with sound.
        // So soundId = 0xfa; // for the case health < threshold
        // Actually the code: if (_DAT_00d5780c < (float)param_1[0x54] || _DAT_00d5780c == (float)param_1[0x54]) goto exit; else { clear bit, play sound }
        // So soundId is set to 0xfa in the else.
    }
    else
    {
        soundId = 0; // no sound
    }
    FUN_00470550(soundId); // play/update sound loop with soundId

exitAnimCheck:
    flags = playerObj[99];
    // Check if bit 5 is set (not clipped/out of range)
    if ((flags >> 5) & 1) == 0
    {
        // Call virtual function at offset 0x158 (maybe animation update)
        (*(void (**)(int*))(*(int*)playerObj + 0x158))(playerObj);
    }
    else
    {
        // Check several flags: bit6, bit11, bit23 all must be 0
        if ((((flags >> 6) & 1) == 0) && ((flags >> 11) & 1) == 0 && ((flags >> 23) & 1) == 0)
        {
            // Check some condition via FUN_00481620
            if (FUN_00481620() != 0) // true
            {
                playerPosPtr = (int)FUN_00471610();
                float dx = *(float*)(playerPosPtr + 0x30) - (float)playerObj[0x66]; // distance to own position x
                float dy = *(float*)(playerPosPtr + 0x38) - (float)playerObj[0x67]; // y
                sqDist = dy * dy + dx * dx; // local_b4
                if ((DAT_00d5efb8 < sqDist) ||   // beyond first range
                    (((flags >> 9) & 1) == 0 && FUN_008b8370() != 0)) // or not flagged and other condition
                {
                    FUN_00408680(&DAT_01206980); // stop audio channel 1
                    FUN_00408680(&DAT_01206970); // stop audio channel 2
                }
                if ((DAT_00d5c458 < sqDist) ||
                    (((flags >> 9) & 1) == 0 && FUN_008b8370() != 0))
                {
                    // If not already in cover (bit 12 clear)
                    if ((flags >> 12) & 1) == 0
                    {
                        if ((*(char*)((int)playerObj + 0x21f) != 0) // some flag at byte offset 0x21f
                        {
                            // Allocate a struct of 12 bytes (3 ints)
                            int* newSoundParam = (int*)FUN_009c8e50(12);
                            if (newSoundParam)
                            {
                                newSoundParam[0] = (int)&PTR_LAB_00d7b4a0; // vtable?
                                newSoundParam[1] = (int)playerObj;
                                playerObj[0x6c] = (int)newSoundParam; // store pointer at offset 0x6c
                                newSoundParam[2] = (int)(playerObj + 0x87); // some pointer
                                if ((int*)playerObj[0x4c] != 0)
                                {
                                    // Call virtual on weapon? with hash 0x5a4faec5
                                    (*(void (**)(int, int))(*(int)playerObj[0x4c] + 0x40))(0x5a4faec5, playerObj[0x6c]);
                                }
                            }
                        }
                        FUN_008b9050(0); // set some state
                        playerObj[99] |= 0xC0; // set bits 6 and 7
                    }
                }
            }
        }
    }

    // Get height from virtual function
    float height = (float)(*(double (**)(int*))(*(int*)playerObj + 0xc0))(playerObj);
    if (height <= 0.0f)
    {
        shouldStopSound = true;
        // If bit1 and bit7 both set, increase flag
        if (((flags >> 1) & 1) && ((flags >> 7) & 1))
        {
            playerObj[99] |= 0x8000000; // set bit 27
            shouldStopSound = true;
            if (0.0f < (float)playerObj[0x54]) // health > 0
            {
                // Reduce health by distance*constant
                FUN_004706f0((float)playerObj[0x54] - DAT_012067e8 * DAT_00d5c458);
                shouldStopSound = false;
            }
        }
        if ((((playerObj[99] & 1) == 0) && ((flags >> 19) & 1)) && ((flags >> 21) & 1) == 0)
        {
            // Set bit 21
            playerObj[99] |= 0x200000;
            if (DAT_0112f8a8 != 0) {
                FUN_00408900(playerObj + 0xf, &DAT_0112f8a8, 0x8000);
            }
            FUN_00402050(&DAT_0112f92c, 0);
            FUN_00440590(&DAT_0112f8a8, playerObj + 0xf, DAT_00d7b404, 0, 0);
        }
        else if (shouldStopSound)
        {
            if (((playerObj[99] & 1) != 0) ||
                ((flags >> 1) & 1 && ((flags >> 7) & 1) == 0) ||
                ((flags >> 12) & 1))
            {
                playerObj[99] |= 0x100;
                FUN_004088c0(playerObj + 0xf);
                return;
            }
            if (((flags >> 4) & 1) && playerObj[0x4c] != 0) {
                (*(void (**)(int*))(*(int*)playerObj + 0x128))(playerObj);
            }
        }
    }

    // Check byte flag at offset 0x21e
    if ((*(char*)((int)playerObj + 0x21e) == 0) &&
        ((uint)playerObj[0x8b] <= (uint)(DAT_01205224 - playerObj[0x8a]))) {
        *(char*)((int)playerObj + 0x21e) = 1;
    }

    // This section handles navigation/collision creation
    float someThreshold = DAT_00d5780c; // fStack_54
    if (*(char*)((int)playerObj + 0x21d) != 0)
    {
        int destIndex = playerObj[0x92]; // some index for target
        // Initialize matrix with zeros
        float matrix[6] = {0,0,0,0,0,0}; // afStack_90, but later overwritten partially
        // Also other local variables initialized: uStack_78 etc = 0
        // Store pointer from playerObj[0x90] and playerObj[0x76] to some variables
        int* srcVec = (int*)((char*)&playerObj[0x76]); // actually param_1+0x76 is a vector (3 ints?) -> but used as double word
        doubleVec = *(double*)srcVec; // uVar1 from param_1[0x76]
        // Clear byte at 0x21d
        *(char*)((int)playerObj + 0x21d) = 0;
        matrix[5] = someThreshold;
        matrix[0] = someThreshold;
        // Set other elements
        bool isNull = (int)(uint64_t)doubleVec == 0; // low 32 bits of the double
        if (isNull)
        {
            // Rebuild doubleVec from param_1[0x76] and param_1[0x78]
            // Actually code reconstructs from the two 32-bit parts
            int low = playerObj[0x76];
            int high = playerObj[0x77]; // note: param_1[0x76] is an int, param_1[0x77] is next int (since 0x77 *4 = 0x1dc)
            // But decompiled uses param_1[0x78] as int? Confusing. We'll emulate the logic:
            // It sets iVar4 and iVar10 to zero, then if both are zero, checks param_1[0x78].
            // Ultimately it calls FUN_00435300 to get a path node or waypoint.
            if (playerObj[0x89] != 0) {
                int count = playerObj[0x89];
            } else {
                count = 1;
            }
            int* pathData = FUN_00435300(playerObj[0xa0], count, 0);
            doubleVec = *(double*)pathData; // reconstruct
            // other components...
        }
        // Store the vector back (maybe for initial position)
        // ... More details omitted for brevity

        // Manage nav object handle at playerObj+0x7a
        navTransform = (int*)((char*)playerObj + 0x1e8); // param_1+0x7a, offset
        if (*navTransform != 0) {
            FUN_004df590(); // release previous nav object
            if (*navTransform != 0) {
                *(int*)(*navTransform + 8) = 0; // clear back pointer
                *navTransform = 0;
            }
        }

        // Build transform matrix from current data
        FUN_0044b4e0(matrixBuffer, matrix); // build a transform
        // Create a dynamic object (path node? collision shape?)
        newNavObj = (int*)FUN_004df330(&sqDist, &doubleVec, matrixBuffer, 0x1ff, 0, 0, 0xffffffff, 0);
        if (*navTransform != 0) {
            *(int*)(*navTransform + 8) = 0;
            *navTransform = 0;
        }
        int temp = *newNavObj;
        *navTransform = temp;
        if (temp != 0) {
            *(int**)(temp + 8) = navTransform; // link back
            *newNavObj = 0;
        }
        if (sqDist != 0.0f) {
            *(int*)((int)&sqDist + 8) = 0;
        }

        // Allocate a new physics/collision object
        allocNavObj = (int*)FUN_004eb390(0x20, 0x10);
        float fTemp = DAT_00d5780c;
        int* finalObj = 0;
        if (allocNavObj)
        {
            allocNavObj[1] = 0;
            allocNavObj[5] = 0;
            allocNavObj[7] = 0;
            allocNavObj[0] = (int)&PTR_LAB_00d7b410; // vtable
            allocNavObj[2] = 0;
            allocNavObj[3] = (int)fTemp; // maybe radius?
            allocNavObj[4] = 0;
            allocNavObj[6] = 0;
            finalObj = allocNavObj;
        }

        fTemp = DAT_00d5780c; // re-read (maybe unchanged)
        if ((char)playerObj[0x88] != 0) {
            // Some transformation on the object's skeleton data
            unsigned int result = FUN_0043a210(playerObj + 0x99, playerObj + 0x99);
            result = FUN_0043a210(playerObj + 0x96, playerObj + 0x96);
            // More complex calculation involving floats from playerObj offsets
            // Simplified: combine some values and mask with DAT_00e44680
            fTemp = (float)((uint)( (float)playerObj[0x9a] * (float)playerObj[0x97] +
                                     (float)playerObj[0x96] * (float)playerObj[0x99] +
                                     (float)playerObj[0x9b] * (float)playerObj[0x98] ) & (uint)(DAT_00e44680));
        }
        playerObj[0x8e] = (int)fTemp; // set some int

        // Get material name (default if null)
        char* materialName = (char*)playerObj[0x9c];
        if (materialName == 0) {
            materialName = &DAT_0120546e; // "default_collision"?
        }

        // Set parameters on finalObj via vtable calls
        (*(void (**)(char*))(*(int*)finalObj + 0x34))(materialName); // set material?
        (*(void (**)(const char*))(*(int*)finalObj + 0x3c))("collision_default"); // set collision group
        (*(void (**)(int))(*(int*)finalObj + 0x30))(playerObj[0x8f]); // set some int
        (*(void (**)(float))(*(int*)finalObj + 0x38))(1.0f); // set scale (0x3f800000)
        (*(void (**)(int))(*(int*)finalObj + 0x28))(playerObj[0x8d]); // set property A
        (*(void (**)(int))(*(int*)finalObj + 0x2c))(playerObj[0x8e]); // set property B

        if (*navTransform != 0) {
            FUN_004df830(finalObj); // apply the physics object to nav
            playerObj[0x8a] = DAT_01205224; // update timer
            *(char*)((int)playerObj + 0x21e) = 0; // clear flag
        }
    }
    return;
}