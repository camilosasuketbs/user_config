#include "framework.h"
#include "app-core/appseed/xmpp_resident/xmpp_resident.h"
#pragma comment (lib,"vericard.lib" )
#pragma comment (lib,"xmpp.lib" )
#pragma comment (lib,"app_core_xmpp_bot.lib" )
#pragma comment (lib,"app_core_xmpp_client.lib" )
#pragma comment (lib,"app_core_xmpp_resident.lib" )
class this_plugin:
   virtual public ::xmpp_resident::plugin
{
public:
   











   this_plugin(::aura::application * papp, object * p) :
      object(papp),
      ::vericard::plugin(papp, dynamic_cast <::vericard::comm *> (p)),
      ::xmpp_resident::plugin(papp, dynamic_cast <::vericard::comm *> (p))

	  
#include "xmpp_bot_common.cpp"

};

BEG_ONLY_FACT
   CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT