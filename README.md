# LeeDateTime
A cross-platform C++ class which manages the datetime and datetime-span. It is similar to COleDateTime and COleDateTimeSpan.

2018-08-27 1.0版本.

日期时间类 和 日期时间跨度类.

接口类似于OLE的COleDateTime类和COleDateTimeSpan类.

CLeeDateTime: 日期时间类. windows中能表示1601/01/01以来的日期, linux中能表示的日期没有限制. 可精确到1毫秒. 
可以与 time_t, struct tm, SYSTEMTIME(windows), timeval(linux), date/double (windows OLE) 等时间类型相互转换, 可解析表示日期时间的字符串, 并可按指定格式格式化为字符串.

CLeeDateTimeSpan: 日期时间跨度类. 可精确到1毫秒. 用于CLeeDateTime 的日期时间计算.

Examples:
//ctor
CLeeDateTime dt1("2020-05-21 17:26:00");                 //ctor (from string)
CLeeDateTime dt2(2020, 5, 21, 17, 26, 0);                //ctor (from year, month, ...)
CLeeDateTime dt3(static_cast<time_t>(1590053160));       //ctor (from time_t)
CLeeDateTime dt4(43972.726389);                          //ctor (from double)
CLeeDateTime dt5(dt4);                                   //copy ctor
CLeeDateTime dt6 = CLeeDateTime::GetCurrentTime();       //copy ctor

//some other examples
dt1.GetYear();                                           //2020
dt1 > CLeeDateTime(2020, 5, 21, 16, 36, 20);             //true
dt1.SetDateTime(2020, 5, 21, 16, 36, 20);                //set new time
dt1.Get_tm();                                            //get struct tm
dt1.Format();                                            //string("2020-05-21 16:36:20")
auto dtsp1 = dt2 - dt1;                                  //CLeeDateTimeSpan, 49min40sec
dtsp1 == dt3 - dt1;                                      //true
dt1 -= CLeeDateTimeSpan(1, 0, 0, 0, 200);                //minus 1 day and 200 milliseconds
dt1.FormatWithMillisecond();                             //string("2020-05-20 16:36:19.800")
