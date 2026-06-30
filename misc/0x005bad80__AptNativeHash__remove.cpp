// FUNC_NAME: AptNativeHash::remove
// Source: ..\source\Apt\AptNativeHash.cpp line 0xe3 (227)
// Hash table removal for Apt native hash (Scaleform GFx).
// Structure: this[0]: bucketCountExp (byte exponent for bucket count = 2^exp)
//            this[2]: count (short)
//            this[4]: bucketArray (pointer to array of bucket heads)
// Node structure (0x10 bytes):
//            node[0]: key (pointer to HashKey object)
//            node[1]: value (pointer to associated data)
//            node[2]: next (pointer to next node in chain)
//            node[3]: stored hash (uint)
// HashKey object (at key pointer):
//            +0x0: unknown int (used for direct comparison)
//            +0x4: type discriminator? (int)
//            +0xC: name string (char*)
// Global destructor dispatch table (DAT_0103aee0) indexed by low 15 bits of pointer
// Global deallocation function (*DAT_0119caf8) for node memory.

#include <cstring>
#include <cstdint>

// Forward declarations
extern uint32_t hashFunction(); // FUN_005ba580
extern void* destructorTable;   // DAT_0103aee0 (array of function pointers)
extern void (*nodeFree)(void*, uint32_t); // DAT_0119caf8, free with size 0x10

// Debug assert mechanism (simplified)
#define ASSERT(cond, msg) if (!(cond)) { /* debug break */ }

void AptNativeHash::remove(void* key) __thiscall
{
    if (key == nullptr)
    {
        // Assertion check (debug build)
        const char* file = "..\\source\\Apt\\AptNativeHash.cpp";
        int line = 0xe3; // 227
        int severity = 2;
        // Assume debug flag is set
        if (DAT_01129166 != 0)
        {
            // Retrieve assertion handler
            int* module = *(int**)(*(int**)(__readfsdword(0x2C) + 0x30) + 0x30);
            uint32_t action = 1;
            if (module == nullptr)
            {
                // Fallback: just clear the flag
                if (action & 2) 
                    DAT_01129166 = 0;
            }
            else
            {
                action = (*(code**)(*module + 8))(&file, &file); // simplified
                if (DAT_01129166 != 0)
                {
                    if (action & 2) 
                        DAT_01129166 = 0;
                }
            }
            if ((module != nullptr || severity == 4) &&
                ((action & 1) || (severity == 0 || severity == 1)))
            {
                // Break into debugger
                __debugbreak();
            }
        }
        goto continue_search;
    }

continue_search:
    // Compute hash for the key
    uint32_t hash = hashFunction();
    uint32_t bucketCount = (1 << (this->bucketCountExp & 0x1F));
    uint32_t bucketIndex = hash & (bucketCount - 1);

    int** bucketHeadPtr = this->buckets + bucketIndex;
    int* node = *bucketHeadPtr;
    int* prevNode = nullptr;

    while (node != nullptr)
    {
        if (node[0] == (int)key &&  // Direct pointer comparison
            node[3] == hash &&     // Hash match
            *(int*)(node[0] + 4) == *(int*)((int)key + 4) && // Second int match
            _stricmp(*(const char**)(node[0] + 0xC), *(const char**)((int)key + 0xC)) == 0) // String match
        {
            // Found the entry
            if (prevNode == nullptr)
            {
                // Update bucket head
                *bucketHeadPtr = (int*)node[2];
            }
            else
            {
                prevNode[2] = node[2];
            }

            // Release key and value using global destructor table
            typedef void (*DestructorFn)(uint32_t*);
            DestructorFn destructKey = (DestructorFn)destructorTable[(node[0] & 0x7FFF) * 4];
            DestructorFn destructValue = (DestructorFn)destructorTable[(node[1] & 0x7FFF) * 4];
            destructKey((uint32_t*)node[0]);
            destructValue((uint32_t*)node[1]);

            // Free the node
            nodeFree(node, 0x10);

            // Decrement count
            this->count--;
            return;
        }

        prevNode = node;
        node = (int*)node[2];
    }
}