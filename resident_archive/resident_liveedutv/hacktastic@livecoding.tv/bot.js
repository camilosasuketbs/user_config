


function warn(strUser)
{
	
	return "This operation is not permitted to you, " +strUser+"! Contact moderator if you think its wrong.";
	
}

function isbot(strUser)
{

	if(strUser.substring(0, 3) == "bot" || strUser.substring(strUser.length - 3, strUser.length) == "bot")
	{
	
		return true;	
		
	}
	else
	{
		
		return false;
		
	}
	
}

function olink(strUser, strUrl)
{
	
	if(spam(strUser))
	{
		
	}
	else
	{
	
		open_link(strUrl);
		
	}
	
}


function spam(strUser)
{
	
	if(strUser.substring(0, 4) == "spam" || strUser.substring(strUser.length - 4, strUser.length) == "spam" 
	|| strUser == "coldzer0")
	{
		
		return true;
		
	}
	else
	{
		
		return false;
		
	}
	
	
}

function lspeak(strUser, strLang, strText)
{
	
	if(spam(strUser))
	{
		
	}
	else
	{
		
		lang_speak(strLang, strText);
		
	}
	
}

function lang(strLang)
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


function glang(strLang)
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


function l_and(strLang)
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


function username(strUser)
{

	var strName = get_user_data(strUser, "name");
	
	if(strName.length == 0)
	{
		
		strName = strUser;
		
	}
	
	return strName;
	
}


function ws() // welcome sound
{
	
	play_sound("C:\\ca2\\audio\\hidden\\glockd.wav");
	
}

function bye() // welcome sound
{
	
	play_sound("C:\\ca2\\audio\\hidden\\chirp7.wav");
	
}


function auto_translate(strUser, strDst, strText)
{
	
	olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#auto/"+strDst+"/" + url_encode(strText));
	
}

function translate(strUser, strDst, strSrc, strText)
{
	
	olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#"+strSrc+"/"+strDst+"/" + url_encode(strText));
	
}




