#include "pch.h"
#include "Table.h"

#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace Leraje::Database::Tables;

using namespace std;

Table::Table(ITableConnector* _connector) : lastId(0), connector(_connector)
{}

Table::~Table()
{
  //for (auto it = table->begin(); it != table->end(); ++it) delete (*it).second;
  //delete table;
}

bool Table::WriteToTable(string json)
{
  bool result = false;
  shared_ptr<ITableConnector::TableRow> row;
  int32_t id;
  try
  {
    id = 0;
    row = FromJson(json, &id);

    if ((row) && (!IsIdExist(id)) && (id > 0))
    {
      table.insert(table.end(), pair<uint32_t, shared_ptr<ITableConnector::TableRow>>(id, row));
      result = true;
    }
  }
  catch(const std::bad_alloc& error)
  {}
  return result;
}

bool Table::UpdateToTable(string json, int32_t id)
{
  bool result = false;
  try
  {
    auto row = table.at(id);
    MergeJsons(row, json);
    table[id] = row;
    result = true;
  }
  catch(const std::bad_alloc& error)
  {}
  catch(std::out_of_range& error)
  {}
  return result;
}

bool Table::ReadFromTable(uint32_t id, string& json)
{
  bool result = false;
  try
  {
    auto row = table.at(id);
    result = ToJson(id, row, json);
  }
  catch(std::out_of_range& error)
  {}
  return result;
}

bool Table::LoadToTable(string json)
{
  bool result = false;
  shared_ptr<ITableConnector::TableRow> row;
  try
  {
    row = FromJson(json);
    if (row)
    {
      table.insert(table.end(), pair<uint32_t, shared_ptr<ITableConnector::TableRow>>(++lastId, row));
      result = true;
    }
  }
  catch(const std::bad_alloc& error)
  {}
  return result;
}

shared_ptr<ITableConnector::TableRow> Table::FromJson(string json, int32_t* foundId)
{
  shared_ptr<ITableConnector::TableRow> result;
  try
  {
    JsonTree tree;
    stringstream ss(json);
    ss << json;
    boost::property_tree::read_json(ss, static_cast<boost::property_tree::ptree&>(tree));
    if (foundId) *foundId = tree.get<int32_t>("id");
    result = connector->IncomeData(&tree);
  }
  catch(const boost::exception& error)
  {
    result = nullptr;
  }
  catch(const std::invalid_argument& error)
  {
    result = nullptr;
  }
  return result;
}

bool Table::ToJson(uint32_t id, shared_ptr<ITableConnector::TableRow> row, string& json)
{
  bool result = false;
  try
  {
    JsonTree tree;
    tree.put("id", id);
    connector->OutcomeData(row.get(), tree);
    stringstream ss;
    boost::property_tree::write_json(ss, static_cast<boost::property_tree::ptree&>(tree), false);
    json = ss.str();
    result = true;
  }
  catch(const boost::exception& error)
  {}
  return result;
}

bool Table::MergeJsons(shared_ptr<ITableConnector::TableRow> row, string json)
{
  try
  {
    JsonTree tree;
    stringstream ss(json);
    boost::property_tree::read_json(ss, static_cast<boost::property_tree::ptree&>(tree));
    connector->UpdateData(row.get(), &tree);
  }
  catch(const boost::exception& error)
  {}
  catch(const std::invalid_argument& error)
  {}
  return true;
}

bool Table::IsIdExist(int32_t id)
{
  return table.find(id) != table.end();
}
