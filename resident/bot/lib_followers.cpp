

string on_new_followers(stringa & straNew)
{

   string str;

   stringa straLang;

   string strLastLang;

   bool bSameLang = true;
   
   string strAnnounce;

   __pointera(::resident::user) usera;

   for(auto strUser : straNew)
   {

      auto puser = get_user(strUser, true);

      usera.add(puser);

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

      if (strAnnounce.has_char())
      {

         strAnnounce += "\r";

      }

      if(strLang == "pt")
      {

         str += "Te dou Boas Vindas, " + username(strUser, strLang) + "! Obrigado por seguir!";

         strAnnounce += "Obrigado por seguir,\r"+ username(strUser, strLang) +"!";

      }
      else
      {

         str += "You're welcome, " + username(strUser, "en") + "! Thank you for following!";

         strAnnounce += "Thanks for following,\r"+ username(strUser, "en") +"!";

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

   if (!bMsg)
   {
      if (straNew.get_size() > 1)
      {

         str += "\nOpening Rick Roll for you all new followers!!\n";

      }
      else
      {

         str += "\nOpening Rick Roll for you!!\n";

      }

      str += rr("en", true);

   }
   else
   {

      str += rr(strLastLang, true);

   }


   Sleep(6000);


   Application.mainstage().add_announce(strAnnounce, usera, 20000);

   sound_for_follower();

   Sleep(5000);

   if(!bMsg)
   {

      m_pcomm->post_message(str, true);

      lspeak("","en",str, true);

   }
   else
   {

      m_pcomm->post_message(str, true);

      lspeak("",strLastLang,str, true);

   }


   return "";

}










