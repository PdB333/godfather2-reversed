// FUNC_NAME: TimerManager::scheduleTimer
class TimerManager {
public:
    // Virtual function at vtable offset 8, likely adds a timer with callback info
    virtual void addTimer(void *userContext, struct CallbackInfo *info, int flags, unsigned int delayMs) = 0;
};

// Callback info structure passed to addTimer
struct CallbackInfo {
    void (*callback)();      // +0x0: function to call on timer fire
    int callbackId;          // +0x4: identifier for the callback
    void *contextData;       // +0x8: additional context (address 0x568a70)
    int flags;               // +0xC: flags (0)
};

void __fastcall TimerManager::scheduleTimer(TimerManager *this, int callbackId, void *userContext)
{
    struct CallbackInfo info;
    info.callback = (void (*)())0x00568ca0;   // address of the callback function
    info.callbackId = callbackId;              // stored from second parameter
    info.contextData = (void *)0x00568a70;     // fixed context data (likely another callback or object)
    info.flags = 0;

    // Schedule the timer with a 10-second delay via the virtual function
    this->addTimer(userContext, &info, 0, 10000);
}