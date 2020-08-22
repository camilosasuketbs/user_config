


function bot(strUser, strText)
{
	
	var str;
	
	if(cmd == "help")
	{
		
		str = "Hi "+strUser+", currently supported commands are: !help and !about";
		
	}
	else if(cmd == "about")
	{

		str = "Hi " + strUser + ", camilosasuke works with ca2. ca2 is a framework and set of libraries written in C++ language to help developers create great apps for users.";
		
	}
	else
	{
		
		str = "Hi " + strUser + ", currently supported commands are: !help and !about. You typed \""+ strText + "\"";
		
	}
	
	
	return str;
	
}