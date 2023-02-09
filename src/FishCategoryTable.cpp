#include "FishCategoryTable.h"

inline int FishCategoriesTable::GetRecordId()
{
    int record_id;
    std::cout << "Enter record 'id': \n";
    std::cin >> record_id;
    return std::abs(record_id);
}

FishCategoriesTable::FishCategoriesTable()
    : id(0)
{
}

FishCategoriesTable::~FishCategoriesTable()
{
}

void FishCategoriesTable::AddRecord()
{
    char name[50];

    std::cout << "Enter the name of your category: 'name'\n\n";
    std::cin >> name;

    id++;
    FishCategories* cat = new FishCategories{ id, name };
    m_FishCategories.push_back(cat);
}

void FishCategoriesTable::RemoveRecord()
{
    int record_id = GetRecordId();

    for (auto it = m_FishCategories.begin(); it != m_FishCategories.end(); ++it)
    {
        if ((*it)->id == record_id)
        {
            m_FishCategories.erase(it);
            return;
        }
    }

    std::cout << "You don't have category with id: '" << record_id << "'. Your last category id: '" <<
        m_FishCategories.size() << "'.\n";
}

void FishCategoriesTable::UpdateRecord()
{
    int record_id = GetRecordId();

    char name[50];

    std::cout << "Enter the name of your category: 'name'\n\n";
    std::cin >> name;

    for (auto it = m_FishCategories.begin(); it != m_FishCategories.end(); ++it)
    {
        if ((*it)->id == record_id)
        {
            (*it)->name = name;
            return;
        }
    }

    std::cout << "You don't have category with id: '" << record_id << "'. Your last category id: '" <<
        m_FishCategories.size() << "'.\n";
}

void FishCategoriesTable::PrintList()
{
    std::cout << "FISH CATEGORIES:\n";
    std::cout << "id\t\t\t\tname\n";
    for (auto el : m_FishCategories)
        std::cout << el->id << "\t\t\t\t" << el->name << "\n";
}
