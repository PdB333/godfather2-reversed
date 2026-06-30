// FUNC_NAME: StateProcessor::processState
void __fastcall StateProcessor::processState(void* thisPointer, int state)
{
    // Call preprocessing or initialization routine
    doPreProcessing();

    // Dispatch based on state value (passed in EAX)
    switch (state) {
        case 2:
        case 4:
            // Handle states 2 and 4 with common update
            doUpdate(thisPointer);
            return;

        case 3:
            // Reset state first, then update
            resetState();
            doUpdate(thisPointer);
            return;

        default:
            // Default handler: call default action then update
            handleDefaultState(0);   // parameter likely zero
            doUpdate(thisPointer);
            return;

        case 9:
            // Special handler for state 9
            handleState9();
            doUpdate(thisPointer);
            return;
    }
}