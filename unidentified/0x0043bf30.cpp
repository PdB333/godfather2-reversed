// FUN_NAME: GameGridManager::GameGridManager
class GameGridManager {
    void** vtable;                    // +0x0
    void* slotArray;                  // +0x4 - array of 64 objects (0x1c bytes each)
    void* gridObject;                 // +0x8 - manages the 2D grid data

public:
    __thiscall GameGridManager(int width, int height) {
        int cellCount = width * height;
        int gridDataSize = (cellCount + 3) * 0xC; // +3 for alignment padding, 12 bytes per cell
        gGameGridManagerSingleton = this;        // store singleton (DAT_01223414)

        this->vtable = &GameGridManager_VTable;  // PTR_FUN_00e30fd4

        // Allocate raw grid data
        void* gridData = operatorNew(gridDataSize);  // FUN_009c8e80

        // Create the grid manager object (size 0x28 = 40 bytes)
        void* gridObj = operatorNew(0x28);           // FUN_009c8e50
        if (gridObj) {
            *(void**)gridObj = &GridObject_VTable;   // PTR_LAB_00e30fc0
            // Initialize grid data: fill with 0x00 (or run constructor for each cell of size 0xC)
            // Parameters: destination, size, element size (0xC), stride (4)
            FUN_004abe90(gridData, gridDataSize, 0xC, 4);
            *(int*)((char*)gridObj + 0x24) = 1;      // +0x24: some flag (offset 9 ints)
            *(int*)((char*)gridObj + 0x20) = 0;      // +0x20: another flag (offset 8 ints)
        }
        this->gridObject = gridObj;                  // +0x8

        // Allocate array of 64 slot objects (0x1c bytes each)
        void* slotArrayMem = operatorNew(0x704);     // 0x704 = 0x4 (count) + 0x40 * 0x1c
        if (slotArrayMem) {
            *(int*)slotArrayMem = 0x40;              // count = 64
            // Construct each slot via default constructor FUN_0043c0b0
            _vector_constructor_iterator_((char*)slotArrayMem + 4, 0x1c, 0x40, FUN_0043c0b0);
            this->slotArray = (char*)slotArrayMem + 4;
        } else {
            this->slotArray = nullptr;
        }
    }
};