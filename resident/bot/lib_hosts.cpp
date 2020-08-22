



string on_new_hosts(stringa & straNew, int_array & iaViewers)
{

   string str;

   string strLang;

   string strHost;

   string strSpeakText;

   int iViewers;

   stringa straLang;

   string strLastLang;

   bool bSameLang = true;

   string strAnnounce;

   __pointera(::resident::user) usera;

   stringa straMessage;
   stringa straSpeakMessage;

   string strMessage;

   for (index i = 0; i < straNew.get_count(); i++)
   {

      strHost = straNew[i];

      iViewers = iaViewers[i];

      auto puser = get_user(strHost, true);

      usera.add(puser);

      param(1, username(strHost, strLang));
      
      param(2, ::str::from(iViewers));
      
      if (iViewers <= 0)
      {
      
         strMessage = _t("Thank you for hosting, %param1!!");
      
      }
      else
      {
      
         strMessage = _t("Thank you %param1 for hosting with %param2 viewers!!");
      
      }

      straMessage.add(strMessage);
      straSpeakMessage.add(strSpeakText);

   }

   strMessage = straMessage.implode("\n");
   strSpeakText = straSpeakMessage.implode("\n");

   //__pointera(::resident::user) usera;
   
   //usera.add(puser);
   
   Application.mainstage().add_announce(strMessage, usera, 15000);
   
   hostsbell();
   
   m_pcomm->post_message(strMessage, true);
   
   lspeak(strHost,strLang,strSpeakText, true);
   
   Sleep(15000);
   //if (!bMsg)
   //{

   //   m_pcomm->msg(str);

   //   lspeak("", "en", str, true);

   //}
   //else
   //{

   //   m_pcomm->msg(str);

   //   lspeak("", strLastLang, str, true);

   //}


   return "";

}










//
//
//string on_new_host(const string & strHost, int iViewers)
//{
//
//   string strMessage;
//
//   string strSpeakText;
//
//   auto puser = get_user(strHost, true);
//
//   string strLang = Application.lang(puser->get_user_data("lang").get_string().lower());
//
//   if(strLang.is_empty())
//   {
//
//      string strCountry = puser->get_user_data("country_code").get_string().lower();
//
//      if(strCountry.is_empty())
//      {
//
//         strCountry = puser->get_user_info("country_code").get_string().lower();
//
//         puser->set_user_data("country_code",strCountry);
//
//      }
//
//      strLang = Application.initial_country_lang(strCountry);
//
//      puser->set_user_data("lang",strLang);
//
//   }
//
//   param(1, username(strHost, strLang));
//
//   param(2, ::str::from(iViewers));
//
//   if (iViewers <= 0)
//   {
//
//      strMessage = _t("Thank you for hosting, %param1!!");
//
//   }
//   else
//   {
//
//      strMessage = _t("Thank you %param1 for hosting with %param2 viewers!!");
//
//   }
//
//   __pointera(::resident::user) usera;
//
//   usera.add(puser);
//
//   Application.mainstage().add_announce(strMessage, usera, 15000);
//
//   hostsbell();
//
//   m_pcomm->msg(strMessage);
//
//   lspeak(strHost,strLang,strSpeakText, true);
//
//   Sleep(15000);
//
//   return "";
//
//}
//
//
//
//
//
//
//
//
//
//
