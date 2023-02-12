#pragma once
#include "Table.h"
#include "FishCategoriesTable.h"
#include <map>


class FishTable : public Table {
public:
    FishTable(FishCategoriesTable* categories);
    ~FishTable();

    virtual void AddRecord() override;
    virtual void RemoveRecord() override;
    virtual void UpdateRecord() override;

    virtual void PrintList() override;
    inline virtual void PrintRecordsNumber() override { std::cout << "Number of records: " << m_Fish.size() << std::endl; }

    inline std::map<int, Fish*> GetFish() { return m_Fish; }

private:
    inline virtual int GetRecordId() override;
    inline virtual int GoBack() override;
    virtual void DeleteRecordFromFile(int record_id) override;
    virtual void ReplaceRecordInFile(int record_id, std::string to_update) override;

private:
    uint32_t id;
    std::map<int, Fish*> m_Fish;
    FishCategoriesTable* m_Categories;
};
