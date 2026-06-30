// FUNC_NAME: ChatterPlaybackManager::ChatterPlaybackManager
// Address: 0x006f0ff0 – Constructor for the global chatter playback manager singleton.
// Handles allocation of 5 speaker slots and 100 message entries, registration of chat toggle console messages.

class ChatterPlaybackManager {
public:
    // Vtable at +0x00
    // +0x04: m_bInitialized (int)
    // +0x08: m_unknown0 (int)
    // +0x0C: m_secondaryVTable (void*)
    // +0x10: m_ownerId (uint) – e.g. controller or engine instance ID
    // +0x14: m_chatterMessages (ChatterMessageEntry*) – pointer to array of 100 entries
    // +0x18: m_chatterMessagesEnd (ChatterMessageEntry*)
    // +0x1C: m_chatterMessagesCursor (ChatterMessageEntry*) – write cursor
    // +0x20: m_messageCount (int)
    // +0x24: m_nextMessageIndex (int)
    // +0x28: m_playbackActive (int)
    // +0x2C: m_unknown1 (int)
    // +0x30: m_unknown2 (int)
    // +0x34: m_unknown3 (int)
    // +0x38: m_unknown4 (int)
    // +0x3C: m_unknown5 (int)
    // +0x40: m_unknown6 (int)
    // +0x44: m_unknown7 (int)
    // +0x48: m_unknown8 (int)
    // +0x4C: m_unknown9 (int)
    // +0x50: m_unknown10 (int)
    // +0x54: m_unknown11 (int)
    // +0x58: m_unknown12 (int)
    // +0x5C: m_unknown13 (int)
    // +0x60: m_unknown14 (int)
    // +0x64: m_speakerSlots (ChatterSpeakerSlot*) – pointer to array of 5 slots (each 0x2C bytes)

