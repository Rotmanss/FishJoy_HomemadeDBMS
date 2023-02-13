#pragma once
#include "Table.h"
#include "GarbageCollector.h"
#include <map>


class FishCategoriesTable : public Table {
public:
    FishCategoriesTable(GarbageCollector* garbage);
    ~FishCategoriesTable();

    virtual void AddRecord() override;
    virtual void RemoveRecord() override;
    virtual void UpdateRecord() override;

    virtual void PrintList() override;
    inline virtual void PrintRecordsNumber() override;

    inline std::map<int, FishCategories*> GetFishCategories() { return m_FishCategories; }

private:
    inline virtual int GetRecordId() override;
    inline virtual int GoBack() override;
    virtual void DeleteRecordFromFile(int record_id) override;
    virtual void ReplaceRecordInFile(int record_id, std::string to_update) override;

private:
    void ClearDependencies(int record_id);

private:
    uint32_t id;
    std::map<int, FishCategories*> m_FishCategories;
    GarbageCollector* m_Garbage;
};
