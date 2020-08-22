string bot_a()
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

   string strSound;

   stringa straAdj;

   straAdj.add("nice");

   stringa straGreet;
   straGreet.add("welcome");
   straGreet.add("wb");

   string strUrl = strQuery;

   strUrl.trim();

   if (::url::is_url(strUrl))
   {

      string strServer = System.url().get_server(strUrl);

      if (::str::find_wwci("youtube.com", strServer) >= 0)
      {

         string strScript = System.url().get_script(strUrl);

         if (strScript.compare_ci("/watch") == 0)
         {

            waven_add_to_playlist(strUrl);

         }

      }
      else if (::str::find_wwci("youtu.be", strServer) >= 0)
      {

         waven_add_to_playlist(strUrl);

      }

   }
   else if (strUser != m_pcomm->m_strBot && strUser != m_pcomm->m_strBotId)
   {

      if (::str::x_contains(strQuery, "resident") || ::str::x_contains(strQuery, "bot") || ::str::x_contains(strQuery, "ca2bot"))
      {

         if (::str::x_find(straAdj, strQuery))
         {

            if (::str::x_find(straGreet, strQuery))
            {

               str = _t("Thank you, %name!!");

            }

         }

      }

      if (::str::x_contains(strQuery, "cya") || ::str::x_contains(strQuery, "see you") || ::str::x_contains(strQuery, "bye"))
      {

         str = _t("See you, %name!!");

      }

      if (::str::x_contains(strQuery, "hi") || ::str::x_contains(strQuery, "hello") || ::str::x_contains(strQuery, "hey"))
      {

         str = _t("Hi, %name!!");
         strSound = "element/creation";

      }

      if (::str::x_contains(strQuery, "yay") || ::str::x_contains(strQuery, "yey") || ::str::x_contains(strQuery, "wow") || ::str::x_contains(strQuery, "victory"))
      {

         str = _t("Victory!!");
         strSound = "hidden/tada";

      }

   }

   bool bBabylonTheHistoryBookInTheShelfAlwaysRepeatingItself_ItIsTrueEvenIfItDidntHappened = false;

   string strBabylonTopic;

   {

      stringa straBabylon;

      stringa & stra = straBabylon;

      if(!strUser.contains_ci("Catherina"))
      {
         stra.add("Java");
      }
      if(!strUser.contains_ci("camwhite")
            && !strUser.contains_ci("scamwhite")
            && !strUser.contains_ci("xmx")
            && !strUser.contains_ci("xmetrix")
            && !strUser.contains_ci("zjrosen")
            && !strUser.contains_ci("unicorn")
            && !strUser.contains_ci("phanx"))
      {
         stra.add("Nude");
         stra.add("Nude.js");
         stra.add("Node");
         stra.add("Node.js");
         stra.add("Javascript");
         stra.add("Jee");
         stra.add("Js");
      }
      if(!strUser.contains_ci("david")
            && strCountry.compare_ci("spain") != 0
            && strCountry.compare_ci("italy") != 0
            && strCountry.compare_ci("france") != 0)
      {
         stra.add("Python");
      }
      stra.add("Lua");
      if(strCountry.compare_ci("japan") != 0)
      {
         stra.add("Ror");
         stra.add("Ruby-on-Rails");
      }
      if(!strUser.contains_ci("foamy"))
      {
         stra.add("Lisp"); // Foamy
      }
      stra.add("Cobol");
      stra.add("Prolog");
      if(!strUser.contains_ci("Jegas") && !strUser.contains_ci("Jason") && !strUser.contains_ci("Sage"))
      {
         stra.add("Pascal"); // Jegas
      }
      stra.add("F#");
      stra.add("C#");
      stra.add("vim");
      stra.add("e-macs");
      stra.add("bash");
      stra.add("DOS");
      stra.add("scripting");
      stra.add("Obj-C");
      stra.add("Objective-C");
      stra.add("Swift");
//      stra.add("Go");
      stra.add("Qt");
      stra.add("SDL");
      stra.add("SMFL");
      stra.add("Unreal");
      stra.add("unity");
      stra.add("Angular");
      stra.add("React");
      stra.add("Reactive");
      stra.add("Framework");
      stra.add("library");
      stra.add("language");
      stra.add("programming");
      if(!strUser.contains_ci("Phanx"))
      {
         stra.add("ActionScript"); // PhanxGames
      }
      if(!strUser.contains_ci("Thomas"))
      {
         stra.add("PHP"); // Thomas
      }

      stringa straTopics;

      for(auto & str : stra)
      {

         if(::str::x_contains(strQuery, str))
         {

            bBabylonTheHistoryBookInTheShelfAlwaysRepeatingItself_ItIsTrueEvenIfItDidntHappened = true;

            straTopics.add(str);

         }

      }

      strBabylonTopic = straTopics.implode(", ");

   }

   if (::str::x_contains(strQuery, "Visual Basic") || ::str::x_contains(strQuery, "VB.net") || ::str::x_contains(strQuery, "vb") || ::str::x_contains(strQuery, "basic"))
   {

      str = _t("Yes!! Learn the Basic of Programming... good to start small, so you grow right to the next level... C.... (and don't go much bigger...)");

   }

   if (bBabylonTheHistoryBookInTheShelfAlwaysRepeatingItself_ItIsTrueEvenIfItDidntHappened)
   {

      Sleep(8000);

      static int s_iBabylonWar = 0;

      switch(s_iBabylonWar % 3)
      {
      case 0:
         //str = _t("(Language: "+strBabylonTopic+" ...) Viewers, please, prefer C++ or ca2 framework (let's focus :) Thank you for your comprehension...)");
         str = _t("Hey Everybody! Thanks for your preference. Entropy is increasing... Let's focus :) Thank you for your comprehension...");
         break;

      // case 1:
      //    str = _t("(Language: "+strBabylonTopic+" ...)\" Starting big is not good idea (C#, D, F#, Java...) ... C (see), you may have to (c)ut down a bit...");
      //    break;

      // case 2:
      //    str = _t("(Language: "+strBabylonTopic+" ...)\" Why not (c)ut down the language interpretation and inline/runtime translation? Maybe the CPU is hot and the battery is firing...");
      //    break;
      default:
         break;

      }

      s_iBabylonWar++;

   }

   if(str.is_empty())
   {

      // this is the default behaviour of bot_a

      m_pcomm->add_chat(this);

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

      Application.mainstage().schedule_speech(strUser, m_strLang, strMessage, strSpeakText, this, strSound);

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


