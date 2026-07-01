// FUNC_NAME: PresentationManager::stopPresentationSequence
void __cdecl PresentationManager::stopPresentationSequence(int sequenceId, Presentation* presentation, char immediate)
{
    int local_c;
    int local_8;
    char local_4;

    if (immediate == '\0') {
        // Get the internal object from presentation+0x10 (likely a source handle)
        int sourcePtr = FUN_00446100(*(int*)(presentation + 0x10), 0);
        if (sequenceId == -1) {
            // Stop all: zero out the sequence state at sourcePtr+0x1b4
            local_c = *(int*)(sourcePtr + 0x1b4);
            local_8 = 0;
            local_4 = 0;
            FUN_00408a00(&local_c, 0);  // clear the struct
        } else {
            // Stop specific sequence: reset queue and apply changes
            FUN_00408680(&DAT_01130248);
            FUN_009213c0();
        }
    }
    if (presentation != 0) {
        // Release resources and destroy the presentation object
        FUN_009823b0();
        FUN_009c8eb0(presentation);
    }
}