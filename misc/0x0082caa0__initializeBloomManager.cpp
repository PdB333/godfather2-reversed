// FUNC_NAME: initializeBloomManager

// 0x0082caa0 - Initializes the bloom post-processing effect manager (singleton)
// This function is called during game initialization.

#include <cstdint>

// Forward declarations (from known EA EARS engine APIs)
extern int **_DAT_00d5780c; // Some global data (likely a constant or timer value)
extern int *DAT_0112dbbc;    // Singleton pointer to BloomManager
extern int *DAT_0112dbc0;    // Pointer to bloom effect node list head

void* __fastcall operator_new(size_t size, uint32_t alignment); // 0x004eb390
void FUN_004eacb0(const char* name); // Likely Render::registerEffect or similar
int* FUN_004df3c0(int* outParam, void* stackBuffer, int* color, int unk, int unk2, int* extra); // Creates bloom effect node
void FUN_004df830(int* manager); // Initialize manager with data
void FUN_004df5c0(); // Activate bloom effect

void initializeBloomManager()
{
    // Persistent global value (e.g., initial time or render target color)
    int persistentColor = *_DAT_00d5780c;

    // --- Initialize the bloom manager singleton (DAT_0112dbbc) ---
    if (DAT_0112dbbc == nullptr)
    {
        // Allocate 0x70 bytes for BloomManager (might be a custom allocator)
        int* manager = (int*)operator_new(0x70, 0x10);
        if (manager == nullptr)
        {
            DAT_0112dbbc = nullptr;
        }
        else
        {
            // Set vtable pointer (offset 0x00) to global vtable
            manager[0] = (int)&PTR_LAB_00d73608; // VTable for BloomManager? (global label)
            
            // Initialize fields (offsets in 4-byte units)
            manager[0x14] = (int)_DAT_00d5d7b8; // +0x50: some other global data
            manager[1]   = 0;                     // +0x04
            manager[0x17] = 0;                    // +0x5C
            manager[7]   = 0;                     // +0x1C
            manager[6]   = 0;                     // +0x18
            manager[5]   = 0;                     // +0x14
            manager[4]   = 0;                     // +0x10

            // Set color data (likely RGBA or similar)
            manager[0x0e] = persistentColor;      // +0x38
            manager[0x0d] = persistentColor;      // +0x34
            manager[0x0c] = persistentColor;      // +0x30

            manager[0x0f] = 0;                    // +0x3C

            // Copy color to other buffers (ring buffer or history)
            manager[8]  = manager[0x0c];          // +0x20 = +0x30
            manager[9]  = manager[0x0d];          // +0x24 = +0x34
            manager[10] = manager[0x0e];          // +0x28 = +0x38
            manager[0xb]= manager[0x0f];          // +0x2C = +0x3C

            // Clear other fields
            manager[0x13] = 0; // +0x4C
            manager[0x12] = 0; // +0x48
            manager[0x11] = 0; // +0x44
            manager[0x10] = 0; // +0x40
            manager[0x15] = 0; // +0x54
            manager[0x16] = 0; // +0x58
            manager[0x18] = 0; // +0x60
        }
        DAT_0112dbbc = manager;

        // Increment reference count? (offset 0x04)
        if (DAT_0112dbbc != nullptr)
            DAT_0112dbbc[1]++;
    }

    // --- Initialize the bloom effect node list (DAT_0112dbc0) ---
    if (DAT_0112dbc0 == 0)
    {
        // Prepare stack buffers for effect creation call
        int local_50 = persistentColor;          // Default color
        int local_64 = 0;                       // Out parameter
        char local_60[16] = {0};                // Buffer for shader name?
        int local_68 = 0;                       // Extra parameter

        // Register the "bloom" effect with the renderer
        FUN_004eacb0("bloom");

        // Create a bloom effect node (returns pointer to node pointer?)
        int** ppNode = (int**)FUN_004df3c0(&local_64, local_60, &local_50, 0xFFFFFFFF, 0, &local_68);
        
        // Manage linked list of glow nodes
        if (DAT_0112dbc0 != 0)
        {
            // Clear next pointer of existing head? (offset +0x08)
            *(int*)(DAT_0112dbc0 + 8) = 0;
        }

        // Set new head (the result points to the new node's pointer)
        DAT_0112dbc0 = *ppNode;

        if (DAT_0112dbc0 != 0)
        {
            // Set list head pointer for the new node (offset +0x08)
            *(int**)(DAT_0112dbc0 + 8) = &DAT_0112dbc0;
        }

        // Clear the original pointer (to avoid double use)
        *ppNode = 0;

        // Clean up previous node if it exists (local_64 might be the old head)
        if (local_64 != 0)
        {
            *(int*)(local_64 + 8) = 0;
        }

        // Finalize initialization
        if (DAT_0112dbc0 != 0)
        {
            // Initialize bloom manager with effect data
            FUN_004df830(DAT_0112dbbc);
            // Activate bloom rendering
            FUN_004df5c0();
        }
    }
    return;
}