#pragma once
#include <iostream>
#include <string>


struct FishCategories {
    uint32_t id;
    std::string name;
};

struct Fish {
    uint32_t id;
    std::string name;
    float average_weight;
    FishCategories* fish_category_id;
};

class Table
{
public:
    virtual void AddRecord() = 0;
    virtual void RemoveRecord() = 0;
    virtual void UpdateRecord() = 0;

    virtual void PrintList() = 0;
    inline virtual void PrintRecordsNumber() = 0;
};
