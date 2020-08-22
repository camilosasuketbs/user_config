#include "framework.h"
#include "../../../resident/bot/bot_prefix.h"

#define __IRC


class this_plugin :
   virtual public ::vericard::plugin
{


public:











   this_plugin(::aura::application * papp, object * p) :
      object(papp),
      ::vericard::chat_item(papp),
      ::vericard::plugin(papp,dynamic_cast <::vericard::comm * > (p))
   {

      construct_this_plugin();

   }


#include "../../../resident/bot/bot_common.cpp"


};


BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT(resident_youtube_bot)



