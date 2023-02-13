#pragma once
#include <iostream>
#include <string>


struct FishCategories {
    uint32_t id;
    std::string name;

    bool is_published = true;
};

struct Fish {
    uint32_t id;
    std::string name;
    float average_weight;
    FishCategories* fish_category_id;

    bool is_published = true;
};

class Table
{
public:
    virtual void AddRecord() = 0;
    virtual void RemoveRecord() = 0;
    virtual void UpdateRecord() = 0;

    virtual void PrintList() = 0;
    inline virtual void PrintRecordsNumber() = 0;

private:
    inline virtual int GetRecordId() = 0;
    inline virtual int GoBack() = 0;
    virtual void DeleteRecordFromFile(int record_id) = 0;
    virtual void ReplaceRecordInFile(int record_id, std::string to_update) = 0;
};
