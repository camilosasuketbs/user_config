


function pres(strUser, strType)
{
	
	var strText;
	
	if(strType == "unavailable")
	{
		
		strText = "Bye " + strUser + "! :(";
			
		
		return strText;

	}
	else
	{
		
		strText = "Welcome " + strUser + "! :) You can type exclamation mark and then press enter to get some help.";
		

		return strText;
		
	}
		
}

