
long getnewtime()
{
  DateTime now = RTC. now (); // Time = time current RTC
  long  unix_time = now.unixtime();
  return unix_time;
}
