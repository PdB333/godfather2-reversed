// FUNC_NAME: GameManager::initData

void __fastcall GameManager::initData(GameManager* this)
{
    bool success;
    int allocResult;
    struct AllocInfo {
        int type;       // +0x00: memory pool type (2 = Static)
        int alignment;  // +0x04: alignment (16)
        int flags;      // +0x08: allocation flags (0)
    } allocInfo;

    // Ensure global memory system is initialized
    Memory::globalInit();

    // Set up allocation parameters: type Static, 16-byte alignment, no flags
    allocInfo.type = 2;
    allocInfo.alignment = 0x10;
    allocInfo.flags = 0;

    // Allocate a large memory block (0x4d38 bytes) for game data
    allocResult = Memory::allocate(0x4d38, &allocInfo);
    if (allocResult != 0) {
        // Create the data block and store its pointer at +0x1c
        this->dataPtr = GameManager::createDataBlock(this);
        return;
    }

    // Allocation failed – clear pointer
    this->dataPtr = 0;
}