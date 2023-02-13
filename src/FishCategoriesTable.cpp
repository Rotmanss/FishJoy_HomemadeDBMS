#include "FishCategoriesTable.h"
#include <fstream>
#include <sstream>
#include <vector>


std::ostream& operator<<(std::ostream& os, const FishCategories* category) {
    os << "id: " << category->id << ", name: " << category->name << ", is_published: " <<
        std::boolalpha << category->is_published << " (Fish Categories)";
    return os;
}

inline int FishCategoriesTable::GetRecordId()
{
    int record_id;
    std::cout << "Enter record 'id': \n";
    std::cin >> record_id;
    return std::abs(record_id);
}

inline int FishCategoriesTable::GoBack()
{
    int back;
    std::cout << "Press '1' to return back <-, '0' to continue\n";
    std::cin >> back;
    return back;
}

void FishCategoriesTable::ClearDependencies(int record_id)
{
    std::vector<std::string> dependencies_lines;
    std::string dependencies_line;
    std::fstream dependencies_file;
    dependencies_file.open("slave_file.txt", std::ios::in);
    if (dependencies_file.is_open())
    {
        while (std::getline(dependencies_file, dependencies_line))
        {
            int pos = dependencies_line.rfind('\t');
            std::string value = dependencies_line.substr(pos + 1);
            if (value == std::to_string(record_id))
                dependencies_line[0] = '0';
            dependencies_lines.push_back(dependencies_line);
        }
    }
    dependencies_file.close();

    std::fstream dependencies_write_file;
    dependencies_write_file.open("slave_file.txt", std::ios::out);
    if (dependencies_write_file.is_open())
    {
        for (const auto& l : dependencies_lines)
            dependencies_write_file << l << "\n";
    }
    dependencies_write_file.close();
}

void FishCategoriesTable::DeleteRecordFromFile(int record_id)
{
    std::stringstream ss;
    ss << "1\t" << m_FishCategories[record_id]->id << "\t" << m_FishCategories[record_id]->name;
    std::string to_remove = ss.str();

    std::vector<std::string> lines;
    std::string line;
    std::fstream file;
    file.open("master_file.txt", std::ios::in);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (line == to_remove)
                line[0] = '0';
            lines.push_back(line);
        }
    }
    file.close();

    std::fstream write_file;
    write_file.open("master_file.txt", std::ios::out);
    if (write_file.is_open())
    {
        for (const auto& l : lines)
            write_file << l << "\n";
    }
    write_file.close();

    ClearDependencies(record_id);
}

void FishCategoriesTable::ReplaceRecordInFile(int record_id, std::string to_update)
{
    std::stringstream ss;
    ss << "1\t" << m_FishCategories[record_id]->id << "\t" << m_FishCategories[record_id]->name;
    std::string updated = ss.str();

    std::vector<std::string> lines;
    std::string line;

    std::fstream file;
    file.open("master_file.txt", std::ios::in);
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
    write_file.open("master_file.txt", std::ios::out);
    if (write_file.is_open())
    {
        for (const auto& l : lines)
            write_file << l << "\n";
    }
    write_file.close();
}


FishCategoriesTable::FishCategoriesTable(GarbageCollector* garbage)
    : id(0), m_Garbage(garbage)
{
    uint32_t pk;
    char name[50];

    bool is_published;
    
    std::fstream file;
    file.open("master_file.txt", std::ios::in);
    if (file.is_open())
    {
        while (file >> is_published >> pk >> name)
        {
            if (is_published)
            {
                FishCategories* cat = new FishCategories{ pk, name };
                m_FishCategories[pk] = cat;
                id = pk;
            }
        }
    }
}

FishCategoriesTable::~FishCategoriesTable()
{
}

void FishCategoriesTable::AddRecord()
{
    if (GoBack() == 1)
        return;

    char name[50];

    std::cout << "Enter the name of your category: 'name'\n\n";
    std::cin >> name;

    id++;
    FishCategories* cat = new FishCategories{ id, name };
    m_FishCategories[id] = cat;

    std::fstream file;
    file.open("master_file.txt", std::ios::app);
    if (file.is_open())
    {
        file << "1\t" << cat->id << "\t" << cat->name << "\n";
        file.close();
    }
}

void FishCategoriesTable::RemoveRecord()
{
    if (GoBack() == 1)
        return;

    int record_id = GetRecordId();

    if (m_FishCategories.find(record_id) == m_FishCategories.end())
    {
        std::cout << "You don't have category with id: '" << record_id << "'\n";
        return;
    }

    DeleteRecordFromFile(record_id);
    m_FishCategories[record_id]->is_published = false;
    std::stringstream ss;
    ss << m_FishCategories[record_id];
    m_Garbage->AddToGarbage(ss.str());
}

void FishCategoriesTable::UpdateRecord()
{
    if (GoBack() == 1)
        return;

    int record_id = GetRecordId();

    char name[50];

    std::cout << "Enter the name of your category: 'name'\n\n";
    std::cin >> name;

    if (m_FishCategories.find(record_id) == m_FishCategories.end())
    {
        std::cout << "You don't have category with id: '" << record_id << "'\n";
        return;
    }

    std::stringstream ss;
    ss << "1\t" << m_FishCategories[record_id]->id << "\t" << m_FishCategories[record_id]->name;
    std::string to_update = ss.str();

    m_FishCategories[record_id]->name = name;
    ReplaceRecordInFile(record_id, to_update);
}

void FishCategoriesTable::PrintList()
{
    std::cout << "FISH CATEGORIES:\n";
    std::cout << "id\t\t\tname\n";

    std::string line;
    std::fstream file;
    file.open("master_file.txt", std::ios::in);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            bool is_published = std::stoi(line.substr(0, 1));

            if (is_published)
            {
                std::string item;
                line = line.substr(2);
                std::stringstream ss(line);
                while (std::getline(ss, item, '\t'))
                    std::cout << item + "\t\t\t";
                std::cout << "\n";
            }
        }
    }
    file.close();
}

inline void FishCategoriesTable::PrintRecordsNumber()
{
    std::string line;
    std::fstream file;
    file.open("master_file.txt", std::ios::in);
    int count = 0;

    while (std::getline(file, line)) {
        if (line[0] == '1') {
            count++;
        }
    }

    std::cout << "Number of categories records: " << count << std::endl;
}