    ChatterPlaybackManager(uint ownerId) {
        m_bInitialized = 1;
        m_unknown0 = 0;
        m_secondaryVTable = &PTR_LAB_00d60570;  // secondary vtable
        g_pChatterPlaybackManager = this;       // global singleton
        m_ownerId = ownerId;
        vtable = &PTR_FUN_00d60574;             // main vtable
        m_secondaryVTable = &PTR_LAB_00d60570;  // again? (likely set twice)
        // Virtual function table entries for playback handles:
        *(void**)((int)this + 0x24) = &PTR_FUN_00d60538;
        *(void**)((int)this + 0x44) = &PTR_FUN_00d60538;
        m_unknown4 = 0;
        m_unknown9 = 0;

        // Call a virtual function on the owner object (e.g. engine initialization)
        (**(code **)(*(int *)m_ownerId + 8))();

        // Allocate 5 speaker slots (0x2C bytes each + 4 byte count)
        int* slotBuf = (int*)HAL_Alloc(0xE0);
        if (slotBuf) {
            *slotBuf = 5;  // count
            // Initialize slots via vector constructor (calls LAB_006f0ce0 for each)
            _vector_constructor_iterator_(slotBuf + 1, 0x2C, 5, &LAB_006f0ce0);
        }
        m_speakerSlots = (ChatterSpeakerSlot*)(slotBuf ? slotBuf + 1 : nullptr);

        // Initialize each speaker slot with default values
        for (int i = 0; i < 5; i++) {
            ChatterSpeakerSlot* slot = (ChatterSpeakerSlot*)((int)m_speakerSlots + i * 0x2C);
            slot->field0 = 0;
            if (slot->field1 != 0) {
                // Release previous string (if any)
                FUN_004daf90(&slot->field1);
                slot->field1 = 0;
            }
            slot->field3 = 0;
            slot->field4 = 0;
            // Copy a default "empty" chatter item from global (FUN_006fbc40(0,0))
            ChatterEmptyItem empty;
            FUN_006fbc40(0, 0, &empty);
            slot->field5 = empty.first;
            slot->field6 = empty.second;
            FUN_006fbc70();  // reset maybe internal state
            slot->field9 = 0;
            slot->byte28 = 0;
            slot->byte29 = 0;
        }

        // Allocate 100 message entries (0x2C bytes each + 4 byte count = 0x1134)
        int* msgBuf = (int*)HAL_Alloc(0x1134);
        if (msgBuf) {
            *msgBuf = 100;  // count
            // Initialize each entry (11 ints each)
            int* entryStart = msgBuf + 7;   // skip count (1) + first 6 ints of first entry? offset to int 6
            for (int i = 99; i >= 0; i--) {
                entryStart[-3] = 0;  // int 4
                entryStart[-2] = 0;  // int 5
                entryStart[-1] = 0;  // int 6
                entryStart[0] = 0;   // int 7
                entryStart[1] = 0;   // int 8
                entryStart[2] = 0;   // int 9
                entryStart += 11;    // 44 bytes per entry
            }
            m_chatterMessages = (ChatterMessageEntry*)(msgBuf + 1);
        } else {
            m_chatterMessages = nullptr;
        }
        m_chatterMessagesEnd = m_chatterMessages;
        m_chatterMessagesCursor = m_chatterMessages;
        m_messageCount = 0;
        m_nextMessageIndex = 0;

        // Initialize all message entries via FUN_006f5320 (probably resets each)
        for (int offset = 0; offset < 0x1130; offset += 0x2C) {
            FUN_006f5320((int)m_chatterMessages + offset);
        }

        // Reinitialize cursor and counters
        m_chatterMessagesCursor = m_chatterMessagesEnd;  // same as end
        m_unknown0_again = 0;

        // Reset all other fields to zero
        m_playbackActive = 0;
        m_nextMessageIndex = 0;
        m_unknown3 = 0;
        m_unknown5 = 0;
        m_unknown6 = 0;
        m_unknown7 = 0;
        m_unknown8 = 0;
        m_unknown10 = 0;
        m_unknown11 = 0;
        m_unknown12 = 0;
        m_unknown13 = 0;
        m_unknown14 = 0;

        // Register console message handlers for chatter enable/disable
        if (s_maxChannels < 0x41) {
            int* chnlBuf = (int*)HAL_Alloc(0x100);
            if (chnlBuf) {
                if (s_channelArray) {
                    HAL_Free(s_channelArray);
                }
                s_maxChannels = 0x40;
                s_channelArray = chnlBuf;
            }
        }

        // Register "iMsgAllChatterEnabled" handler (ID 0x8000)
        int msgId = FUN_00408240(&s_msgAllChatterEnabled, "iMsgAllChatterEnabled");
        if (msgId != 0) {
            FUN_00408900(this, &s_msgAllChatterEnabled, 0x8000);
        }

        // Register "iMsgAllChatterDisabled" handler (ID 0x8000)
        int msgId2 = FUN_00408240(&s_msgAllChatterDisabled, "iMsgAllChatterDisabled");
        if (msgId2 != 0) {
            FUN_00408900(this, &s_msgAllChatterDisabled, 0x8000);
        }

        // Register another unnamed message (e.g. "iMsgAllChatterMute")
        if (s_anotherMsg != 0) {
            FUN_00408900(this, &s_anotherMsg, 0x8000);
        }
    }

private:
    // Internal structures (not fully reverse-engineered)
    struct ChatterSpeakerSlot {
        int field0;       // +0x00
        int field1;       // +0x04 (string pointer?)
        int field2;       // +0x08
        int field3;       // +0x0C
        int field4;       // +0x10
        int field5;       // +0x14
        int field6;       // +0x18
        int field7;       // +0x1C
        int field8;       // +0x20
        int field9;       // +0x24
        char byte28;      // +0x28
        char byte29;      // +0x29
        // padded to 0x2C
    };
    struct ChatterMessageEntry {
        // 11 ints = 0x2C bytes
        int d[11];
    };
    struct ChatterEmptyItem {
        int first;
        int second;
    };
};

// Global singleton pointer
ChatterPlaybackManager* g_pChatterPlaybackManager;

// Static storage for channel management (used for message subscription)
static int s_maxChannels;
static int* s_channelArray;
static int s_msgAllChatterEnabled;
static int s_msgAllChatterDisabled;
static int s_anotherMsg;