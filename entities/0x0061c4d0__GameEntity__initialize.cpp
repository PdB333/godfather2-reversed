// FUNC_NAME: GameEntity::initialize
// Function address: 0x0061c4d0
// This function appears to be a constructor or initializer for a game entity object.
// It first calls a global base initialization routine, then sets up a component/sub-object
// using two fields from the object and a pointer to an internal buffer.

void __fastcall GameEntity::initialize(GameEntity* thisPtr) // param_1 is ECX (this)
{
    // Base class/global initialization (likely a static or base constructor)
    globalBaseInit();

    // Setup component:
    //   arg1: value at offset +0x10 (likely an ID, type, or object handle)
    //   arg2: value at offset +0xC0 (likely a size, count, or flag)
    //   arg3: pointer to buffer at offset +0xB0 (likely a structure to be filled)
    setupComponent(
        *(uint32_t*)((uint8_t*)thisPtr + 0x10), // +0x10: field1
        *(uint32_t*)((uint8_t*)thisPtr + 0xC0), // +0xC0: field2
        (uint32_t*)((uint8_t*)thisPtr + 0xB0)   // +0xB0: component buffer
    );
}