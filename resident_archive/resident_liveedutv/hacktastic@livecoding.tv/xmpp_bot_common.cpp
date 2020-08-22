   {
      m_straSpecialCommand.add("exclamation");
      m_straSpecialCommand.add("exclamation mark");
   }

   stringa m_straSpecialCommand;

#define _t(strText) get_text(strLang, strText, strName, strTopic)

   string_map < string_to_string > m_text;

   string_map < file_time > m_ftime;

   bool _load_text(string strLang)
   {
      
      auto & m = m_text[strLang];

      ::file::path path = "C:\\ca2\\config\\xmpp_resident\\room\\"+comm()->m_strRoomJid+"\\xmpp_resident_po\\" + strLang + ".po";

      ::file_time ft = get_file_time(path);

      if (m_ftime[strLang] == ft)
      {

         return true;

      }

      m_ftime[strLang] = ft;

      string strPo = Application.file().as_string(path);

      stringa stra;

      stra.add_lines(strPo);
      int iState = -1;
      string strMsgId;
      string strText;

      for (index i = 0; i < stra.get_count();  i++)
      {
         string strLine = stra[i];

         const char * psz = strLine;
         const char * pszEnd = psz + strLine.get_length();

         ::str::consume_spaces(psz, 0, pszEnd);
         try
         {
            if (iState == -1)
            {
               strMsgId = ::str::consume_nc_name(psz);
               if (strMsgId == "msgid")
               {
                  iState = 0;
                  ::str::consume_spaces(psz, 1, pszEnd);
                  strMsgId = ::str::consume_quoted_value_ex(psz, pszEnd);
               }
            }
            else if (iState == 0)
            {
               strText = ::str::consume_nc_name(psz);
               if (strText == "msgtext")
               {
                  iState = -1;
                  ::str::consume_spaces(psz, 1, pszEnd);
                  strText = ::str::consume_quoted_value_ex(psz, pszEnd);
                  m[strMsgId] = strText;
               }


            }
         }
         catch (...)
         {
            

         }
      }


      return true;

   }

   string _get_text(string strLang, string strId)
   {

      _load_text(strLang);

      auto p = m_text.PLookup(strLang);

      if (p == NULL)
      {

//         _load_text(strLang);

  //       p = m_text.PLookup(strLang);

    //     if (p == NULL)
      //   {

        //    return strId;

         //}

         return strId;

      }

      if(p->m_element2[strId].is_empty())
         return strId;
      else
         return p->m_element2[strId];

   }

   string get_text(string strLang, string strId, string strName, string strTopic)
   {

      string strText = _get_text(strLang, strId);

      return process_text(strText, strName, strTopic);

   }

   string process_text(string strText, string strName, string strTopic)
   {
      int iFind = 0;
      while (true)
      {
         iFind = strText.find_ci("%name", iFind);

         if (iFind < 0)
            break;

         if (iFind == 0)
         {
            strText = strName + strText.Mid(5);
         }
         // lazy check, it is not correct way of checking, it may result errors (triple %)
         else if(strText[iFind - 1] != '%')
         {
            strText = strText.Left(iFind) + strName + strText.Mid(iFind + 5);
         }
         iFind += 5;
      }
      iFind = 0;
      while (true)
      {
         iFind = strText.find_ci("%topic", iFind);

         if (iFind < 0)
            break;

         if (iFind == 0)
         {
            strText = strName + strText.Mid(6);
         }
         // lazy check, it is not correct way of checking, it may result errors (triple %)
         else if (strText[iFind - 1] != '%')
         {
            strText = strText.Left(iFind) + strTopic + strText.Mid(iFind + 6);
         }
         iFind += 6;
      }
      return strText;
   }

   string warn(string strUser)
   {
      return "This operation is not permitted to you, " + strUser + "! Contact moderator if you think its wrong.";
   }
   bool enable_speech(string strLang)
   {

      if (strLang == "en")
      {
         return true;
      }
      else if (strLang == "fr")
      {
         return true;
      }
      else if (strLang == "de")
      {
         return true;
      }
      else if (strLang == "pl")
      {
         return true;
      }
      else if (strLang == "zh")
      {
         return true;
      }
      else if (strLang == "cn")
      {
         return true;
      }
      else if (strLang == "pt")
      {
         return true;
      }
      else if (strLang == "br")
      {
         return true;
      }
      else if (strLang == "es")
      {
         return true;
      }
      else if (strLang == "it")
      {
         return true;
      }
      else
      {
         return false;
      }

   }

   bool isbot(string strUser)
   {
      
      if (::str::find_ci(strUser, "l3vl69") >= 0)
      {
         return true;
      }
      else if(::str::find_ci(strUser,"iamfree") >= 0)
      {
         return true;
      }
      else if(::str::find_ci(strUser,"iwanttodie") >= 0)
      {
         return true;
      }
      else if(::str::begins_ci(strUser,"bot"))
      {
         return true;
      }
      else if(::str::ends_ci(strUser,"bot"))
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   void olink(string strUser,string strUrl)
   {
      if(spam(strUser))
      {
      }
      else
      {
         open_link(strUrl);
      }
   }
   bool spam(string strUser)
   {
      if(::str::begins_ci(strUser,"spam"))
      {
         return true;
      }
      else if(::str::ends_ci(strUser,"spam"))
      {
         return true;
      }
      else if(strUser.CompareNoCase("coldzer0") == 0)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   void lspeak(string strUser,string strLang,string strText)
   {
      if(spam(strUser))
      {
      }
      else if (!enable_speech(strLang))
      {
      }
      else
      {
         lang_speak(strLang,strText);
      }
   }
   string  lang(string strLang)
   {
      if(strLang == "br")
      {
         return "pt";
      }
      else if(strLang == "do")
      {
         return "es";
      }
      else if(strLang == "co")
      {
         return "es";
      }
      else if(strLang == "pe")
      {
         return "es";
      }
      else if(strLang == "ec")
      {
         return "es";
      }
      else if(strLang == "mx")
      {
         return "es";
      }
      else if(strLang == "pa")
      {
         return "es";
      }
      else if(strLang == "py")
      {
         return "es";
      }
      else if(strLang == "uy")
      {
         return "es";
      }
      else if(strLang == "ar")
      {
         return "es";
      }
      else if(strLang == "cl")
      {
         return "es";
      }
      else if(strLang == "us")
      {
         return "en";
      }
      else if(strLang == "uk")
      {
         return "en-uk";
      }
      else if(strLang == "en-uk")
      {
         return "en-uk";
      }
      else
      {
         stringa stra;
         stra.explode("-",strLang);
         if(stra.get_count() == 2)
         {
            return lang(stra[0]);
         }
         else
         {
            return strLang;
         }
      }
   }
   string  initial_country_lang(string strCountry)
   {
      if (strCountry == "de")
      {
         return "en";
      }
      else 
      {
         return lang(strCountry);
      }
   }
   double  time_zone(string str)
   {
      str.make_lower();
      //Московское время (UTC+3)
      if(str == "msk")
      {
         return 3.0;

      }

      else if(str == "brt")
      {
         return -2.0;
      }
      else if(str == "cet")
      {
         return 1.0;
      }

      else
      {
         return 1000.0; // earth?
      }
   }
   string glang(string strLang)
   {
      if(strLang == "en")
      {
         return "en";
      }
      else if(strLang == "jp")
      {
         return "ja";
      }
      else
      {
         return lang(strLang);
      }
   }
   string l_and(string strLang)
   {
      if(strLang == "de")
      {
         return "und";
      }
      if(strLang == "pt")
      {
         return "e";
      }
      if(strLang == "fr")
      {
         return "et";
      }
      if(strLang == "ru")
      {
         return "и";
      }
      return "and";
   }
   string username(string strUser)
   {
      var strName = get_user_data(strUser,"name");
      if(strName.is_empty())
      {
         strName = strUser;
      }
      return strName;
   }
   void ws() // welcome sound
   {
      play_sound("C:\\ca2\\audio\\hidden\\glockd.wav");
   }
   void bye() // welcome sound
   {
      play_sound("C:\\ca2\\audio\\hidden\\chirp7.wav");
   }
   void auto_translate(string strUser,string strDst,string strText)
   {
      olink(strUser,"https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#auto/" + strDst + "/" + url_encode(strText));
   }
   void translate(string strUser,string strDst,string strSrc,string strText)
   {
      olink(strUser,"https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#" + strSrc + "/" + strDst + "/" + url_encode(strText));
   }
   string bot_x(string strName,string strUser,string strText,string strCountry,string strLang)
   {
      string strTopic;
      string str;
      if(strText == "!" || strText == "exclamation" || strText == "exclamation mark")
      {
         str = _t("%name, Some supported commands !hlp, !about and !vaimepassarobot?");
      }
      else if(strText == "!reset!")
      {
         set_user_data(strUser,"country","");
         set_user_data(strUser,"lang","");
         set_user_data(strUser,"visit_count","");
         set_user_data(strUser,"last_visit","");
         set_user_data(strUser,"last_visit_time","");
      }
      else if(strText == "!rickroll" || strText == "!rr" || strText == "!rick") // xmetrix commanded !rickroll (me: probably he is referring to Rick Astley hit...)
      {
         if(spam(strUser))
         {
            return warn(strUser);
         }
         else
         {
            str = rr(strName, strLang);
         }
      }
      else if(strText == "!song")
      {
         
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
      else if(strText == "!hlp")
      {

         str = _t("%name, help information is grouped in:\n!hlp util\n!hlp info\n!hlp config\n and\n!hlp media");

      }
      else if(strText == "!commands")
      {

         str = _t("%name, commands help info were grouped in:\n!commands info\n!commands config\n and\n!commands media");

      }
      else if(::str::begins(strText,"!hlp ") || ::str::begins(strText,"!commands "))
      {
         string strGroup(strText);
         var strC;
         strC = "";
         ::str::begins_eat(strGroup,"!commands ");
         ::str::begins_eat(strGroup,"!hlp ");
         if(strGroup == "config")
         {
            
            strGroup = _t(" settings commands are:");
            str = _t("!setname \"name\"\n!setlang \"country code\"\n and\n!setzone \"time zone\"");

         }
         else if(strGroup == "media")
         {

            strGroup = _t(" multimedia commands are:");
            str = _t("!rr\n!rickroll\n!say \"text\"\n!playlist\n and\n!play \"sound\"");

         }
         else if(strGroup == "util")
         {
             strGroup = _t(" some utility commands:");
             str = _t("!urbd \"urban dictionary query\"\n!at \"google auto translate\"\n and\n!t \"lang\" \"text to translate from lang\"");
         }
         else if(strGroup == "rr" || strGroup == "rickroll")
         {

            strC = _t("%name, !rr or !rickroll plays 80s hit Never Gonna Give You Up performed by Rick Astley with ASCII animation.");

         }
         else if(strGroup == "cmdtips")
         {
              
            strC = _t("%name, Use this command to get special tips");

         }
         else if(strGroup == "say")
         {

            strC = _t("%name, say uses Windows Narrator to speak the supplied text.");

         }
         else if(strGroup == "ide")
         {

            strC = _t("%name, ide <platform> display information about tools used for development of ca2 framework and apps at the specified platform. <platform> may be: windows (Desktop), linux, macos, ios, android and winrt.");

         }
         else if(strGroup == "setlang")
         {

            strC = _t("%name, setlang <language code and/or two-letter country code> sets user preferred language. Communication is preferrably done using specified language or country.");

         }
         else if(strGroup == "setname")
         {

            strC = _t("%name, use setname command to set better user name, matching nick or name, with desired capitalization and spacing. It can make it better the name pronunciantion by Text-To-Speech.");

         }
         else
         {

            strGroup = _t(" information retrieval commands are:");
            str = _t("!ide \"platform\"\n!hlp \"command\"\n!cmdtips\n!commands\n!about\n!vaimepassarobot?\n" + l_and(strLang) + "\n!credits");
      
         }

         if(strC.is_empty())
         {
            if(strLang == "pt")
            {
               str = strName + ", " + strGroup + "\n" + str;
            }
            else
            {
               str = strName + ", " + strGroup + "\n" + str;
            }
         }
         else
         {
            str = strC;
         }
      }
      else if(strText == "!ide windows")
      {

         str = _t("%name, For Windows Desktop Software Development, ca2 uses Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");

      }
      else if(strText == "!ide linux")
      {

         str = _t("%name, For Linux Software Development, ca2 uses latest version of Ubuntu LTS, Code::Blocks and SmartSVN.");

      }
      else if(strText == "!ide macos")
      {

         str = _t("%name, At MacOS, ca2 uses El Capitan, XCode and SmartSVN.");

      }
      else if(strText == "!ide ios")
      {

         str = _t("%name, for iOS development, ca2 uses Mac OS X El Capitan, XCode, SmartSVN, XCode iOS simulator and trying to convince co-founder to borrow iOS device.");

      }
      else if(strText == "!ide android")
      {
         
         str = _t("%name, for Android development, ca2 uses Windows with Hyper-V, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN, WinMerge, Visual Studio Emulator for Android and Galaxy Tab 3 (Door Prize for co-founder, gift for me, help for ca2 developers and users).");

      }
      else if(strText == "!ide winrt")
      {

         str = _t("%name, for Windows Store App development, ca2 uses Windows, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");

      }
      else if(strText == "!cmdtips")
      {

         str = _t("%name, For the exclamation mark, if an existing command is not found, an audio clip is played from !playlist. If a corresponding audio clip is not found, the text is played like in !say <text>");

      }
      else if(strText == "!about")
      {

         str = _t("%name, ca2 is an all-purpose multi-platform framework and set of libraries written in C++ language to help developers create great apps for users.");

      }
      else if(strText == "!credits")
      {
         str = _t("%name, user info user thumb, user country and user flag are supplied by xmetrix code, web api and web server.Thank you, Vapaamies for Russian translation.Thank you, r00tkiller for French translation.Thank you, andremommert for some German translation.Remarks many translations still Google.");
      }
      else if(strText.get_length() > 6 && ::str::begins_eat(strText,"!urbd "))
      {
         olink(strUser,"http://www.urbandictionary.com/define.php?term=" + url_encode(strText));
      }
      else if(strText.get_length() > 4 && ::str::begins(strText,"!at "))
      {
         auto_translate(strUser,glang(strLang),strText.substr(4));
      }
      else if(strText.get_length() > 3 && ::str::begins(strText,"!t ") && strText.substr(5,1) == " ")
      {
         translate(strUser,glang(strText.substr(3,2)),glang(strLang),strText.substr(6));
      }
      else if(strText == "!getlang")
      {

         string strTopic = ::str::from(get_user_data(strUser, "lang"));

         str = _t("%name, your language is set to %topic");

      }
      else if(strText.get_length() == 11 && ::str::begins_eat(strText,"!setlang "))
      {
         strLang = lang(strText);
         set_user_data(strUser,"lang",strLang);
         strLang = get_user_data(strUser,"lang");
         strTopic = strLang;
         str = _t("%name, your language was set to \"%topic\"");
      }
      else if(::str::begins_eat(strText,"!setzone "))
      {
         var v = strText;
         if(v.is_double())
         {
            set_user_data(strUser,"time_zone",v.get_double());
            set_user_data(strUser,"time_zone_text","");

            strTopic = ::str::from(get_user_data(strUser, "time_zone"));
            
            str = _t("%name, your time zone was set to UTC %topic");
            
         }
         else
         {
            double d = time_zone(strText);
            set_user_data(strUser,"time_zone_text",strText);
            set_user_data(strUser,"time_zone",d);

            strTopic = get_user_data(strUser,"time_zone_text");
               
            str  = _t("%name, your time zone was set to \"%topic\".");

            if(time_zone(get_user_data(strUser,"time_zone_text")) > 900.0)
            {

               str += _t(" Actually, it is currently \"Unknown Time Zone\". Yell ca2 on this (or not).");

            }

         }

      }
      else if(strText == "!getzone")
      {
         if(get_user_data(strUser,"time_zone_text").has_char())
         {
            strTopic = "\"" + get_user_data(strUser, "time_zone_text") + "\" : UTC " + ::str::from(user_time_zone(strUser));

            str = _t("%name, your time zone is set to %topic");

         }
         else
         {
            strTopic = ::str::from(user_time_zone(strUser));

            str = _t("%name, your time zone is set to UTC %topic");
         }
      }
      else if(strText.get_length() == 14 && ::str::begins_eat(strText,"!setlang ") && strText.substr(2,1) == "-")
      {
         strLang = lang(strText);
         set_user_data(strUser,"lang",strLang);
         strLang = get_user_data(strUser,"lang");
         set_user_data(strUser,"lang",strLang);
         set_user_data(strUser,"country",strText.substr(3,2));

         strTopic = strLang;

         str = _t("%name, your language was set to %topic");
            
         strTopic = ::str::from(get_user_data(strUser, "country"));
            
         str += _t(" and your country was set to %topic");

      }
      else if(strText == "!resetlang")
      {
         set_user_data(strUser,"lang","");
      }
      else if(strText == "!vaimepassarobot?") // question by julienb16 //2015-10-09 sexta-feira 23:23
      {

         str = _t("%name, Currently only the client will be made available.");

      }
      else if(strText == "!playlist")
      {
         stringa a = ls_names("C:\\ca2\\audio\\element");
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
         return str;
      }
      else
      {
         stringa a = ls_names("C:\\ca2\\audio\\element");
         str = strText.substr(1);
         bool found = false;
         int i = 0;
         for(; i < a.get_count() && !found; i++)
         {
            if(a[i].lower() == str.lower())
            {
               found = 1;
            }
         }
         if(found == 1)
         {
            play_sound("C:\\ca2\\audio\\element\\" + str + ".wav");
            return "";
         }
         else
         {
            str = strText;
            lspeak(strUser,strLang,str);
            return "";
         }
      }
      if(str.is_empty())
      {
         return "";
      }
      lspeak(strUser,strLang,str);
      return str;
   }

   string on_bot(string strUser,string strText)
   {
      if(!strText.begins_ci("!") && !m_straSpecialCommand.contains_ci(strText))
         return "";
      string strName = username(strUser);
      string strCountry = get_user_data(strUser,"country").get_string().lower();
      if(strCountry.is_empty())
      {
         strCountry = get_lctv_info(strUser,"country_code").get_string().lower();
         set_user_data(strUser,"country",strCountry);
      }
      string strLang = lang(get_user_data(strUser,"lang").get_string().lower());
      if(strLang.is_empty())
      {
         strLang = initial_country_lang(strCountry);
         set_user_data(strUser,"lang",strLang);
      }
      if(strText.get_length() > 9 && ::str::begins(strText,"!setname "))
      {
         var str = strText.substr(9);
         set_user_data(strUser,"name",str);
         lspeak(strUser,strLang,str);
         return "";
      }
      else if(strText.get_length() > 5 && ::str::begins(strText,"!say "))
      {
         var str = strText.substr(5);
         lspeak(strUser,strLang,str);
         return "";
      }
      else if(strText.get_length() > 6 && ::str::begins(strText,"!play "))
      {
         stringa a = ls_names("C:\\ca2\\audio\\element");
         string str = strText.substr(6);
         bool found = false;
         int i = 0;
         for(; i < a.get_count() && !found; i++)
         {
            if(a[i].lower() == str.lower())
            {
               found = true;
            }
         }
         if(found)
         {
            play_sound("C:\\ca2\\audio\\element\\" + str + ".wav");
            return "";
         }
         else
         {
            if(strLang == "ru")
            {

               return "Звук \"" + str + "\" не найден. Используйте команду !playlist для получения списка доступных звуков";

            }
            else
            {

               return "\"" + str + "\" not found. Please, use !playlist command to list existing sounds.";

            }

         }
      }
      stringa tokens;
      tokens.explode(" ",strText);
      if(tokens.get_count() == 1)
      {
         if(::str::begins(tokens.last(),"!@"))
         {
            strUser = tokens[0].substr(2);
            strText = "!";
         }
      }
      else
      {
         if(::str::begins(tokens.last(),"@"))
         {
            strUser = tokens.last().substr(1);
            string str = "";
            int i = 0;
            for(; i < tokens.get_upper_bound(); i++)
            {
               if(i > 0)
               {
                  str += " ";
               }
               str += tokens[i];
            }
            strText = str;
         }
      }
      strName = username(strUser);
      strCountry = get_user_data(strUser,"country").get_string().lower();
      if(strCountry.is_empty())
      {
         strCountry = get_lctv_info(strUser,"country_code").get_string().lower();
         set_user_data(strUser,"country",strCountry);
      }
      strLang = lang(get_user_data(strUser,"lang").get_string().lower());
      if(strLang.is_empty())
      {
         strLang = initial_country_lang(strCountry);
         set_user_data(strUser,"lang",strLang);
      }
      return bot_x(strName,strUser,strText,strCountry,strLang);
   }
   string on_pres(string strUser,string strType)
   {
      string strTopic;
      var strName = username(strUser);
      string strCountry = get_user_data(strUser,"country").get_string().lower();
      if(strCountry.is_empty())
      {
         strCountry = get_lctv_info(strUser,"country_code").get_string().lower();
         set_user_data(strUser,"country",strCountry);
      }
      string strLang = lang(get_user_data(strUser,"lang").get_string().lower());
      if(strLang.is_empty())
      {
         strLang = initial_country_lang(strCountry);
         set_user_data(strUser,"lang",strLang);
      }
      var strText;
      if(strType == "unavailable")
      {
         
         if(spam(strUser))
         {

            strText = _t("%name gone, uff...");

         }
         else if (isbot(strUser))
         {
            
            strText = _t("%name was unplugged!");

         }
         else
         {
            bye();
            if(get_user_data(strUser,"visit_count") <= 4)
            {

                strText = _t("Bye %name! :(");

            }
            else
            {
                
               strText = _t("See you %name!");

            }
         }
         lspeak(strUser,strLang,strText);
         return strText;
      }
      else
      {
         if(spam(strUser))
         {
            strText = strUser + " entered!! (Subset of commands enabled).";
            return strText;
         }
         else if(isbot(strUser))
         {
            strText = strName + " you are connected!";
         }
         else
         {
            ws();
            if(get_user_data(strUser,"visit_count") <= 4)
            {
               strText = _t("Welcome %name! :) You can type exclamation mark and then press enter to get some help.");
               if(strCountry == "be")
               {
                  strText += " You can choose between \"Deutsch\" and \"Français\" using \"!setlang de\" or \"!setlang fr\"";
               }
               else if(strCountry == "ch")
               {
                  strText += " You can choose between \"Deutsch\", \"Français\" and \"Italiano\" using \"!setlang de\", \"!setlang fr\" or \"!setlang it\"";
               }
            }
            else if(get_user_data(strUser,"last_visit") > 60 * 60 * 18 || get_user_data(strUser,"today_visit_count") <= 1)
            {

               strText = _t("Hi %name! Welcome! What brings you here today?");

            }
            else
            {

               strText = _t("%name is back! :)");

            }

         }

         lspeak(strUser,strLang,strText);

         return strText;

      }

   }


   string on_new_followers(stringa & straNew)
   {

      string str;

      stringa straLang;

      string strLastLang;

      bool bSameLang = true;

      for(auto strUser : straNew)
      {

         string strLang = lang(get_user_data(strUser,"lang").get_string().lower());
         if(strLang.is_empty())
         {
            string strCountry = get_user_data(strUser,"country").get_string().lower();
            if(strCountry.is_empty())
            {
               strCountry = get_lctv_info(strUser,"country_code").get_string().lower();
               set_user_data(strUser,"country",strCountry);
            }
            strLang = initial_country_lang(strCountry);
            set_user_data(strUser,"lang",strLang);
         }

         if(strLastLang.is_empty())
         {

            strLastLang = strLang;

         }

         if(strLang.get_length() < 2 || strLastLang.get_length() < 2 || strLang.Left(2) != strLastLang.Left(2))
         {

            bSameLang = false;

         }

         if(strLang == "pt")
         {

            str += "Te dou Boas Vindas, " + strUser + "! Obrigado por seguir!";

         }
         else
         {

            str += "You're welcome, " + strUser + "! Thank you for following!";

         }

         strLastLang = strLang;

      }

      bool bMsg = true;
      
      if(bSameLang)
      {

         if(strLastLang == "pt")
         {
            if(straNew.get_size() > 1)
            {

               str += "\nAbrindo o Rick Roll para todos vocês novos seguidores!!\n";

            }
            else
            {

               str += "\nAbrindo o Rick Roll para você!\n";

            }
         }
         else
         {
            bMsg = false;
         }
      }
      else
      {

         bMsg = false;

      }

      if(!bMsg)
      {
         if(straNew.get_size() > 1)
         {

            str += "\nOpening Rick Roll for you all new followers!!\n";

         }
         else
         {

            str += "\nOpening Rick Roll for you!!\n";

         }

         str += rr("en");

         lspeak("","en",str);

      }
      else
      {

         str += rr(strLastLang);

         lspeak("",strLastLang,str);

      }

      return str;

   }


   string rr(string strName, string strLang)
   {
      
      string strTopic;
      
      string str;

      str = _t("%name, Opening Rick Astley - Never Gonna Give You Up!");
   
      call_async("X:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "Y:\\bergedge\\hi5\\user\\northamerica\\us\\xmetrix\\never_gonna_give_you_up.asciimedia : dont_add_to_playlist", "X:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

      return str;

   }


   string rr(string strLang)
   {

      string strName;

      string strTopic;

      string str;

      str = _t("Opening Rick Astley - Never Gonna Give You Up!");

      call_async("X:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "Y:\\bergedge\\hi5\\user\\northamerica\\us\\xmetrix\\never_gonna_give_you_up.asciimedia : dont_add_to_playlist", "X:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

      return str;

   }




