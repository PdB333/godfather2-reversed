// Xbox PDB: EARS_Apt_UIConnections_CollectCurrentRewardInfo
// FUNC_NAME: RewardManager::updateCurrentReward
// Address: 0x009218e0
// Role: Processes the next pending reward from the queue and updates reward display state.

typedef struct {
    void** items; // array of 8-byte entries (pointer + data)
    int    count;
    int    reserved;
} RewardListIterator;

// External functions (declarations)
void getRewardList(RewardListIterator* it);
void scriptCall(const char* func, int arg1, const char* arg2, int arg3);
int  getRewardUIInstance(); // FUN_00891980
void attachRewardToUI(int uiObj); // FUN_00921430
void destroyUIElement(void* ui); // FUN_004daf90
void releaseRewardList(void* list); // FUN_009c8f10

void __fastcall RewardManager::updateCurrentReward()
{
    RewardListIterator iter;
    getRewardList(&iter); // initializes iter with current reward queue

    void* rewardList = iter.items;
    int   count      = iter.count;

    int currentIndex = *(int*)((char*)this + 0x74); // m_currentRewardIndex

    if (currentIndex < count)
    {
        // Reward entry is 8 bytes: [object pointer (4)] [data (4)]
        struct RewardEntry {
            void* object;
            int   data;
        };
        RewardEntry* entries = (RewardEntry*)rewardList;
        RewardEntry* entry   = &entries[currentIndex];

        *(int*)((char*)this + 0x9c) = entry->data; // m_rewardData

        void* rewardObject = entry->object;
        // Read position from reward object (offsets 0x80, 0x84)
        float x = *(float*)((char*)rewardObject + 0x80);
        float y = *(float*)((char*)rewardObject + 0x84);
        *(float*)((char*)this + 0x88) = x; // m_rewardPosX
        *(float*)((char*)this + 0x8c) = y; // m_rewardPosY

        bool isNew = (*(int*)((char*)rewardObject + 0x160) == 0); // flag: 0 = new, non-zero = seen
        *(bool*)((char*)this + 0xa0) = isNew; // m_bIsNewReward

        // Trigger Lua/script for reward UI
        scriptCall("ShowCurrentReward", 0, &DAT_00d861fc, 0);

        if (isNew || (getRewardUIInstance() == 0))
        {
            // Destroy existing reward UI if any
            void* uiElement = *(void**)((char*)this + 0xa4); // m_pRewardUI
            if (uiElement != 0)
            {
                destroyUIElement(uiElement);
                *(void**)((char*)this + 0xa4) = 0;
            }
        }
        else
        {
            int uiObj = getRewardUIInstance();
            attachRewardToUI(uiObj);
        }
    }

    if (rewardList != 0)
    {
        releaseRewardList(rewardList);
    }
}