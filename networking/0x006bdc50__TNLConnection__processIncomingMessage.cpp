// FUNC_NAME: TNLConnection::processIncomingMessage

#define kMessageType_ActionRequest  0x0120e93c
#define kMessageType_EntityUpdate   0x0112a6ac
#define kMessageType_Timeout        0x012067dc

// External helper functions (stubs - actual implementations elsewhere)
void readMessageType(int* param_2);                          // 0x0046c6a0
void acknowledgeMessage(int* messageTypePtr);                // 0x004086d0
void rejectMessage(int* messageTypePtr);                     // 0x00408680
Controller* getControllerFromSlot(int slotIndex);            // 0x006bca80
bool isActiveRequest();                                       // 0x006bdb50
int resolveEntityHandle(int handle);                         // 0x006bda40
bool isValidOwnedEntity(int entity);                         // 0x006bdc10
void startCancelTimeout();                                    // 0x006bd750
void resetMessageState();                                     // 0x006bd730

class Controller {
public:
    int vtable;
    // vtable +0x1c: virtual void handleIncomingAction(Controller* parent);
};

class TNLConnection {
public:
    // Offset 0x24: slot index for controller lookup
    int currentSlotIndex;              // +0x24
    // Offset 0x34: expected message type for ongoing transaction
    int expectedMessageType;           // +0x34
    // Offset 0x3c: alternative expected message type
    int altExpectedMessageType;        // +0x3c
    // Offset 0x94: timeout flag
    int timeoutActive;                 // +0x94
};

void __thiscall TNLConnection::processIncomingMessage(int* param_2) {
    int messageType;
    Controller* ctrl;
    int entityHandle;

    readMessageType(param_2);
    messageType = *param_2;

    if (messageType == kMessageType_ActionRequest) {
        acknowledgeMessage(&kMessageType_ActionRequest);
        if (this->expectedMessageType == 0) {
            ctrl = getControllerFromSlot(this->currentSlotIndex);
            if (ctrl == nullptr) {
                rejectMessage(&kMessageType_EntityUpdate);
                return;
            }
            if (isActiveRequest()) {
                // Call virtual function at vtable+0x1c on parent object (this - 0x3c)
                ((void (__thiscall*)(TNLConnection*))ctrl->vtable[0x1c])((TNLConnection*)((char*)this - 0x3c));
                return;
            }
        }
    }
    else if (messageType == kMessageType_EntityUpdate) {
        entityHandle = resolveEntityHandle(param_2[1]);
        if ((entityHandle != 0) && isValidOwnedEntity(entityHandle)) {
            acknowledgeMessage(&kMessageType_EntityUpdate);
            return;
        }
    }
    else if (messageType == this->expectedMessageType) {
        if (isActiveRequest()) {
            ctrl = getControllerFromSlot(this->currentSlotIndex);
            if (ctrl == nullptr) {
                rejectMessage(&kMessageType_EntityUpdate);
                return;
            }
            if (isActiveRequest()) {
                ((void (__thiscall*)(TNLConnection*))ctrl->vtable[0x1c])((TNLConnection*)((char*)this - 0x3c));
                return;
            }
        }
    }
    else {
        // Must equal altExpectedMessageType or kMessageType_Timeout
        if (messageType != this->altExpectedMessageType) {
            if (messageType != kMessageType_Timeout) {
                return; // Unknown message type, ignore
            }
            // Timeout handling
            if (this->timeoutActive != 0) {
                startCancelTimeout();
            }
        }
        resetMessageState();
    }
    return;
}