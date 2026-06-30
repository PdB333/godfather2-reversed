// FUNC_NAME: QueueManager::processItems
// Function address: 0x00699ff0
// Iterates through a global array of ints (g_queueEntriesStart to g_queueEntriesEnd),
// compares each entry's associated value with a decoded result from FUN_00698c00,
// and calls a cleanup callback if mismatch. Returns the matched entry value or 0.

#include <cstdint>

// Global queue array pointers (initialized elsewhere)
extern int* g_queueEntriesStart; // DAT_01129f8c
extern int* g_queueEntriesEnd;   // DAT_01129f90

// External functions (to be defined elsewhere)
// Decodes a node from a buffer and returns a pointer to an int field
int* DecodeNode(uint8_t buffer[4], int* pInput); // FUN_00698c00
// Releases a node: likely operator delete or destructor call at offset +0x20
void ReleaseNode(int* pNode); // FUN_004d3e20

int QueueManager::processItems(int context, int param2, int param3, void (*cleanupCallback)(int)) // param2, param3 unused?
{
    int* iter = g_queueEntriesStart;
    if (iter != g_queueEntriesEnd)
    {
        do
        {
            int entryValue = *iter; // Value from the queue entry
            
            uint8_t buffer[4]; // Local buffer for decoding (size 4)
            int local1 = 0;
            int local2 = 0;
            int local3 = 0;
            void (*localCallback)(int) = nullptr;
            
            // Decode node from buffer and context? param_1 is passed as &context
            int* pDecoded = DecodeNode(buffer, &context);
            int decodedValue = *pDecoded;
            
            bool mismatch = (decodedValue != entryValue + 12); // +0xc offset check
            
            if (mismatch)
            {
                // Release node at decodedValue + 0x20 (offset to vtable/destructor)
                ReleaseNode(decodedValue + 0x20);
            }
            
            // If localCallback was set (via DecodeNode?), call it
            if (localCallback != nullptr)
            {
                localCallback(local1);
            }
            
            if (mismatch)
            {
                if (context != 0)
                {
                    cleanupCallback(context);
                }
                return entryValue; // Return the entry value on mismatch
            }
            
            iter++;
        } while (iter != g_queueEntriesEnd);
    }
    
    if (context != 0)
    {
        cleanupCallback(context);
    }
    return 0; // No match found
}