#pragma once
#include <cstdint>

struct GuiState;
class AppData;


typedef void (*InputBoxStrategy)(GuiState&, AppData&);
typedef void (*DataTableStrategy)(GuiState&, AppData&);
typedef void (*EntryDisplayStrategy)(const GuiState&, AppData&);
typedef uint32_t (GuiState::*GetSelectedId)() const;
typedef void (GuiState::*DraftSettingStrategy)(uint32_t ,AppData&);
typedef void (GuiState::*SearchStrategy)(AppData&);
typedef void (*SearchFieldComboStrategy)(GuiState&);


struct GuiStrategy{
InputBoxStrategy addEntryStrategy;
InputBoxStrategy editEntryStrategy;
InputBoxStrategy deleteEntryStrategy;
DataTableStrategy dataTableStrategy;
EntryDisplayStrategy entryDisplayStrategy;
bool (AppData::*validator)(uint32_t);
GetSelectedId IDStrategy;
DraftSettingStrategy draftSettingStrategy;
SearchStrategy searchStrategy;
SearchFieldComboStrategy searchFieldStrategy;
};


