{
   m_straSpecialCommand.add("exclamation");
   m_straSpecialCommand.add("exclamation mark");
   m_straSpecialCommand.add("interrogation");
   m_straSpecialCommand.add("interrogation mark");
   m_straSpecialCommand.add("question");
   m_straSpecialCommand.add("question mark");
}



stringa m_straSpecialCommand;

#define _t(strText) get_text(strSpeakText,  strText)
#define _t2(strText) get_text(strSpeakText,  strText, true)
#define _trans1(function) function(strSpeakText)

string_map < string_to_string > m_text;

string_map < file_time > m_ftime;


string_map < string_to_string > m_country;

string_map < file_time > m_ftimeCountry;

#include "lib1.cpp"
//#include "lib_datetime.cpp"
#include "lib_entertainment.cpp"
#include "lib_language.cpp"
#include "lib_policy.cpp"


#include "lib_followers.cpp"
#include "lib_bot.cpp"
#include "lib_bot_x.cpp"
#include "lib_pres.cpp"