function bot_x(strName, strUser, strText, strCountry, strLang)
{

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
		set_user_data(strUser, "country", "");
		set_user_data(strUser, "lang", "");
		set_user_data(strUser, "visit_count", "");
		set_user_data(strUser, "last_visit", "");
		set_user_data(strUser, "last_visit_time", "");
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
		
		if(response.length == 0)
		{

	 		str = strName + ", song not playing or not in record.";
			
		}
		else
		{
			
			str = strName + ", currently playing song is: \""+response+"\".";
			
		}
		
	}
	else if(strText == "!help")
	{

		if(strLang == "pt")
		{

			str = strName + ", a ajuda foi dividida em:\n!help util\n!help info\n!help config\n"+l_and(strLang)+"\n!help media";
			
		}
		else
		{
			
			str = strName + ", help information is grouped in:\n!help util\n!help info\n!help config\n"+l_and(strLang)+"\n!help media";
			
		}
			
	}
	else if(strText == "!commands")
	{

		if(strLang == "pt")
		{

			str = strName + ", a ajuda dos comandos foi agrupada em:\n!commands info\n!commands config\ne\n!commands media";
			
		}
		else
		{

			str = strName + ", commands help info were grouped in:\n!commands info\n!commands config\n"+l_and(strLang)+"\n!commands media";
			
		}
			
	}
	else if(strText.substring(0, 6) == "!help " || strText.substring(0, 10) == "!commands ")
	{
		
		var strGroup;
		
		var strC;
		
		strC = "";
		
		if(strText.substring(0, 10) == "!commands ")
		{
			
			strGroup = strText.substring(10);
			
		}
		else
		{

			strGroup = strText.substring(6);

		}
		
		if(strGroup == "config")
		{

			if(strLang == "pt")
			{
				
				strGroup = " os comandos de configuração são:";
			
				str = "!setname \"nome\"\ne\n!setlang \"código do país\"";
				
			}
			else
			{

				strGroup = " settings commands are:";
	
				str = "!setname \"name\"\n"+l_and(strLang)+"\n!setlang \"country code\"";
	
			}
		}
		else if(strGroup == "media")
		{
			if(strLang == "pt")
			{
			
				strGroup = " os comandos de multimídia são:";
			
				str = "!rr\n!rickroll\n!say \"texto\"\n!playlist\ne\n!play \"som\"";
				
			}
			else
			{
	
				strGroup = " multimedia commands are:";
	
				str = "!rr\n!rickroll\n!say \"text\"\n!playlist\n"+l_and(strLang)+"\n!play \"sound\"";
	
			}
		}
		else if(strGroup == "util")
		{
			
			if(strLang == "pt")
			{
			
				strGroup = " alguns comandos utilitários:";
			
				str = "!urbd \"pergunta ao urban dictionary\"\n!at \"traduzir automaticament do google\"\n"+l_and(strLang)+"\n!t \"lang\" \"texto a ser traduzido de lang\"";				
				
			}
			else
			{
	
				strGroup = " some utility commands:";
	
				str = "!urbd \"urban dictionary query\"\n!at \"google auto translate\"\n"+l_and(strLang)+"\n!t \"lang\" \"text to translate from lang\"";
	
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
	
			strC = strName + ", ide <platform> display info about IDE used with ca2 framework. Platforms: windows (Desktop), linux, macos, ios, android, winrt.";
			
		}
		else if(strGroup == "setlang")
		{
	
			strC = strName + ", setlang <language code and-or two letter country code> set user current language. It is made effort to supply resources using user current language.";
			
		}
		else
		{
			if(strLang == "pt")
			{
			
				strGroup = " os comandos para obter informações são:";
	
				str = "!ide \"plataforma\"\n!help \"comando\"\n!cmdtips\n!help <comando>\n!commands\n!about\n!vaimepassarobot?\n"+l_and(strLang)+"\n!credits";
				
			}
			else
			{
	
				strGroup = " information retrieval commands are:";
	
				str = "!ide \"platform\"\n!help \"command\"\n!cmdtips\n!help <command>\n!commands\n!about\n!vaimepassarobot?\n"+l_and(strLang)+"\n!credits";
	
			}
		}
		
		if(strC.length == 0)
		{
		
			if(strLang == "pt")
			{
				
				str = strName + ", " + strGroup + "\n" + str;
				
			}
			else 
			{
				
				str = strName + ", " + strGroup + "\n" + str;
				
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
	else if(strText.length > 6 && strText.substring(0, 6) == "!urbd ")
	{
		
		olink(strUser, "http://www.urbandictionary.com/define.php?term=" + url_encode(strText.substring(6)));
		
	}
	else if(strText.length > 4 && strText.substring(0, 4) == "!at ")
	{
		
		auto_translate(strUser, glang(strLang), strText.substring(4));
		
    }
	else if(strText.length > 3 && strText.substring(0, 3) == "!t " && strText.substring(5, 6) == " ")
	{
		
		translate(strUser, glang(strText.substring(3, 5)), glang(strLang), strText.substring(6));
		
    }
	else if(strText.length == 11 && strText.substring(0, 9) == "!setlang ")
	{

        set_user_data(strUser, "lang", lang(strText.substring(9, 11)));
		
    }
	else if(strText.length == 14 && strText.substring(0, 9) == "!setlang " && strText.substring(11, 12) == "-")
	{

        set_user_data(strUser, "lang", lang(strText.substring(9, 11)));
        set_user_data(strUser, "country", strText.substring(12, 14));
		
    }
	else if(strText == "!resetlang")
	{

        set_user_data(strUser, "lang", "");
		
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
		
		var a = ls_names("C:\\ca2\\audio\\element").split('\n');
		
		if(a.length > 0)
		{
	  
			var str = "Type !play ";
		  
			for(i = 0; i < a.length - 1; i++)
			{
				
				if(i > 0)
				{
					str += ", ";
				}
				
				str += a[i].toLowerCase();
				
				
			}
	
			if(a.length > 1)
			{
				
				str += " or " + a[a.length - 1].toLowerCase();
				
			}
			else if(a.length == 1)
			{
				
				str += a[0].toLowerCase();
				
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

		var a = ls_names("C:\\ca2\\audio\\element").split('\n');

		var str = strText.substring(1);
	  	
		var found = 0;

		for(i = 0; i < a.length && !found; i++)
		{

			if(a[i].toLowerCase() == str.toLowerCase())
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
		
			lspeak(strUser, strLang, str);
		
			return "";
			
		}
		
	}


	if(str.length <= 0)
	{

		return "";		
		
	}
	  
	lspeak(strUser, strLang, str);
	
	return str;

}


function bot(strUser, strText)
{

	var strName = username(strUser);
	
	var strCountry = get_user_data(strUser, "country").toLowerCase();
	
	if(get_user_data(strUser, "lang") == "")
	{
		
		set_user_data(strUser, "lang", lang(strCountry));
		
	}
	
	var strLang = lang(get_user_data(strUser, "lang").toLowerCase());

	if(strText.length > 9 && strText.substring(0, 9) == "!setname ")
	{

		var str = strText.substring(9);
		
		set_user_data(strUser, "name", str);
		
		lspeak(strUser, strLang, str);
		
		return "";
		
	}
	else if(strText.length > 5 && strText.substring(0, 5) == "!say ")
	{

		var str = strText.substring(5);
		
		lspeak(strUser, strLang, str);
		
		return "";
		
	}
	else if(strText.length > 6 && strText.substring(0, 6) == "!play ")
	{
		
		var a = ls_names("C:\\ca2\\audio\\element").split('\n');

		var str = strText.substring(6);
	  	
		var found = 0;

		for(i = 0; i < a.length && !found; i++)
		{

			if(a[i].toLowerCase() == str.toLowerCase())
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
		
			return "\"" + str +  "\" not found. Please, use !playlist command to list existing sounds.";
		
		}
	
	}
	
	
	var tokens = strText.split(" ");
	
	if(tokens.length == 1)
	{
		
		if(tokens[tokens.length - 1].charAt(0) == "!" && tokens[tokens.length - 1].charAt(1) == "@")
		{
			
			strUser = tokens[0].substring(2);
			
			strText = "!";
			
		}
		
	}
	else
	{
		
		if(tokens[tokens.length - 1].charAt(0) == "@")
		{
			
			strUser = tokens[tokens.length - 1].substring(1);
			
			str = "";
	
			for(i = 0; i < tokens.length - 1; i++)
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
	
	strCountry = get_user_data(strUser, "country").toLowerCase();
	
	if(get_user_data(strUser, "country") == "")
	{
		
		set_user_data(strUser, "country", get_lctv_info(strUser, "country_code").toLowerCase());
		
	}

	if(get_user_data(strUser, "lang") == "")
	{
		
		set_user_data(strUser, "lang", lang(strCountry));
		
	}
	
	var strLang = lang(get_user_data(strUser, "lang").toLowerCase());

	return bot_x(strName, strUser, strText, strCountry, strLang);
	
}








































































































































function pres(strUser, strType)
{

	var strName = username(strUser);
	
	var strText;
	
	if(strType == "unavailable")
	{
		
		if(get_user_data(strUser, "country") == "")
		{
			
			set_user_data(strUser, "country", get_lctv_info(strUser, "country_code").toLowerCase());
			
		}

		var strCountry = get_user_data(strUser, "country").toLowerCase();
		
		if(get_user_data(strUser, "lang") == "")
		{
			
			set_user_data(strUser, "lang", lang(strCountry));
			
		}
		
		var strLang = lang(get_user_data(strUser, "lang").toLowerCase());

		if(spam(strUser))
		{
			
			strText = strUser + " gone, uff...";
			
		}
		else
		{

			bye();


			if(Integer.parseInt(get_user_data(strUser, "visit_count"))  <= 4)
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
		
		lspeak(strUser, strLang, strText);
		
		return strText;

	}
	else
	{
		
		if(get_user_data(strUser, "country") == "")
		{
			
			set_user_data(strUser, "country", get_lctv_info(strUser, "country_code").toLowerCase());
			
		}

		var strCountry = get_user_data(strUser, "country").toLowerCase();
		
		if(get_user_data(strUser, "lang") == "")
		{
			
			set_user_data(strUser, "lang", lang(strCountry));
			
		}
		
		var strLang = lang(get_user_data(strUser, "lang").toLowerCase());
		
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
		

			if(Integer.parseInt(get_user_data(strUser, "visit_count"))  <= 4)
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
			else if(Integer.parseInt(get_user_data(strUser, "last_visit"))  > 60 * 60 * 18 || Integer.parseInt(get_user_data(strUser, "today_visit_count")) <= 1)
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

		lspeak(strUser, strLang, strText);

		return strText;
		
	}
		
}

