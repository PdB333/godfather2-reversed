// FUNC_NAME: ObjectFactory::createObject
// Function at 0x00684740: Factory method that allocates memory for an object of size 0x130 and calls its constructor.
// Returns pointer to new object on success, 0 on failure.
void* ObjectFactory::createObject(void* param_1, uint param_2)
{
    // Allocation descriptor structure (size: 12 bytes)
    struct AllocInfo {
        int type;       // +0x0: allocation type (2 = likely heap object)
        int alignment;  // +0x4: requested alignment (0x10)
        int flags;      // +0x8: flags (0 = default)
    } allocInfo;

    allocInfo.type = 2;
    allocInfo.alignment = 0x10;
    allocInfo.flags = 0;

    // Allocate memory of size 0x130 (304 bytes)
    void* newObject = FUN_0043b980(0x130, &allocInfo, param_2);
    if (newObject != 0) {
        // Call the constructor on the allocated block
        FUN_0080f610(newObject);
        return newObject;
    }
    return 0;
}