// FUNC_NAME: UINode::resetSubNode
void __fastcall UINode::resetSubNode(UINode* this)
{
    // Pseudocode reconstruction based on decompiled assembly
    // this: ecx (param_1)
    // +0x58: pointer to sub-container node (UINode*)
    UINode* pContainer = *(UINode**)((char*)this + 0x58);
    
    // Get global scene manager singleton (FUN_007ff880)
    CSceneManager* pSceneMgr = GetSceneManager();
    
    // Stack locals for temporary data
    int local_10 = 0;
    int local_c = 0;
    int local_8 = 0;
    int local_4 = 0;
    
    // Virtual calls on scene manager (offsets 0x1f8, 0x204)
    // These likely begin/end a frame or push/pop context
    (*(void(__thiscall**)(CSceneManager*))((int*)pSceneMgr + 0x1f8 / 4))(pSceneMgr);
    (*(void(__thiscall**)(CSceneManager*))((int*)pSceneMgr + 0x204 / 4))(pSceneMgr);
    
    // Virtual call on pContainer: clear or reset (offset 0x1b4)
    (*(void(__thiscall**)(UINode*))((int*)pContainer + 0x1b4 / 4))(pContainer);
    
    // Find the root node named "m_root" (offset 0x94)
    UINode* pRootNode = nullptr;
    (*(void(__thiscall**)(UINode*, UINode**, const char*))((int*)pContainer + 0x94 / 4))(pContainer, &pRootNode, "m_root");
    
    // Attach or insert the container node relative to root (offset 0x80)
    // Signature: void addChild(CSceneManager* mgr, UINode** child, UINode** sibling, int flags, int something)
    (*(void(__thiscall**)(UINode*, CSceneManager*, UINode**, UINode**, int, int))((int*)pContainer + 0x80 / 4))(pContainer, pSceneMgr, &pRootNode, &pContainer, 0, 0);
    
    // Set a character flag at offset 0x782 (e.g., ' ' space)
    *(char*)((char*)pContainer + 0x782) = 0x20;
}