// FUNC_NAME: NetConnection::~NetConnection
// Address: 0x006ae3f0
// Destructor for a network connection object. Removes the connection from an 
// intrusive linked list (node at +0x48) and clears a packet queue (at +0x27c).

class SimObject; // forward declaration
class PacketQueue; 

class NetConnection : public SimObject {
    // +0x48: Node* mConnectionNode;       // embedded node for global connection list
    // +0x4c: Node* mConnectionNext;       // next pointer within the list (part of node)
    // +0x27c: PacketQueue* mPacketQueue; // outgoing packet queue
};

void __thiscall NetConnection::~NetConnection(NetConnection* this) {
    // Call base class destructor (likely SimObject)
    SimObject::~SimObject(this);

    // Pointer to the embedded node (this + 0x48)
    void* nodePtr = reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x48);
    // Original code: local_10 = *(this+0x4c); (saves the next pointer)
    int savedNext = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x4c);

    // Intrusive list unlink – writes the address of the local 'nodePtr' into 
    // the next field. This is likely a debug hook or a peculiar unlinking 
    // pattern (self-loop). Actual semantics unclear.
    if (nodePtr != nullptr) {
        *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x4c) = reinterpret_cast<int*>(&nodePtr);
    }

    // Clear the packet queue (container at offset +0x27c)
    PacketQueue* queue = reinterpret_cast<PacketQueue*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x27c));
    // Call to FUN_00408a00 (likely PacketQueue::clear with second argument 0)
    PacketQueue::clear(queue, 0);

    // Free the node memory if it was allocated separately
    if (nodePtr != nullptr) {
        // Call to FUN_004daf90 (likely operator delete)
        operator delete(nodePtr);
    }
}