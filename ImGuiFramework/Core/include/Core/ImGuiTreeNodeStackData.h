#pragma once

#include "Basic/ImTypeDefs.h"
#include "Basic/ImRect.h"

// Store data emitted by TreeNode() for usage by TreePop()
// - To implement ImGuiTreeNodeFlags_NavLeftJumpsBackHere: store the minimum amount of data
//   which we can't infer in TreePop(), to perform the equivalent of NavApplyItemToResult().
//   Only stored when the node is a potential candidate for landing on a Left arrow jump.
struct ImGuiTreeNodeStackData
{
    ImGuiID ID;
    ImGuiTreeNodeFlags TreeFlags;
    ImGuiItemFlags InFlags; // Used for nav landing
    ImRect NavRect;         // Used for nav landing
};