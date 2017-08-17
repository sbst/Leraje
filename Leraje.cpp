#include "Components/Implementations/VisitsComponent.h"
#include "Components/Implementations/UsersComponent.h"
#include "Components/Implementations/LocationsComponent.h"

using namespace Leraje;

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("Visits"   ,   Components::VisitsComponent   )
FCGIDAEMON_ADD_DEFAULT_FACTORY("Users"    ,   Components::UsersComponent    )
FCGIDAEMON_ADD_DEFAULT_FACTORY("Locations",   Components::LocationsComponent)
FCGIDAEMON_REGISTER_FACTORIES_END()
