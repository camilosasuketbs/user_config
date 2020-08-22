


string bot_x()
{

   string & strText = m_strText;

   string strSpeakText;

   string & strTopic = m_strTopic;

   string & strTopicUser = m_strTopicUser;
   
   string str;

   string & strUserParam = m_strUser;

   string & strNameParam = m_strName;

   string & strCountry = m_strCountry;

   string & strLangParam = m_strLang;

   string & strTimeZone = m_strTimeZone;
   
   string & strOther = m_strOther;

   string & strOtherName = m_strOtherName;

   string & strOtherCountry = m_strOtherCountry;

   string & strOtherLang = m_strOtherLang;
   
   string & strOtherTimerZone = m_strOtherTimeZone;

   string & strUser = m_strUser;
   
   string & strName = m_strName;

   string & strLang = m_strLang;

   string strLoText = lotext();

   string strQuery = strText;

   bool bPlay = false;

   if (::str::begins_eat_ci(strQuery, "!ss "))
   {

      set_user_data(m_strUser, "ss", var::type_empty);

      //property_set setUserString(get_app());

      string strUrl = "https://api.spotify.com/v1/search?q=" + System.url().url_encode(strQuery) + "&type=track&limit=8";

      //string strSetUrl = "https://api.ca2.cc/account/set_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
      //   + "&key=" + System.url().url_encode(m_strUser) + "." + System.url().url_encode(strUrl)
      //   + "&value=";

      //Application.http().get(strSetUrl, str, setUserString);

#ifdef WINDOWS

      call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "\"" + strUrl + "\" : for_resident=" + m_strUser,  "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", "\""+strUrl+"\" : for_resident="+m_strUser, "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);

#else

      call_async("/xcore/time/x64/basis/app", "\""+strUrl+"\" : for_resident="+m_strUser +" app=app-veriwell/waven build_number=basis locale=_std schema=_std ", "/xcore/time/x64/basis/", SW_SHOW, false);

#endif

      //property_set set(get_app());

      int iWait = 0;

      //string strGetUrl = "https://api.ca2.cc/account/get_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
      //   + "&key=" + System.url().url_encode(m_strUser) + "." + System.url().url_encode(strUrl);

      var_array vara;

      while (true)
      {

         {
            
            single_lock sl(Application.veripack().m_pmutex);

            for (index i = 0; i < Application.veripack().m_vaResponse.get_size(); i++)
            {

               if (Application.veripack().m_vaResponse[i][0].get_string() == strUrl)
               {
                  vara = Application.veripack().m_vaResponse[i];
                  Application.veripack().m_vaResponse.remove_at(i);
                  break;
               }

            }

         }

         if (vara.get_count() > 0)
         {

            break;

         }
         else if (iWait > 120)
         {

            break;

         }
         else
         {

            Sleep(484);

            iWait++;

         }

      }

      stringa stra;

      if (vara.get_size() > 1)
      {

         stra.add_lines(vara[1]);

      }

      string strNew;

      stringa straNew;

      index iIndex = 1;

      for (index i = 0; i < stra.get_size(); i++)
      {

         string strLine = stra[i];

         if (strLine.is_empty())
         {

            continue;

         }

         stringa straLine;

         straLine.explode("|", strLine);

         if (straLine.get_size() != 4)
         {

            continue;

         }

         straNew.add(straLine[3]);

         strNew += ::str::from(iIndex);

         strNew += " - ";

         strNew += straLine[1];

         strNew += " - ";

         strNew += straLine[2];

         strNew += "\n";

         iIndex++;

      }

      set_user_data(m_strUser, "ss", straNew);

      str = strNew;

      if(str.is_empty())
      {
         
         str = "(no results)";

      }

   }
   else if ((bPlay = ::str::begins_eat_ci(strQuery, "!p ")) || ::str::begins_eat_ci(strQuery, "!q "))
   {
      
      if (strQuery.get_length() == 1)
      {

         if (isdigit_dup(strQuery[0]))
         {

            int i = atoi(strQuery);

            stringa stra;

            stra = get_user_data(m_strUser, "ss").stra();

            if (i <= 0 || i > stra.get_size())
            {
            
               str = "no such song";

            }
            else
            {

               str = stra[i-1];

               string strAddUp;

               if (bPlay)
               {
                  
                  strAddUp = "play_now";

               }

#ifdef WINDOWS

               call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "\"" + str + "\" : "+ strAddUp +" for_resident=" + m_strUser + "", "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

               call_async("/Applications/Waven.app/Contents/MacOS/Waven", "\"" + str + "\" : "+ strAddUp +" for_resident=" + m_strUser, "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);

#else

               call_async("/xcore/time/x64/basis/app", "\"" + str + "\" : play_now for_resident=" + m_strUser + " " + strAddUp + " app=app-veriwell/waven build_number=basis locale=_std schema=_std ", "/xcore/time/x64/basis/", SW_SHOW, false);

#endif

            }

         }

      }

      if (str != "no such song")
      {

         //property_set set(get_app());

         int iWait = 0;

         //string strGetUrl = "https://api.ca2.cc/account/get_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
         //   + "&key=" + System.url().url_encode(m_strUser) + "." + System.url().url_encode(strUrl);

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.veripack().m_pmutex);

               for (index i = 0; i < Application.veripack().m_vaResponse.get_size(); i++)
               {

                  if (Application.veripack().m_vaResponse[i][0].get_string() == str)
                  {
                     vara = Application.veripack().m_vaResponse[i];
                     Application.veripack().m_vaResponse.remove_at(i);
                     break;
                  }

               }

            }

            if (vara.get_count() > 0)
            {

               break;

            }
            else if (iWait > 120)
            {

               break;

            }
            else
            {

               Sleep(484);

               iWait++;

            }

         }

         stringa stra;

         if (vara.get_size() > 1)
         {

            stra.add_lines(vara[1]);

         }

         string strNew;

         stringa straNew;

         index iIndex = 1;

         for (index i = 0; i < stra.get_size(); i++)
         {

            if (i >= 2)
            {

               strNew += "\n";

            }

            string strLine = stra[i];

            if (strLine.is_empty())
            {

               continue;

            }

            stringa straLine;

            straLine.explode("|", strLine);

            if (straLine.get_size() != 3)
            {

               continue;

            }

            straNew.add(straLine[2]);

            strNew += straLine[0];

            strNew += " - ";

            strNew += straLine[1];

            iIndex++;

         }

         str = strNew;

         if (str.has_char())
         {

            if (bPlay)
            {
               str = "Going to play \"" + str + "\"";
            }
            else
            {
               str = "\"" + str + "\" queued.";
            }

         }
         else
         {

            str = "(no results)";

         }

      }

   }
   else if (::str::begins_ci(strText, "!p spotify:track:"))
   {



#ifdef WINDOWS

      call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "\"" + strText.substr(1) + "\" : play_now", "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);
      
#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", "\"" + strText.substr(1) + "\" : play_now", "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);

#else

      call_async("/xcore/time/x64/basis/app", "\"" + strText.substr(1) + "\" : play_now app=app-veriwell/waven build_number=basis locale=_std schema=_std ", "/xcore/time/x64/basis/", SW_SHOW, false);

#endif

   }
   else if(::str::begins_ci(strText, "!q spotify:track:"))
   {

      

#ifdef WINDOWS

      call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "\"" + strText.substr(1) + "\"", "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", "\"" + strText.substr(1) + "\" : play_now", "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);

#else

      call_async("/xcore/time/x64/basis/app", "\"" + strText.substr(1) + "\" : app=app-veriwell/waven build_number=basis locale=_std schema=_std ", "/xcore/time/x64/basis/", SW_SHOW, false);

#endif

   }
   else if (
      target_info("!", false)
      || target_info("exclamation mark", false)
      || target_info("exclamation", false)
      || target_info("?", false)
      || target_info("interrogation mark", false)
      || target_info("interrogation", false)
      || target_info("enter", false)
      || target_info("question mark", false)
      || target_info("question", false))
   {
      
      defer_extra_to_vocative();
      str = _t("%name, Some supported commands !help, !about and !want the bot");

   }
   else if (about_user("cc"))
   {

      strTopic = get_user(strTopicUser)->get_user_country_code();

      if (is_about_self())
      {

         str = _t("%name, your country code is set to \"%topic\"");

      }
      else
      {

         str = _t("%name, country code of %param1 is \"%topic\"");

      }

   }
   else if (about_user("userinfo"))
   {

      if (is_about_self())
      {

         str = _t("%name, your user information is:");

      }
      else
      {

         str = _t2("%name, user information about %param1 is:");

      }
      
      str += "\n";
      str += "\n";
      strSpeakText += "\n";
      strSpeakText += "\n";

      ws(strTopicUser, false);

      ::vericard::user * puser = get_user(strTopicUser, true);

      string strUsername = username(strTopicUser, strLang);

      string strWeatherQuery;

      string strCountryCode;

      string strCity;

      bool bLocation = false;

      string strWeather = user_weather(puser, strWeatherQuery, strCountryCode, strCity, bLocation);

      string strCountry = get_country(strCountryCode);

      string strTime = user_time_text(puser, m_strLang, true, false);

      string strTopScope = puser->get_user_info("favorite_programming", false);

      string strNewSpeak;

      strTopic = strUsername;

      if (strTopic.is_empty())
      {

         strTopic = strTopicUser;

      }

      str += _t2("name: %topic");

      str += "\n";
      strSpeakText += "\n";

      if (strCountryCode.is_empty())
      {
         string strSpeakText;
         strCountryCode = _t("(unknown)");
         strNewSpeak = strCountryCode;

      }
      else if(strCountryCode.get_length() == 2)
      {

         strNewSpeak = string(strCountryCode[0]) + "." + string(strCountryCode[1]) + ".";
          
      }
      else
      {

         strNewSpeak = strCountryCode;

      }

      str += _t2("country code:");
      str += " ";
      str += strCountryCode;
      strSpeakText += " ";
      strSpeakText += strNewSpeak;

      str += "\n";
      strSpeakText += "\n";

      strTopic = strCountry;

      if (strTopic.is_empty())
      {

         string strSpeakText;
         strTopic = _t("(unknown)");

      }

      str += _t2("country: %topic");

      str += "\n";
      strSpeakText += "\n";

      strTopic = strCity;

      if (strTopic.is_empty())
      {

         string strSpeakText;
         strTopic = _t("(unknown)");

      }

      str += _t2("city: %topic");


      str += "\n";
      strSpeakText += "\n";

      strTopic = strTime;
      
      if (strTopic.is_empty())
      {

         string strSpeakText;
         strTopic = _t("(unknown)");

      }

      str += _t2("time:");
      str += " ";
      str += strTime;
      strSpeakText += " ";
      strSpeakText += strTime;


      str += "\n";
      strSpeakText += "\n";


      if (strWeather.is_empty())
      {

         string strSpeakText;
         strWeather = _t("(unknown)");

      }

      str += _t2("weather:");
      strWeather.replace("/", " ");
      str += " ";
      str += strWeather;
      strSpeakText += " ";
      strSpeakText += strWeather;

      str += "\n";
      strSpeakText += "\n";
 
      if (strTopScope.is_empty())
      {

         string strSpeakText;
         strTopScope = _t("(unknown)");

      }

      str += _t2("top scope:");
      str += " ";
      str += strTopScope;
      strSpeakText += " ";
      strSpeakText += strTopScope;

      str += "\n";
      strSpeakText += "\n";


   }
   else if (about_user("ws"))
   {

      ws(strTopicUser, false);

      strText = "";

      strSpeakText = "";

   }
   else if (about_user("land"))
   {

      string strCountryCode = get_user(strTopicUser)->get_user_country_code(true).get_string().uppered();

      strTopic = get_country(strCountryCode);

      if (strTopic.is_empty())
      {

         strTopic = get_country("en", strCountryCode);

      }

      if (strTopic.is_empty())
      {

         strTopic = strCountryCode;

      }

      if (is_about_self())
      {

         if (strTopic.is_empty())
         {

            str = _t("%name, your country is unknown");

         }
         else
         {

            str = _t("%name, your country is set to \"%topic\"");

         }

      }
      else
      {

         if (strTopic.is_empty())
         {

            str = _t("%name, country of %param1 is unknown");

         }
         else
         {

            str = _t("%name, country of %param1 is \"%topic\"");

         }

      }

   }
   else if (about_user("city"))
   {

      strTopic = get_user(strTopicUser)->get_user_city(true);

      if (is_about_self())
      {

         if (strTopic.is_empty())
         {

            str = _t("%name, your city is unknown");

         }
         else
         {

            str = _t("%name, your city is set to \"%topic\"");

         }

      }
      else
      {

         if (strTopic.is_empty())
         {

            str = _t("%name, city of %param1 is unknown");

         }
         else
         {

            str = _t("%name, city of %param1 is \"%topic\"");

         }

      }

   }
   else if (::str::begins_eat_ci(strText, "!subj "))
   {

      if (strUser == "ca2")
      {

         m_pcomm->defer_set_subject(strText);

      }

   }
   else if (strText == "!pres")
   {

#ifdef __XMPP
      sp(::xmpp::comm) pcomm = m_pcomm;

      pcomm->defer_request_roster();
      ::fork(get_app(), [=]()
      {
         string strSpeakText;
         string str;
         pcomm->m_evRoster.wait(seconds(15));

         stringa straFiltered;

         stringa straBot;

         stringa stra;

         stra.explode("@", pcomm->m_strRoomJid);

         string strRoom;

         if (stra.get_count() > 0)
         {

            strRoom = stra[0];

         }

         stra.explode("@", pcomm->m_strJid);

         string strBot;

         ::count cGuest = 0;

         if (stra.get_count() > 0)
         {

            strBot = stra[0];

         }

         int iAddUp = 0;

         int iAddUpBot = 0;

         for (index i = 0; i < pcomm->m_straPresenceName.get_count(); i++)
         {

            string strName = pcomm->m_straPresenceName[i];

            string strJid = pcomm->m_straPresenceJid[i];

            if (strRoom.has_char() && ::str::ends_ci(strJid, "/" + strRoom))
            {
               string str1 = _t("\"myself\"");
               straFiltered.add_unique(str1);

            }
            else if (strBot.has_char() && ::str::ends_ci(strJid, "/" + strBot))
            {

               straBot.add_unique(strBot);

            }
            else
            {

               if (::str::begins_ci(strName, "guest_"))
               {

                  cGuest++;

               }
               else
               {

                  if (isbot(strName))
                  {

                     straBot.add_unique(strName);

                  }
                  else
                  {

                     strName = username(strName, strLang);

                     straFiltered.add_unique(strName);

                  }

               }

            }

         }

         string & strTopic = m_strTopic;

         strTopic = ::str::from(straFiltered.get_count() + cGuest);

         str = _t("%name, There are %topic online people at chat");

         straFiltered.quick_sort(NULL, NULL, true);

         str += straFiltered._008IfImplode(" : ", ", ", " " + l_and(strLang) + " ", cGuest > 0);

         if (cGuest > 0)
         {

            if (straFiltered.get_count() > 0)
            {

               //str += "\n";
               str += " ";

            }

            if (cGuest == 1)
            {

               str += _t("and one guest.");

            }
            else
            {

               strTopic = ::str::from(cGuest);

               str += _t("and %topic guests.");

            }

         }

         if (straBot.get_count() > 0)
         {

            strTopic = ::str::from(straBot.get_count());

            if (straBot.get_count() <= 0)
            {

               str += " " + _t("and no detected bots.");

            }
            else if (straBot.get_count() == 1)
            {

               str += " " + _t("and 1 detected bot");

            }
            else
            {

               str += " " + _t("and %topic detected bots");

            }

            str += straBot._008IfImplode(" : ", ", ", " " + l_and(strLang) + " ");
         }

         if (str.has_char())
         {

            Application.veripack().schedule_speech(strUser, strLang, str, strSpeakText, this);

         }
         else
         {

            if (!lspeak(strUser, strLang, str, true))
            {

            }

         }

         pcomm->msg(str);


      });

#endif
   }
   else if (strText == "!live")
   {
#ifdef __XMPP

      var v;
      Application.lctv_api_get("/api/livestreams/onair/", v, "bot");

      stringa stra;

      for (auto & i : v["results"].vara())
      {
         if ((bool)i["is_live"])
         {
            stra.add(i["user__slug"]);
         }
      }
      stra.quick_sort(NULL, NULL, true);

      strTopic = ::str::from(stra.get_count());

      str = _t("%name, There are %topic live streams");

      if (stra.get_count() > 0)
      {

         str += " ";

         str += stra._008Implode(", ", " " + l_and(strLang) + " ");

      }

#endif
   }
   else if(strText == "!reset!")
   {
      auto puser = get_user(strUser, true);
      m_strCountry = puser->get_user_country_code(true);
      puser->get_user_city(true);
      m_strLang = puser->get_user_lang();
      set_user_data(strUser, "visit_count","");
      set_user_data(strUser, "last_visit","");
      set_user_data(strUser, "last_visit_time","");
      set_user_data(strUser, "last_presence", "");
      set_user_data(strUser, "last_see_you", "");
      set_user_data(strUser, "back", "");
      set_user_data(strUser, "official_back", "");
      set_user_data(strUser, "last_welcome_time", "");
      set_user_data(strUser, "today_visit_count", "");

   }
   else if(strText == "!rickroll" || strText == "!rr" || strText == "!rick") // xmetrix commanded !rickroll (me: probably he is referring to Rick Astley hit...)
   {
      if(spam(strUser))
      {
         return warn(strUser);
      }
      else
      {
         str = rr(strName, strLang, strUser == "ca2");
      }
   }
   else if (strText.CompareNoCase("!song url") == 0)
   {

      str = song_url();

   }
   else if(target_info("song"))
   {

      defer_extra_to_vocative();

      strTopic = song("");

      if(strTopic.is_empty())
      {

         str = _t("%name, song not playing or not in record.");

      }
      else
      {

         str = _t("%name, currently playing song is: \"%topic\".");

      }
   }
   else if(target_info("help") || target_info("hlp") || target_info("hlep"))
   {
      
      string strGroup;

      stringa stra;

      stra.add_tokens(m_strExtra, " ", false);

      if (stra.get_count() >= 1)
      {

         strGroup = stra[0];

      }
      
      strGroup.make_lower();
      
      var strC;
      
      strC = "";
      
      string strSpeakGroup;

      string strSpeakC;

      int iParamCount = 1;

      if(strGroup == "config")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" settings commands are:");
         strSpeakGroup = strGroup;
         str = _t("!setname \"name\"\n!setlang \"country code\"\n!cc\n!land\n!getlang, and\n!setzone \"time zone\"");

      }
      else if (strGroup == "search")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" search commands are:");
         strSpeakGroup = strSpeakText;
         str = _t("!ss \"song search\"\n!p \"play song by number\"\n!q \"queue song by number\"");

      }
      else if(strGroup == "media")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" multimedia commands are:");
         strSpeakGroup = strSpeakText;
         str = _t("!rr\n!rickroll\n!say \"text\"\n!song\n!song url\n!play \"sound\"\n!play\n!stop\n!next\n!previous");

      }
      else if (strGroup == "playlist")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" playlist commands are:");
         strSpeakGroup = strSpeakText;
         str = _t("!playlist\n!playlist list\n!playlist \"number-or-text\"\n!playlist name\n!playlist url\n!playlist next\n!playlist previous");

      }
      else if(strGroup == "util")
      {
         defer_vocative(stra, iParamCount);
         strGroup = _t(" some utility commands:");
         strSpeakGroup = strSpeakText;
         str = _t("!timer [\"topic\"]:\"interval\"\n!urbd \"urban dictionary query\"\n!at \"google auto translate\", and\n!t \"lang\" \"text to translate from lang\"");
      }
      else if(strGroup == "rr" || strGroup == "rickroll")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, !rr or !rickroll plays 80s hit Never Gonna Give You Up performed by Rick Astley with ASCII animation.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "cmdtips")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, Use this command to get special tips");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "say")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, say uses Windows Narrator to speak the supplied text.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "ide")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, ide \"platform\" display information about tools used for development of ca2 framework and apps at the specified platform. \"platform\" may be: windows (Desktop), linux, macos, ios, android and winrt.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "setlang")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, setlang \"language code and/or two-letter country code\" sets user preferred language. The bot speaks to you in selected language, as much as possible.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "setname")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, use setname command to set better user name, matching nick or name, with desired capitalization and spacing. It can make it better the name pronunciantion by Text-To-Speech.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "info")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" information retrieval commands are:");
         strSpeakGroup = strSpeakText;
         str = _t("!ide \"platform\"\n!time\n!sky\n!getzone\n!help \"command\"\n!cmdtips\n!about\n!want the bot, and\n!credits");

      }
      else

      {

         defer_extra_to_vocative();
         strC = _t("%name, help information is grouped in:\n!help util\n!help info\n!help config\n!help search\n!help media, and\n!help playlist");
         strSpeakC = strSpeakText;

      }


      if(strC.is_empty())
      {
      
         str = name() + ", " + strGroup + "\n" + str;

         strSpeakText = name() + ", " + strSpeakGroup + "\n" + strSpeakText;

      }
      else
      {

         str = strC;

         strSpeakText = strSpeakC;

      }

   }
   else if(target_info("ide"))
   {
      
      string strGroup;
      
      stringa stra;
      
      stra.add_tokens(m_strExtra, " ", false);
      
      if (stra.get_count() >= 1)
      {
         
         strGroup = stra[0];
         
      }
      
      strGroup.make_lower();
      
      int iParamCount = 1;
      
      if(strGroup == "windows")
      {
         
         defer_vocative(stra, iParamCount);
         
         str = _t("%name, For Windows Desktop Software Development, ca2 uses Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");
         
      }
      else if(strGroup == "linux")
      {

         strTopic = "16.04";
         
         defer_vocative(stra, iParamCount);

         str = _t("%name, For Linux Software Development, ca2 uses Ubuntu %topic, Code::Blocks and SmartSVN.");

      }
      else if(strGroup == "macos")
      {

         strTopic = "El Capitan";

         defer_vocative(stra, iParamCount);
      
         str = _t("%name, At MacOS, ca2 uses Mac OS %topic, XCode and SmartSVN.");

      }
      else if(strGroup == "ios")
      {

         defer_vocative(stra, iParamCount);
         
         str = _t("%name, for iOS development, ca2 uses Mac OS X El Capitan, XCode, SmartSVN, XCode iOS simulator and trying to convince co-founder to borrow iOS device.");

      }
      else if(strGroup == "android")
      {
         
         defer_vocative(stra, iParamCount);
         
         str = _t("%name, for Android development, ca2 uses Windows with Hyper-V, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN, WinMerge, Visual Studio Emulator for Android and Galaxy Tab 3 (Door Prize for co-founder, gift for me, help for ca2 developers and users).");

      }
      else if(strGroup == "winrt")
      {

         defer_vocative(stra, iParamCount);
      
         str = _t("%name, for Windows Store App development, ca2 uses Windows, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");
         
      }
      else
      {
         
         defer_extra_to_vocative();
         
         str = _t("%name, ide \"platform\" display information about tools used for development of ca2 framework and apps at the specified platform. \"platform\" may be: windows (Desktop), linux, macos, ios, android and winrt.");
         
      }

   }
   else if(target_info("cmdtips"))
   {
      
      defer_extra_to_vocative();

      str = _t("%name, For the exclamation mark, if an existing command is not found, an audio clip is played from !playlist. If a corresponding audio clip is not found, the text is played like in !say <text>");

   }
   else if(target_info("about"))
   {
       
      defer_extra_to_vocative();

      str = _t("%name, ca2 is an all-purpose multi-platform framework and set of libraries written in C++ language to help developers create great apps for users.");

   }
   else if (
      strLoText == "!next"
   || strLoText == "!previous"
   || strLoText == "!play" 
   || strLoText == "!stop" 
   || strLoText == "!first" 
   || strLoText == "!last")
   {

      string strCommand = "mediaplay:execute_" + strLoText.Mid(1);

#ifdef WINDOWS
      
      call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", " : " + strCommand, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(MACOS)
      
      ::system("/Applications/Waven.app/Contents/MacOS/Waven : " + strCommand);

#else

      call_async("/xcore/time/x64/basis/app", " : app=app-veriwell/waven build_number=basis locale=_std schema=_std " + strCommand, "/xcore/time/x64/basis", SW_SHOW, false);

#endif

   }
   else if (::str::begins_eat_ci(strText, "!playlist "))
   {

      string strNew;

      int iWait = 0;

      string strLo = strText;

      strLo.make_lower();

      if (strLo == "next" || strLo == "previous")
      {

#ifdef WINDOWS

         call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", " : mediaplay:playlist_" + strLo, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", " : mediaplay:playlist_" + strLo, "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);

#else

         call_async("/xcore/time/x64/basis/app", " : app=app-veriwell/waven build_number=basis locale=_std schema=_std mediaplay:playlist_" + strLo, "/xcore/time/x64/basis", SW_SHOW, false);

#endif


         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.veripack().m_pmutex);

               for (index i = 0; i < Application.veripack().m_vaResponse.get_size(); i++)
               {

                  if (Application.veripack().m_vaResponse[i][0].get_string() == "mediaplay:playlist_next"
                     || Application.veripack().m_vaResponse[i][0].get_string() == "mediaplay:playlist_previous")
                  {
                     vara = Application.veripack().m_vaResponse[i];
                     Application.veripack().m_vaResponse.remove_at(i);
                     break;
                  }

               }

            }

            if (vara.get_count() > 0)
            {

               break;

            }
            else if (iWait > 120)
            {

               break;

            }
            else
            {

               Sleep(484);

               iWait++;

            }

         }

         if (vara.get_size() > 1)
         {

            str = vara[1];

            if (str.is_empty())
            {

               str = "(no results)";

            }
            else
            {

               if (strLo == "next")
               {

                  Application.broad_msg("Next Playlist: " + str);

               }
               else
               {

                  Application.broad_msg("Previous Playlist: " + str);

               }

               str.Empty();

            }

         }
         else
         {

            str = "(no results)";

         }


      }
      else if (strLo == "list")
      {

         //property_set setUserString(get_app());

         string strUrl = "https://api.spotify.com/v1/search?q=" + System.url().url_encode(strQuery) + "&type=track&limit=8";

         //string strSetUrl = "https://api.ca2.cc/account/set_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
         //   + "&key=" + System.url().url_encode(m_strUser) + "." + System.url().url_encode(strUrl)
         //   + "&value=";

         //Application.http().get(strSetUrl, str, setUserString);

#ifdef WINDOWS

         call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", " : mediaplay:playlist_list", "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", " : mediaplay:playlist_list", "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);

