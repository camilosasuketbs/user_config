
void construct_this_plugin()
{

#ifdef __XMPP

   if (Application.m_pcommForAnimation == NULL)
   {

      Application.m_pcommForAnimation = m_pcomm;

   }

#endif

   m_straSpecialCommand.add("exclamation");
   m_straSpecialCommand.add("exclamation mark");
   m_straSpecialCommand.add("interrogation");
   m_straSpecialCommand.add("interrogation mark");
   m_straSpecialCommand.add("question");
   m_straSpecialCommand.add("question mark");
   m_straSpecialCommand.add("spotify:track:");
   m_straSpecialCommand.add("https://open.spotify.com/track/");

}



bool is_exclamation(string str)
{

   if (plugin::is_exclamation(str))
      return true;

   if (::str::find_ci("wtf", str) >= 0)
      return true;

   if (::str::find_ci("fuck", str) >= 0)
      return true;

   if (::str::find_ci("fck", str) >= 0)
      return true;

   if (::str::find_ci("**", str) >= 1)
      return true;

   return false;

}


bool is_vowel(string str)
{

   str = ::str::to_lower(str);

   if (str == unitext("å"))
      return true;
   if (str == unitext("a"))
      return true;
   if (str == unitext("á"))
      return true;
   if (str == unitext("à"))
      return true;
   if (str == unitext("â"))
      return true;
   if (str == unitext("ã"))
      return true;
   if (str == unitext("ä"))
      return true;
   if (str == unitext("e"))
      return true;
   if (str == unitext("é"))
      return true;
   if (str == unitext("è"))
      return true;
   if (str == unitext("ë"))
      return true;
   if (str == unitext("ê"))
      return true;
   if (str == unitext("i"))
      return true;
   if (str == unitext("ì"))
      return true;
   if (str == unitext("í"))
      return true;
   if (str == unitext("o"))
      return true;
   if (str == unitext("õ"))
      return true;
   if (str == unitext("ó"))
      return true;
   if (str == unitext("ò"))
      return true;
   if (str == unitext("u"))
      return true;
   if (str == unitext("ę"))
      return true;
   if (str == unitext("ę"))
      return true;
   if (str == unitext("ą"))
      return true;
   if (str == unitext("y"))
      return true;
   return false;

}

bool is_consonant(string str)
{

   if(str == unitext("ç"))
   {
      return true;
   }
   if (str == unitext("ń"))
   {
      return true;
   }

   if (str.get_length() != 1)
   {

      return false;

   }

   if (!isalpha(str[0]))
   {
      return false;
   }

   if (is_vowel(str[0]))
   {
      return false;
   }

   return true;

}


::file::path archive()
{

#ifdef WINDOWS
   return "C:\\archive";
#else
   return "/archive";
#endif

}

::file::path hi5()
{
   return archive() / "hi5";
}

::file::path hi5_user(string strUser)
{
   if (strUser == "xmetrix")
   {
      return hi5() / "user/northamerica/us/xmetrix";
   }
   else
   {
      return "";
   }
}









bool set_user_timer(string strName, string strTitle, string strSpec, string strLang)
{

   ::file::path path = core_app_path("app-core/timer");

   string strUrl = "\"timer://" + strTitle + "/" + strSpec + "?user="+System.url().url_encode(strName)+"&alias="+System.url().url_encode(strTitle)+"&lang="+System.url().url_encode(strLang)+"&autoclose=1\"";

   call_async(path, strUrl, path.folder(), SW_SHOW, false);

   return true;

}




void olink(string strUser, string strUrl, string strTarget = "")
{

   if (spam(strUser))
   {

   }
   else
   {

      open_link(strUrl, strTarget);

   }

}








void auto_translate(string strUser, string strDst, string strText)
{

   olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#auto/" + strDst + "/" + url_encode(strText), "translation");

}


void translate(string strUser, string strDst, string strSrc, string strText)
{

   olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#" + strSrc + "/" + strDst + "/" + url_encode(strText), "translation");

}


