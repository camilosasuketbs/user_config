
void timers()
{


   DWORD dwLastText = get_tick_count();

   stringa straText;

   while(::get_thread_run())
   {

      if(straText.is_empty())
      {

         ::file::path path = Application.resident_get_app_path("resident") / "text";

         ::file::listing listing(get_app());

         listing.ls_pattern(path, { "*.txt" });

         for(auto & path : listing)
         {

            straText.add(path.title());

         }

      }


      if(m_commptra.has_elements() && straText.has_elements() && get_tick_count() - dwLastText > 5000)
      {

         dwLastText = get_tick_count();

         string strText = ::lemon::array::pop_random(straText);

         ::file::path path = Application.resident_get_app_path("resident") / "text" / (strText + ".txt");

         string strPrompt = file_as_string_dup(path);

         m_straShouldSpeak.add(strPrompt);

         broad_msg(strPrompt, "en");

      }

   }


   {

      synch_lock sl(Application.mainstage().m_pmutex);
      
      Application.mainstage().m_pthreadTimers.release();

      
   }

}