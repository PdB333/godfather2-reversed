// FUNC_NAME: PathManager::computeDistanceAlongPath
// Function address: 0x005cffe0
// This function computes a float distance value from path data.
// It retrieves a 104-byte data block from the object, then parses it into an array of 37 path object pointers.
// It calls a query function that returns an integer, and computes the distance as (pathObject[0][5] - queryResult).
// Returns 1 on success, 0 on failure.

int __thiscall PathManager::computeDistanceAlongPath(PathManager* thisPtr, int usePath, float* outDistance)
{
    char success;
    int queryResult;
    byte buffer104[104]; // Data buffer, size 0x68
    byte buffer4_1[4];   // Small buffer for query
    byte buffer4_2[4];   // Small buffer for query
    int* pathObjects[37]; // Array of 37 pointers to path objects

    // Step 1: Retrieve path data from the object into buffer104
    success = thisPtr->getPathData(buffer104);
    if (success != 0 && usePath != 0) {
        // Step 2: Initialize path processing
        pathProcessingInit();

        // Step 3: Parse the data into an array of path object pointers
        parsePathData(pathObjects, buffer104);

        // Step 4: Query a parameter from the path system
        queryResult = 0;
        success = queryPathParameter(1, &queryResult, buffer4_1, buffer4_2);
        if (success != 0) {
            // Step 5: Compute the distance: (pathObject[0][5] - queryResult) as float
            *outDistance = (float)(pathObjects[0][5] - queryResult);

            // Step 6: Release the first path object (if allocated)
            if (pathObjects[0] != (int*)0x0) {
                (*(code**)(*(int*)pathObjects[0] + 4))(); // virtual destructor call
            }
            return 1;
        }

        // Cleanup even if query failed
        if (pathObjects[0] != (int*)0x0) {
            (*(code**)(*(int*)pathObjects[0] + 4))(); // virtual destructor call
        }
    }
    return 0;
}