// FUNC_NAME: AudioManager::initializeStreams
// Address: 0x008d74a0
// Role: Initializes stereo and mono stream slots, plus fixed extra channels.
//       Fields: +0x30 = numStereoStreams, +0x3c = numMonoStreams.

void __thiscall AudioManager::initializeStreams(int this) {
    int i;
    uint j;
    uint index;

    // Initial call for a master/pre-allocated stream (stereo?)
    initializePartA();

    index = 0;
    if (*(int *)(this + 0x30) != 0) {
        do {
            i = 2;
            do {
                // Two per stereo stream (left/right or front/back?)
                initializePartA();
                i = i - 1;
            } while (i != 0);
            index = index + 1;
        } while (index < *(uint *)(this + 0x30));
    }

    j = 0;
    if (*(int *)(this + 0x3c) != 0) {
        do {
            // One call per mono stream
            initializePartB();
            j = j + 1;
        } while (j < *(uint *)(this + 0x3c));
    }

    i = 4;
    do {
        // Four extra mono/effect channels
        initializePartB();
        i = i - 1;
    } while (i != 0);

    // One additional mono/effect channel
    initializePartB();
}