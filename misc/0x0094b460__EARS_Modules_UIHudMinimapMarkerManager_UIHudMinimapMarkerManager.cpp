// Xbox PDB: EARS_Modules_UIHudMinimapMarkerManager_UIHudMinimapMarkerManager
// FUNC_NAME: UIHudMinimapMarkerManager::MarkerPool::constructor
undefined4 * __fastcall UIHudMinimapMarkerManager::MarkerPool::constructor(undefined4 *this_ptr)
{
    undefined4 *freeListItemPtr;
    undefined4 poolBlock;

    // Initialize fields at offset 0x0C, 0x04, 0x08, 0x10, 0x14 to zero
    this_ptr[3] = 0;  // +0x0C: some counter/index
    this_ptr[1] = 0;  // +0x04
    this_ptr[2] = 0;  // +0x08
    this_ptr[4] = 0;  // +0x10
    this_ptr[5] = 0;  // +0x14

    // Set initial vtable pointer at +0x18
    this_ptr[6] = &PTR_LAB_00d8b67c;   // +0x18: vtable or function pointer

    // Grab pointer to free list head storage (+0x1C)
    freeListItemPtr = this_ptr + 7;    // +0x1C

    // Store this pool instance globally
    g_markerPoolManager = this_ptr;

    // Set vtable pointers at +0x1C and +0x24
    *freeListItemPtr = &PTR_FUN_00e2f19c; // +0x1C: free list head
    this_ptr[8] = 1;                     // +0x20: some active flag?
    this_ptr[9] = 0;                     // +0x24

    // Overwrite the main vtable pointer at +0x00
    *this_ptr = &PTR_FUN_00d8b694;       // +0x00: primary vtable

    // Overwrite +0x18 and +0x1C with more vtable-like pointers
    this_ptr[6] = &PTR_LAB_00d8b690;     // +0x18
    *freeListItemPtr = &PTR_LAB_00d8b680; // +0x1C

    // Register memory debug tracking for a pool of 0x220-sized elements, 8 items
    // (0x220 is size of each marker, 8 is pool capacity, 0x10 is alignment)
    FUN_004de0b0(0x220, 8, "UIHudMinimapMarkerManager::MarkerPool", 0, 0x10);

    // Set pool management vtable at +0x28
    this_ptr[10] = &PTR_FUN_00d8b674;    // +0x28: vtable for pool operations

    // Allocate the actual pool memory block (0x40 bytes for 8 marker slots?)
    poolBlock = FUN_009c8e80(0x40);      // +0x60: pointer to allocated block
    this_ptr[0x18] = poolBlock;          // +0x60
    this_ptr[0x19] = 0;                  // +0x64: current free count?
    this_ptr[0x1a] = 8;                  // +0x68: max pool size
    this_ptr[0x1b] = 0;                  // +0x6C: some flag
    *(undefined1 *)(this_ptr + 0x1c) = 0; // +0x70: byte flag (e.g., initialized)

    // If a default pool data block exists, copy it into the pool
    if (g_defaultMarkerPoolData != 0) {
        FUN_00408900(freeListItemPtr, &g_defaultMarkerPoolData, 0x8000);
    }

    return this_ptr;
}