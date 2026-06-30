// FUNC_NAME: Queue::~Queue

void __fastcall Queue::~Queue(Queue* this)
{
    int retryCount;
    int* pStackArray;
    int currentCount;
    float conditionResult;

    // Set vtable to initial vtable (constructor vtable)
    this->vtable = &PTR_FUN_00e41490;

    // Enter critical section
    FUN_00c9eac0();

    // If flag at offset 0x24 is set, release resource at offset 0x0C
    if (*(char*)((int)this + 0x24) != '\0') {
        FUN_00ca5480((int*)this + 3); // offset 0x0C
    }

    // Signal condition variable with type 1 and null data
    FUN_00c9cd40(1, 0);

    // Leave critical section
    FUN_00c9eae0();

    // Initialize retry counter
    retryCount = 0;

    // Loop while there are items in the queue
    currentCount = this->m_count; // offset 0x88
    while (currentCount != 0) {
        // Process an item: call with m_pBuffer (offset 0x08), data from m_anotherPointer+0x10 (offset 0xA0), type 3, and stack array
        FUN_00c9cbe0(this->m_pBuffer, *(undefined4*)(this->m_anotherPointer + 0x10), 3, &pStackArray);

        // Prepare data for condition variable
        if (this->m_count == 0) {
            pStackArray = 0;
        } else {
            pStackArray = (int*)(this->m_readIndex * 0x10 + this->m_baseOffset); // offset 0x94 and 0x98
        }

        // Enter critical section
        FUN_00c9eac0();

        // Signal condition variable with type 3 and the computed data
        FUN_00c9cd40(3, &pStackArray);

        // Leave critical section
        FUN_00c9eae0();

        // Check if condition variable signaled success (compare with global float)
        if (conditionResult == DAT_00e2b1a4) {
            // Dequeue an item
            if (this->m_count != 0) {
                int* pDest = (int*)(this->m_readIndex * 0x10 + this->m_baseOffset);
                *pDest = this->m_writeValue; // offset 0x8C
                pDest[2] = pDest[2]; // self-assignment (likely a bug or placeholder)
                pDest[1] = 0;
                this->m_readIndex++;
                if ((uint)this->m_readIndex >= (uint)this->m_capacity) { // offset 0x84
                    this->m_readIndex = 0;
                }
                this->m_count--;
            }
        } else {
            // Condition not met, yield and retry
            FUN_00ab4b40(&conditionResult);
            retryCount++;
            if (retryCount == 250) {
                break;
            }
        }

        // Update current count for loop condition
        currentCount = this->m_count;
    }

    // If flag at offset 0x9C is set, perform additional cleanup
    if (this->m_someFlag != 0) { // offset 0x9C
        FUN_00c9eac0();
        FUN_00ca5940();
        FUN_00c9eae0();
    }

    // Final cleanup functions
    FUN_006200d0();
    FUN_00ab4d30();
    FUN_00c9ec70();

    // Set vtable to destructor vtable
    this->vtable = &PTR_LAB_00e4145c;
    return;
}