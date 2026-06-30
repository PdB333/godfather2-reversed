// FUNC_NAME: EARSObjectSystem::initializeObjectRegistry
// Function address: 0x004181f0
// Rebuilds a linked list of all registered game objects (templates) using stored IDs and serial numbers.
// Iterates over three sets: a pointer array (152 pointers), a static object array (36 objects, each 0x104 bytes), and another pointer array (52 pointers).
// Each object must have a vtable: vtable+4 returns a hash/ID, vtable+0x10 is called after registration.

// Global flags indicating which sets to process
extern bool DAT_01205358; // set to true when first ring is active
extern bool DAT_01205359; // set to true when second pointer array should be processed

// Global linked list head and serial counter
extern EARSObject* DAT_012058ec; // linked list head (previously registered)
extern int DAT_012058f8;         // incrementing serial number

// External arrays of pointers and static objects
extern EARSObject* PTR_PTR_0110ad18[152]; // array of object pointers (first ring)
extern EARSObject* PTR_DAT_0110adb0[52];  // array of object pointers (third ring)
extern EARSObject DAT_01211a90[36];       // static array of objects (second ring), each 0x104 bytes

// Object structure assumed (simplified for registration)
struct EARSObject {
    void** vtable;      // +0x00
    EARSObject* prev;   // +0x04
    int hash;           // +0x08
    int serialNumber;   // +0x0C
    // other fields up to 0x104 bytes
};

// External hash function (likely CRC or custom)
extern int FUN_0060d740(int value);

void FUN_004181f0(void) {
    int uVar4;
    EARSObject* current;
    int hash;
    int idx;

    if (DAT_01205358) {
        // Process first ring: pointer array of 152 entries
        for (idx = 0; idx < 152; idx++) {
            current = PTR_PTR_0110ad18[idx]; // get object ptr
            hash = (*(int (**)(void))(*(int*)current + 4))(); // vtable+4 -> get some ID
            hash = FUN_0060d740(hash); // transform to final hash
            current->hash = hash;                // store at +0x08
            (*(void (**)(void))(*(int*)current + 0x10))(); // vtable+0x10 -> onRegistered callback
            current->prev = DAT_012058ec;        // link previous head to current->prev (+0x04)
            DAT_012058ec = current;              // update head
            current->serialNumber = DAT_012058f8++; // assign and increment serial (+0x0C)
        }

        // Process second ring: static array of 36 objects (size 0x104 each)
        current = &DAT_01211a90[0];
        while ((int)current < (int)&DAT_01211a90[36]) { // iterate until the end of the array
            hash = (*(int (**)(void))(*(int*)current + 4))();
            hash = FUN_0060d740(hash);
            current->hash = hash;
            (*(void (**)(void))(*(int*)current + 0x10))();
            current->prev = DAT_012058ec;
            DAT_012058ec = current;
            current->serialNumber = DAT_012058f8++;
            // Move to next object (stride 0x104 = 260 bytes)
            current = (EARSObject*)((char*)current + 0x104);
        }

        if (DAT_01205359) {
            // Process third ring: pointer array of 52 entries
            for (idx = 0; idx < 52; idx++) {
                current = PTR_DAT_0110adb0[idx];
                hash = (*(int (**)(void))(*(int*)current + 4))();
                hash = FUN_0060d740(hash);
                current->hash = hash;
                (*(void (**)(void))(*(int*)current + 0x10))();
                current->prev = DAT_012058ec;
                DAT_012058ec = current;
                current->serialNumber = DAT_012058f8++;
            }
        }
    }
}