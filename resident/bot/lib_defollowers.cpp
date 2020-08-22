

string on_defollowers(stringa & straNew)
{

   string str;

   stringa straLang;

   string strLastLang = "en";

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

		 str += username(strUser, strLang) + " de-followed!";

	  }

      strLastLang = strLang;

   }

 	m_pcomm->post_message(str, true);


   return "";

}










