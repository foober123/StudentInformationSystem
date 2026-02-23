#include <imgui.h>
#include <cctype>

static int LettersDashAndPeriodCallback(ImGuiInputTextCallbackData* data)
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter)
    {
        ImWchar c = data->EventChar;

        if (isalpha(c) || c == '-' || c == '.') 
            return 0;

        return 1; 
    }
    return 0;
}
