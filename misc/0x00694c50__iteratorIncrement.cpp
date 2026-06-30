// FUNC_NAME: iteratorIncrement
// Function address: 0x00694c50
// Role: Helper function for custom iterator. Checks container validity and end condition,
// then returns pointer to next element (offset 0xC) for iteration.

// Assumes iterator structure:
// +0x00: pointer to container (has begin/end)
// +0x04: current element pointer
// Container structure:
// +0x00: begin pointer
// +0x04: end pointer (sentinel)

typedef int* IteratorContainer;

typedef struct Iterator {
    IteratorContainer* container; // +0x00
    int* current;                // +0x04
} Iterator;

// External assertion failure function (FUN_00b97aea)
void assertFailed(void);

int* __fastcall iteratorIncrement(int* param_1)
{
    Iterator* iter = (Iterator*)param_1;

    if (iter->container == 0) {
        assertFailed();
    }
    if (iter->current == *(int**)(*iter->container + 4)) {
        assertFailed();
    }
    // Return pointer to next element (advance by element size 0xC)
    return iter->current + 0xC;
}