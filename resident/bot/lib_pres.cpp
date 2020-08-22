
string on_pres(string strUserId, string strType)
{

   m_epersonTopic = ::resident::person_user;

   m_epersonVocative = ::resident::person_user;

   m_strUserId = strUserId;

   int iThreshold = 16;

   string & strTopic = m_strTopic;

   auto puser = get_user(strUserId, true);

   m_strCountry = puser->get_user_country_code(true);

   puser->get_user_city(true);

   m_strLang = puser->get_user_lang();

   string strTimeZone = puser->get_user_time_zone();

   m_strName = username(strUserId, m_strLang);

   if (strType == "unavailable")
   {


      ::datetime::time last_back;

      last_back.m_time = get_user_data(strUserId, "last_presence").i64();

      ::datetime::time now = ::datetime::time::get_current_time();

      set_user_data(strUserId, "last_see_you", now.m_time);

      set_user_data(strUserId, "back", 0);

      fork([=]()
      {



         Sleep(iThreshold * 1000);

         if (get_user_data(strUserId, "back") == 0)
         {

            string strSpeakText;
            string strText;

            if (get_user_data(strUserId, "official_back") == 1)
            {

               set_user_data(strUserId, "official_back", 0);

               if (spam(strUserId))
               {

                  strText = _t("%name gone, uff...");

               }
               else if (isbot(strUserId))
               {

                  strText = _t("%name was unplugged!");

               }
               else
               {

                  if (get_user_data(strUserId, "visit_count") <= 4)
                  {

                     //bye();

                     //strText = _t("Bye %name! :(");

                     strText = _t("%name has left the room.");

                  }
                  else
                  {

                     if (now.m_time - last_back.m_time > 8 * 60)  // 1 hour
                     {

                        //strText = _t("See you %name! :(");

                        //bye();

                        strText = _t("%name has left the room.");

                     }
                     else
                     {

                        //strText = _t("See you %name! :(");

                        //strText.replace(":(", "");

                        //bye();

                        strText = _t("%name has left the room.");

                     }

                  }

                  //if (strText.has_char())
                  //{

                  //   Application.mainstage().schedule_speech(strUserId, m_strLang, strText, strSpeakText, this);

                  //}
                  //else
                  //{

                  //   if (!lspeak(strUserId, m_strLang, strSpeakText, false))
                  //   {

                  //   }

                  //}

               }

            }
            else if (now.m_time - last_back.m_time < iThreshold)
            {

               strText = _t("%name passed by here...");

            }

            if (strText.has_char())
            {

               __pointer(::resident::chat_item) pitem = __sp(new chat_item(get_app(), m_pcomm->m_pchatcommBot->m_strUserId, strText, m_pcomm->m_strProtocol, m_pcomm->m_pchatcommBot));

               ::resident::user * puser = pitem->m_puser;

               if (puser == NULL)
               {

                  puser = Application.mainstage().get_user(pitem->m_strUserId, m_pcomm, false);

                  if (puser == NULL)
                  {

                     return;

                  }

                  pitem->m_puser = puser;

               }

               m_pcomm->add_chat(pitem);

            }

         }

      });

      Sleep(500);

      return "";

   }
   else
   {

      ::datetime::time last_see_you;

      last_see_you.m_time = get_user_data(strUserId, "last_see_you").i64();

      ::datetime::time now = ::datetime::time::get_current_time();

      set_user_data(strUserId, "last_presence", now.m_time);

      set_user_data(strUserId, "back", 1);

      //      if (now.m_time - last_see_you.m_time > 8)
      fork([=]()
      {


         Sleep(iThreshold * 1000);

         if (get_user_data(strUserId, "back") == 1 && get_user_data(strUserId, "official_back") == 0)
         {

            set_user_data(strUserId, "official_back", 1);


            string strText;
            string strSpeakText;

            if (spam(strUserId))
            {
               strText = strUserId + " entered!! (Subset of commands enabled).";
            }
            else if (isbot(strUserId))
            {

               strText = m_strName + " you are connected!";

            }
            else
            {

               if (get_user_data(strUserId, "visit_count") <= 4)
               {

                  ws(strUserId, true);

                  param1(_trans1(welcome_time));

                  set_user_data(strUserId, "last_welcome_time", _trans1(welcome_time));

                  strText = _t("<emph>Welcome %name! :) %param1</emph> Please, use exclamation mark to get help.");

                  if (m_strCountry == "be")
                  {
                     strText += "\nYou can choose between \"Nederlands\", \"Deutsch\" and \"Français\" using \"!setlang nl\", \"!setlang de\" or \"!setlang fr\"";
                  }
                  else if (m_strCountry == "ch")
                  {
                     strText += "\nYou can choose between \"Deutsch\", \"Français\" and \"Italiano\" using \"!setlang de\", \"!setlang fr\" or \"!setlang it\"";
                  }
                  else if (m_strCountry == "ca")
                  {
                     strText += "\nYou can choose between \"Français\" and \"English\" using \"!setlang fr\" or \"!setlang en\"";
                  }
               }
               else if (get_user_data(strUserId, "last_visit") > 60 * 60 * 18 || get_user_data(strUserId, "today_visit_count") <= 1)
               {

                  ws(strUserId, true);

                  param1(_trans1(welcome_time));

                  set_user_data(strUserId, "last_welcome_time", _trans1(welcome_time));

                  strText = _t("<emph>Hi %name! Welcome! %param1</emph> What brings you here today?");

               }
               else if (get_user_data(strUserId, "last_visit") > 60 * 60 * 3 || get_user_data(strUserId, "last_welcome_time") != _trans1(welcome_time))
               {

                  ws(strUserId, true);

                  param1(_trans1(name_welcome_time));

                  set_user_data(strUserId, "last_welcome_time", _trans1(welcome_time));

                  strText = _t("%param1! :)");

               }
               else
               {


                  if (now.m_time - last_see_you.m_time > 8 * 60)  // 8 (infinite standing up) minutes
                  {

                     ws(strUserId, true);

                  }
                  else
                  {

                     doorbell();

                  }

                  strText = _t("<emph>%name is back! :)</emph>");

               }

               if (strText.has_char())
               {

                  Application.mainstage().schedule_speech(strUserId, m_strLang, strText, strSpeakText, this);

               }
               else
               {

                  if (!lspeak(strUserId, m_strLang, strSpeakText, false))
                  {

                  }

               }

            }

            if (strText.has_char())
            {

               auto puser = get_user(strUserId);

               if (puser->m_image)
               {

                  if (!puser->m_imageCircle)
                  {

                     puser->m_imageCircle.create_circle(puser->m_image, 72);

                  }

                  Application.mainstage().m_d2[strText] = puser->m_imageCircle;

               }

               m_pcomm->post_message(strText, true);

            }

         }

      });

      return "";

   }

}




