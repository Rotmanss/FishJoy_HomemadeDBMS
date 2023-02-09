#include "FishTable.h"


int FishTable::GetRecordId()
{
    int record_id;
    std::cout << "Enter record 'id': \n";
    std::cin >> record_id;
    return std::abs(record_id);
}

FishTable::FishTable(FishCategoriesTable* categories)
    : m_Categories(categories), id(0)
{
}

FishTable::~FishTable()
{
}

void FishTable::AddRecord()
{
    char name[50];
    float average_weight;
    int category_id;

    std::cout << "Enter the value through space: 'name' 'average_weight' 'category_id'\n\n";
    std::cin >> name >> average_weight >> category_id;
    average_weight = std::abs(average_weight);
    category_id = std::abs(category_id);

    for (auto cat : m_Categories->GetFishCategories())
    {
        if (cat->id == category_id)
        {
            id++;
            Fish* fish = new Fish{ id, name, average_weight, cat };
            m_Fish.push_back(fish);
            return;
        }
    }

    std::cout << "You don't have category with id: '" << category_id << "'. Your last category id: '" <<
        m_Categories->GetFishCategories().size() << "'.\n";
}

void FishTable::RemoveRecord()
{
    int record_id = GetRecordId();

    for (auto it = m_Fish.begin(); it != m_Fish.end(); ++it)
    {
        if ((*it)->id == record_id)
        {
            m_Fish.erase(it);
            return;
        }
    }

    std::cout << "You don't have fish with id: '" << record_id << "'. Your last fish id: '" <<
        m_Fish.size() << "'.\n";
}

void FishTable::UpdateRecord()
{
    int record_id = GetRecordId();

    char name[50];
    float average_weight;
    int category_id;

    std::cout << "Enter the value through space: 'name' 'average_weight' 'category_id'\n\n";
    std::cin >> name >> average_weight >> category_id;
    average_weight = std::abs(average_weight);
    category_id = std::abs(category_id);

    FishCategories* category = nullptr;
    for (auto cat : m_Categories->GetFishCategories())
    {
        if (cat->id == category_id)
            category = cat;
    }

    if (category != nullptr)
    {
        for (auto it = m_Fish.begin(); it != m_Fish.end(); ++it)
        {
            if ((*it)->id == record_id)
            {
                (*it)->name = name;
                (*it)->average_weight = average_weight;
                (*it)->fish_category_id = category;
                return;
            }
        }
    }
    else
    {
        std::cout << "You don't have category with id: '" << category_id << "'. Your last category id: '" <<
            m_Categories->GetFishCategories().size() << "'.\n";
        return;
    }

    std::cout << "You don't have fish with id: '" << record_id << "'. Your last fish id: '" <<
        m_Fish.size() << "'.\n";
}

void FishTable::PrintList()
{
    std::cout << "FISH:\n";
    std::cout << "id\t\t\t\tname\t\t\t\taverage_weight\t\t\tcategory_id\n";
    for (auto el : m_Fish)
        std::cout << el->id << "\t\t\t\t" << el->name << "\t\t\t\t\t" << el->average_weight << "\t\t\t" << el->fish_category_id->id << "\n";
}
