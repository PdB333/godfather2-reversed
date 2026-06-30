// FUNC_NAME: EntityBase::create
// Address: 0x006d7980
// Role: Allocates and initializes an EntityBase object (size 0x270). Checks type at +0x90 and conditionally sets up a sub-object at +0x58.

typedef struct {
    unsigned int size;       // +0x00
    unsigned int alignment;  // +0x04
    unsigned int flags;      // +0x08
} AllocationParams;

typedef int (__thiscall *AllocFunc)(void*, unsigned int, AllocationParams*);

void* getMemoryManager(); // FUN_009c8f80

int __fastcall EntityBase::create(EntityBase* this) {
    void* memoryManager = getMemoryManager();
    unsigned int allocResult;
    int result;
    
    AllocationParams allocParams;
    allocParams.size = 2;        // allocation type?
    allocParams.alignment = 0x10;
    allocParams.flags = 0;
    
    // Virtual call: MemoryManager::allocate(0x270, &allocParams)
    allocResult = (*(AllocFunc*)(*(uint32_t*)memoryManager))(memoryManager, 0x270, &allocParams);
    
    if (allocResult == 0) {
        return 0;
    }
    
    // Call the internal constructor on the allocated memory
    result = FUN_006d7020(this);  // EntityBase::constructor(this)
    
    // Check if object type is 0 or 0x48 (maybe "player" or "vehicle")
    if ((*(int*)((char*)this + 0x90) == 0) || (*(int*)((char*)this + 0x90) == 0x48)) {
        // Get sub-component at +0x58 and set property via hash
        int subComponent = FUN_00445ff0((char*)this + 0x58, 0);  // get some interface
        FUN_004480d0(subComponent, 0x38523fc3, &allocParams);    // set property (e.g., "persistent")
    }
    
    // Initialize other sub-component at +0x68
    FUN_006bfa70((char*)this + 0x68);  // e.g., script component init
    
    return result;
}