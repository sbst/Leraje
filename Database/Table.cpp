#include "pch.h"
#include "Table.h"

#include <fstream>

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
  bool result = true;
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

shared_ptr<ITableConnector::TableRow> Table::FromJson(string json)
{
  shared_ptr<ITableConnector::TableRow> result;
  try
  {
    boost::property_tree::ptree tree;
    stringstream ss(json);
    ss << json;
    boost::property_tree::read_json(ss, tree);
    result = connector->IncomeData(&tree);
  }
  catch(const boost::property_tree::json_parser_error& error)
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
    boost::property_tree::ptree tree;
    tree.put("id", id);
    connector->OutcomeData(id, row.get(), tree);
    stringstream ss;
    boost::property_tree::write_json(ss, tree, false);
    json = ss.str();
    result = true;
  }
  catch(const boost::property_tree::json_parser_error& error)
  {}
  return result;
}
