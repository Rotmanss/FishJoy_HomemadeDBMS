#pragma once
#include "Table.h"
#include <vector>


class FishCategoriesTable : public Table {
public:
    FishCategoriesTable();
    ~FishCategoriesTable();

    virtual void AddRecord() override;
    virtual void RemoveRecord() override;
    virtual void UpdateRecord() override;

    virtual void PrintList() override;
    inline virtual void PrintRecordsNumber() override { std::cout << "Number of records: " << m_FishCategories.size() << std::endl; }

    inline std::vector<FishCategories*> GetFishCategories() { return m_FishCategories; }

private:
    inline int GetRecordId();

private:
    uint32_t id;
    std::vector<FishCategories*> m_FishCategories;
};
