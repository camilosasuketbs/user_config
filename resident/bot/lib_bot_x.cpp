


string bot_x()
{

   string strText = m_strText;

   string strSpeakText;

   string & strTopic = m_strTopic;

   string & strTopicUser = m_strTopicUserId;

   string str;

   string & strUserParam = m_strUserId;

   string & strNameParam = m_strName;

   string & strCountry = m_strCountry;

   string & strLangParam = m_strLang;

   string & strTimeZone = m_strTimeZone;

   string & strOther = m_strOtherUserId;

   string & strOtherName = m_strOtherName;

   string & strOtherCountry = m_strOtherCountry;

   string & strOtherLang = m_strOtherLang;

   string & strOtherTimerZone = m_strOtherTimeZone;

   string & strUser = m_strUserId;

   string & strName = m_strName;

   string & strLang = m_strLang;

   string strLoText = lotext();

   string strQuery = strText;

   bool bPlay = false;

#ifdef __XMPP

   bool bAdmin = strUser == "ca2" || strUser == "ca2live" || strUser == "ca2bot" || strUser == "resident";

#else

   bool bAdmin = strUser == "ca2" || strUser == "ca2live" || strUser == "ca2bot";

#endif

   if (strQuery == "!s1")
   {

      str = "ssssss.....";

   }
   else if(strQuery == "!a1")
   {

      auto puser = get_user(strUser, true);

      __pointera(::resident::user) usera;

      usera.add(puser);

      Application.mainstage().add_announce("Thank you for hosting, XanderGamingTwich!!\nThank you for hosting, sipher_academy!!", usera, 60000);

   }
   else if(strQuery == "restart-rw")
   {

      if (!bAdmin)
      {

         return not_admin();

      }

      restart_rw();

   }
   else if(::str::begins_eat_ci(strQuery,"!anime "))
   {

      if (!bAdmin)
      {

         return not_admin();

      }

      stringa stra;

      stra.add_tokens(strQuery, " ", false);

      string strAnimation;

      string strStyle;

      if (stra.get_size() > 0)
      {

         strAnimation = stra[0];

         if (stra.get_size() > 1)
         {

            strStyle = stra[1];

         }

      }

      if (strAnimation.compare_ci("off") == 0 || strAnimation.compare_ci("stop") == 0)
      {

         Application.mainstage().m_strAnimationNew.Empty();
         Application.mainstage().m_strAnimationStyleNew.Empty();

      }
      else
      {

         Application.m_pcommForAnimation = m_pcomm;
         Application.mainstage().m_strAnimationNew = strAnimation;
         Application.mainstage().m_strAnimationStyleNew = strStyle;
         Application.mainstage().set_need_redraw();

      }

   }
   else if (::str::begins_eat_ci(strQuery, "!ss "))
   {

      set_user_var(m_strUserId, "ss", ::type_empty);

      //property_set setUserString(get_app());

      string strUrl = "https://api.spotify.com/v1/search?q=" + System.url().url_encode(strQuery) + "&type=track&limit=8";

      //string strSetUrl = "https://api.ca2.cc/account/set_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
      //   + "&key=" + System.url().url_encode(m_strUserId) + "." + System.url().url_encode(strUrl)
      //   + "&value=";

      //Application.http().get(strSetUrl, str, setUserString);

      ::file::path path = core_app_path("app-veriwell/waven");

      string strCmd = "\"" + strUrl + "\" : for_resident=" + m_strUserId;

      call_async(path, strCmd, path.folder(), SW_SHOW, false);

      //property_set set(get_app());

      int iWait = 0;

      //string strGetUrl = "https://api.ca2.cc/account/get_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
      //   + "&key=" + System.url().url_encode(m_strUserId) + "." + System.url().url_encode(strUrl);

      var_array vara;

      while (true)
      {

         {

            single_lock sl(Application.mainstage().m_pmutex);

            for (index i = 0; i < Application.mainstage().m_varaWavenResponse.get_size(); i++)
            {

               if (Application.mainstage().m_varaWavenResponse[i][0].get_string() == strUrl)
               {
                  vara = Application.mainstage().m_varaWavenResponse[i];
                  Application.mainstage().m_varaWavenResponse.remove_at(i);
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

      set_user_var(m_strUserId, "ss", straNew);

      str = strNew;

      if(str.is_empty())
      {

         str = "(no results)";

      }
      else
      {

         var v = get_user_data(m_strUserId, "experience");

         set_user_data(m_strUserId, "experience", v.i64() + 1);

      }

   }
   else if ((bPlay = ::str::begins_eat_ci(strQuery, "!p ")) || ::str::begins_eat_ci(strQuery, "!q "))
   {

      auto puser = get_user(strUser, true);

      if (puser == NULL)
      {

         return "";

      }

      if (puser->get_points() < 25)
      {

         str = _("You need at least 25 points to complete song request");

      }
      else
      {

         if (strQuery.get_length() == 1)
         {

            if (isdigit_dup(strQuery[0]))
            {

               int i = atoi(strQuery);

               stringa stra;

               stra = get_user_var(m_strUserId, "ss").stra();

               if (i <= 0 || i > stra.get_size())
               {

                  str = "no such song";

               }
               else
               {

                  str = stra[i - 1];

                  string strAddUp;

                  if (bPlay)
                  {

                     strAddUp = "play_now";

                  }

                  ::file::path path = core_app_path("app-veriwell/waven");

                  string strCmd = "\"" + str + "\" : " + strAddUp + " for_resident=" + m_strUserId;

                  call_async(path, strCmd, path.folder(), SW_SHOW, false);

               }

            }

         }

         if (str != "no such song")
         {

            //property_set set(get_app());

            int iWait = 0;

            //string strGetUrl = "https://api.ca2.cc/account/get_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
            //   + "&key=" + System.url().url_encode(m_strUserId) + "." + System.url().url_encode(strUrl);

            var_array vara;

            while (true)
            {

               {

                  single_lock sl(Application.mainstage().m_pmutex);

                  for (index i = 0; i < Application.mainstage().m_varaWavenResponse.get_size(); i++)
                  {

                     if (Application.mainstage().m_varaWavenResponse[i][0].get_string() == str)
                     {
                        vara = Application.mainstage().m_varaWavenResponse[i];
                        Application.mainstage().m_varaWavenResponse.remove_at(i);
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

               puser->discount_points(25);

            }
            else
            {

               str = "(no results)";

            }

         }

      }

   }
   else if (::str::begins_eat_ci(strText, "!p spotify:track:")
            || ::str::begins_eat_ci(strText, "!spotify:track:")
            || ::str::begins_eat_ci(strText, "spotify:track:")
            || ::str::begins_eat_ci(strText, "https://open.spotify.com/track/"))
   {

      ::file::path path = core_app_path("app-veriwell/waven");

      string strCmd = "\"spotify:track:" + strText + "\" : play_now";

      call_async(path, strCmd, path.folder(), SW_SHOW, false);

   }
   else if(::str::begins_ci(strText, "!q spotify:track:"))
   {

      ::file::path path = core_app_path("app-veriwell/waven");

      call_async(path, "\"" + strText.substr(1) + "\"", path.folder(), SW_SHOW, false);

   }
   else if (
   strText == "!"
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

      ::resident::user * puser = get_user(strTopicUser, true);

      string strUsername = username(strTopicUser, strLang, false, puser);

      string strWeatherQuery;

      string strCountryCode;

      string strCity;

      bool bLocation = false;

      string strWeather = user_weather(puser, strWeatherQuery, strCountryCode, strCity, bLocation);

      string strCountry = get_country(strCountryCode);

      string strTime = user_time_text(puser, m_strLang, true, false);


#ifdef __XMPP

      string strTopScope = puser->get_user_info("favorite_programming", false);

#else

      string strTopScope = puser->m_strBio;

#endif

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

      strTopic = get_user(strTopicUser, true)->get_user_city(true, false);

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
   else if (about_user("points"))
   {

      strTopic = ::str::from(get_user(strTopicUser, false)->get_points());

      if (is_about_self())
      {

         str = _t("%name you have %topic points.");

      }
      else
      {

         str = _t2("%name, %param1 has %topic points.");

      }

   }
   else if (about_user("exp"))
   {

      strTopic = ::str::from(get_user(strTopicUser, false)->get_experience());

      if (is_about_self())
      {

         str = _t("%name you have %topic experience.");

      }
      else
      {

         str = _t2("%name, %param1 has %topic experience.");

      }

   }
   else if (strText.compare_ci("!prestodo") == 0 || ::str::begins_ci(strText, "!prestodo "))
   {

      // if (!bAdmin)
      // {

      //    return not_admin();

      // }

      str = prestodo(strSpeakText);

   }
   else if (strText == "!pres")
   {

      ::resident::comm * pcomm = m_pcomm;

      stringa straUser;

      pcomm->get_present_users(straUser);

      string strSpeakText;

      string str;

      string strName;

      stringa straFiltered;

      stringa straBot;

      string strBot;

      stringa stra;

      int cGuest = 0;

      //stra.explode("@", pcomm->m_strRoomJid);

      string strRoom;

      //if (stra.get_count() > 0)
      {

         // strRoom = stra[0];
         strRoom = strUser;

      }

      stra.explode("@", pcomm->m_strBot);

      //string strBot;

      //::count cGuest = 0;

      if (stra.get_count() > 0)
      {

         strBot = stra[0];

      }

      int iAddUp = 0;

      int iAddUpBot = 0;

      for (index i = 0; i < straUser; i++)
      {

         string strItem = straUser[i];

         //string strName = username(strItem, strLang);

         //string strJid = pcomm->m_straPresenceJid[i];

         if (strRoom.has_char() && strItem.compare_ci(strRoom)==0)
         {

            string str1 = _t("\"myself\"");

            straFiltered.add_unique(str1);

         }
         else if (strBot.has_char() && strItem.compare_ci(strBot) == 0)
         {

            strName = username(strItem, strLang);

            straBot.add_unique(strName);

         }
         else
         {

            if (::str::begins_ci(strItem, "guest_"))
            {

               cGuest++;

            }
            else
            {

               strName = username(strItem, strLang);

               if (isbot(strItem) || isbot(strName))
               {

                  straBot.add_unique(strName);

               }
               else
               {

                  straFiltered.add_unique(strName);

               }

            }

         }

      }

      string & strTopic = m_strTopic;

      ::count cOnline = straFiltered.get_count() + cGuest;

      strTopic = ::str::from(cOnline);

      if (cOnline <= 0)
      {

         str = _t("%name, There is no online person at chat");

      }
      else if (cOnline == 1)
      {

         str = _t("%name, There is 1 online person at chat");

      }
      else
      {

         str = _t("%name, There are %topic online people at chat");

      }

      straFiltered.sort();

      string strTime = straFiltered._008IfImplode(" : ", ", ", " " + l_and(strLang) + " ", cGuest > 0);;

      str += strTime;

      strSpeakText += strTime;

      if (cGuest > 0)
      {

         if (straFiltered.get_count() > 0)
         {

            //str += "\n";
            str += " ";

         }

         if (cGuest == 1)
         {

            str += _t2("and one guest.");

         }
         else
         {

            strTopic = ::str::from(cGuest);

            str += _t2("and %topic guests.");

         }

      }

      if (straBot.get_count() > 0)
      {

         strTopic = ::str::from(straBot.get_count());

         if (straBot.get_count() <= 0)
         {

            str += " " + _t2("and no detected bots.");

         }
         else if (straBot.get_count() == 1)
         {

            str += " " + _t2("and 1 detected bot");

         }
         else
         {

            str += " " + _t2("and %topic detected bots");

         }

         strTime = straBot._008IfImplode(" : ", ", ", " " + l_and(strLang) + " ");

         str += strTime;

         strSpeakText += strTime;

      }

      if (str.has_char())
      {

         Application.mainstage().schedule_speech(strUser, strLang, str, strSpeakText, this);

      }
      else
      {

         if (!lspeak(strUser, strLang, str, true))
         {

         }

      }

      pcomm->post_message(str, true);

   }
   else if (strText == "!live")
   {
#ifdef __XMPP

      __pointer(::resident::comm) pcomm = m_pcomm;

      var v;

      if(!pcomm->api_get("/api/livestreams/onair/", v, "bot"))
      {

         str = _t("(error)");

      }
      else
      {

         stringa stra;

         for (auto & i : v["results"].vara())
         {
            if ((bool)i["is_live"])
            {
               stra.add(i["user__slug"]);
            }
         }
         stra.sort();

         strTopic = ::str::from(stra.get_count());

         str = _t("%name, There are %topic live streams");

         if (stra.get_count() > 0)
         {

            str += " ";

            str += stra._008Implode(", ", " " + l_and(strLang) + " ");

         }

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
   else if (strText.compare_ci("!song url") == 0)
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
   else if(target_info("help") || target_info("hlp") || target_info("hlep") || target_info("commands") || target_info("command"))
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
         str = _t("!setname \"name\"\n!setcity \"city\"\n!setcc \"two-letter country code\"\n!setcountry \"country name\"\n!setlang \"country code\"\n!cc\n!land\n!getlang, and\n!setzone \"time zone\"");

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
         str = _t("!rr\n!rickroll\n!say \"text\"\n!song\n!song url\n!play \"sound\"\n!play\n!stop\n!next\n!previous\n!roll");

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
   else if(target_info("crossplatform"))
   {

      defer_extra_to_vocative();

      str = _t("explain to %name that I am now coding cross platform round");

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

         strTopic = "Sierra";

         defer_vocative(stra, iParamCount);

         str = _t("%name, At MacOS, ca2 uses macOS %topic, XCode and SmartSVN.");

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
   || strLoText == "!last"
   || strLoText == "!roulette")
   {

      string strCommand = "mediaplay:execute_" + strLoText.Mid(1);

      ::file::path path = core_app_path("app-veriwell/waven");

      call_async(path, " : " + strCommand, path.folder(), SW_SHOW, false);

   }
   else if (::str::begins_eat_ci(strText, "!volume "))
   {

      ::file::path path = core_app_path("app-veriwell/waven");

      call_async(path.folder(), " : mediaplay:set_volume=" + strText, path.folder(), SW_SHOW, false);

   }
   else if (::str::begins_eat_ci(strText, "!playlist "))
   {

      string strNew;

      int iWait = 0;

      string strLo = strText;

      strLo.make_lower();

      if (strLo == "next" || strLo == "previous")
      {

         call_async(core_app_path("app-veriwell/waven"), " : mediaplay:playlist_" + strLo, core_app_path("app-veriwell/waven").folder(), SW_SHOW, false);

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.mainstage().m_pmutex);

               for (index i = 0; i < Application.mainstage().m_varaWavenResponse.get_size(); i++)
               {

                  if (Application.mainstage().m_varaWavenResponse[i][0].get_string() == "mediaplay:playlist_next"
                        || Application.mainstage().m_varaWavenResponse[i][0].get_string() == "mediaplay:playlist_previous")
                  {
                     vara = Application.mainstage().m_varaWavenResponse[i];
                     Application.mainstage().m_varaWavenResponse.remove_at(i);
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

               strTopic = str;

               if (strLo == "next")
               {

                  str = _t("Next Playlist: %topic");

               }
               else
               {

                  str = _t("Previous Playlist: %topic");

               }

               Application.mainstage().broad_msg(str, strLang);

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
         //   + "&key=" + System.url().url_encode(m_strUserId) + "." + System.url().url_encode(strUrl)
         //   + "&value=";

         //Application.http().get(strSetUrl, str, setUserString);

         ::file::path path = core_app_path("app-veriwell/waven");

         call_async(path, " : mediaplay:playlist_list", path.folder(), SW_SHOW, false);

         //property_set set(get_app());

         int iWait = 0;

         //string strGetUrl = "https://api.ca2.cc/account/get_user_string?sessid=" + Session.fontopus()->get_user()->get_sessid("api.ca2.cc")
         //   + "&key=" + System.url().url_encode(m_strUserId) + "." + System.url().url_encode(strUrl);

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.mainstage().m_pmutex);

               for (index i = 0; i < Application.mainstage().m_varaWavenResponse.get_size(); i++)
               {

                  if (Application.mainstage().m_varaWavenResponse[i][0].get_string() == "mediaplay:playlist_list")
                  {
                     vara = Application.mainstage().m_varaWavenResponse[i];
                     Application.mainstage().m_varaWavenResponse.remove_at(i);
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

         ::file::path path = core_app_path("app-veriwell/waven");

         call_async(path, " : " + strCommand, path.folder(), SW_SHOW, false);

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.mainstage().m_pmutex);

               for (index i = 0; i < Application.mainstage().m_varaWavenResponse.get_size(); i++)
               {

                  if (Application.mainstage().m_varaWavenResponse[i][0].get_string() == strCommand)
                  {
                     vara = Application.mainstage().m_varaWavenResponse[i];
                     Application.mainstage().m_varaWavenResponse.remove_at(i);
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

         ::file::path path = core_app_path("app-veriwell/waven");

         call_async(path, " : " + strCommand, path.folder(), SW_SHOW, false);

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.mainstage().m_pmutex);

               for (index i = 0; i < Application.mainstage().m_varaWavenResponse.get_size(); i++)
               {

                  if (Application.mainstage().m_varaWavenResponse[i][0].get_string() == strCommand)
                  {
                     vara = Application.mainstage().m_varaWavenResponse[i];
                     Application.mainstage().m_varaWavenResponse.remove_at(i);
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

         ::file::path path = core_app_path("app-veriwell/waven");

         call_async(path, " : " + strCommand, path.folder(), SW_SHOW, false);

         var_array vara;

         while (true)
         {

            {

               single_lock sl(Application.mainstage().m_pmutex);

               for (index i = 0; i < Application.mainstage().m_varaWavenResponse.get_size(); i++)
               {

                  if (Application.mainstage().m_varaWavenResponse[i][0].get_string() == strCommand)
                  {
                     vara = Application.mainstage().m_varaWavenResponse[i];
                     Application.mainstage().m_varaWavenResponse.remove_at(i);
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

      olink(strUser,"http://www.urbandictionary.com/define.php?term=" + url_encode(strText), "urban_dictionary");

   }
   else if (strText.get_length() > 7 && ::str::begins_eat(strText, "!urban "))
   {

      olink(strUser, "http://www.urbandictionary.com/define.php?term=" + url_encode(strText), "urban_dictionary");

   }
   else if(strText.get_length() > 4 && ::str::begins(strText,"!at "))
   {
      auto_translate(strUser,glang(strLang),strText.substr(4));
   }
   else if(strText.get_length() > 3 && ::str::begins(strText,"!t ") && strText.substr(5,1) == " ")
   {
      translate(strUser,glang(strText.substr(3,2)),glang(strLang),strText.substr(6));
   }
   else if (strText.compare_ci("!lctv") == 0)
   {
      lctv_profile(strUserParam, strUser);
   }
   else if (::str::begins_eat_ci(strText, "!lctv "))
   {
      lctv_profile(strUserParam, strText);
   }
   else if (::str::begins_eat_ci(strText, "!sr "))
   {

      string strServer = System.url().get_server(strText);

      if (::str::find_wwci("youtube.com", strServer) >= 0)
      {

         waven_add_to_playlist(strText);

      }
      else if (::str::find_wwci("youtu.be", strServer) >= 0)
      {

         waven_add_to_playlist(strText);

      }
      else
      {


         str = _t("%name, not going to open this link!");

      }

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
   else if (third_info("defzone") || third_info("resetzone"))
   {

      string strCurrentUser = m_strExtra;

      if (strCurrentUser.is_empty())
      {

         if (m_strOtherUserId.compare_ci(m_strUserId) != 0 && m_strOtherUserId.has_char())
         {

            strCurrentUser = m_strOtherUserId;

         }
         else
         {

            strCurrentUser = m_strUserId;

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

      //i64 iId;

      //double dLat;

      //double dLon;

      auto pcity = System.openweather_find_city(strQ);

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
               "http://api.timezonedb.com/?key=" + file_as_string(strPath)
               + "&format=json&lat="+strLat+"&lng="+strLng,
               set);

         if (str.has_char())
         {

            const char * pszJson = str;

            var v;

            v.parse_json(pszJson);

            double dUTCOffset = v["gmtOffset"].get_double() / 3600.0;

            string strTimeZoneText = v["abbreviation"];

            param(1, v["countryCode"]);
            param(2, v["zoneName"]);
            param(3, strTimeZoneText);
            param(4, ::str::from(dUTCOffset));
            param(5, v["dst"].get_bool() ? "true" : "false");

            bool bReset = false;

            if(::str::begins_ci(strLoText, "!resetzone"))
            {

               if (strCurrentUser.compare_ci(strUser) == 0 || bAdmin)
               {

                  set_user_data(strCurrentUser, "time_zone", dUTCOffset);

                  set_user_data(strCurrentUser, "time_zone_text", strTimeZoneText);

                  bReset = true;

               }

            }

            m_strTopic = strCurrentUser;

            if (bReset)
            {

               str = _t("%name, default time zone for %topic reset to: country code: %param1, zone name: %param2, abbreviation: %param3, UTC: %param4, daylight saving: %param5");

            }
            else
            {

               str = _t("%name, default time zone information for %topic is: code: %param1, zone name: %param2, abbreviation: %param3, UTC: %param4, daylight saving: %param5");

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

         if (m_strOtherUserId.compare_ci(m_strUserId) != 0 && m_strOtherUserId.has_char())
         {

            strCurrentUser = m_strOtherUserId;

         }
         else
         {

            strCurrentUser = m_strUserId;

         }

      }

      ::resident::user * puser = get_user(strCurrentUser, false);

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

            if (strCurrentUser.compare_ci(m_strUserId) == 0)
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

      strTopic = user_time_text(strTopicUser, m_strLang, false, false);

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

         dUTCOffset = System.datetime().time_zone(strText, get_user(strUser)->get_user_country_code(false, true));

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
   else if (::str::begins_eat(strText, "!setcity "))
   {

#ifdef __XMPP

      str = "Please change your city in your Livecoding.tv profile";

#else

      set_user_data(strUser, "city", strText);

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      set_user_data(strUser, "city_set", timeNow.m_time);

      if (get_user_data(strUser, "city_set") != 0)
      {

         strTopic = get_user_data(strUser, "city");

      }

      if (strTopic.has_char())
      {

         str = _t("%name, your city was set to %topic.");

      }
      else
      {

         str = _t("I could not set your city, call Camilo to heal me.");

      }

#endif

   }
   else if (::str::begins_eat(strText, "!setcc "))
   {

#ifdef __XMPP

      str = "Please change your country in your Livecoding.tv profile";

#else

      if (strText.get_length() != 2)
      {

         str = _t("%name, the country code should be 2-letter country code.");

      }
      else
      {

         strText.make_upper();

         set_user_data(strUser, "country_code", strText);

         ::datetime::time timeNow = ::datetime::time::get_current_time();

         set_user_data(strUser, "country_code_set", itoa_dup(timeNow.m_time));

         strTopic.Empty();

         if (get_user_data(strUser, "country_code_set") != 0)
         {

            strTopic = get_user_data(strUser, "country_code");

         }

         if (strTopic.has_char())
         {

            str = _t("%name, your country code was set to %topic.");

         }
         else
         {

            str = _t("I could not set your country code, call Camilo to heal me.");

         }

      }

#endif

   }
   else if (::str::begins_eat(strText, "!setcountry "))
   {

#ifdef __XMPP

      str = "Please change your country in your Livecoding.tv profile";

#else

      string strCC = get_country_code(strLang, strText);

      if (strCC.is_empty())
      {

         strCC = get_country_code("en", strText);

      }

      if (strCC.get_length() != 2)
      {

         str = _t("%name, the country name you typed in (\"" + strText  +"\") was not recognized. Check for correct spelling or use !setcc command to set two-letter country code.");

      }
      else
      {

         strTopic.Empty();

         strCC.make_upper();

         set_user_data(strUser, "country_code", strCC);

         ::datetime::time timeNow = ::datetime::time::get_current_time();

         set_user_data(strUser, "country_code_set", itoa_dup(timeNow.m_time));

         if (get_user_data(strUser, "country_code_set") != 0)
         {

            strTopic = get_country(strLang, get_user_data(strUser, "country_code"));

         }

         if (strTopic.has_char())
         {

            str = _t("%name, your country was set to %topic.");

         }
         else
         {

            str = _t("I could not set your country code, call Camilo to heal me.");

         }

      }

#endif

   }
   else if(about_user("getzone"))
   {

      double dUTCOffset = get_user(strTopicUser)->user_time_zone();

      strTopic = System.datetime().utc_offset_string(dUTCOffset);

      if(get_user(strUser)->get_user_data("time_zone_text").has_char() && get_user(strTopicUser)->get_user_data("time_zone_text").get_string().upper().compare_ci(strTopic) != 0)
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

            str = L"В списке воспроизведения нет файлов";

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
//      if (::str::begins_ci(str, "spotify:track:"))
//      {
//
//         ::file::path path = core_app_path("app-veriwell/waven");
//
//         call_async(path, str, path.folder, SW_SHOW, false);
//
//      }
//      else
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
            stringa a = ls_names(Application.resident_get_app_path("resident") / "text");
            bool found = false;
            int i = 0;
            for (; i < a.get_count() && !found; i++)
            {
               if (a[i].lower() == str.lower())
               {
                  found = true;
               }
            }

            if(found)
            {

               ::file::path path = Application.resident_get_app_path("resident") / "text" / str + ".txt";

               str = file_as_string(path);

               strSpeakText = str;

            }
            else if(::str::begins_eat_ci(strText, "-") || strUser.compare_ci("RevloBot") == 0 || strUser.compare_ci("Nightbot") == 0 || strUser.contains_ci("bot")) // botanical also matches (bots too??!)
            {
               str = strText;
               {
                  string strLink = _t("at this link");
                  strsize iFind = 0;
                  while ((iFind = str.find_ci("http://", iFind)) >= 0)
                  {
                     if (iFind == 0 || !(isalpha_dup(str[iFind - 1]) || isdigit_dup(str[iFind - 1])))
                     {
                        strsize iPos = iFind + 7;
                        while (iPos < str.get_length() && (isalpha_dup(str[iPos])) || isdigit_dup(str[iPos])
                               || str[iPos] == '/' || str[iPos] == '+' || str[iPos] == '_' || str[iPos] == '-'
                               || str[iPos] == ':' || str[iPos] == '@' || str[iPos] == '?' || str[iPos] == '!'
                               || str[iPos] == ',' || str[iPos] == '.' || str[iPos] == '&' || str[iPos] == '='
                               || str[iPos] == '(' || str[iPos] == ')' || str[iPos] == '[' || str[iPos] == ']'
                               || str[iPos] == '%')
                        {
                           iPos++;
                        }
                        str = str.Left(iFind) + " "+strLink+ " " + str.Mid(iPos);
                        iFind += strLink.get_length() + 2;
                     }
                     else
                     {
                        iFind = iFind + 7;
                     }
                  }
                  iFind = 0;
                  while ((iFind = str.find_ci("https://", iFind)) >= 0)
                  {
                     if (iFind == 0 || !(isalpha_dup(str[iFind - 1]) || isdigit_dup(str[iFind - 1])))
                     {
                        strsize iPos = iFind + 8;
                        while (iPos < str.get_length() && (isalpha_dup(str[iPos])) || isdigit_dup(str[iPos])
                               || str[iPos] == '/' || str[iPos] == '+' || str[iPos] == '_' || str[iPos] == '-'
                               || str[iPos] == ':' || str[iPos] == '@' || str[iPos] == '?' || str[iPos] == '!'
                               || str[iPos] == ',' || str[iPos] == '.' || str[iPos] == '&' || str[iPos] == '='
                               || str[iPos] == '(' || str[iPos] == ')' || str[iPos] == '[' || str[iPos] == ']'
                               || str[iPos] == '%')
                        {
                           iPos++;
                        }
                        str = str.Left(iFind) + " " + strLink + " " + str.Mid(iPos);
                        iFind += strLink.get_length() + 2;
                     }
                     else
                     {
                        iFind = iFind + 8;
                     }
                  }

               }
               {
                  string strLink = _t("at this spotify track");
                  strsize iFind = 0;
                  while ((iFind = str.find_ci("spotify:track:", iFind)) >= 0)
                  {
                     if (iFind == 0 || !(isalpha_dup(str[iFind - 1]) || isdigit_dup(str[iFind - 1])))
                     {
                        strsize iPos = iFind + 14;
                        while (iPos < str.get_length() && (isalpha_dup(str[iPos])) || isdigit_dup(str[iPos]))
                        {
                           iPos++;
                        }
                        str = str.Left(iFind) + " " + strLink + " " + str.Mid(iPos);
                        iFind += strLink.get_length() + 2;
                     }
                     else
                     {
                        iFind = iFind + 14;
                     }
                  }
               }
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
            else
            {
               return "";
               //str = _t("to speak a text, use exclamation mark followed by space character");
            }

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

      string strMessage = m_pcomm->prepare_message(str);

      Application.mainstage().schedule_speech(strUser, m_strLang, strMessage, strSpeakText, this);

      m_pcomm->post_message(strMessage, true);

   }
   else if(strSpeakText.has_char())
   {

      if (!lspeak(strUser, m_strLang, strSpeakText, true))
      {

      }

   }

   return "";

}



string not_admin()
{

   return "";

}

