// FUNC_NAME: AudioSource::play
// Address: 0x004df890
// Role: If internal audio object exists, delegate play call to it with given parameter

class AudioSource {
    int* mInternalObject; // +0x00: pointer to internal audio resource or handle
public:
    void play(unsigned int param) {
        if (mInternalObject != nullptr) {
            FUN_0051c530(mInternalObject, param); // Internal sound play function
        }
    }
};