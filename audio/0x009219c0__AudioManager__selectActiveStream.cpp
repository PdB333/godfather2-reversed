// FUNC_NAME: AudioManager::selectActiveStream
void __thiscall AudioManager::selectActiveStream(int this, int streamId)
{
    int index = getStreamIndex(streamId);
    if (index < 0) {
        if (*(int *)(this + 0xa4) != 0) {
            releaseStreamNode((int *)(this + 0xa4));
            *(int *)(this + 0xa4) = 0;
        }
    } else {
        int *poolNode = (int *)(*(int *)(this + 0x5c) + index * 8);
        int *activeNode = (int *)(this + 0xa4);
        if (activeNode != poolNode) {
            int streamData = *poolNode;
            if (*activeNode != streamData) {
                if (*activeNode != 0) {
                    releaseStreamNode(activeNode);
                }
                *activeNode = streamData;
                if (streamData != 0) {
                    *(int *)(this + 0xa8) = *(int *)(streamData + 4);
                    *(int **)(streamData + 4) = activeNode;
                }
            }
        }
        if (*(int *)(DAT_01130020 + 0x6c) != 2) {
            *(int *)(this + 0x74) = index;
            *(int *)(this + 0x58) = 0;
            return;
        }
        if (*(int *)(this + 0x58) != 0) {
            *(int *)(this + 0x74) = index;
            resetAudioSystem(0, 0);
            return;
        }
        if (*(int *)(this + 0x74) != index) {
            *(int *)(this + 0x74) = index;
            stopCurrentAudio();
            loadAudio(0);
            startStream();
            return;
        }
    }
    return;
}