void lctv_profile(string strUser, string strProfile)
{

   olink(strUser, "https://www.livecoding.tv/" + strProfile + "/", "viewer_profile");

}




string lotext(string strText)
{

   return strText.lower();

}


string lotext()
{

   return lotext(m_strText);

}



bool third_info(string strQuery, bool bPrefix = true)
{

   string strText = m_strText;

   string strQuery1 = "!" + strQuery;

   string strQuery2 = "!" + strQuery;

   if (strText.compare_ci(strQuery1) == 0 || ::str::begins_eat_ci(strText, strQuery1 + " ")
         || strText.compare_ci(strQuery2) == 0 || ::str::begins_eat_ci(strText, strQuery2 + " ")
         || (!bPrefix && (strText.compare_ci(strQuery) == 0 || ::str::begins_eat_ci(strText, strQuery + " "))))
   {

      if (strText.compare_ci(strQuery1) == 0
            || strText.compare_ci(strQuery2) == 0
            || (!bPrefix && strText.compare_ci(strQuery) == 0))
      {

         strText.Empty();

      }

      m_strExtra = strText;

      if (strText == m_strUserId || m_strUserId == m_strOtherUserId || (m_strOtherUserId.is_empty() && strText.is_empty()))
      {

         m_epersonVocative = ::resident::person_user;

         //m_strTopicUserId = m_strUserId;

      }
      else
      {



         if (strText.has_char())
         {

            //m_strTopicUserId = strText;

            m_strOtherName = strText;

         }
         else if (m_strOtherUserId.has_char())
         {

            m_strOtherLang = get_user(m_strOtherUserId)->get_user_lang();

            m_strOtherName = username(m_strOtherUserId, m_strOtherLang);

            //   m_strTopicUserId = m_strOtherUserId;

         }

         //param1_topic_username();

      }

      return true;

   }
   else
   {

      return false;

   }

}


string user_weather(::resident::user * puser, string & strQuery, string & strCountryCode, string & strCity, bool & bLocation)
{

   string strWeather;

   strCountryCode = puser->get_user_country_code(false, false).get_string().uppered();

   strCity = puser->get_user_city(false, false);

   bLocation = false;

   if (strCity.has_char())
   {

      strQuery = strCity;

      if (strCountryCode.has_char())
      {

         strQuery += ", ";

         strQuery += strCountryCode;

      }

   }
   else
   {

      bLocation = true;

      strQuery = m_strExtra;

   }

   ::file::path path = core_app_path("app-core/weather");

   string strParam = "\"" + strQuery + "\" : for_resident=" + m_strUserId;

   call_async(path, strParam, path.folder(), SW_SHOW, false);

   string strResponse = strQuery + "@" + m_strUserId;

   int iWait = 0;

   var_array vara;

   while (true)
   {

      {

         single_lock sl(Application.mainstage().m_pmutex);

         for (index i = 0; i < Application.mainstage().m_varaWeatherResponse.get_size(); i++)
         {

            string str = Application.mainstage().m_varaWeatherResponse[i][0].get_string();

            if (str.compare_ci(strResponse) == 0)
            {

               vara = Application.mainstage().m_varaWeatherResponse[i];

               Application.mainstage().m_varaWeatherResponse.remove_at(i);

               break;

            }

         }

      }

      if (vara.get_count() > 0)
      {

         break;

      }
      else if (iWait > 30)
      {

         break;

      }
      else
      {

         Sleep(500);

         iWait++;

      }

   }

   stringa stra;

   if (vara.get_size() > 1)
   {

      string strVar1 = vara[1];

      stra.explode("|", strVar1);

   }

   if (stra.get_size() == 2)
   {

      strWeather = stra[0] + " " + stra[1];

   }

   return strWeather;

}




void restart_rw()
{

#ifdef WINDOWS

   ::system("restart-rw");

#else

   ::system("bash -c /archive/hi5/linux/bin/restart-rw  </dev/null &>/dev/null &");

#endif

}





