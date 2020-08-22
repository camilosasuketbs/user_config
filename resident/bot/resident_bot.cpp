#include "framework.h"
#include "resident_bot_prefix.h"

class this_plugin :
   virtual public ::resident::plugin
{


public:












   this_plugin(::object * pobject, object * p) :
      object(pobject),
      ::resident::chat_item(pobject->get_app()),
      ::resident::plugin(pobject->get_app(), dynamic_cast <::resident::comm * > (p))
   {

      construct_this_plugin();

   }


#include "resident_bot_common.cpp"


};


BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT(resident_bot)



