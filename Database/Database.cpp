#include "pch.h"
#include "Database.h"

using namespace Leraje::Database;

std::shared_ptr<Database> Database::GetDatabase()
{
  static std::shared_ptr<Database> instance(new Database);
  return instance;
}

Database::Database()
{}

Database::~Database()
{}
