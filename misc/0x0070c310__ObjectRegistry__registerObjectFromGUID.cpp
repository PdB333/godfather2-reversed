// FUNC_NAME: ObjectRegistry::registerObjectFromGUID
// Function at 0x0070c310: Registers an object by its GUID, creates a node in internal linked lists.
// Called from 0x0070ce60 and 0x0070d410 (likely virtual dispatchers).
// Uses magic GUIDs (0xBADDBDBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911) as null/ignored markers.

#define GUID_WORD0 0xBADDBDBA
#define GUID_WORD1 0xBEEFBEEF
#define GUID_WORD2 0xEAC15A55
#define GUID_WORD3 0x91100911

class ObjectRegistry {
public:
    // param_1: pointer to 4-int GUID
    // param_2: if non-zero, release the created object
    // param_3: pointer to a resource manager (vtable at +0x58 returns a uint)
    static void registerObjectFromGUID(int* guidPtr, int doCleanup, int* resourceManager) {
        // Check if GUID matches the ignore markers or is all-zero
        if (!((guidPtr[0] == GUID_WORD0 && guidPtr[1] == GUID_WORD1 && guidPtr[2] == GUID_WORD2 && guidPtr[3] == GUID_WORD3) ||
              (guidPtr[0] == 0 && guidPtr[1] == 0 && guidPtr[2] == 0 && guidPtr[3] == 0))) {
            
            uint* staticBuffer = (uint*)getStaticStringBuffer(); // FUN_00471610() returns a 64-byte buffer
            uint hashBuffer[16]; // local_90
            for (int i = 0; i < 16; i++) {
                hashBuffer[i] = staticBuffer[i];
            }
            char stringBuffer[76]; // local_50
            hashStringToBuffer(stringBuffer, hashBuffer); // FUN_0044b4e0 - likely hash or transform
            
            uint extraParam;
            if (resourceManager == nullptr) {
                extraParam = 0x1ff;
            } else {
                // vtable at +0x58 returns a uint (e.g., a version or flags)
                extraParam = (*(uint (__thiscall**)(int*))(*(int*)resourceManager + 0x58))();
            }
            
            // Copy GUID into local vars for the creation call
            int guidCopy[4];
            guidCopy[0] = guidPtr[0];
            guidCopy[1] = guidPtr[1];
            guidCopy[2] = guidPtr[2];
            guidCopy[3] = guidPtr[3];
            
            int createdObject; // iStack_a8
            int containerHandle; // local_a4 (set by createObjectByGUID)
            createObjectByGUID(&createdObject, &guidCopy, stringBuffer, extraParam, 0, resourceManager, 0xffffffff, 0);
            // FUN_004df330( &createdObject, &guidCopy, stringBuffer, extraParam, 0, resourceManager, 0xffffffff, 0 )
            
            if (doCleanup != 0) {
                releaseObject(&createdObject); // FUN_00414db0
            }
            
            // Allocate a new node (size 0x24, alignment 0x10)
            uint* newNode = (uint*)allocateMemory(0x24, 0x10); // FUN_004eb390
            if (newNode != nullptr) {
                uint datVal = DAT_00d5ccf8; // global value
                newNode[0] = (uint)&PTR_FUN_00d61508; // vtable pointer
                newNode[1] = 0;          // +0x04
                newNode[2] = 0;          // +0x08 (linked list prev)
                newNode[3] = 0;          // +0x0C (linked list next)
                newNode[4] = 0;          // +0x10 (second list prev)
                newNode[5] = 0;          // +0x14 (second list next)
                newNode[6] = datVal;     // +0x18
                
                // Insert into first linked list (using containerHandle + 0x48)
                uint* list1PrevPtr = &newNode[2]; // offset +0x08
                int target1;
                if (containerHandle == 0) {
                    target1 = 0;
                } else {
                    target1 = containerHandle + 0x48;
                }
                if (*list1PrevPtr != target1) {
                    if (*list1PrevPtr != 0) {
                        unlinkNode(list1PrevPtr); // FUN_004daf90
                    }
                    *list1PrevPtr = target1;
                    if (target1 != 0) {
                        newNode[3] = *(uint*)(target1 + 4); // set forward pointer
                        *(int**)(target1 + 4) = list1PrevPtr; // update previous node's next
                    }
                }
                
                // Insert into second linked list (using containerHandle + 0x2d4)
                uint* list2PrevPtr = &newNode[4]; // offset +0x10
                int target2;
                int* containerOffset = (int*)(containerHandle + 0x2d4);
                if (*containerOffset == 0) {
                    target2 = 0;
                } else {
                    target2 = *containerOffset - 0x48;
                }
                if (target2 == 0) {
                    target2 = 0;
                } else {
                    target2 = target2 + 0x48;
                }
                if (*list2PrevPtr != target2) {
                    if (*list2PrevPtr != 0) {
                        unlinkNode(list2PrevPtr);
                    }
                    *list2PrevPtr = target2;
                    if (target2 != 0) {
                        newNode[5] = *(uint*)(target2 + 4);
                        *(int**)(target2 + 4) = list2PrevPtr;
                    }
                }
                
                registerNode(newNode); // FUN_004df830
            }
            
            if (createdObject != 0) {
                *(uint*)(createdObject + 8) = 0; // clear reference?
            }
        }
    }

private:
    // Forward declarations of the called functions (assumed internal to the engine)
    static uint* getStaticStringBuffer();
    static void hashStringToBuffer(char* out, uint* in);
    static void createObjectByGUID(int* outObject, int* guid, char* hashBuffer, uint extra, int zero, int* resourceManager, int negative, int zero2);
    static void releaseObject(int* obj);
    static void* allocateMemory(size_t size, uint align);
    static void unlinkNode(uint* listPrev);
    static void registerNode(uint* node);
};

// Note: The magic numbers, vtable address (0x00d61508) and globals (DAT_00d5ccf8) are assumed from the binary.
// Offsets: containerHandle +0x48 = first linked list head, containerHandle +0x2d4 = second linked list head.
// The node structure: +0x00 vtable, +0x04 reserved, +0x08 list1Prev, +0x0C list1Next, +0x10 list2Prev, +0x14 list2Next, +0x18 data.