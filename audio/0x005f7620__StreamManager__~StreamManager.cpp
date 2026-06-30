// FUNC_NAME: StreamManager::~StreamManager
// Function address: 0x005f7620
// Role: Destructor for StreamManager - cleans up two linked lists of pending operations,
// releases owned objects via virtual interface, and frees internal memory.
// Offsets (from this):
// +0x00: vtable pointer (set to derived vtable initially, base vtable at end)
// +0x04: pointer to memory freed via FUN_009c8f10 (likely operator delete)
// +0x10: pointer to sub-object with vtable (used to release objects)
// +0x28: object 1 (released via sub-object's vtable[1])
// +0x2c: object 2 (released via sub-object's vtable[1])
// +0x30: object 3 (released via sub-object's vtable[1])
// +0x4c: sentinel head of circular doubly linked list 1 (list of pending items)
// +0x50: count of items in list 1
// +0x6c: sentinel head of circular doubly linked list 2
// +0x70: count of items in list 2

#include <cstddef>

class StreamManager {
public:
    void** vtable;             // +0x00
    void* somePointer;         // +0x04
    // padding? (unknown)
    void* subObject;           // +0x10 - object with virtual functions
    // ...
    void* objToRelease1;       // +0x28
    void* objToRelease2;       // +0x2c
    void* objToRelease3;       // +0x30
    // ...
    // List 1: circular doubly linked list with sentinel at head
    struct ListNode {
        ListNode* next;        // +0x00
        ListNode* prev;        // +0x04
        void* data;            // +0x08 - data pointer passed to cleanup function
    };
    ListNode list1Head;        // +0x4c (sentinel)
    int list1Count;            // +0x50
    // List 2: similar structure
    ListNode list2Head;        // +0x6c
    int list2Count;            // +0x70

    // External cleanup functions (defined elsewhere)
    static void cleanupListItem1(void* data); // FUN_005f7860
    static void cleanupListItem2(void* data); // FUN_005f7d40
    static void assertFailure();             // FUN_00b97aea
    static void globalCleanup1();            // FUN_005f9220
    static void globalCleanup2();            // FUN_005f9020
    static void freeMemory(void* ptr);       // FUN_009c8f10

    // Virtual function table layout for subObject:
    // vtable[0] : unknown
    // vtable[1] : release(void* obj, int flag)
    // vtable[3] : someCleanup() (no args)

    void releaseObject(void* obj) const {
        // Call subObject's vtable[1] (offset 4) with obj and 0
        void** subVtable = *reinterpret_cast<void***>(subObject);
        using ReleaseFunc = void(__thiscall*)(void*, void*, int);
        ReleaseFunc release = reinterpret_cast<ReleaseFunc>(subVtable[1]);
        release(subObject, obj, 0);
    }

    void subObjectCleanup() const {
        // Call subObject's vtable[3] (offset 12)
        void** subVtable = *reinterpret_cast<void***>(subObject);
        using CleanupFunc = void(__thiscall*)(void*);
        CleanupFunc cleanup = reinterpret_cast<CleanupFunc>(subVtable[3]);
        cleanup(subObject);
    }

    ~StreamManager() {
        // Set vtable to derived class vtable (to ensure correct virtual dispatch during destruction)
        vtable = reinterpret_cast<void**>(0x00e407bc); // &PTR_FUN_00e407bc

        // Clean up list 1
        while (list1Count != 0) {
            ListNode* node = list1Head.next; // first real node
            if (node == &list1Head) {
                assertFailure();
            }
            cleanupListItem1(node->data);
            // Count updated by cleanup (node removed, count decremented)
        }

        // Release object at offset 0x2c (objToRelease2)
        if (objToRelease2 != nullptr) {
            releaseObject(objToRelease2);
        }

        // Clean up list 2
        while (list2Count != 0) {
            ListNode* node = list2Head.next; // first real node
            if (node == &list2Head) {
                assertFailure();
            }
            cleanupListItem2(node->data);
        }

        // Release objects at offsets 0x28 and 0x30
        if (objToRelease1 != nullptr) {
            releaseObject(objToRelease1);
        }
        if (objToRelease3 != nullptr) {
            releaseObject(objToRelease3);
        }

        // Call subObject's cleanup
        subObjectCleanup();

        // Global cleanup functions (likely static singletons)
        globalCleanup1();
        globalCleanup2();

        // Free the memory pointed to by somePointer
        if (somePointer != nullptr) {
            freeMemory(somePointer);
        }

        // Set vtable to base class vtable (chaining)
        vtable = reinterpret_cast<void**>(0x00e407c0); // &PTR_LAB_00e407c0

        // Clear global flag
        DAT_01223520 = 0;
    }

    // External global variable
    static int DAT_01223520;
};