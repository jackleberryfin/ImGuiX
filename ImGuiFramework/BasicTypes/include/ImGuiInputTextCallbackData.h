#pragma once

#include "ImGuiContext.h"

struct ImGuiInputTextCallbackData
{
    ImGuiContext *Ctx;             // Parent UI context
    ImGuiInputTextFlags EventFlag; // One ImGuiInputTextFlags_Callback*    // Read-only
    ImGuiInputTextFlags Flags;     // What user passed to InputText()      // Read-only
    void *UserData;                // What user passed to InputText()      // Read-only

    // Arguments for the different callback events
    // - During Resize callback, Buf will be same as your input buffer.
    // - However, during Completion/History/Always callback, Buf always points to our own internal data (it is not the same as your buffer)! Changes to it will be reflected into your own buffer shortly after the callback.
    // - To modify the text buffer in a callback, prefer using the InsertChars() / DeleteChars() function. InsertChars() will take care of calling the resize callback if necessary.
    // - If you know your edits are not going to resize the underlying buffer allocation, you may modify the contents of 'Buf[]' directly. You need to update 'BufTextLen' accordingly (0 <= BufTextLen < BufSize) and set 'BufDirty'' to true so InputText can update its internal state.
    ImWchar EventChar;  // Character input                      // Read-write   // [CharFilter] Replace character with another one, or set to zero to drop. return 1 is equivalent to setting EventChar=0;
    ImGuiKey EventKey;  // Key pressed (Up/Down/TAB)            // Read-only    // [Completion,History]
    char *Buf;          // Text buffer                          // Read-write   // [Resize] Can replace pointer / [Completion,History,Always] Only write to pointed data, don't replace the actual pointer!
    int BufTextLen;     // Text length (in bytes)               // Read-write   // [Resize,Completion,History,Always] Exclude zero-terminator storage. In C land: == strlen(some_text), in C++ land: string.length()
    int BufSize;        // Buffer size (in bytes) = capacity+1  // Read-only    // [Resize,Completion,History,Always] Include zero-terminator storage. In C land == ARRAYSIZE(my_char_array), in C++ land: string.capacity()+1
    bool BufDirty;      // Set if you modify Buf/BufTextLen!    // Write        // [Completion,History,Always]
    int CursorPos;      //                                      // Read-write   // [Completion,History,Always]
    int SelectionStart; //                                      // Read-write   // [Completion,History,Always] == to SelectionEnd when no selection)
    int SelectionEnd;   //                                      // Read-write   // [Completion,History,Always]

    // Helper functions for text manipulation.
    // Use those function to benefit from the CallbackResize behaviors. Calling those function reset the selection.
    IMGUI_API ImGuiInputTextCallbackData();
    IMGUI_API void DeleteChars(int pos, int bytes_count);
    IMGUI_API void InsertChars(int pos, const char *text, const char *text_end = NULL);
    void SelectAll()
    {
        SelectionStart = 0;
        SelectionEnd = BufTextLen;
    }
    void ClearSelection() { SelectionStart = SelectionEnd = BufTextLen; }
    bool HasSelection() const { return SelectionStart != SelectionEnd; }
};