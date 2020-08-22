

bool _load_text(string strLang)
{

   auto & m = m_text[strLang];

   ::file::path path = Application.resident_get_app_path("resident") / "po" / strLang + ".po";

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
            if (strText == "msgstr")
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
   string strLang = m_epersonVocative == ::resident::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::resident::person_user ? m_strName : m_strOtherName;

   string strText = _get_text(strLang, strId);

   string strNewSpeakText;

   strNewSpeakText = strText;

   strNewSpeakText.replace("<emph>", "");
   strNewSpeakText.replace("</emph>", "");

   strNewSpeakText.replace("($name)", "");
   strNewSpeakText.replace("$name", "");
   strNewSpeakText = process_text(strNewSpeakText, strName, strTopic, straParam);

   strNewSpeakText = process_text_to_speech(strNewSpeakText, strLang);

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

   if (p->element2()[strId].is_empty())
      return strId;
   else
      return p->element2()[strId];

}


bool load_lang_countries(string strLang)
{

   strLang.make_lower();

   string strFileName = (strLang + ".json");

   strFileName.make_lower();

   ::file::path path = Application.resident_get_app_path("resident") / "country" / strFileName;

   ::file_time ft = get_file_time(path);

   if (m_ftimeCountry[strLang] == ft)
   {

      return true;

   }

   m_ftimeCountry[strLang] = ft;

   string strJson = Application.file().as_string(path);

   if (strJson.is_empty())
   {

      return false;

   }

   try
   {

      const char * psz = strJson;

      var v;

      v.parse_json(psz);

      string strCode;

      string strName;

      for (auto & item : v.vara())
      {

         strCode = item["Code"];

         strCode.make_lower();

         strName = item["Name"];

         m_country[strLang][strCode] = strName;

         strName.make_lower();

         m_countrycode[strLang][strName] = strCode;

      }

      string strFileName = "C:\\archive\\lang\\"+(strLang + ".json");

      file_put_contents_dup(strFileName, v.get_json());

   }
   catch (...)
   {


   }

   return true;

}



string get_country(string strLang, string strCountryCode)
{

   if (!load_lang_countries(strLang))
   {

      return get_country("en", strCountryCode);

   }

   strCountryCode.make_lower();

   return m_country[strLang][strCountryCode];

}


string get_country_code(string strLang, string strCountry)
{

   if (!load_lang_countries(strLang))
   {

      return get_country_code("en", strCountry);

   }

   strCountry.make_lower();

   return m_countrycode[strLang][strCountry];

}



string name_welcome_time(string & strSpeakText)
{


   string & strTopic = m_strTopic;
   stringa & straParam = m_straParam;
   string strUser = m_epersonVocative == ::resident::person_user ? m_strUserId : m_strUserId;
   string strLang = m_epersonVocative == ::resident::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::resident::person_user ? m_strName : m_strOtherName;


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
   string strUser = m_epersonVocative == ::resident::person_user ? m_strUserId : m_strUserId;
   string strLang = m_epersonVocative == ::resident::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::resident::person_user ? m_strName : m_strOtherName;



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

   string strCountry = get_country(m_epersonVocative == ::resident::person_user ? m_strLang : m_strOtherLang, strCountryCode);

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



string user_time_text(::resident::user * puser, string strLang, bool bTimeZone = false, bool bSynch = true)
{

   ::datetime::zonetime now = puser->user_time(bSynch);

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

   return now.FormatZone(_t("%Y-%m-%d %H:%M:%S")) + strZone;

}




bool consider_speakable_text(string strText)
{

   string str;
   string str1;
   string str2;
   string str3;
   string str4;
   string str5;
   string str6;
   string str7;
   string str8;

   int iMax4Vowel = 3;
   int iMax5pVowel = 1;
   int iMax8Consonant = 1;
   int iv5p = 0;
   int iv4 = 0;
   int ic8 = 0;

   {

      stringa stra;
      stra.add("vagina");
      stra.add("penis");
      stra.add("bitch");
      int iFind;
      for (auto str : stra)
      {
         iFind = strText.find_ci(str);
         if (iFind >= 0)
         {
            return false;
         }
      }
   }

   {

      stringa stra;

      stra.add("shit");
      stra.add("cock");
      stra.add("dick");
      stra.add("cum");
      stra.add("anal");
      stra.add("cum");
      stra.add("fuck");
      int iFind;
      for (auto str : stra)
      {
         iFind = 0;
         if (str.compare_ci(strText.trimmed()) == 0)
         {
            return false;
         }
         while (true)
         {
            iFind = strText.find_ci(str, iFind);
            if (iFind < 0)
            {
               break;
            }
            if (iFind == 0)
            {
               if (!isalpha(strText[iFind + str.get_length()]))
               {
                  return false;
               }
            }
            else if (iFind == strText.get_length() - str.get_length())
            {
               if (!isalpha(strText[iFind - 1]))
               {
                  return false;
               }
            }
            else if (!isalpha(strText[iFind - 1]) && !isalpha(strText[iFind + str.get_length()]))
            {

               return false;
            }
            iFind += str.get_length();
         }
      }
   }

   if (strText.get_length() < 12)
   {
      return true;
   }


   int i = 0;
   const char * psz = strText;
   while (true)
   {

      str = ::str::get_utf8_char(psz);
      if (str.is_empty())
         break;
      psz += str.get_length();

      if (i == 0)
      {
         str1 = str;
      }
      else if (i == 1)
      {
         str2 = str;
      }
      else if (i == 2)
      {
         str3 = str;
      }
      else if (i == 3)
      {
         str4 = str;
      }
      else if (i == 4)
      {
         str5 = str;
      }
      else if (i == 5)
      {
         str6 = str;
      }
      else if (i == 6)
      {
         str7 = str;
      }
      else if (i == 7)
      {
         str8 = str;
      }
      else
      {

         if (is_vowel(str1) && is_vowel(str2) && is_vowel(str3) && is_vowel(str4) && is_vowel(str5))
         {
            iv5p++;
            if (iv5p >= iMax5pVowel)
            {
               return false;
            }
         }
         else if (is_vowel(str1) && is_vowel(str2) && is_vowel(str3) && is_vowel(str4))
         {
            iv4++;
            if (iv4 >= iMax4Vowel)
            {
               return false;
            }
         }
         else if (is_consonant(str1) && is_consonant(str2) && is_consonant(str3) && is_consonant(str4) && is_consonant(str5) && is_consonant(str6) && is_consonant(str7) && is_consonant(str8))
         {
            ic8++;
            if (ic8 >= iMax8Consonant)
            {
               return false;
            }
         }


         str1 = str2;
         str2 = str3;
         str3 = str4;
         str4 = str5;
         str5 = str6;
         str6 = str;
      }
      i++;
   }

   return true;
}


string process_text_to_speech(string strNewSpeakText, string strLang)
{


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

   ::str::x_left_remove(strNewSpeakText, "https://");

   ::str::x_left_remove(strNewSpeakText, "http://");

   return strNewSpeakText;

}


