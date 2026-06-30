// FUNC_NAME: AudioManager::processAudioCommand

struct SoundRequest {
    short m_soundId;          // +0x00
    float m_volume;           // +0x02 (actually offset 2, but aligned? Maybe packed)
    int m_categoryIndex;      // +0x04
    unsigned short m_flags;   // +0x06
    void (*m_finishCallback)(void*, int); // +0x08 (function pointer, called on finish)
    int m_param;              // +0x0C
    unsigned short m_priority;// +0x0E (actually offset 0x0E? But used as ushort? See note)
    unsigned char m_priorityByte; // +0x0E as byte used in comparison
};

struct SoundInstance {
    SoundInstance* m_next;            // +0x00 (next in linked list)
    SoundInstance* m_prev;            // +0x04 (prev or unused, set to 0)
    int m_unknown08;                  // +0x08 (unused, set to 0)
    int m_unknown0C;                  // +0x0C (unused, set to 0)
    unsigned short m_flagsWord;       // +0x10 (flags from request, offset 16)
    unsigned char m_flagsByte;        // +0x12 (flags, bit 0x10 checked)
    unsigned char m_active;           // +0x13? Actually from code: *(byte*)(puVar6+4) & 0x10 => offset 16? Wait, that's the short word. Confusing.
    int m_unknown14;                  // +0x14 (set to 0)
    int m_unknown18;                  // +0x18 (set to 0)
    unsigned char m_priorityLevel;    // +0x1E (byte at offset 30)
    unsigned char m_unknown1C;        // +0x1C (unused)
    unsigned char m_unknown1D;        // +0x1D (set to 0)
    int m_unknown20;                  // +0x20 (set to 0)
    void (*m_callback)(void*, int);   // +0x24 (function pointer, offset 36)
    int m_param;                      // +0x28 (offset 40)
    int m_unknown2C;                  // +0x2C (offset 44, set from request offset 0x0C)
    int m_categoryIndex;              // +0x30 (offset 48, set from request offset 0x04)
    int m_soundId;                    // +0x34 (offset 52, set from request offset 0x00? Actually short)
    short m_extraField;               // +0x42 (offset 66, set to 0)
    // Total size maybe 0x44 or more
};

// Global state
SoundInstance* g_soundPoolHead = nullptr;           // DAT_011a0ec0 (per category? Actually array of heads)
SoundInstance* g_soundPoolTail = nullptr;           // DAT_011a0ec4 (array of tails)
unsigned short g_soundPoolCount = 0;                // DAT_011a0ec8 (array of counts? Actually offset used as *short)
unsigned short g_soundPoolMax = 0;                  // DAT_011a0eca (array of max counts)
SoundInstance* g_freeListHead = nullptr;            // DAT_011a0ed8
int g_freeListCount = 0;                             // DAT_011a0edc
int g_activeSoundCount = 0;                          // DAT_011a0ee4
void** g_soundManagerVtable = nullptr;              // DAT_01223510 (singleton vtable pointer)

// External functions
void finalizeSound(SoundInstance* instance);        // FUN_005dbc10
void startSound(SoundInstance* instance);           // FUN_005f57b0?
void abortSound(SoundInstance* instance);           // FUN_005f16b0?

SoundInstance* AudioManager::processAudioCommand()
{
    SoundInstance* activeInstance = nullptr;
    bool newSoundStarted = false;
    
    if (g_activeSoundCount < 9) {
        unsigned char requestPriority = request->m_priorityByte; // from request struct offset 0x0E
        SoundInstance* candidate = nullptr;
        SoundInstance* prev = nullptr;
        
        if (g_soundPoolHead != nullptr) {
            SoundInstance* current = g_soundPoolHead;
            do {
                // Check if category index differs and instance is not busy (bit 0x10 clear)
                if (request->m_categoryIndex != current->m_categoryIndex &&
                    (current->m_flagsByte & 0x10) == 0 &&
                    current->m_priorityLevel <= requestPriority) {
                    candidate = current;  // last such instance? Actually loop picks highest priority?
                    prev = candidate;     // bug? should be tracking previous for removal?
                    requestPriority = current->m_priorityLevel;
                }
                current = current->m_next;
            } while (current != nullptr);
            
            if (candidate != nullptr) {
                if (candidate->m_callback != nullptr) {
                    candidate->m_callback(candidate, 1);  // stop current sound
                }
                finalizeSound(candidate);
                
                if (g_activeSoundCount == 0) {
                    // Call vtable method at offset 0x20 with sound ID from candidate
                    typedef void (*SoundMethod)(unsigned short);
                    SoundMethod method = (SoundMethod)(*(int*)g_soundManagerVtable + 0x20);
                    method(candidate->m_soundId);
                    startSound(candidate);  // start new sound
                    newSoundStarted = true;
                } else {
                    abortSound(candidate);
                    activeInstance = nullptr;
                }
            }
        }
    }
    
    // Check if there is a free node to reuse
    if (g_activeSoundCount != 0 && g_freeListCount != 0 && g_freeListHead != (SoundInstance*)&g_freeListHead) {
        g_activeSoundCount--;
        activeInstance = g_freeListHead;
        g_freeListHead = g_freeListHead->m_next;
    }
    
    if (activeInstance == nullptr) {
        // No free node, create a new one? Actually call finalize with request data
        finalizeSound(request->m_soundId, request->m_volume, request->m_flags, request->m_param, request->m_param2);
    } else {
        // Fill the reused node with request data
        int category = request->m_categoryIndex;
        activeInstance->m_priorityLevel = request->m_priorityByte; // offset 0x1E <-- from request offset 0x0E? Actually they assign *(char*)(puVar9+0x1E) = (char)unaff_EDI[0x0E]; (that's byte at request offset 0x1C? Wait - see note)
        // Note: unaff_EDI[0x0E] is a short? Actually they cast to char, so offset 0x1C in request? To match node offset 0x1E.
        // This mapping is distorted. We simplify.
        
        activeInstance->m_callback = request->m_callback;
        activeInstance->m_param = request->m_param;
        activeInstance->m_soundId = request->m_soundId;
        
        unsigned short flags = request->m_flags;
        activeInstance->m_flagsWord = flags;
        activeInstance->m_flagsByte = 0;
        activeInstance->m_active = 0;
        // ... More assignments omitted for brevity
    }
    
    return activeInstance;
}