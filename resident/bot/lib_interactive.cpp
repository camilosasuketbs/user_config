string on_interactive_action(string strUserId, string strControl)
{

   if (::str::begins_eat_ci(strControl, "waven_execute_"))
   {

      string strCommand = "mediaplay:execute_"+ strControl;

      ::file::path path = core_app_path("app-veriwell/waven");

      call_async(path, " : " + strCommand, path.folder(), SW_SHOW, false);

   }
   else if (strControl.compare_ci("waven_restart") == 0)
   {

      ::system("killall -9 app_veriwell_waven");

      Sleep(500);

      ::file::path path = core_app_path("app-veriwell/waven");

      call_async(path, "", path.folder(), SW_SHOW, false);

   }

   return "";

}


