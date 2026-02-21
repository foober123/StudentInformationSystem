#include <string>
#include <vector>

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last  = str.find_last_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";

    return str.substr(first, last - first + 1);
}

std::string escapeCSV(const std::string& input)
{
    bool needsQuotes = false;

    for (char c : input)
    {
        if (c == ',' || c == '"' || c == '\n')
        {
            needsQuotes = true;
            break;
        }
    }

    if (!needsQuotes)
        return input;

    std::string output = "\"";

    for (char c : input)
    {
        if (c == '"')
            output += "\"\"";  // escape quote
        else
            output += c;
    }

    output += "\"";
    return output;
}

std::vector<std::string> parseCSVLine(const std::string& line)
{
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i)
    {
        char c = line[i];

        if (c == '"')
        {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"')
            {
                field += '"'; // escaped quote
                ++i;
            }
            else
            {
                inQuotes = !inQuotes;
            }
        }
        else if (c == ',' && !inQuotes)
        {
            fields.push_back(field);
            field.clear();
        }
        else
        {
            field += c;
        }
    }

    fields.push_back(field);
    return fields;
}

