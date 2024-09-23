#pragma once

#include <cstddef>

#include "ImVector.h"
#include "ImGuiStoragePair.h"

// Helper: Key->Value storage
// Typically you don't have to worry about this since a storage is held within each Window.
// We use it to e.g. store collapse state for a tree (Int 0/1)
// This is optimized for efficient lookup (dichotomy into a contiguous buffer) and rare insertion (typically tied to user interactions aka max once a frame)
// You can use it as custom user storage for temporary values. Declare your own storage if, for example:
// - You want to manipulate the open/close state of a particular sub-tree in your interface (tree node uses Int 0/1 to store their state).
// - You want to store custom debug data easily without adding or editing structures in your code (probably not efficient, but convenient)
// Types are NOT stored, so it is up to you to make sure your Key don't collide with different types.
struct ImGuiStorage
{
    // [Internal]
    ImVector<ImGuiStoragePair> Data;

    // - Get***() functions find pair, never add/allocate. Pairs are sorted so a query is O(log N)
    // - Set***() functions find pair, insertion on demand if missing.
    // - Sorted insertion is costly, paid once. A typical frame shouldn't need to insert any new pair.
    void Clear() { Data.clear(); }
    IMGUI_API int GetInt(ImGuiID key, int default_val = 0) const;
    IMGUI_API void SetInt(ImGuiID key, int val);
    IMGUI_API bool GetBool(ImGuiID key, bool default_val = false) const;
    IMGUI_API void SetBool(ImGuiID key, bool val);
    IMGUI_API float GetFloat(ImGuiID key, float default_val = 0.0f) const;
    IMGUI_API void SetFloat(ImGuiID key, float val);
    IMGUI_API void *GetVoidPtr(ImGuiID key) const; // default_val is NULL
    IMGUI_API void SetVoidPtr(ImGuiID key, void *val);

    // - Get***Ref() functions finds pair, insert on demand if missing, return pointer. Useful if you intend to do Get+Set.
    // - References are only valid until a new value is added to the storage. Calling a Set***() function or a Get***Ref() function invalidates the pointer.
    // - A typical use case where this is convenient for quick hacking (e.g. add storage during a live Edit&Continue session if you can't modify existing struct)
    //      float* pvar = ImGui::GetFloatRef(key); ImGui::SliderFloat("var", pvar, 0, 100.0f); some_var += *pvar;
    IMGUI_API int *GetIntRef(ImGuiID key, int default_val = 0);
    IMGUI_API bool *GetBoolRef(ImGuiID key, bool default_val = false);
    IMGUI_API float *GetFloatRef(ImGuiID key, float default_val = 0.0f);
    IMGUI_API void **GetVoidPtrRef(ImGuiID key, void *default_val = NULL);

    // Advanced: for quicker full rebuild of a storage (instead of an incremental one), you may add all your contents and then sort once.
    IMGUI_API void BuildSortByKey();
    // Obsolete: use on your own storage if you know only integer are being stored (open/close all tree nodes)
    IMGUI_API void SetAllInt(int val);

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    // typedef ::ImGuiStoragePair ImGuiStoragePair;  // 1.90.8: moved type outside struct
#endif
};