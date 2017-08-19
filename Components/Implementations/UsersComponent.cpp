#include "pch.h"
#include "UsersComponent.h"

using namespace Leraje::Components;
using namespace std;

UsersComponent::UsersComponent(fastcgi::ComponentContext* context)
  : fastcgi::Component(context), Leraje::Components::Component(context)
{}

void UsersComponent::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
{
  request->setContentType("text/plain; charset=utf-8");
  string result;
  bool status = false;
  if(request->getRequestMethod() == "GET")
  {
    uint32_t val = 0;
    sscanf(request->getURI().c_str(), "/users/%d", &val);
    if (db->ReadFromTable("users", val, result))
      status = true;
  }
  if (status)
  {
    stringbuf buffer(result);
    request->write(&buffer);
    request->setStatus(200);
  }
  else
    request->setStatus(404);

}

void UsersComponent::loadDatabase()
{
  db->LoadDatabase("users");
}
