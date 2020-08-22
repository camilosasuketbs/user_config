

bool _load_text(string strLang)
{

   auto & m = m_text[strLang];

   ::file::path path = ::dir::system() / "config/xmpp_resident/room/ca2@livecoding.tv/xmpp_resident_po" / strLang + ".po";

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

   avoid_parsing_exception avoidParsingException;

   for (index i = 0; i < stra.get_count(); i++)
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









string get_text(string & strSpeakText, string strId, bool bAppendSpeakText = false)
{

   stringa straParam = m_straParam;
   string strTopic = m_strTopic;
   string strLang = m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::vericard::person_user ? m_strName : m_strOtherName;

   string strText = _get_text(strLang, strId);

   string strNewSpeakText;

   strNewSpeakText = strText;

   strNewSpeakText.replace("<emph>", "");
   strNewSpeakText.replace("</emph>", "");

   strNewSpeakText.replace("($name)", "");
   strNewSpeakText.replace("$name", "");
   strNewSpeakText = process_text(strNewSpeakText, strName, strTopic, straParam);

   if (strLang == "en" || strLang == "pt" || strLang == "de" || strLang == "nl")
   {
      strNewSpeakText.replace(":)", "");
      strNewSpeakText.replace(":(", "");
   }
   if (strLang == "ja" || strLang == "jp")
   {
      strNewSpeakText.replace("{!}", unitext("エクスクラメーションマーク"));
   }

   strNewSpeakText.replace("\"", " ");

   if (bAppendSpeakText)
   {

      strSpeakText += " " + strNewSpeakText;

   }
   else
   {

      strSpeakText = strNewSpeakText;

   }

   strText.replace("($name)", "(%name)");
   strText.replace("$name", "%name");
   return process_text(strText, strName, strTopic, straParam);

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

   if (p->m_element2[strId].is_empty())
      return strId;
   else
      return p->m_element2[strId];

}



string get_country(string strLang, string strCountry)
{

   strLang.make_upper();

   strCountry.make_upper();

   string strFileName = (strLang + ".json");

   strFileName.make_lower();

   ::file::path path = ::dir::system() / "config/xmpp_resident/room/ca2@livecoding.tv/xmpp_resident_country" / strFileName;

   ::file_time ft = get_file_time(path);

   if (m_ftimeCountry[strLang] == ft)
   {

      return m_country[strLang][strCountry];

   }

   m_ftimeCountry[strLang] = ft;

   string strJson = Application.file().as_string(path);

   try
   {

      const char * psz = strJson;

      var v;

      v.parse_json(psz);

      for (auto & item : v.vara())
      {

         m_country[strLang][item["code"].get_string().upper()] = item["name"];

      }

   }
   catch (...)
   {


   }

   return m_country[strLang][strCountry];

}




string name_welcome_time(string & strSpeakText)
{


   string & strTopic = m_strTopic;
   stringa & straParam = m_straParam;
   string strUser = m_epersonVocative == ::vericard::person_user ? m_strUser : m_strUser;
   string strLang = m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::vericard::person_user ? m_strName : m_strOtherName;


   ::datetime::time now = ::datetime::time::get_current_time();

   string strZoneUser = strUser;

   int iZone = get_user_data(strUser, "time_zone");

   string strZone = get_user_data(strUser, "time_zone_text");

   if (strZone.is_empty())
   {

      strZone = "UTC";

      if (iZone > 0)
      {

         strZone += "+";

      }
      else
      {

         strZone += "-";

      }

      strZone += ::str::from(abs(iZone));

   }

   now += ::datetime::time_span(0, iZone, 0, 0);



   if (now.GetGmtHour() >= 6 && now.GetGmtHour() < 12)
   {

      return _t("%name, Good Morning!");

   }
   else if (now.GetGmtHour() >= 12 && now.GetGmtHour() < 18)
   {

      return _t("%name, Good Afternoon!");

   }
   else
   {

      return _t("%name, Good Evening!");

   }


}


string welcome_time(string & strSpeakText)
{

   string & strTopic = m_strTopic;
   stringa & straParam = m_straParam;
   string strUser = m_epersonVocative == ::vericard::person_user ? m_strUser : m_strUser;
   string strLang = m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::vericard::person_user ? m_strName : m_strOtherName;



   ::datetime::time now = get_user(strUser)->user_time();

   if (now.GetGmtHour() >= 6 && now.GetGmtHour() < 12)
   {

      return _t("Good Morning!");

   }
   else if (now.GetGmtHour() >= 12 && now.GetGmtHour() < 18)
   {

      return _t("Good Afternoon!");

   }
   else
   {

      return _t("Good Evening!");

   }





}


string glang(string strLang)
{
   if (strLang == "en")
   {
      return "en";
   }
   else if (strLang == "jp")
   {
      return "ja";
   }
   else
   {
      return Application.lang(strLang);
   }
}

string l_and(string strLang)
{
   if (strLang == "de")
   {
      return "und";
   }
   if (strLang == "pt")
   {
      return "e";
   }
   if (strLang == "fr")
   {
      return "et";
   }
   if (strLang == "ru")
   {
      return "и";
   }
   return "and";
}



string process_text(string strText, string strName, string strTopic, stringa straParam)
{
   int iFind = 0;
   string strParamName;
   for (index i = 0; i < straParam.get_size(); i++)
   {
      iFind = 0;
      strParamName = "%param" + ::str::from(i + 1);
      while (true)
      {
         iFind = strText.find_ci(strParamName, iFind);

         if (iFind < 0)
            break;

         if (iFind == 0)
         {
            strText = straParam[i] + strText.Mid(strParamName.get_length());
         }
         // lazy check, it is not correct way of checking, it may result errors (triple %)
         else if (strText[iFind - 1] != '%')
         {
            strText = strText.Left(iFind) + straParam[i] + strText.Mid(iFind + strParamName.get_length());
         }
         iFind += straParam[i].get_length();
      }
   }
   iFind = 0;
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
      else if (strText[iFind - 1] != '%')
      {
         strText = strText.Left(iFind) + strName + strText.Mid(iFind + 5);
      }
      iFind += strName.get_length();
   }
   iFind = 0;
   while (true)
   {
      iFind = strText.find_ci("%topic", iFind);

      if (iFind < 0)
         break;

      if (iFind == 0)
      {
         strText = strTopic + strText.Mid(6);
      }
      // lazy check, it is not correct way of checking, it may result errors (triple %)
      else if (strText[iFind - 1] != '%')
      {
         strText = strText.Left(iFind) + strTopic + strText.Mid(iFind + 6);
      }
      iFind += strTopic.get_length();
   }
   return strText;
}





string get_country(string strCountryCode)
{

   string strCountry = get_country(m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang, strCountryCode);

   if (strCountry.is_empty())
   {

      strCountry = get_country("en", strCountryCode);

   }

   return strCountry;

}



string user_time_text(string strUser, string strLang, bool bTimeZone = false, bool bSynch = true)
{

   auto puser = get_user(strUser, bSynch);

   return user_time_text(puser, strLang, bTimeZone, bSynch);

}



string user_time_text(::vericard::user * puser, string strLang, bool bTimeZone = false, bool bSynch = true)
{

   ::datetime::time now = puser->user_time(bSynch);

   string strZone;

   if (bTimeZone)
   {

      strZone = puser->get_user_data("time_zone_text");

      if (strZone.has_char())
      {

         strZone.make_upper();

         strZone += " ";

      }

      strZone += puser->user_time_span_text(bSynch);

      strZone = " " + strZone;

   }

   string strSpeakText;

   return System.datetime().international().get_gmt_date_time(now, _t("%Y-%m-%d %H:%M:%S")) + strZone;

}

