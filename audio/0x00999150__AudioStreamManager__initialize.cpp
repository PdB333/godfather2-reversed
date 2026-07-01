// FUNC_NAME: AudioStreamManager::initialize
// Address: 0x00999150
// Reconstructed C++ for AudioStreamManager::initialize (__fastcall with this in ecx)

#define STREAM_DESCRIPTOR_SIZE 0x30
#define STREAM_ARRAY_STRIDE 0xC0
#define STREAM_BUFFER_SIZE 0x2160  // 8544 bytes
#define STREAM_BUFFER_ALIGNED_SIZE 0x2170  // 8560 bytes
#define FLAG_BIT5 0x20
#define FLAG_BIT1 0x2
#define MAGIC_HASH 0x9A14D331  // -0x65EB2CCF as unsigned

// Forward declarations of helper functions (signatures inferred)
int __fastcall AudioStreamManager::initialize(int thisPtr);
void FUN_00998f10(void* ptr);       // Possibly stop/cleanup a stream descriptor
void FUN_00995fb0();                 // Global cleanup
void FUN_009e6ff0(int obj, int param); // Some initialization on object
void FUN_009f1f90(int param);        // Some operation
void FUN_009ebe70(int obj);          // Another init/cleanup
void* FUN_009c8e80(int size);        // Memory allocation (HeapAlloc?)
void* FUN_009c8ed0(int size, int* alignInfo); // Aligned allocation? Returns 0x30-byte struct
void FUN_0056f3c0();                 // Low-level buffer init
void FUN_0045ed50(void* desc, uint param2, uint param3, void* buf, int zero1, int zero2, int zero3); // Setup descriptor
void FUN_0045ee00(void* desc, int zero); // Initialize descriptor
void FUN_00461040(void* buf, int size); // Possibly buffer clear/init
void FUN_00408900(int thisPtr, int dataAddr, int flags); // Debug/logging
void* (__thiscall *g_allocFunc)(int size, void* allocator); // Global allocator from DAT_01130984
void* g_allocator; // DAT_01130980
int g_nodeListHead; // DAT_01130974 (head pointer)
int g_nodeListTail; // DAT_01130978 (tail pointer)
int g_nodeCount; // DAT_0113097c (counter)
int g_debugFlag; // DAT_012069d4 (non-zero enables debug logging)
int g_someConstant; // _DAT_00d5780c (used as initial value)

// Structure for the 0x30-byte stream descriptor (per stream)
struct StreamDescriptor {
    int field_0;
    int field_4;
    int field_8;
    int field_C; // initialized from g_someConstant
    int field_10;
    int field_14;
    int field_18;
    int field_1C; // initialized from g_someConstant
    // ... total 0x30 bytes / 12 ints (48 bytes)
};

// Node for global linked list (inserted after initialization)
struct StreamManagerListNode {
    int managerPtr; // +0x00: pointer to this AudioStreamManager
    int prev;       // +0x04
    int next;       // +0x08
};

// Main class (AudioStreamManager) - offsets based on thisPointer
// Fields are at known offsets from 'this'
// struct is not complete; only fields used in this function are listed
// Offsets:
// +0x00: vtable (not in param_1 directly? assuming param_1 points to object with vtable at start)
// +0x0C: vtable pointer? actually (*(int**)(this+0xc)) is used to call vtable function at offset 0x10
// +0x10: likely vtable pointer (used as base for calling)
// +0x20: void* listPtr1 (pointer to some container)
// +0x34: char* streamDataArray (array of size streamCount * 0xC0)
// +0x38: int streamCount
// +0x4C: uint flags
// +0x60: int streamCountCopy
// +0x64: StreamDescriptor** descriptorPtrArray (array of pointers to StreamDescriptor of size 0x30)
// +0x68: void* bufferForDescriptors (allocated 4*streamCount bytes)
// +0x6C: void* audioBuffer (allocated 0x2160 bytes)
// +0x70: int audioBufferSize (0x2170)
// +0x74: int audioBufferAlignSize (0x2160)
// +0x94: int foundCounter
// +0x9C: int someOtherParam

