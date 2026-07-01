// FUNC_NAME: ScrollBar::checkAndStartScroll
// Address: 0x0098fca0
// Compares the provided path with the expected scrollbar slider highlight sprite path,
// and if matched, triggers a scrolling effect and sets a flag.

bool __thiscall ScrollBar::checkAndStartScroll(char* path) {
    char* expectedPath;
    char* inputPath;
    int remainingChars;
    bool equal;

    expectedPath = "/tuto/mainmenu/scrollbar/slider/hspt";
    inputPath = path;
    remainingChars = 37; // length of expected path (excluding null)
    equal = true;
    do {
        if (remainingChars == 0) break;
        remainingChars--;
        equal = (*expectedPath == *inputPath);
        expectedPath++;
        inputPath++;
    } while (equal);

    if (equal) {
        // Trigger scrolling UI event
        sendUICommand("StartScrolling", 0, &globalScrollData /* +0x00d91b68 */, 0);
        // Set scrolling active flag at offset +0x186
        this->scrollActive = 1;
    }
    return equal;
}