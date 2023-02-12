#include "FishTable.h"
#include <fstream>
#include <sstream>
#include <vector>


inline int FishTable::GetRecordId()
{
    int record_id;
    std::cout << "Enter record 'id': \n";
    std::cin >> record_id;
    return std::abs(record_id);
}

inline int FishTable::GoBack()
{
    int back;
    std::cout << "Press '1' to return back <-, '0' to continue\n";
    std::cin >> back;
    return back;
}

void FishTable::DeleteRecordFromFile(int record_id)
{
    std::stringstream ss;
    ss << m_Fish[record_id]->id << "\t" << m_Fish[record_id]->name << "\t" <<
        m_Fish[record_id]->average_weight << "\t" << m_Fish[record_id]->fish_category_id->id;
    std::string to_remove = ss.str();

    std::vector<std::string> lines;
    std::string line;

    std::fstream file;
    file.open("slave_file.txt", std::ios::in);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (line != to_remove)
                lines.push_back(line);
        }
    }
    file.close();

    std::fstream write_file;
    write_file.open("slave_file.txt", std::ios::out);
    if (write_file.is_open())
    {
        for (const auto& l : lines)
            write_file << l << "\n";
    }
    write_file.close();
}

void FishTable::ReplaceRecordInFile(int record_id, std::string to_update)
{
    std::stringstream ss;
    ss << m_Fish[record_id]->id << "\t" << m_Fish[record_id]->name << "\t" <<
        m_Fish[record_id]->average_weight << "\t" << m_Fish[record_id]->fish_category_id->id;
    std::string updated = ss.str();

    std::vector<std::string> lines;
    std::string line;

    std::fstream file;
    file.open("slave_file.txt", std::ios::in);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (line == to_update)
                lines.push_back(updated);
            else
                lines.push_back(line);
        }
    }
    file.close();

    std::fstream write_file;
    write_file.open("slave_file.txt", std::ios::out);
    if (write_file.is_open())
    {
        for (const auto& l : lines)
            write_file << l << "\n";
    }
    write_file.close();
}

FishTable::FishTable(FishCategoriesTable* categories)
    : m_Categories(categories), id(0)
{
    uint32_t pk;
    char name[50];
    float average_weight;
    int category_id;

    std::fstream file;
    file.open("slave_file.txt", std::ios::in);
    if (file.is_open())
    {
        while (file >> pk >> name >> average_weight >> category_id)
        {
            Fish* fish = new Fish{ pk, name, average_weight, (FishCategories*)m_Categories->GetFishCategories()[category_id] };
            m_Fish[pk] = fish;
            id = pk;
        }
    }
}

FishTable::~FishTable()
{
}

void FishTable::AddRecord()
{
    if (GoBack() == 1)
        return;

    char name[50];
    float average_weight;
    int category_id;

    std::cout << "Enter the value through space: 'name' 'average_weight' 'category_id'\n\n";
    std::cin >> name >> average_weight >> category_id;
    average_weight = std::abs(average_weight);
    category_id = std::abs(category_id);

    FishCategories* category = m_Categories->GetFishCategories()[category_id];
    if (category != nullptr)
    {
        id++;
        Fish* fish = new Fish{ id, name, average_weight, category };
        m_Fish[id] = fish;

        std::fstream file;
        file.open("slave_file.txt", std::ios::app);
        if (file.is_open())
        {
            file << fish->id << "\t" << fish->name << "\t" << fish->average_weight << "\t" << fish->fish_category_id->id << "\n";
            file.close();
        }
        return;
    }

    std::cout << "You don't have category with id: '" << category_id << "'\n";
}

void FishTable::RemoveRecord()
{
    if (GoBack() == 1)
        return;

    int record_id = GetRecordId();

    if (m_Fish.find(record_id) == m_Fish.end())
    {
        std::cout << "You don't have fish with id: '" << record_id << "'\n";
        return;
    }

    DeleteRecordFromFile(record_id);
    delete m_Fish[record_id];
    m_Fish.erase(record_id);
}

void FishTable::UpdateRecord()
{
    if (GoBack() == 1)
        return;

    int record_id = GetRecordId();

    char name[50];
    float average_weight;
    int category_id;

    std::cout << "Enter the value through space: 'name' 'average_weight' 'category_id'\n\n";
    std::cin >> name >> average_weight >> category_id;
    average_weight = std::abs(average_weight);
    category_id = std::abs(category_id);

    FishCategories* category = m_Categories->GetFishCategories()[category_id];
    if (category)
    {
        if (m_Fish.find(record_id) == m_Fish.end())
        {
            std::cout << "You don't have fish with id: '" << record_id << "'\n";
            return;
        }
        std::stringstream ss;
        ss << m_Fish[record_id]->id << "\t" << m_Fish[record_id]->name << "\t" <<
            m_Fish[record_id]->average_weight << "\t" << m_Fish[record_id]->fish_category_id->id;
        std::string to_update = ss.str();

        m_Fish[record_id]->name = name;
        m_Fish[record_id]->average_weight = average_weight;
        m_Fish[record_id]->fish_category_id = category;
        ReplaceRecordInFile(record_id, to_update);
        return;
    }
    else
    {
        std::cout << "You don't have category with id: '" << category_id << "'\n";
        return;
    }
}

void FishTable::PrintList()
{
    std::cout << "FISH:\n";
    std::cout << "id\t\t\t\tname\t\t\t\taverage_weight\t\t\tcategory_id\n";
    for (auto el : m_Fish)
        if (el.second->fish_category_id != nullptr)
            std::cout << el.second->id << "\t\t\t\t" << el.second->name << "\t\t\t\t\t" << el.second->average_weight << "\t\t\t" << el.second->fish_category_id->id << "\n";
}
