
function dspeak(text)
{
	speak(text);
	
}


function ws() // welcome sound
{
	
	play_sound("C:\\ca2\\audio\\hidden\\glockd.wav");
	
}

function bye() // welcome sound
{
	
	play_sound("C:\\ca2\\audio\\hidden\\chirp7.wav");
	
}


function bot_x(strUser, strText)
{

    if(strText == "!")
    {
		
		str = strUser + "! Some commands supported !help, !about and !vaimepassarobot?";
		
    }
	else if(strText == "!help")
	{

		str = strUser + "! Commands supported !say <text>, !playlist, !play <sound>, !help, !about and !vaimepassarobot?";
		
	}
	else if(strText == "!about")
	{

        str = strUser + "! ca2 is a set of Libraries written in C++ language to help developers create great apps for users.";
		
    }
	else if(strText == "!vaimepassarobot?") // question by julienb16 //2015-10-09 sexta-feira 23:23
  	{
		
		str = strUser + "! Currently, only the client will be made available. The bot is still handmade.";
		
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
		
			dspeak(str);
		
			return "";
			
		}
		
	}


	if(str.length <= 0)
	{

		return "";		
		
	}
	  
	dspeak(str);
	
		str += "(last visit:" + get_user_data(strUser, "last_visit") + " seconds ago";

	
	return str;

}


function bot(strUser, strText)
{

	if(strText.length > 5 && strText.substring(0, 5) == "!say ")
	{

		var str = strText.substring(5);
		
		dspeak(str);
		
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
	
	return bot_x(strUser, strText);
	
}





function pres(strUser, strType)
{
	
	if(strType == "unavailable")
	{
		
		bye();

		var strText = "Bye, " + strUser + "!!";
		
		dspeak(strText);
		
		return "";

	}
	else
	{
		
		ws();
		
		var strText = "Welcome, " + strUser + "!!";
		
		dspeak(strText);
		
		return "";
		
	}
		
}

