// FUNC_NAME: Component::initialize
undefined4 __fastcall Component::initialize(Component* this)
{
    Allocator* allocator;
    int result;
    undefined4 returnVal;
    undefined4 someHandle;
    AllocInfo allocInfo;
    
    allocator = (Allocator*)FUN_009c8f80(); // Get global allocator instance
    allocInfo.type = 2;                     // Allocation type (e.g., type 2 = object)
    allocInfo.size = 0x10;                  // Additional allocation info
    allocInfo.flags = 0;                    // Allocation flags
    
    // Allocate memory block of size 0x270 (624 bytes)
    result = allocator->vtable->allocate(0x270, &allocInfo);
    if (result == 0) {
        returnVal = 0;
    } else {
        returnVal = FUN_006d7020(this);     // Initialize derived state
    }
    
    // Check current state at +0x90 (0 = inactive, 0x48 = some active state)
    if ((*(int*)((int)this + 0x90) == 0) || (*(int*)((int)this + 0x90) == 0x48)) {
        // Get manager/handler from +0x58 and register with hash 0x38523fc3
        someHandle = FUN_00445ff0((int)this + 0x58, 0);
        FUN_004480d0(someHandle, 0x38523fc3, &allocInfo);  // Registration using allocInfo
    }
    
    // Cleanup/update at +0x68
    FUN_006bfa70((int)this + 0x68);
    
    return returnVal;
}