// FUNC_NAME: FindObjectByKey
// Function at 0x004544a0: Searches a global linked list of objects for one matching a two-integer key.
// Each object has a vtable; the second virtual function (offset 4) returns a pointer to a key pair (int key1, int key2).
// The list head is stored at global DAT_0120e9f4, an object pointer.
// Returns a pointer to the object (node) if found, else NULL.

// Object layout:
// +0x00: vtable pointer (int*)
// +0x04: next pointer (int*)

// Key returned by vtable[1] is assumed to be two consecutive ints: key[0] and key[1].

int* FindObjectByKey(int key1, int key2)
{
    int* pCurrent = (int*)DAT_0120e9f4;  // Global list head

    while (pCurrent != (int*)0x0)
    {
        // Call virtual function at vtable offset 4 (second entry) to get key pointer.
        // The argument (local buffer) is ignored; the function returns a pointer to the key.
        int* pKey = (int*)(**(code**)(*pCurrent + 4))(0x0);  // Simplified: no meaningful argument

        if (pKey[0] == key1 && pKey[1] == key2)
        {
            return pCurrent;  // Found matching object
        }

        // Advance to next node (offset 4 from object start)
        pCurrent = (int*)(*(pCurrent + 1));
    }

    return (int*)0x0;
}