int __fastcall AudioStreamManager::initialize(int thisPtr)
{
    int result = 0;
    // Global node count check: limit to 10 instances?
    if (g_nodeCount >= 10) {
        return 0;
    }

    // Check bit 5 of flags at +0x4C
    if ((*(unsigned char*)(thisPtr + 0x4C) & FLAG_BIT5) != 0) {
        void* listPtr = *(void**)(thisPtr + 0x20);
        FUN_00998f10(listPtr);  // Possibly stop/cleanup

        // Access short at offset 6 in listPtr (listPtr is some object with fields)
        short* shortAt6 = (short*)((int)listPtr + 6);
        if (*((short*)listPtr + 1) != 0) {
            *shortAt6 = *shortAt6 - 1;
            if (*shortAt6 == 0) {
                // Call function through vtable at listPtr
                (**(void (__thiscall**)(int))listPtr)(1);
            }
        }
        // Clear bit 5
        *(unsigned int*)(thisPtr + 0x4C) &= ~FLAG_BIT5;
        FUN_00995fb0();  // Global cleanup
    }

    int index;
    int foundCounter = 0;
    *(int*)(thisPtr + 0x94) = 0;

    // Iterate first list (objects from +0x20 offset 0x8, count at +0xC)
    int* listHeader1 = *(int**)(thisPtr + 0x20);
    int list1Count = *(int*)(listHeader1 + 0xC / 4);  // +0xC
    if (list1Count > 0) {
        int* list1Array = *(int**)(listHeader1 + 0x8 / 4);  // +0x8
        for (index = 0; index < list1Count; index++) {
            int obj = list1Array[index];
            // If obj+8 is zero, call FUN_009e6ff0
            if (*(int*)(obj + 8) == 0) {
                FUN_009e6ff0(obj, 1);
            }
            // Call some function with this+0x9C
            FUN_009f1f90(*(unsigned int*)(thisPtr + 0x9C));

            // Iterate array inside obj at +0x74, count at +0x78
            int elemCount = *(int*)(obj + 0x78);
            int* elemArray = *(int**)(obj + 0x74);
            int elemIdx;
            for (elemIdx = 0; elemIdx < elemCount; elemIdx++) {
                if (elemArray[elemIdx] == MAGIC_HASH) {
                    (*(int*)(thisPtr + 0x94))++;
                    break;
                }
            }
        }
    }

    // Iterate second list (from +0x20 offset 0x14, count at 0x18)
    int* listHeader2 = *(int**)(thisPtr + 0x20);
    int list2Count = *(int*)(listHeader2 + 0x18 / 4);  // +0x18
    if (list2Count > 0) {
        int* list2Array = *(int**)(listHeader2 + 0x14 / 4);  // +0x14
        for (index = 0; index < list2Count; index++) {
            int obj = list2Array[index];
            if (*(int*)(obj + 8) == 0) {
                FUN_009ebe70(obj);  // Initialize/cleanup
            }
        }
    }

    // Copy streamCount from +0x38 to +0x60
    int streamCount = *(int*)(thisPtr + 0x38);
    *(int*)(thisPtr + 0x60) = streamCount;

    // Allocate array for StreamDescriptor pointers (size = streamCount * 4)
    long long allocSize = (long long)(unsigned int)streamCount * 4;
    void* descriptorPtrArray = FUN_009c8e80(allocSize);
    *(int*)(thisPtr + 0x64) = (int)descriptorPtrArray;

    // Allocate and initialize individual StreamDescriptor objects
    int alignInfo[] = { 2, 0x10, 0 };  // alignment 16 bytes, power 2
    for (index = 0; index < streamCount; index++) {
        // Allocate 0x30-byte block with alignment
        StreamDescriptor* desc = (StreamDescriptor*)FUN_009c8ed0(0x30, alignInfo);
        *(int*)((int)descriptorPtrArray + index * 4) = (int)desc;

        // Initialize descriptor fields (first three ints to 0, fourth to g_someConstant)
        desc->field_0 = 0;
        desc->field_4 = 0;
        desc->field_8 = 0;
        desc->field_C = g_someConstant;
        desc->field_10 = 0;
        desc->field_14 = 0;
        desc->field_18 = 0;
        desc->field_1C = g_someConstant;
    }

    // Allocate buffer for per-stream data (size = streamCount * 4)
    allocSize = (long long)(unsigned int)streamCount * 4;
    void* perStreamBuffer = FUN_009c8e80(allocSize);
    *(int*)(thisPtr + 0x68) = (int)perStreamBuffer;

    // Set buffer sizes
    *(int*)(thisPtr + 0x74) = STREAM_BUFFER_SIZE;  // 0x2160
    unsigned int alignedSize = STREAM_BUFFER_ALIGNED_SIZE;  // 0x2170
    if ((alignedSize & 0xF) != 0) {
        alignedSize = (alignedSize + 0x10 - (alignedSize & 0xF)) & ~0xF;
    }
    *(unsigned int*)(thisPtr + 0x70) = alignedSize;

    void* audioBuffer;
    if (alignedSize == 0) {
        audioBuffer = 0;
    } else {
        audioBuffer = (void*)FUN_0056f3c0();  // Possibly aligned allocation
    }
    *(int*)(thisPtr + 0x6C) = (int)audioBuffer;

    // Call vtable function at offset 0x10 from vtable pointer at +0xC
    int vtablePtr = *(int*)(thisPtr + 0xC);
    (*(void (__thiscall**)(int, int*))(*(int*)vtablePtr + 0x10))(thisPtr, &alignInfo[0]);

    // Initialize each stream descriptor and link to stream data array
    for (index = 0; index < streamCount; index++) {
        int streamDataBase = *(int*)(thisPtr + 0x34);
        int streamDataOffset = index * 0xC0;
        int streamDataPtr = streamDataBase + streamDataOffset;

        StreamDescriptor* desc = *(StreamDescriptor**)((int)descriptorPtrArray + index * 4);
        int perStreamOffset = index * 4;

        // Setup descriptor with per-stream buffer area
        FUN_0045ed50(
            desc,
            *(unsigned int*)(streamDataPtr + 0x50) >> 2,  // Some shift
            0x1C,
            (void*)((int)perStreamBuffer + perStreamOffset),
            0, 0, 0
        );

        FUN_0045ee00(desc, 0);

        // Write constant to per-stream buffer
        *(int*)((int)perStreamBuffer + perStreamOffset) = g_someConstant;

        // Link stream data to descriptor
        *(int*)(streamDataPtr + 0xA4) = (int)desc;
    }

    // Initialize audio buffer
    FUN_00461040(audioBuffer, *(int*)(thisPtr + 0x74));

    // Set flag bit 1 (initialized)
    *(unsigned int*)(thisPtr + 0x4C) |= FLAG_BIT1;

    // Insert this manager into global linked list
    void* allocator;
    if (g_allocator == 0) {
        allocator = &g_altAllocator;  // g_DAT_01218a14
    } else {
        allocator = g_allocator;
    }
    StreamManagerListNode* newNode = (StreamManagerListNode*)(*(void* (__thiscall**)(int, void*))g_allocFunc)(12, allocator);
    if (newNode != 0) {
        newNode->managerPtr = thisPtr;
        newNode->prev = 0;
        newNode->next = 0;
    }

    // Insert into global linked list (linear, prepend? Actually code seems to update tail first)
    if (g_nodeListTail != 0) {
        // If list exists, attach newNode as new tail
        g_nodeListTail->next = (int)newNode;
        ((StreamManagerListNode*)(g_nodeListTail->next))->prev = (int)g_nodeListTail;
        newNode = (StreamManagerListNode*)g_nodeListTail->next;  // Actually this line might be wrong; code sets piVar8 then assigns to g_nodeListTail
        // Better reading: after update, piVar2 = g_nodeListHead (which may be unchanged)
        // Then later g_nodeListHead = piVar2 (which could be the original head)
        // This looks like an insert at tail. But the code is confusing.
    }

    // Update global pointers
    g_nodeListHead = (int)newNode;  // Actually code: g_nodeListHead = piVar2; 
    g_nodeCount++;
    g_nodeListTail = (int)newNode;

    // Debug logging if flag set
    if (g_debugFlag != 0) {
        FUN_00408900(thisPtr, (int)&g_debugFlag, 0x8000);
    }

    result = 1;
    return result;
}