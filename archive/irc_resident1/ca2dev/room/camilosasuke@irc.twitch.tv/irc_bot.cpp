#include "framework.h"
#include "app-core/appseed/irc_resident/irc_resident.h"
#pragma comment (lib,"vericard.lib" )
#pragma comment (lib,"irc.lib" )
#pragma comment (lib,"app_core_irc_bot.lib" )
#pragma comment (lib,"app_core_irc_client.lib" )
#pragma comment (lib,"app_core_irc_resident.lib" )


class this_plugin :
	virtual public ::irc_resident::plugin
{
	
	public:
	
	
      this_plugin(::aura::application * papp, object * p) :
		object(papp),
      ::vericard::plugin(papp,dynamic_cast <::vericard::comm * > (p)),
		::irc_resident::plugin(papp, dynamic_cast <::vericard::comm * > (p))
	{
		
	}

      string warn(string strUser)
      {

         return "This operation is not permitted to you, " + strUser + "! Contact moderator if you think its wrong.";

      }

      bool isbot(string strUser)
      {

         if(::str::begins_ci(strUser,"bot"))
         {

            return true;

         }
         else if(::str::ends_ci(strUser,"bot"))
         {

            return true;

         }
         else
         {

            return false;

         }

      }

      void olink(string strUser,string strUrl)
      {

         if(spam(strUser))
         {

         }
         else
         {

            open_link(strUrl);

         }

      }


      bool spam(string strUser)
      {

         if(::str::begins_ci(strUser,"spam"))
         {

            return true;

         }
         else if(::str::ends_ci(strUser,"spam"))
         {

            return true;

         }
         else if(strUser.CompareNoCase("coldzer0") == 0)
         {

            return true;

         }
         else
         {

            return false;

         }


      }

      void lspeak(string strUser,string strLang,string strText)
      {

         if(spam(strUser))
         {

         }
         else
         {

            lang_speak(strLang,strText);

         }

      }

      string  lang(string strLang)
      {

         if(strLang == "br")
         {
            return "pt";
         }
         else if(strLang == "do")
         {
            return "es";
         }
         else if(strLang == "co")
         {
            return "es";
         }
         else if(strLang == "pe")
         {
            return "es";
         }
         else if(strLang == "ec")
         {
            return "es";
         }
         else if(strLang == "mx")
         {
            return "es";
         }
         else if(strLang == "pa")
         {
            return "es";
         }
         else if(strLang == "py")
         {
            return "es";
         }
         else if(strLang == "uy")
         {
            return "es";
         }
         else if(strLang == "ar")
         {
            return "es";
         }
         else if(strLang == "cl")
         {
            return "es";
         }
         else if(strLang == "us")
         {
            return "en";
         }
         else if(strLang == "uk")
         {
            return "en";
         }
         else
         {
            return strLang;
         }

      }


      string glang(string strLang)
      {

         if(strLang == "en")
         {
            return "en";
         }
         else if(strLang == "jp")
         {
            return "ja";
         }
         else
         {
            return lang(strLang);
         }

      }


      string l_and(string strLang)
      {

         if(strLang == "pt")
         {
            return "e";
         }
         if(strLang == "fr")
         {
            return "et";
         }
         else
         {
            return "and";
         }

      }


      string username(string strUser)
      {

         var strName = get_user_data(strUser,"name");

         if(strName.is_empty())
         {

            strName = strUser;

         }

         return strName;

      }


      void ws() // welcome sound
      {

         play_sound("C:\\ca2\\audio\\hidden\\glockd.wav");

      }

      void bye() // welcome sound
      {

         play_sound("C:\\ca2\\audio\\hidden\\chirp7.wav");

      }


      void auto_translate(string strUser,string strDst,string strText)
      {

         olink(strUser,"https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#auto/" + strDst + "/" + url_encode(strText));

      }

      void translate(string strUser,string strDst,string strSrc,string strText)
      {

         olink(strUser,"https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#" + strSrc + "/" + strDst + "/" + url_encode(strText));

      }




      string bot_x(string strName,string strUser,string strText,string strCountry,string strLang)
      {

         string str;

         if(strText == "!")
         {

            if(strLang == "pt")
            {

               str = strName + ", Alguns comandos suportados são ";

            }
            else
            {

               str = strName + ", Some commands supported ";

            }

            str += "!help, !about " + l_and(strLang) + " !vaimepassarobot?";

         }
         else if(strText == "!reset!")
         {
            set_user_data(strUser,"country","");
            set_user_data(strUser,"lang","");
            set_user_data(strUser,"visit_count","");
            set_user_data(strUser,"last_visit","");
            set_user_data(strUser,"last_visit_time","");
         }
         else if(strText == "!rickroll" || strText == "!rr" || strText == "!rick") // xmetrix commanded !rickroll (me: probably he is referring to Rick Astley hit...)
         {

            if(spam(strUser))
            {

               return warn(strUser);

            }
            else
            {

               if(strLang == "es")
               {

                  str = "Abriendo la canción Rick Astley - Never Gonna Give You Up!";

               }
               else if(strLang == "pt")
               {

                  str = "Abrindo Rick Astley - Never Gonna Give You Up!";

               }
               else
               {

                  str = "Opening Rick Astley - Never Gonna Give You Up!";

               }

               system("Y:\\bergedge\\hi5\\program\\hstart.exe /NOCONSOLE \"X:\\core\\time\\x64\\basis\\app_veriwell_asciimedia.exe Y:\\bergedge\\hi5\\user\\northamerica\\us\\xmetrix\\never_gonna_give_you_up.asciimedia\"");

            }

         }
         else if(strText == "!song")
         {

            var response;

            response = song("");

            if(response.is_empty())
            {

               str = strName + ", song not playing or not in record.";

            }
            else
            {

               str = strName + ", currently playing song is: \"" + response + "\".";

            }

         }
         else if(strText == "!help")
         {

            if(strLang == "pt")
            {

               str = strName + ", a ajuda foi dividida em: !help util, !help info, !help config " + l_and(strLang) + " !help media";

            }
            else
            {

               str = strName + ", help information is grouped in: !help util, !help info, !help config " + l_and(strLang) + " !help media";

            }

         }
         else if(strText == "!commands")
         {

            if(strLang == "pt")
            {

               str = strName + ", a ajuda dos comandos foi agrupada em: !commands info, !commands config e !commands media";

            }
            else
            {

               str = strName + ", commands help info were grouped in: !commands info, !commands config " + l_and(strLang) + " !commands media";

            }

         }
         else if(::str::begins(strText,"!help ") || ::str::begins(strText,"!commands "))
         {

            string strGroup(strText);

            var strC;

            strC = "";

            ::str::begins_eat(strGroup,"!commands ");

            ::str::begins_eat(strGroup,"!help ");

            if(strGroup == "config")
            {

               if(strLang == "pt")
               {

                  strGroup = " os comandos de configuração são:";

                  str = "!setname \"nome\" e !setlang \"código do país\"";

               }
               else
               {

                  strGroup = " settings commands are:";

                  str = "!setname \"name\" " + l_and(strLang) + " !setlang \"country code\"";

               }
            }
            else if(strGroup == "media")
            {
               if(strLang == "pt")
               {

                  strGroup = " os comandos de multimídia são:";

                  str = "!rr, !rickroll, !say \"texto\", !playlist e !play \"som\"";

               }
               else
               {

                  strGroup = " multimedia commands are:";

                  str = "!rr, !rickroll, !say \"text\", !playlist " + l_and(strLang) + " !play \"sound\"";

               }
            }
            else if(strGroup == "util")
            {

               if(strLang == "pt")
               {

                  strGroup = " alguns comandos utilitários:";

                  str = "!urbd \"pergunta ao urban dictionary\", !at \"traduzir automaticament do google\" " + l_and(strLang) + " !t \"lang\" \"texto a ser traduzido de lang\"";

               }
               else
               {

                  strGroup = " some utility commands:";

                  str = "!urbd \"urban dictionary query\", !at \"google auto translate\" " + l_and(strLang) + " !t \"lang\" \"text to translate from lang\"";

               }
            }
            else if(strGroup == "rr" || strGroup == "rickroll")
            {

               strC = strName + ", !rr or !rickroll plays 80s hit Never Gonna Give You Up performed by Rick Astley with ASCII animation.";

            }
            else if(strGroup == "cmdtips")
            {

               strC = strName + ", Use this command to get special tips";

            }
            else if(strGroup == "say")
            {

               strC = strName + ", say uses Windows Narrator to speak the supplied text.";

            }
            else if(strGroup == "ide")
            {

               strC = strName + ", ide <platform> display information about tools used for development of ca2 framework and apps at the specified platform. <platform> maybe: windows (Desktop), linux, macos, ios, android and winrt.";

            }
            else if(strGroup == "setlang")
            {

               strC = strName + ", setlang <language code and/or two-letter country code> sets user preferred language. Communication is preferrably done using specified language or country.";

            }
            else
            {
               if(strLang == "pt")
               {

                  strGroup = " os comandos para obter informações são:";

                  str = "!ide \"plataforma\", !help \"comando\", !cmdtips, !commands, !about,!vaimepassarobot? " + l_and(strLang) + " !credits";

               }
               else
               {

                  strGroup = " information retrieval commands are:";

                  str = "!ide \"platform\", !help \"command\", !cmdtips, !commands, !about, !vaimepassarobot? " + l_and(strLang) + " !credits";

               }
            }

            if(strC.is_empty())
            {

               if(strLang == "pt")
               {

                  str = strName + ", " + strGroup + " : " + str;

               }
               else
               {

                  str = strName + ", " + strGroup + " : " + str;

               }

            }
            else
            {

               str = strC;

            }

         }
         else if(strText == "!ide windows")
         {

            str = strName + ", For Windows Desktop Software Development, ca2 uses Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.";

         }
         else if(strText == "!ide linux")
         {

            str = strName + ", For Linux Software Development, ca2 uses latest version of Ubuntu LTS, Code::Blocks and SmartSVN.";

         }
         else if(strText == "!ide macos")
         {

            str = strName + ", At MacOS, ca2 uses El Capitan, XCode and SmartSVN.";

         }
         else if(strText == "!ide ios")
         {

            str = strName + ", for iOS development, ca2 uses Mac OS X El Capitan, XCode, SmartSVN, XCode iOS simulator and trying to convince co-founder to borrow iOS device.";

         }
         else if(strText == "!ide android")
         {

            str = strName + ", for Android development, ca2 uses Windows, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN, WinMerge, Visual Studio Emulator for Android and Galaxy Tab 3 (Door Prize for co-founder, gift for me, help for ca2 developers and users).";

         }
         else if(strText == "!ide winrt")
         {

            str = strName + ", for Windows Store App development, ca2 uses Windows, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.";

         }
         else if(strText == "!cmdtips")
         {

            str = strName + ", For the exclamation mark, if an existing command is not found, an audio clip is played from !playlist. If a corresponding audio clip is not found, the text is played like in !say <text>";

         }
         else if(strText == "!about")
         {

            if(strLang == "pt")
            {

               str = strName + ", ca2 é uma framework e conjunto de bibliotecas escritas em linguagem C++ para ajudar desenvolvedores criarem grandes aplicativos para usuários.";

            }
            else if(strLang == "es")
            {
               str = strName + ", ca2 es un framework y un conjunto de bibliotecas escritas en lenguaje C ++ para ayudar a los desarrolladores a crear aplicaciones muy buenas para los usuarios.";
            }
            else
            {

               str = strName + ", ca2 is a framework and set of libraries written in C++ language to help developers create great apps for users.";

            }

         }
         else if(strText == "!credits")
         {

            str = strName + ", user info user thumb, user country and user flag are supplied by xmetrix code, web api and web server.";

         }
         else if(strText.get_length() > 6 && ::str::begins(strText,"!urbd "))
         {

            olink(strUser,"http://www.urbandictionary.com/define.php?term=" + url_encode(strText.substr(6)));

         }
         else if(strText.get_length() > 4 && ::str::begins(strText,"!at "))
         {

            auto_translate(strUser,glang(strLang),strText.substr(4));

         }
         else if(strText.get_length() > 3 && ::str::begins(strText,"!t ") && strText.substr(5,1) == " ")
         {

            translate(strUser,glang(strText.substr(3,2)),glang(strLang),strText.substr(6));

         }
         else if(strText.get_length() == 11 && ::str::begins(strText,"!setlang "))
         {

            set_user_data(strUser,"lang",lang(strText.substr(9,11)));

         }
         else if(strText.get_length() == 14 && ::str::begins(strText,"!setlang ") && strText.substr(11,1) == "-")
         {

            set_user_data(strUser,"lang",lang(strText.substr(9,2)));
            set_user_data(strUser,"country",strText.substr(12,2));

         }
         else if(strText == "!resetlang")
         {

            set_user_data(strUser,"lang","");

         }
         else if(strText == "!vaimepassarobot?") // question by julienb16 //2015-10-09 sexta-feira 23:23
         {

            if(strLang == "pt")
            {

               str = strName + ", No momento somente o aplicativo cliente será disponibilizado.";

            }
            else
            {

               str = strName + ", Currently only the client will be made available.";

            }

         }
         else if(strText == "!playlist")
         {

            stringa a = ls_names("C:\\ca2\\audio\\element");

            if(a.get_count() > 0)
            {

               var str = "Type !play ";

               for(int i = 0; i < a.get_upper_bound(); i++)
               {

                  if(i > 0)
                  {
                     str += ", ";
                  }

                  str += a[i].make_lower();


               }

               if(a.get_count() > 1)
               {

                  str += " or " + a.last().make_lower();

               }
               else if(a.get_count() == 1)
               {

                  str += a[0].lower();

               }

               str += ".";

            }
            else
            {
               str = "No files in the playlist";
            }

            return str;

         }
         else
         {

            stringa a = ls_names("C:\\ca2\\audio\\element");

            string str = strText.substr(1);

            bool found = false;

            int i = 0;

            for(; i < a.get_count() && !found; i++)
            {

               if(a[i].lower() == str.lower())
               {

                  found = 1;
               }

            }

            if(found == 1)
            {

               play_sound("C:\\ca2\\audio\\element\\" + str + ".wav");

               return "";

            }
            else
            {

               var str = strText;

               lspeak(strUser,strLang,str);

               return "";

            }

         }


         if(str.is_empty())
         {

            return "";

         }

         lspeak(strUser,strLang,str);

         return str;

      }


      string on_bot(string strUser,string strText)
      {

         if(!strText.begins_ci("!"))
            return "";

         var strName = username(strUser);

         string strCountry = get_user_data(strUser,"country").get_string().lower();

         if(get_user_data(strUser,"lang") == "")
         {

            set_user_data(strUser,"lang",lang(strCountry));

         }

         var strLang = lang(get_user_data(strUser,"lang").get_string().lower());

         if(strText.get_length() > 9 && ::str::begins(strText,"!setname "))
         {

            var str = strText.substr(9);

            set_user_data(strUser,"name",str);

            lspeak(strUser,strLang,str);

            return "";

         }
         else if(strText.get_length() > 5 && ::str::begins(strText,"!say "))
         {

            var str = strText.substr(5);

            lspeak(strUser,strLang,str);

            return "";

         }
         else if(strText.get_length() > 6 && ::str::begins(strText,"!play "))
         {

            stringa a = ls_names("C:\\ca2\\audio\\element");

            string str = strText.substr(6);

            bool found = false;

            int i = 0;

            for(; i < a.get_count() && !found; i++)
            {

               if(a[i].lower() == str.lower())
               {

                  found = true;

               }

            }

            if(found)
            {

               play_sound("C:\\ca2\\audio\\element\\" + str + ".wav");

               return "";

            }
            else
            {

               return "\"" + str + "\" not found. Please, use !playlist command to list existing sounds.";

            }

         }


         stringa tokens;

         tokens.explode(" ",strText);

         if(tokens.get_count() == 1)
         {

            if(::str::begins(tokens.last(),"!@"))
            {

               strUser = tokens[0].substr(2);

               strText = "!";

            }

         }
         else
         {

            if(::str::begins(tokens.last(),"@"))
            {

               strUser = tokens.last().substr(1);

               string str = "";

               int i = 0;

               for(; i < tokens.get_upper_bound(); i++)
               {

                  if(i > 0)
                  {

                     str += " ";

                  }

                  str += tokens[i];

               }

               strText = str;

            }

         }

         strName = username(strUser);

         strCountry = get_user_data(strUser,"country").get_string().lower();

         if(get_user_data(strUser,"country") == "")
         {

            set_user_data(strUser,"country",get_lctv_info(strUser,"country_code").get_string().lower());

         }

         if(get_user_data(strUser,"lang") == "")
         {

            set_user_data(strUser,"lang",lang(strCountry));

         }

         strLang = lang(get_user_data(strUser,"lang").get_string().lower());

         return bot_x(strName,strUser,strText,strCountry,strLang);

      }








































































































































      string on_pres(string strUser,string strType)
      {

         var strName = username(strUser);

         var strText;

         if(strType == "unavailable")
         {

            if(get_user_data(strUser,"country") == "")
            {

               set_user_data(strUser,"country",get_lctv_info(strUser,"country_code").get_string().lower());

            }

            var strCountry = get_user_data(strUser,"country").get_string().lower();

            if(get_user_data(strUser,"lang") == "")
            {

               set_user_data(strUser,"lang",lang(strCountry));

            }

            var strLang = lang(get_user_data(strUser,"lang").get_string().lower());

            if(spam(strUser))
            {

               strText = strUser + " gone, uff...";

            }
            else
            {

               bye();


               if(get_user_data(strUser,"visit_count") <= 4)
               {

                  if(strLang == "pt")
                  {

                     strText = "Tchau " + strName + "! :(";

                  }
                  else
                  {

                     strText = "Bye " + strName + "! :(";

                  }

               }
               else
               {

                  if(strLang == "pt")
                  {

                     strText = "Até mais " + strName + "!";

                  }
                  else
                  {

                     strText = "See you " + strName + "!";

                  }

               }

            }

            lspeak(strUser,strLang,strText);

            return strText;

         }
         else
         {

            if(get_user_data(strUser,"country") == "")
            {

               set_user_data(strUser,"country",get_lctv_info(strUser,"country_code").get_string().lower());

            }

            var strCountry = get_user_data(strUser,"country").get_string().lower();

            if(get_user_data(strUser,"lang") == "")
            {

               set_user_data(strUser,"lang",lang(strCountry));

            }

            var strLang = lang(get_user_data(strUser,"lang").get_string().lower());

            if(spam(strUser))
            {

               strText = strUser + " entered!! (Subset of commands enabled).";

               return strText;

            }
            else if(isbot(strUser))
            {

               strText = strName + " you are connected!";

            }
            else
            {

               ws();


               if(get_user_data(strUser,"visit_count") <= 4)
               {



                  if(strLang == "pt")
                  {

                     strText = "Boas Vindas a você " + strName + "! :) Você pode digitar exclamação seguido de Enter para obter ajuda.";

                  }
                  else if(strLang == "fr")
                  {

                     strText = "Bienvenue à vous " + strName + "! :) Vous pouvez taper un point d'exclamation et appuyez sur Entrée pour obtenir de l'aide.";

                  }
                  else if(strLang == "jp")
                  {

                     strText = "いらっしゃいませ " + strName + "! :)  You can type exclamation mark and then press enter to get help.";

                  }
                  else if(strLang == "de")
                  {

                     strText = "Willkommen " + strName + "! :-) Sie können Ausrufezeichen geben und drücken Sie die Eingabetaste, um etwas Hilfe zu bekommen.";

                  }
                  else if(strLang == "cn")
                  {

                     strText = "欢迎" + strName + "! :) 类型感叹号，然后按回车键得到一些帮助。";

                  }
                  else if(strLang == "es")
                  {

                     strText = "Gracias por venir, " + strName + "! Puede escribir el signo de exclamación y luego pulse Enter para obtener ayuda.";

                  }
                  else
                  {

                     strText = "Welcome " + strName + "! :) You can type exclamation mark and then press enter to get some help.";

                     if(strCountry == "be")
                     {

                        strText += " Choose between \"Français\" and \"Deustch\" using \"!setlang de\" or \"!setlang fr\"";

                     }
                     else if(strCountry == "ch")
                     {

                        strText += " Choose between \"Français\", \"Italiano\" and \"Deustch\" using \"!setlang de\", \"!setlang it\" or \"!setlang fr\"";

                     }

                  }

               }
               else if(get_user_data(strUser,"last_visit")  > 60 * 60 * 18 || get_user_data(strUser,"today_visit_count") <= 1)
               {

                  if(strLang == "pt")
                  {

                     strText = "Oi " + strName + "! Boas vindas a você! O que traz você aqui hoje?";

                  }
                  else
                  {

                     strText = "Hi " + strName + "! Welcome! What brings you here today?";

                  }

               }
               else
               {

                  if(strLang == "pt")
                  {

                     strText = strName + " está de volta! :)";

                  }
                  else if(strLang == "fr")
                  {

                     strText = strName + " est de retour! :)";

                  }
                  else if(strLang == "es")
                  {

                     strText = strName + " está de vuelta! :)";

                  }
                  else if(strLang == "cn")
                  {

                     strText = strName + "又回来了! :)";

                  }
                  else if(strLang == "jp")
                  {

                     strText = strName + "が帰ってきた! :)";

                  }
                  else if(strLang == "de")
                  {

                     strText = strName + " ist zurück! :)";

                  }
                  else
                  {

                     strText = strName + " is back! :)";

                  }

               }

            }

            lspeak(strUser,strLang,strText);

            return strText;

         }

      }


};


BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT



