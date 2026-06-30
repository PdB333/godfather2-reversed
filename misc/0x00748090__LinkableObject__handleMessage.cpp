// FUNC_NAME: LinkableObject::handleMessage

// Function address: 0x00748090
// Role: Handles two message types (set link / remove link) for an intrusive linked list node.

// Known classes: None directly, but pattern matches intrusive linked list node management.

enum EMessageType : int {
    kMsgType_SetLink    = 0x1b2d5c51,  // Set link pointer message
    kMsgType_RemoveLink = 0x485311a7   // Remove/unlink message
};

// Message header (assumed structure based on usage)
struct Message {
    void** vtable;              // +0x00
    // ... other fields ...
    void*   m_pLinkTarget;      // +0x64 (offset 0x19 * 4) – pointer to be updated
    void*   m_pLinkPrev;        // +0x68 (offset 0x1A * 4) – back pointer (prev node)
    int     m_someGlobal;       // +0x60 (offset 0x18 * 4) – set to global DAT_00d640a8
    uint    m_flags;            // +0x80 (offset 0x20 * 4) – flags to OR
};

// Forward declarations of utility functions (likely from EARS framework)
void __stdcall ReleaseLinkedListNode(void* node);                 // FUN_004daf90
void __stdcall RemoveNode(void* node);                            // FUN_0075b920
void __stdcall NotifyRemoved(int globalManager);                  // FUN_0075b540 (DAT_00d5c454)

// Global variables referenced
extern int DAT_00d640a8;   // Some global constant or singleton pointer
extern int DAT_00d5c454;   // Another global (e.g., manager handle)

// This class: LinkableObject – owns an embedded node pointer at offset +0x54
class LinkableObject {
public:
    // Offset +0x54: pointer to an intrusive linked list node (which is embedded in a larger structure)
    // The full structure containing the node is assumed to be 0x48 bytes before the node pointer.
    void* m_pEmbeddedNode;   // +0x54

    void handleMessage(Message* msg) {
        int msgType = (**(int (__thiscall**)(Message*))msg->vtable)(msg); // Get unique type ID

        if (msgType == kMsgType_SetLink) {
            // Calculate the address of the containing structure from the embedded node pointer.
            // If m_pEmbeddedNode is non-null, subtract 0x48 to get the container address.
            void* container = (m_pEmbeddedNode != nullptr) ? ((char*)m_pEmbeddedNode - 0x48) : nullptr;

            // Compare with the current link target in the message.
            if (msg->m_pLinkTarget != container) {
                // Release the old link target (if any)
                if (msg->m_pLinkTarget != nullptr) {
                    ReleaseLinkedListNode(msg->m_pLinkTarget);
                }
                // Set new link target
                msg->m_pLinkTarget = container;
                // Perform intrusive list linking: set back pointer in message to previous value,
                // and update the back pointer of the new container to point to message's link field.
                if (container != nullptr) {
                    msg->m_pLinkPrev = *(void**)((char*)container + 4);
                    *(void**)((char*)container + 4) = &msg->m_pLinkTarget;
                }
            }
            // Set a global value (likely a counter or singleton reference)
            msg->m_someGlobal = DAT_00d640a8;
        }
        else if (msgType == kMsgType_RemoveLink) {
            // Unlink node: if m_pEmbeddedNode is non-null and not the magic sentinel value 0x48
            if (m_pEmbeddedNode != nullptr && m_pEmbeddedNode != (void*)0x48) {
                // Get the container address and remove the node
                void* container = (char*)m_pEmbeddedNode - 0x48;
                RemoveNode(container);
            }
            // Notify the global manager that removal occurred
            NotifyRemoved(DAT_00d5c454);
            // Set a flag on the message indicating removal processed
            msg->m_flags |= 0x400;
        }
    }
};