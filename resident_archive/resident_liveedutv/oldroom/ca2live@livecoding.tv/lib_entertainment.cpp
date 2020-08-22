string rr(string strName, string strLang, bool bForce = false)
{

   ::datetime::time now;

   if (!bForce)
   {

      ::datetime::time last_rr;

      now = ::datetime::time::get_current_time();

      last_rr.m_time = get_user_data("global", "last_rr").int64();

      if (now.m_time - last_rr.m_time < 1 * 60)
      {

         return "";

      }

   }

   string strSpeakText;

   string & strTopic = m_strTopic;

   strTopic = strName;

   string str;

   str = _t("%topic, Opening Rick Astley - Never Gonna Give You Up!");

   audio_announce(hi5_user("xmetrix") / "never_gonna_give_you_up.asciimedia");

   if (!bForce)
   {

      set_user_data("global", "last_rr", now.m_time);

   }

   return str;

}


string rr(string strLang, bool bForce = false)
{

   ::datetime::time now;

   if (!bForce)
   {

      ::datetime::time last_rr;

      now = ::datetime::time::get_current_time();

      last_rr.m_time = get_user_data("global", "last_rr").int64();

      if (now.m_time - last_rr.m_time < 1 * 60)
      {

         return "";

      }

   }

   string strSpeakText;

   string & strTopic = m_strTopic;

   string str;

   str = _t("Opening Rick Astley - Never Gonna Give You Up!");

   audio_announce(hi5_user("xmetrix") / "never_gonna_give_you_up.asciimedia");

   if (!bForce)
   {

      set_user_data("global", "last_rr", now.m_time);

   }

   return str;

}



stringa wsa(string strUser)
{

   stringa stra;

   ::file::path path;

   index iIndex = 0;

   while (Application.file().exists(path = ::dir::system() / ("audio/hidden/welcome" + ::str::from(iIndex++)) / (strUser + ".wav")))
   {
      stra.add(path);
   }

   return stra;

}

void ws(string strUser, bool bDoorBel) // welcome sound
{

   get_user(strUser, true)->get_user_country_code();

   strUser.make_lower();

   stringa stra = wsa(strUser);

   if (stra.get_size() > 0)
   {

      index iIndex = atoi(file_as_string_dup(::dir::system() / "audio/hidden/welcome0" / strUser + ".txt"));

      if (iIndex >= stra.get_size())
      {

         iIndex = 0;

      }

      auto puser = get_user(strUser);

      audio_announce(stra[iIndex], username(strUser, m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang), puser != NULL ? puser->m_strImage : "");

      iIndex++;

      file_put_contents_dup(::dir::system() / "audio/hidden/welcome0" / strUser + ".txt", ::str::from(iIndex));

   }
   else if (bDoorBel)
   {

      doorbell();

   }
   else
   {

      Application.play_audio(::dir::system() / "audio/hidden/welcome.wav");

   }

}


void doorbell() // welcome sound
{

   Application.play_audio(::dir::system() / "audio/hidden/doorbell.mp3");

}


void bye() // welcome sound
{
   Application.play_audio(::dir::system() / "audio/hidden/youlater.wav");
}
void sound_for_follower() // welcome sound
{
   Application.play_audio(::dir::system() / "audio/hidden/follower.wav");
}
