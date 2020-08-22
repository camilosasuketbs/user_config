#include "framework.h"
#include "bot_prefix.h"


#define __XMPP


























class this_plugin:
   virtual public ::resident::plugin
{
public:  
































   













   

















   




  


      
   this_plugin(::aura::application * papp, object * p) :
      object(papp),
      ::resident::chat_item(papp),
      ::resident::plugin(papp, dynamic_cast <::resident::comm *> (p))
   {

      construct_this_plugin();



   }

#include "bot_common.cpp"





};
















   BEG_ONLY_FACT
   CREATE_OBJECT_ENTRY("plugin",this_plugin)
   END_ONLY_FACT








      










