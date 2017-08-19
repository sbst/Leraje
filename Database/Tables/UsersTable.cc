#include "pch.h"
#include "UsersTable.h"

#include <fstream>


using namespace Leraje::Database::Tables;

using namespace std;

UsersTable::UsersTable() : lastId(0), table(new UsersRows())
{}

UsersTable::~UsersTable()
{
  for (auto it = table->begin(); it != table->end(); ++it) delete (*it).second;
  delete table;
}

bool UsersTable::WriteToTable(string json)
{
  bool result = true;
  UsersData* row;
  try
  {
    row = new UsersData();
    if (FromJson(json, *row))
    {
      table->insert(table->end(), pair<uint32_t, UsersData*>(++lastId, row));
      result = true;
    }
  }
  catch(const std::bad_alloc& error)
  {
    delete row;
  }
  return result;
}

bool UsersTable::ReadFromTable(uint32_t id, string& json)
{
  bool result = false;
  try
  {
    auto row = table->at(id);
    result = ToJson(id, row, json);
  }
  catch(std::out_of_range& error)
  {}
  return result;
}

bool UsersTable::FromJson(string json, UsersData& row)
{
  bool result = false;
  try
  {
    boost::property_tree::ptree tree;
    stringstream ss(json);
    ss << json;
    boost::property_tree::read_json(ss, tree);
    IncomeData(&tree, row);
    result = true;
  }
  catch(const boost::property_tree::json_parser_error& error)
  {}
  return result;
}

bool UsersTable::ToJson(uint32_t id, UsersData* row, string& json)
{
  bool result = false;
  try
  {
    boost::property_tree::ptree tree;
    OutcomeData(id, row, tree);
    stringstream ss;
    boost::property_tree::write_json(ss, tree, false);
    json = ss.str();
    result = true;
  }
  catch(const boost::property_tree::json_parser_error& error)
  {}
  return result;
}

void UsersTable::OutcomeData(uint32_t id, UsersData* data, boost::property_tree::ptree& tree)
{
  tree.put("id", id);
  tree.put("email", data->email);
  tree.put("first_name", data->firstName);
  tree.put("last_name", data->lastName);
  tree.put("gender", data->gender);
  tree.put("birth_date", data->birthDate);
}

void UsersTable::IncomeData(boost::property_tree::ptree* tree, UsersData& data)
{
  data.email = tree->get<string>("email");
  data.firstName = tree->get<string>("first_name");
  data.lastName = tree->get<string>("last_name");
  data.gender = tree->get<char>("gender");
  data.birthDate = tree->get<int64_t>("birth_date");
}
