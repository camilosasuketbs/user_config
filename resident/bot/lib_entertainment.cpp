string rr(string strName, string strLang, bool bForce = false)
{

   ::datetime::time now;

   if (!bForce)
   {

      ::datetime::time last_rr;

      now = ::datetime::time::get_current_time();

      last_rr.m_time = get_user_data("global", "last_rr").i64();

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

   audio_announce(hi5_user("xmetrix") / "Never Gonna Give You Up.asciimedia");

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

      last_rr.m_time = get_user_data("global", "last_rr").i64();

      if (now.m_time - last_rr.m_time < 1 * 60)
      {

         return "";

      }

   }

   string strSpeakText;

   string & strTopic = m_strTopic;

   string str;

   str = _t("Opening Rick Astley - Never Gonna Give You Up!");

   audio_announce(hi5_user("xmetrix") / "Never Gonna Give You Up.asciimedia");

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

   while (Application.file().exists(path = ::dir::ca2roaming() / ("audio/hidden/welcome" + ::str::from(iIndex++)) / (strUser + ".wav")))
   {
      stra.add(path);
   }

   return stra;

}

void ws(string strUser, bool bDoorBel, bool bHosts = false) // welcome sound
{

   auto puser = get_user(strUser, true);

   puser->get_user_country_code();

   string strUsername = username(strUser, m_epersonVocative == ::resident::person_user ? m_strLang : m_strOtherLang);

   __pointera(::resident::user) usera;

   usera.add(puser);

   Application.mainstage().add_announce("Welcome " + strUsername + "!", usera, 10000);

   strUser.make_lower();

   stringa stra = wsa(strUser);

   if (stra.get_size() > 0)
   {

      index iIndex = atoi(file_as_string(::dir::ca2roaming() / "audio/hidden/welcome0" / strUser + ".txt"));

      if (iIndex >= stra.get_size())
      {

         iIndex = 0;

      }

      audio_announce(stra[iIndex], strUsername, puser != NULL ? puser->m_strImage : "");

      iIndex++;

      file_put_contents_dup(::dir::ca2roaming() / "audio/hidden/welcome0" / strUser + ".txt", ::str::from(iIndex));

   }
   else if (bHosts)
   {

      hostsbell();

   }
   else if (bDoorBel)
   {

      doorbell();

   }
   else
   {

      Application.play_audio(::dir::ca2roaming() / "audio/hidden/welcome.wav");

   }

}


void doorbell() // welcome sound
{

   Application.play_audio(::dir::ca2roaming() / "audio/hidden/doorbell.mp3");

}

void hostsbell() // welcome sound
{

   Application.play_audio(::dir::ca2roaming() / "audio/hidden/hostsbell.mp3");

}


void bye() // welcome sound
{

   Application.play_audio(::dir::ca2roaming() / "audio/hidden/youlater.wav");

}


void sound_for_follower() // welcome sound
{

   fork([this]()
   {

      Application.play_audio(::dir::ca2roaming() / "audio/hidden/follower.wav");

      Sleep(1000);

      Application.play_audio(::dir::ca2roaming() / "audio/hidden/follower.wav");

      Sleep(1000);

      Application.play_audio(::dir::ca2roaming() / "audio/hidden/follower.wav");

   });

}


void audio_announce(string strParam, string strTitle = "", string strAlbumArt = "", bool bIgnorePlaybackNotification = true)
{

   if (bIgnorePlaybackNotification)
   {

      ::file::path pathOrigin(strParam);

      Application.mainstage().m_pathaIgnorePlaybackNotification.add(pathOrigin);

   }

   if (strTitle.has_char())
   {

      strTitle = " call_title=\"" + strTitle + "\"";

   }

   if (strAlbumArt.has_char())
   {

      strAlbumArt = " call_albumart=\"" + strAlbumArt + "\"";

   }

   string strExtra = " : dont_add_to_playlist play_now" + strTitle + strAlbumArt;

   ::file::path path = core_app_path("app-veriwell/waven");

   string strCmd = "\"" + strParam + "\"" + strExtra;

   call_async(path, strCmd, path.folder(), SW_SHOW, false);

}


::resident::animation * create_animation(string strAnimation)
{

   if (strAnimation == "disco")
   {

      return new ::resident::animation_disco(&Application.mainstage());

   }
   else if (strAnimation == "llama")
   {

      return new ::resident::animation_llama(&Application.mainstage());

   }

   return NULL;

}


void waven_add_to_playlist(string strUrl)
{

   string & strUser = m_strUserId;

   string strCommand = "\"" + strUrl + "\" : queue=true for_resident=" + strUser;

   ::file::path path = core_app_path("app-veriwell/waven");

   call_async(path, strCommand, path.folder(), SW_SHOW, false);

}



