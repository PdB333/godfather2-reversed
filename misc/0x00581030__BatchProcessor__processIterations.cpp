// FUNC_NAME: BatchProcessor::processIterations
// Address: 0x00581030
// Role: Core loop for processing a batch of steps: initialization, iteration, finalization.

void __thiscall BatchProcessor::processIterations(int count)
{
    // Initialize processing state
    preProcess();                    // FUN_00581080

    // Process each step 'count' times
    if (0 < count) {
        do {
            doProcess();            // FUN_00581370
            count = count - 1;
        } while (count != 0);
    }

    // Finalize processing using this pointer (passed as param_1 in original)
    postProcess();                  // FUN_00581220(this) in asm
}