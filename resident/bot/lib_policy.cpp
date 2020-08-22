

string warn(string strUser)
{
   return "This operation is not permitted to you, " + strUser + "! Contact moderator if you think its wrong.";
}

bool isbot(string strUser)
{

   if (::str::find_ci(strUser, "l3vl69") >= 0)
   {
      return true;
   }
   else if (::str::find_ci(strUser, "iamfree") >= 0)
   {
      return true;
   }
   else if (::str::find_ci(strUser, "iwanttodie") >= 0)
   {
      return true;
   }
   else if (::str::begins_ci(strUser, "bot"))
   {
      return true;
   }
   else if (::str::ends_ci(strUser, "bot"))
   {
      return true;
   }
   else
   {
      return false;
   }
}


bool spam(string strUser)
{
   if (::str::begins_ci(strUser, "spam"))
   {
      return true;
   }
   else if (::str::ends_ci(strUser, "spam"))
   {
      return true;
   }
   else if (strUser.compare_ci("coldzer0") == 0)
   {
      return true;
   }
   else if (strUser.compare_ci("bamberino") == 0 || strUser.compare_ci("bamb3rino") == 0)
   {
      return true;
   }
   else if (strUser.compare_ci("daratho") == 0)
   {
      return true;
   }
   else
   {
      return false;
   }
}
