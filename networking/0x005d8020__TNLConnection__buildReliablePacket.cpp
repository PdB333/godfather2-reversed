// FUNC_NAME: TNLConnection::buildReliablePacket
// Function address: 0x005d8020
// This function builds a reliable packet by serializing a set of notifier objects into a buffer.
// It operates on global state representing the current reliable packet buffer and notifier queue.

// Global state (likely from a TNL Connection instance)
static int s_packetCount = DAT_012056bc;           // Number of notifiers to serialize
static char s_isInitialPacket = DAT_01205656;      // Flag indicating if this is the first packet
static unsigned int s_maxPacketCount = DAT_01205684; // Max allowed notifiers in a packet
static BufferContext* s_bufferContext = (BufferContext*)DAT_01206880; // Buffer writer state
static unsigned int s_notifierData = DAT_0122221c; // Some data to attach to a notifier

// Notifier type identifiers (vtables or type IDs)
static const void* NOTIFIER_TYPE_A = &PTR_LAB_01126c08;
static const void* NOTIFIER_TYPE_B = &PTR_LAB_01126b40;
static const void* NOTIFIER_TYPE_C = &PTR_LAB_01126eec;

// Forward declarations for callees (external)
extern void FUN_005d5880(void* buffer, unsigned int size); // Initialize/reset buffer?
extern void FUN_005d56f0(void);                              // Finalize packet?
extern void FUN_005d5d40(void);                              // Send or queue packet?

// Represents the buffer writer state at offset +0x14
struct BufferWriter {
    unsigned int* writePos; // Current write position
    // Other fields omitted
};

void TNLConnection::buildReliablePacket()
{
    unsigned int maxCount = s_maxPacketCount;
    char isInit = s_isInitialPacket;

    // Only proceed if there are notifiers to send
    if (s_packetCount > 0) {
        // If this is the very first packet, handle initialization
        if (s_isInitialPacket == 0) {
            // Get the buffer writer from the context
            BufferWriter* writer = (BufferWriter*)(s_bufferContext + 0x14);
            
            // Write a notifier of type A with payload 0
            *writer->writePos = (unsigned int)NOTIFIER_TYPE_A;
            writer->writePos++;
            *writer->writePos = 0;
            writer->writePos = (unsigned int*)(((unsigned int)writer->writePos + 4) & 0xFFFFFFFC); // Align to 4 bytes
        }
        else if (maxCount > 1) {
            // If not the first packet and multiple notifiers allowed, reset some state
            FUN_005d5880(DAT_0119da54, 0xc0); // Likely clearing a buffer
            FUN_005d56f0(); // Possibly finalizing previous packet
            DAT_00f1765c = 0xFFFFFFFE; // Some global marker
        }

        BufferWriter* writer = (BufferWriter*)(s_bufferContext + 0x14);
        
        // Write a notifier of type B with payload 1
        *writer->writePos = (unsigned int)NOTIFIER_TYPE_B;
        writer->writePos++;
        *writer->writePos = 1;
        writer->writePos = (unsigned int*)(((unsigned int)writer->writePos + 4) & 0xFFFFFFFC);

        // Write a notifier of type C with the data from s_notifierData
        *writer->writePos = (unsigned int)NOTIFIER_TYPE_C;
        writer->writePos++;
        *writer->writePos = s_notifierData;
        writer->writePos++;

        // Finalize and send the packet
        FUN_005d5d40();

        // Reset the packet counter
        s_packetCount = 0;

        // If this was a non-initial packet and more notifiers are allowed, add another notifier of type A with payload 1
        if (isInit == 0 && maxCount > 1) {
            *writer->writePos = (unsigned int)NOTIFIER_TYPE_A;
            writer->writePos++;
            *writer->writePos = 1;
            writer->writePos = (unsigned int*)(((unsigned int)writer->writePos + 4) & 0xFFFFFFFC);
        }

        // Add a final notifier of type B with payload 0
        *writer->writePos = (unsigned int)NOTIFIER_TYPE_B;
        writer->writePos++;
        *writer->writePos = 0;
        writer->writePos = (unsigned int*)(((unsigned int)writer->writePos + 4) & 0xFFFFFFFC);
    }
}