#else

         call_async("/xcore/time/x64/basis/app", " : mediaplay:playlist_list app=app-veriwell/waven build_number=basis locale=_std schema=_std ", "/xcore/time/x64/basis/", SW_SHOW, false);

#endif

         //property_set set(get_app());

         int iWait = 0;

         //string strGetUrl = "https://api.ca2.cc/account/get_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
         //   + "&key=" + System.url().url_encode(m_strUser) + "." + System.url().url_encode(strUrl);

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.veripack().m_pmutex);

               for (index i = 0; i < Application.veripack().m_vaResponse.get_size(); i++)
               {

                  if (Application.veripack().m_vaResponse[i][0].get_string() == "mediaplay:playlist_list")
                  {
                     vara = Application.veripack().m_vaResponse[i];
                     Application.veripack().m_vaResponse.remove_at(i);
                     break;
                  }

               }

            }

            if (vara.get_count() > 0)
            {

               break;

            }
            else if (iWait > 120)
            {

               break;

            }
            else
            {

               Sleep(484);

               iWait++;

            }

         }

         stringa stra;

         if (vara.get_size() > 1)
         {

            stra = vara[1].stra();

         }

         string strNew;

         stringa straNew;

         index iIndex = 1;

         for (index i = 0; i < stra.get_size(); i++)
         {

            string strLine = stra[i];

            strNew += ::str::from(iIndex);

            strNew += " - ";

            strNew += strLine;

            strNew += "\n";

            iIndex++;

         }

         str = strNew;

         if (str.is_empty())
         {

            str = "(no results)";

         }

      }
      else if(strLo == "url")
      {

         int iPlus = atoi(strText);

         strText = ::str::from(iPlus - 1);

         string strCommand = "mediaplay:playlist_url";

#ifdef WINDOWS

      call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", " : " + strCommand, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", " : " + strCommand, "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);

#else

      call_async("/xcore/time/x64/basis/app", " : app=app-veriwell/waven build_number=basis locale=_std schema=_std " + strCommand, "/xcore/time/x64/basis", SW_SHOW, false);

#endif


         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.veripack().m_pmutex);

               for (index i = 0; i < Application.veripack().m_vaResponse.get_size(); i++)
               {

                  if (Application.veripack().m_vaResponse[i][0].get_string() == strCommand)
                  {
                     vara = Application.veripack().m_vaResponse[i];
                     Application.veripack().m_vaResponse.remove_at(i);
                     break;
                  }

               }

            }

            if (vara.get_count() > 0)
            {

               break;

            }
            else if (iWait > 120)
            {

               break;

            }
            else
            {

               Sleep(484);

               iWait++;

            }

         }

         if (vara.get_size() > 1)
         {

            str = vara[1];

         }
         else
         {

            str = "(no results)";

         }


      }
      else if (atoi(strText) > 0)
      {

         int iPlus = atoi(strText);

         strText = ::str::from(iPlus - 1);

         string strCommand = "mediaplay:playlist_play=" + strText;

#ifdef WINDOWS

         call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", " : " + strCommand, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", " : " + strCommand, "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);
      
#else

         call_async("/xcore/time/x64/basis/app", " : app=app-veriwell/waven build_number=basis locale=_std schema=_std " + strCommand, "/xcore/time/x64/basis", SW_SHOW, false);

#endif


         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.veripack().m_pmutex);

               for (index i = 0; i < Application.veripack().m_vaResponse.get_size(); i++)
               {

                  if (Application.veripack().m_vaResponse[i][0].get_string() == strCommand)
                  {
                     vara = Application.veripack().m_vaResponse[i];
                     Application.veripack().m_vaResponse.remove_at(i);
                     break;
                  }

               }

            }

            if (vara.get_count() > 0)
            {

               break;

            }
            else if (iWait > 120)
            {

               break;

            }
            else
            {

               Sleep(484);

               iWait++;

            }

         }

         if (vara.get_size() > 1)
         {

            str = vara[1];

         }
         else
         {

            str = "(no results)";

         }


      }
      else
      {

         string strCommand = "mediaplay:playlist_splay=\"" + strText + "\"";

#ifdef WINDOWS

         call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", " : " + strCommand, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", " : " + strCommand, "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);
      
#else

         call_async("/xcore/time/x64/basis/app", " : app=app-veriwell/waven build_number=basis locale=_std schema=_std " + strCommand, "/xcore/time/x64/basis", SW_SHOW, false);

#endif

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.veripack().m_pmutex);

               for (index i = 0; i < Application.veripack().m_vaResponse.get_size(); i++)
               {

                  if (Application.veripack().m_vaResponse[i][0].get_string() == strCommand)
                  {
                     vara = Application.veripack().m_vaResponse[i];
                     Application.veripack().m_vaResponse.remove_at(i);
                     break;
                  }

               }

            }

            if (vara.get_count() > 0)
            {

               break;

            }
            else if (iWait > 120)
            {

               break;

            }
            else
            {

               Sleep(484);

               iWait++;

            }

         }

         if (vara.get_size() > 1)
         {

            if (vara.get_size() > 2)
            {

               stringa stra = vara[1].stra();

               int_array ia = vara[2].inta();

               if (stra.get_count() == ia.get_count())
               {

                  for (index i = 0; i < stra.get_size(); i++)
                  {

                     string strLine = stra[i];

                     strNew += ::str::from(ia[i] + 1);

                     strNew += " - ";

                     strNew += strLine;

                     strNew += "\n";

                  }

                  str = strNew;

               }
               else
               {

                  str = "(no results)";

               }

            }
            else
            {

               str = vara[1];

            }


         }
         else
         {

            str = "(no results)";

         }


      }

   }
   else if (strText == "!repos")
   {

      str = _t("%name, you can gain access to ca2 repos https://repos.ca2.cc basically by informally talking at chat at http://livecoding.tv/ca2 and showing interest in C++/ca2. Working e-mail address is needed. Pre-register at https://account.ca2.cc . Type !account for details on registration.");

   }
   else if (strText == "!account")
   {

      str = _t("%name, type e-mail and password at https://account.ca2.cc . If not registered or wrong credentials, the screen will be prompted again. Furthermore, if not registered, you will receive e-mail which should be confirmed.");

   }
   else if(strText == "!credits")
   {
      str = _t("%name presence and interest.\nxmetrix xmxstudio API.\nLivecoding.TV API and web site.\nVapaamies Russian translation.\nr00tkiller French translation.\nCatherina Cortega Dutch translation.\nfuel and andremommert German translation.\nPawel Kulesza Polish translation.\nha10word Traditional Chinese translation.");
   }
   else if(strText.get_length() > 6 && ::str::begins_eat(strText,"!urbd "))
   {
      olink(strUser,"http://www.urbandictionary.com/define.php?term=" + url_encode(strText));
   }
   else if (strText.get_length() > 7 && ::str::begins_eat(strText, "!urban "))
   {
      olink(strUser, "http://www.urbandictionary.com/define.php?term=" + url_encode(strText));
   }
   else if(strText.get_length() > 4 && ::str::begins(strText,"!at "))
   {
      auto_translate(strUser,glang(strLang),strText.substr(4));
   }
   else if(strText.get_length() > 3 && ::str::begins(strText,"!t ") && strText.substr(5,1) == " ")
   {
      translate(strUser,glang(strText.substr(3,2)),glang(strLang),strText.substr(6));
   }
   else if (strText.CompareNoCase("!lctv") == 0)
   {
      lctv_profile(strUserParam, strUser);
   }
   else if (::str::begins_eat_ci(strText, "!lctv "))
   {
      lctv_profile(strUserParam, strText);
   }
   else if(about_user("getlang"))
   {

      strTopic = get_user(strTopicUser)->get_user_lang();

      if (is_about_self())
      {

         str = _t("%name, your language is set to %topic");

      }
      else
      {

         str = _t("%name, language of %param1 is set to %topic");

      }

   }
   else if(strText.get_length() == 11 && ::str::begins_eat(strText,"!setlang "))
   {
      strLang = Application.lang(strText);
      set_user_data(strUser, "lang", strLang);
      set_user_data(strUser, "lang_set", "set");
      strLang = get_user(strUser)->get_user_lang();
      strTopic = strLang;
      strName = username(strUser, m_strLang);
      str = _t("%name, your language was set to \"%topic\"");
   }
   else if (::str::begins_eat(strText, "!timer "))
   {
      stringa stra;
      stra.explode(":", strText);
      if (stra.get_size() < 2)
         stra.insert_at(0, "timer");
      set_user_timer(strName, stra[0], stra[1], strLang);
   }
   else if (third_info("defzone") || strLoText == "!resetzone")
   {

      string strCurrentUser = m_strExtra;

      if (strCurrentUser.is_empty())
      {

         if (m_strOther.CompareNoCase(m_strUser) != 0 && m_strOther.has_char())
         {

            strCurrentUser = m_strOther;

         }
         else
         {

            strCurrentUser = m_strUser;

         }

      }

      string cc = get_user(strCurrentUser)->get_user_country_code().get_string().uppered();

      string ci = get_user(strCurrentUser)->get_user_city();

      string strQ;

      bool bLocation = false;

      if (ci.has_char())
      {

         strQ = ci;

         if (cc.has_char())
         {

            strQ += ", ";

            strQ += cc;

         }

      }
      else
      {

         bLocation = true;

         strQ = m_strExtra;

      }

      int64_t iId;

      double dLat;

      double dLon;

      auto pcity = System.find_city(strQ);
      
      if (pcity->m_iIndex >= 0)
      {
         
         property_set set;

         string strLat = ::str::from(pcity->m_dLat);

         string strLng = ::str::from(pcity->m_dLon);
         
         string strPath;
         
#ifdef WINDOWS
         
         strPath = "C:\\sensitive\\sensitive\\seed\\timezonedb.txt";
         
#else
         
         strPath = "/sensitive/sensitive/seed/timezonedb.txt";
         
#endif
         
         str = Application.http().get(
            "http://api.timezonedb.com/?key=" + file_as_string_dup(strPath)
            + "&format=json&lat="+strLat+"&lng="+strLng,
            set);

         if (str.has_char())
         {

            const char * pszJson = str;

            var v;

            v.parse_json(pszJson);
            
            double dUTCOffset = v["gmtoffset"].get_double() / 3600.0;
            
            string strTimeZoneText = v["abbreviation"];

            param(1, v["countrycode"]);
            param(2, v["zonename"]);
            param(3, strTimeZoneText);
            param(4, ::str::from(dUTCOffset));
            param(5, v["dst"].get_bool() ? "true" : "false");

            str = _t("country code: %param1, zone name: %param2, abbreviation: %param3, UTC: %param4, daylight saving: %param5");
            
            if(strLoText == "!resetzone")
            {
               
               set_user_data(strUser,"time_zone", dUTCOffset);
               
               set_user_data(strUser,"time_zone_text", strTimeZoneText);
               
            }

         }
         else
         {

            str = _t("(No results)");

         }

      }
      else
      {
         
         str = _t("(No results)");

      }

   }
   else if (strText == "!contact")
   {
      str.Empty();
      str += "ca2 Contact:\n";
      str += "Facebook: https://www.facebook.com/camilocc\n";
      str += "Twitter: https://twitter.com/qamilox\n";
      
      strSpeakText = str;

   }
   else if (third_info("sky") || third_info("weather"))
   {

      string strCurrentUser = m_strExtra;

      if (strCurrentUser.is_empty())
      {

         if (m_strOther.CompareNoCase(m_strUser) != 0 && m_strOther.has_char())
         {

            strCurrentUser = m_strOther;

         }
         else
         {

            strCurrentUser = m_strUser;

         }

      }

      ::vericard::user * puser = get_user(strCurrentUser, true);

      string strWeatherQuery;

      string strCountryCode;
      
      string strCity;

      bool bLocation = false;

      strTopic = user_weather(puser, strWeatherQuery, strCountryCode, strCity, bLocation);

      if (strTopic.is_empty())
      {

         str = _t("(No Results)");

      }
      else
      {

         strTopic.replace("/", " ");
         
         if (bLocation)
         {

            param1(strWeatherQuery);

            str = _t("%name, the weather at %param1 is %topic.");

         }
         else
         {

            if (strCurrentUser.CompareNoCase(m_strUser) == 0)
            {

               str = _t("%name, your current weather is %topic.");

            }
            else
            {

               param1(strWeatherQuery);

               param(2, username(strCurrentUser, m_strLang));

               str = _t("%name, the weather for %param2 at %param1 is %topic.");

            }

         }

      }

   }
   else if (about_user("time"))
   {

      strTopic = user_time_text(strTopicUser, m_strLang);

      if (is_about_self())
      {

         str = _t("%name, it is \"%topic\"");

      }
      else
      {

         str = _t("%name, it is \"%topic\" for %param1.");

      }

   }
   else if(::str::begins_eat(strText,"!setzone "))
   {
      
      var v = strText;

      double dUTCOffset;

      if(v.is_double())
      {

         dUTCOffset = v.get_double();

         set_user_data(strUser,"time_zone", dUTCOffset);

         set_user_data(strUser,"time_zone_text","");

         strTopic = ::str::from(get_user_data(strUser, "time_zone"));

         str = _t("%name, your time zone was set to UTC %topic");

      }
      else
      {
         
         dUTCOffset = Application.time_zone(strText, get_user(strUser)->get_user_country_code(false, true));

         set_user_data(strUser, "time_zone", dUTCOffset);

         set_user_data(strUser, "time_zone_text", strText);

         strTopic = get_user_data(strUser, "time_zone_text");

         strTopic.make_upper();

         str = _t("%name, your time zone was set to %topic.");

         if (dUTCOffset == 1000000.0)
         {

            str += _t(" It is unknown time zone. Warn streamer about this.");

         }

      }

   }
   else if(about_user("getzone"))
   {

      double dUTCOffset = get_user(strTopicUser)->user_time_zone();

      strTopic = Application.utc_offset_string(dUTCOffset);

      if(get_user(strUser)->get_user_data("time_zone_text").has_char() && get_user(strTopicUser)->get_user_data("time_zone_text").get_string().upper().CompareNoCase(strTopic) != 0)
      {

         strTopic = get_user_data(strTopicUser, "time_zone_text").get_string().upper() + " " + strTopic;

      }

      if (is_about_self())
      {

         str = _t("%name, your time zone is set to %topic");

      }
      else
      {

         str = _t("%name, %param1 time zone is set to %topic");

      }

      if (dUTCOffset == 1000000.0)
      {

         str += _t(" It is unknown time zone. Warn streamer about this.");

      }

   }
   else if(strText == "!resetlang")
   {
      
      set_user_data(strUser,"lang","");

   }
   else if(target_info("want the bot")) // question by julienb16 //2015-10-09 sexta-feira 23:23
   {

      defer_extra_to_vocative();
      str = _t("%name, you will need Visual Studio 2015 (at least Community Edition), a SVN (Subversion) client and repository access (working e-mail address needed). Talk to Camilo for details.");

   }
   else if(strText == "!playlist")
   {
      stringa a = ls_names(m_pcomm->get_base_path() / "audio/element");
      if(a.get_count() > 0)
      {
         str = "Type !play ";
         for(int i = 0; i < a.get_upper_bound(); i++)
         {
            if(i > 0)
            {
               str += ", ";
            }
            str += a[i].make_lower();
         }
         if(a.get_count() > 1)
         {
            str += " or " + a.last().make_lower();
         }
         else if(a.get_count() == 1)
         {
            str += a[0].lower();
         }
         str += ".";
      }
      else
      {
         if(strLang == "ru")
         {

            str = "В списке воспроизведения нет файлов";

         }
         else
         {

            str = "No files in the playlist";

         }
      }
      // return str;
   }
   else
   {
      stringa a = ls_names(m_pcomm->get_base_path() / "audio/element");
      str = strText.substr(1);
      string strServer = System.url().get_server(str);
      strsize iFind1 = -1;
      if ((iFind1 = strServer.find_ci("spotify.")) == 0
         || (iFind1 = strServer.find_ci(".spotify.")) > 0)
      {

         strsize iFind = str.find_ci("/track/", iFind1);
         if (iFind > 0)
         {
            string strId = str.Mid(iFind + strlen("/track/"));
            str = "spotify:track:" + strId;
         }

      }
      if (::str::begins_ci(str, "spotify:track:"))
      {

#ifdef WINDOWS

         call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", str, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);


#elif defined(__APPLE__)

      call_async("/Applications/Waven.app/Contents/MacOS/Waven", str, "/Applications/Waven.app/Contents/MacOS", SW_SHOW, false);
      
#else

         call_async("/xcore/time/x64/basis/app", "\"" + str + "\" : app=app-veriwell/waven build_number=basis locale=_std schema=_std ", "/xcore/time/x64/basis/", SW_SHOW, false);

#endif

      }
      else
      {
         bool found = false;
         int i = 0;
         for (; i < a.get_count() && !found; i++)
         {
            if (a[i].lower() == str.lower())
            {
               found = true;
            }
         }
         if (found)
         {
            play_sound(m_pcomm->get_base_path() / "audio/element" / str + ".wav");
            return "";
         }
         else
         {
            str = strText;
            if (!consider_speakable_text(strText))
            {
               str = _t("I am not going to say that phrase");
            }
            strSpeakText = strText;
            if (!lspeak(strUser, m_strLang, strSpeakText, true))
            {
               return str;
            }
            return "";
         }
      }
   }
   if(str.is_empty())
   {
      return "";
   }
   
   bool bSpeakable = true;

   if (!consider_speakable_text(strText))
   {
      
      str = _t("I am not going to say that phrase.");

      bSpeakable = false;

   }

   if (!str.has_char() && strSpeakText.has_char())
   {

      m_bSpeak = true;

   }

   m_strResponse = str;

   m_pcomm->add_chat(this);

   if (str.has_char())
   {

      Application.veripack().schedule_speech(strUser, m_strLang, str, strSpeakText, this);

      m_pcomm->msg(str);

   }
   else if(strSpeakText.has_char())
   {
      
      if (!lspeak(strUser, m_strLang, strSpeakText, true))
      {

      }

   }

   return "";

}



