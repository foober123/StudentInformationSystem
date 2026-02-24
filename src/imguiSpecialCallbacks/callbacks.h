#include <imgui.h>
#include <cctype>

static int LetterAndDashCallback(ImGuiInputTextCallbackData* data)
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter)
    {
        ImWchar c = data->EventChar;

        if (isalpha(c) || c == '-') 
            return 0;

        return 1; 
    }
    return 0;
}
