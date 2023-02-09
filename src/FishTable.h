#pragma once
#include "Table.h"
#include "FishCategoryTable.h"
#include <vector>


class FishTable : public Table {
public:
    FishTable(FishCategoriesTable* categories);
    ~FishTable();

    virtual void AddRecord() override;
    virtual void RemoveRecord() override;
    virtual void UpdateRecord() override;

    virtual void PrintList() override;
    inline virtual void PrintRecordsNumber() override { std::cout << "Number of records: " << m_Fish.size() << std::endl; }

private:
    inline int GetRecordId();

private:
    uint32_t id;
    std::vector<Fish*> m_Fish;
    FishCategoriesTable* m_Categories;
};
