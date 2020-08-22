

string on_new_followers(stringa & straNew)
{
   int iCount = straNew.get_size();
   ::fork(get_app(), [=]()
   {

      for (index i = 0; i < MIN(3, iCount); i++)
      {
         sound_for_follower();
         Sleep(1000);
      }

   });

   string str;

   stringa straLang;

   string strLastLang;

   bool bSameLang = true;

   for(auto strUser : straNew)
   {

      auto puser = get_user(strUser);

      string strLang = Application.lang(puser->get_user_data("lang").get_string().lower());
      if(strLang.is_empty())
      {
         string strCountry = puser->get_user_data("country_code").get_string().lower();
         if(strCountry.is_empty())
         {
            strCountry = puser->get_user_info("country_code").get_string().lower();
            puser->set_user_data("country_code",strCountry);
         }
         strLang = Application.initial_country_lang(strCountry);
         puser->set_user_data("lang",strLang);
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

      str += rr("en", true);

      m_pcomm->msg(str);

      lspeak("","en",str, true);

   }
   else
   {

      str += rr(strLastLang, true);

      m_pcomm->msg(str);

      lspeak("",strLastLang,str, true);

   }

   return "";

}










