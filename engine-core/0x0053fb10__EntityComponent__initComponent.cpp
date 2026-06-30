// FUNC_NAME: EntityComponent::initComponent
// 0x0053fb10: Constructor/initializer for an engine component. Allocates a small sub-object (8 bytes) with vtable at +0x0 and stores a value from this+0x24 into it at +0x4. The sub-object is registered via FUN_009e76a0.

class EntityComponent {
public:
    // +0x10: some flag/state (set to 0 here)
    // +0x24: some integer value (e.g., ID or resource handle)
    // +0x58: pointer to allocated sub-object (8 bytes)
    // +0x00: vtable pointer of this class (implicit)

    void initComponent() {
        // Step 1: Clear field at +0x10
        *(int*)((char*)this + 0x10) = 0;

        // Step 2: Call two internal initialization subroutines
        FUN_0053fc40();  // likely initA (details unknown)
        FUN_0053fcc0();  // likely initB

        // Step 3: Allocate 8 bytes for a sub-object
        int* newBlock = (int*)FUN_009c8e50(8);  // custom allocator (likely operator new)
        if (newBlock != nullptr) {
            // Set up sub-object vtable and store the value from this+0x24 at offset 4
            newBlock[0] = (int)&PTR_LAB_00e39178;  // static vtable for sub-object class
            newBlock[1] = *(int*)((char*)this + 0x24);
            *(int**)((char*)this + 0x58) = newBlock;

            // Register the sub-object with the engine
            FUN_009e76a0(newBlock);
        } else {
            // Allocation failed: set pointer to null and attempt to register null
            *(int**)((char*)this + 0x58) = nullptr;
            FUN_009e76a0(nullptr);
        }
    }
};