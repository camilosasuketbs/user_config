#include "framework.h"
#include "app-core/appseed/xmpp_resident/plugin.h"
#pragma comment (lib,"app_core_irc_bot.lib" )


class this_plugin :
	virtual public ::irc::bot::plugin
{
	
	public:
	
	
      this_plugin(::aura::application * papp, object * p) :
		object(papp),
		::irc::bot::plugin(papp, p)
	{
		
	}

	
};


BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT



