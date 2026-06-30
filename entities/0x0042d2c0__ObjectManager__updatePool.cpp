// FUNC_NAME: ObjectManager::updatePool
// Address: 0x0042d2c0
// Description: Iterates over an array of objects (size 0xB0 each) in a pool, 
//   cleaning up inactive states (0-4) and updating active ones (state 5).
//   Uses callback function pointers from the manager instance.

void __thiscall ObjectManager::updatePool(ArrayDescriptor* desc)
{
    // desc->base at +0x50 is the start pointer
    // desc->count at +0x34 is the number of objects (each 0xB0 bytes)
    Object* current = (Object*)(desc->base);          // +0x50
    Object* end = current + (desc->count * 0xB0);     // +0x34 counted in bytes

    for (; current != end; current = (Object*)((uint8_t*)current + 0xB0))
    {
        switch (current->state)                       // +0x29
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                // Inactive/cleanable states: release the object and mark as free
                releaseObject(current);                // FUN_004c4e60
                current->state = 0xFF;                 // mark as unused
                break;

            case 5:
                // Active state: update via callback
                if (this->updateDirectFunc == nullptr) // +0x3a3c
                {
                    // Call the other callback with the object pointer
                    this->updateCallback(current);     // +0x3a28
                }
                else
                {
                    // Call the direct update function, passing address of updateCallback
                    this->updateDirectFunc((uint32_t*)&this->updateCallback); // +0x3a28
                }
                releaseObject(current);                // FUN_004c4e60
                break;
        }
    }

    finalizePoolUpdate();                              // FUN_004c75f0
}

// Supporting types (assumed, based on offsets and size)
// struct Object {
//     uint8_t  field_0x00[0x29]; // padding or other fields
//     uint8_t  state;            // +0x29
//     // ... remaining to 0xB0
// };
//
// struct ArrayDescriptor {
//     uint32_t count;    // +0x34
//     uint8_t  pad[0x1C];
//     Object*  base;     // +0x50
// };