// FUNC_NAME: DataProcessor::processCommands
// Purpose: Parses a data stream, matches 16-byte hash patterns, and copies matching hashes into internal buffers (offsets 0x50, 0x90, 0xd0)

#include <cstdint>

// Forward declarations of engine functions (inferred from Ghidra calls)
extern void initStream(uint8_t* data);                      // FUN_00833510
extern void computeHashSeed(uint8_t* data, uint32_t seed); // FUN_0043aff0
extern char isCancelled();                                  // FUN_0043b120
extern void advanceStream();                                // FUN_0043b210
extern int32_t getCommandType();                            // FUN_0043ab70
extern uint8_t* getCurrentHash();                           // FUN_0043ab90
extern char compareHash(const uint8_t* hash1, const uint8_t* hash2, uint32_t size, const uint8_t* expected); // FUN_004d75d0
extern void copyBuffer(const uint8_t* src, uint8_t* dst);  // FUN_00823010
extern void endCommand();                                   // FUN_0043b1a0

// Static 16-byte buffers (from DAT_0112db10 and DAT_00d73414)
extern const uint8_t s_staticHash[16];    // &DAT_0112db10
extern const uint8_t s_expectedHash[16];  // &DAT_00d73414

class DataProcessor {
public:
    // Offset members (pointers to 16-byte hash buffers)
    uint8_t* m_hashBuffer0; // +0x50
    uint8_t* m_hashBuffer1; // +0x90
    uint8_t* m_hashBuffer2; // +0xd0
    // Other members may follow...

    void processCommands(uint8_t* dataStream) {
        initStream(dataStream);
        computeHashSeed(dataStream, 0xf979ebb6);
        char cancelled = isCancelled();
        do {
            if (cancelled != 0)
                return;

            advanceStream();
            int32_t cmdType = getCommandType();

            if (cmdType == 0) {
                advanceStream();
                uint8_t* hash = getCurrentHash();
                if ((compareHash(hash, s_staticHash, 0x10, s_expectedHash) != 0) ||
                    (compareHash(hash, s_staticHash, 0x10, nullptr) != 0)) {
                    copyBuffer(s_staticHash, m_hashBuffer0); // +0x50
                }
            } else if (cmdType == 1) {
                advanceStream();
                uint8_t* hash = getCurrentHash();
                if ((compareHash(hash, s_staticHash, 0x10, s_expectedHash) != 0) ||
                    (compareHash(hash, s_staticHash, 0x10, nullptr) != 0)) {
                    copyBuffer(s_staticHash, m_hashBuffer1); // +0x90
                }
            } else if (cmdType == 2) {
                advanceStream();
                uint8_t* hash = getCurrentHash();
                if ((compareHash(hash, s_staticHash, 0x10, s_expectedHash) != 0) ||
                    (compareHash(hash, s_staticHash, 0x10, nullptr) != 0)) {
                    copyBuffer(s_staticHash, m_hashBuffer2); // +0xd0
                }
            }

            endCommand();
            cancelled = isCancelled();
        } while (true);
    }
};