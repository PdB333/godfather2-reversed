// FUNC_NAME: StreamHandler::process

struct StreamObject;

struct DefaultStreamData {
    uint64_t data1;   // 8 bytes
    int32_t data2;    // 4 bytes
};

struct DataItem {
    void** vtable;
    // ... other fields
};

// External helper functions (implemented elsewhere)
extern bool checkStreamMode();
extern DefaultStreamData* getDefaultStreamData();
extern DataItem* findDataItem(int index, uint hashConst);
extern uint getCurrentTime();  // returns current timestamp or pointer
extern void handleCompletion();

// Stream object methods
extern bool StreamObject_isReady(StreamObject* self);
extern void StreamObject_setData(StreamObject* self, const DefaultStreamData* data);
extern void StreamObject_setData(StreamObject* self, const void* data); // overloaded for int/ptr
extern void StreamObject_setExtraData(StreamObject* self, uint extra);

// Structure for this pointer
struct StreamHandler {
    void (*onError)(StreamObject* stream, int errorCode, int userData); // +0x00
    int userData;                                                      // +0x04
    int index;                                                         // +0x10 (param_1[4])
    StreamObject* stream;                                              // +0x18 (param_1[6])
    uint flags;                                                        // +0x2C (param_1[0xb])
    byte unk35;                                                        // +0x35
};

bool __fastcall StreamHandler::process() {
    if (this->stream == nullptr) {
        return false;
    }

    if (!StreamObject_isReady(this->stream)) {
        if (this->onError != nullptr) {
            this->onError(this->stream, 0, this->userData);
        }
        return false;
    }

    this->unk35 = 0;

    uint f = this->flags;

    // Bit 6: use default data directly
    if ((f & 0x40) == 0) {
        // Bit 7: custom data via mode check
        if ((int8_t)(f & 0xFF) < 0) { // equivalent to (f & 0x80) != 0
            if (!checkStreamMode()) {
                DefaultStreamData* defaultData = getDefaultStreamData();
                StreamObject_setData(this->stream, defaultData);
            }
        }
        // Bit 2: indexed data
        else if (this->index != 0 && this->index != 0x48 && (f & 4) != 0) {
            int adjustedIndex = (this->index == 0) ? 0 : this->index - 0x48;
            DataItem* item = findDataItem(adjustedIndex, 0x38523fc3);
            if (item != nullptr) {
                uint timePtr = getCurrentTime();                   // returns pointer to a time field
                StreamObject_setData(this->stream, (void*)(timePtr + 0x30));

                // Bit 5: skip extra data
                if ((f & 0x20) == 0) {
                    // Call virtual function at vtable+0x58 (index 22)
                    int (*getExtraFunc)() = (int (*)())item->vtable[22]; // adjust index as needed
                    uint extra = getExtraFunc();
                    StreamObject_setExtraData(this->stream, extra);
                }
            }
        }
    } else {
        // Bit 6 set: always use default data
        DefaultStreamData* defaultData = getDefaultStreamData();
        StreamObject_setData(this->stream, defaultData);
    }

    // Bit 3: completion handler
    if ((f & 8) != 0) {
        handleCompletion();
    }

    return true;
}