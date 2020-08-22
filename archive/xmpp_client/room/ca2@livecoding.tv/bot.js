
function bot(strUser, strText)
{

      if(strText == "!")
      {
         return "Hello @" + strUser + "!! Commands supported !help, !about and !vaimepassarobot?";
      }
      else if(strText == "!help")
      {
         return "Hello @" + strUser + "!! Commands supported !help, !about and !vaimepassarobot?";
      }
      else if(strText == "!about")
      {
         return "Hello @" + strUser + "!!\nca2 is a set of Libraries written in C++ language to help developers create great apps for users.";
      }
      else if(strText == "!vaimepassarobot?") // question by julienb16 //2015-10-09 sexta-feira 23:23
      {
         return "Hello @" + strUser + "!!\nCurrently, only the client will be made available. The bot is still handmade.";
      }
	  
	  return "";

}