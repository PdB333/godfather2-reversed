// Xbox PDB: EARS_Modules_SubtitleManager_SetSubtitleData
// FUNC_NAME: UISubtitleSystem::loadTitlesAndSubtitles

void __thiscall UISubtitleSystem::loadTitlesAndSubtitles(int thisPtr, int param_2) // param_2 likely a resource identifier (e.g., language string)
{
    char isValid;
    int titleId;
    int subtitleId;
    int allocResult;
    int callbackResult;
    void* closureData;
    code* closureCallback;

    // Validate the input parameter (e.g., check if it's a valid language code)
    isValid = FUN_00816a90(param_2, &param_2);
    if (isValid != 0) {
        // Look up the "titles" resource
        titleId = FUN_00604db0("titles"); // returns index or handle, -1 if not found
        if (titleId >= 0) {
            // Start asynchronous loading of titles
            FUN_004d3bc0(param_2); // maybe push a job or begin loading
            FUN_004d57e0(); // possibly process pending operations
            FUN_004d55f0(); // maybe set up a callback context

            // Get a callback function for completion
            callbackResult = FUN_004d46f0(&DAT_00e2f048, 0); // fetch callback from a known address
            if (callbackResult != 0) {
                // Prepare the callback invocation
                int local_array[3];
                void* closurePtr = FUN_004d5170(local_array, &DAT_00e2f048); // create closure
                FUN_004d3e20(closurePtr); // maybe pass to the job system

                if (local_array[0] != 0) {
                    // Invoke the callback (local_4 is a captured function pointer)
                    (*local_4)(local_array[0]); // local_4 is the actual callback function
                }
            }

            // Set the title text (offset +0x8 is the title text buffer)
            // puVar5 = local_20; if local_20 is null, use a default empty string
            if (closureData == (void*)0x0) {
                closureData = &DAT_0120546e; // default empty string data
            }
            FUN_00815d60(thisPtr + 8, 2, closureData); // set text alignment? 2 = center, store string

            // Allocate a font/text object for titles (size 0x1c = 28 bytes)
            allocResult = FUN_009c8e50(0x1c);
            if (allocResult == 0) {
                param_2 = 0; // fallback to null
            } else {
                // Create a text object with a maximum length of 500 characters
                param_2 = FUN_00816630(thisPtr + 8, 500);
            }
            *(int*)(thisPtr + 0x78) = param_2; // store the title text object

            // Finalize loading for titles
            FUN_008161e0(param_2, titleId); // associate with the resource
            FUN_00816080(); // cleanup
            FUN_008160b0(); // maybe notify listeners

            // Free closure data if it was allocated
            if (closureData != (void*)0x0) {
                (*pcStack_14)(closureData); // destroy closure
            }
        }

        // Now handle "subtitles" similarly
        subtitleId = FUN_00604db0("subtitles");
        if ((subtitleId >= 0) && ((*(byte*)(DAT_01129938 + 0x14) & 1) != 0)) { // check a flag (e.g., subtitles enabled)
            // Set subtitle text (offset +0x40 is the subtitle text buffer)
            FUN_00815d60(thisPtr + 0x40, 1, 0); // 1 = left alignment, 0 = default text

            // Allocate a font/text object for subtitles (size 0x1c)
            allocResult = FUN_009c8e50(0x1c);
            if (allocResult == 0) {
                param_2 = 0;
            } else {
                // Create a text object with no length limit (0)
                param_2 = FUN_00816630(thisPtr + 0x40, 0);
            }
            *(int*)(thisPtr + 0x7c) = param_2; // store the subtitle text object

            // Finalize loading for subtitles
            FUN_008161e0(param_2, subtitleId);
            FUN_00816080();
            FUN_008160b0();
        }
    }
    return;
}