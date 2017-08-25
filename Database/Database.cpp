#include "pch.h"
#include "Database.h"

#include <boost/property_tree/json_parser.hpp>

using namespace Leraje::Database;

using namespace std;

//const char* Database::FileDataPath = "/root/data/";
const char* Database::FileDataPath = "/home/sbst/highloadcup/Leraje/data/TRAIN/data/";

std::shared_ptr<Database> Database::GetDatabase()
{
  static std::shared_ptr<Database> instance(new Database);
  return instance;
}

Database::Database()
{
  //system("cp /tmp/data/data.zip /root/Leraje/data.zip");
  //system("unzip /root/Leraje/data.zip -d /root/data/");
}

Database::~Database()
{
  //delete table;
}

void Database::LoadDatabase(string tableName, Tables::ITableConnector* connector)
{
  tables[tableName] = unique_ptr<Tables::Table>(new Tables::Table(connector));
  stringstream builder;
  uint32_t i = 1;
  builder << Database::FileDataPath << tableName << "_" << i << ".json";
  std::ifstream file(builder.str());
  while(file.good())
  {
    LoadFromFile(builder.str(), tableName);
    file.close();
    builder.str("");
    ++i;
    builder << Database::FileDataPath << tableName << "_" << i << ".json";
    file.open(builder.str());
  }
}

bool Database::WriteToTable(string tableName, string json, int32_t id)
{
  return id == 0 ? tables[tableName]->WriteToTable(json) : tables[tableName]->UpdateToTable(json, id);
}

bool Database::ReadFromTable(string tableName, uint32_t id, string& json)
{
  return tables[tableName]->ReadFromTable(id, json);
}

void Database::LoadFromFile(string fileName, string tableName)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(fileName, tree);
    stringstream outData;
    for(auto const& node : tree.get_child(tableName))
    {
      boost::property_tree::write_json(outData, node.second);
      tables[tableName]->LoadToTable(outData.str());
      outData.str("");
    }
}
