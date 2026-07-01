// FUNC_NAME: TaskController::handleEvent
// Address: 0x007eed10
// Role: Handles an event, possibly counting occurrences or managing a two-phase initialization.
// Offsets:
//   this+0x00: unknown (first field)
//   this+0x0c: counter (int)
//   this+0x10: dataNode (pointer to allocated block of 3 uint32s, first two zero, third is float)
//   this+0x14: byteArray[256] (frequency counters for event types)

void __thiscall TaskController::handleEvent(TaskController *this, uint *eventData)
{
    uint hash;
    char *targetByte;
    uint *newBlock;

    // Increment internal counter
    this->counter += 1;

    // On second call, allocate a 12-byte block and initialize it
    if (this->counter == 2) {
        newBlock = (uint *)allocate(0xc);
        if (newBlock != 0) {
            newBlock[0] = 0;
            newBlock[1] = 0;

            // Compute a value using a pseudo-random table and global game manager's fields
            uint seed = g_randomSeed & g_randomIndex;  // g_randomSeed and g_randomIndex are global
            g_randomIndex++;
            float val = g_randomFloatTable[seed] * g_gameManager->field_0x44 + g_gameManager->field_0x40;
            *(float *)&newBlock[2] = val;             // Store as float in the third slot
        }
        this->dataNode = newBlock;                   // Save pointer to the allocated block
    }

    // Compute a hash from the event data, then increment the corresponding byte counter
    hash = getEventHash(*eventData);
    targetByte = (char *)this + 0x14 + (hash & 0xff);
    *targetByte += 1;
}