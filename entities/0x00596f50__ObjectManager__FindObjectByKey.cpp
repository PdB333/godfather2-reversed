// FUNC_NAME: ObjectManager::FindObjectByKey
// Function address: 0x00596f50
// Looks up an object by key in a global array of objects.
// Each object has a virtual method at vtable offset 0x2c (0x2c/4 = 11th method) that checks if the key matches.
// The array is stored at gObjectArray (DAT_0119c6d0), count at gObjectCount (DAT_01205594).
// Returns a pointer to the matching object, or 0 if not found.

int __cdecl FindObjectByKey(int key)
{
    int i;
    int obj;

    if (key == 0) {
        return 0;
    }

    // Iterate over the global array of object pointers
    for (i = 0; i < gObjectCount; i++) {
        obj = gObjectArray[i];
        if (obj != 0) {
            // Call virtual method at offset 0x2c on the object (sub-object at offset 0x30? Actually the object itself)
            // The method takes a key parameter and returns 0 if match found? Or non-zero? The code checks ==0.
            // Assuming the method returns 0 on match.
            int (*checkMethod)(int, int) = (int (*)(int, int))(*((int*)obj) + 0x2c);
            if (checkMethod(obj, key) == 0) {
                return obj;
            }
        }
    }
    return 0;
}