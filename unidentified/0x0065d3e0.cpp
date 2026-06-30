// NET_SESSION_PROCESS_DATA: NetSession::processIncomingPacket
// Reconstructed for Godfather 2 (EA EARS engine, x86)
// Address: 0x0065d3e0
// Uses: NetSession singleton, connection check, optional data transform, critical section

#include <windows.h>

// Forward declarations
class NetSession;
class Connection;
class DataTransform;

// Global singleton accessor (FUN_00ad8d40)
NetSession* NetSession::getInstance();

class NetSession {
public:
    // Vtable layout assumed:
    // +0x34: getActiveConnection() -> Connection*
    // (other virtuals not shown)
    virtual Connection* getActiveConnection() = 0; // offset 0x34
};

class Connection {
public:
    // Vtable layout:
    // +0x24: isActive() -> bool
    virtual bool isActive() = 0; // offset 0x24
};

class DataTransform {
public:
    // Vtable layout (offset relative to DataTransform vtable):
    // +4: setData(char* src, char* dst) -> void  (offset 0x4)
    // +8: testData(char* data, uint32_t size) -> bool (offset 0x8)
    // +0x10: transformData(char* src, uint32_t srcSize, char* dst, uint32_t* dstSize) -> void (offset 0x10)
    virtual void setData(char* src, char* dst) = 0; // offset +4
    virtual bool testData(char* data, uint32_t size) = 0; // offset +8
    virtual void transformData(char* data, uint32_t size, char* outBuf, uint32_t& outSize) = 0; // offset +0x10
};

// Internal function (FUN_0065d730) processing the data after critical section
// Likely sends or queues the data on the connection
void processData(NetSession* session, char* data, uint32_t size); // forward decl

void __thiscall NetSession::processIncomingPacket(void* thisPtr, char* data, uint32_t size)
{
    NetSession* self = static_cast<NetSession*>(thisPtr);
    DataTransform* filter = *(DataTransform**)(reinterpret_cast<char*>(self) + 0x6c);

    // Get singleton instance (likely NetSession::getInstance)
    NetSession* globalSession = NetSession::getInstance();
    if (!globalSession)
        return;

    // Get the active connection from the singleton
    Connection* conn = globalSession->getActiveConnection();
    if (!conn)
        return;

    // Check if connection is active
    if (!conn->isActive())
        return;

    // Local buffer for possible transformation (alloca probe size 16)
    char transformedData[16]; // __alloca_probe_16 handles alignment
    char* dataToProcess = data;

    // If a transform filter exists and its test passes, transform the data
    if (filter && filter->testData(data, size)) {
        // First transform the data into local buffer
        uint32_t transformedSize;
        filter->transformData(data, size, transformedData, transformedSize);
        // Then set the data pointer to the transformed buffer
        filter->setData(data, transformedData);
        dataToProcess = transformedData;
    }

    // Enter critical section (member at offset +0xc)
    CRITICAL_SECTION* cs = reinterpret_cast<CRITICAL_SECTION*>(reinterpret_cast<char*>(self) + 0xc);
    EnterCriticalSection(cs);

    // Process the data (actual work)
    processData(self, dataToProcess, size);

    LeaveCriticalSection(cs);
}