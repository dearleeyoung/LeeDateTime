# LeeDateTime
A cross-platform C++ class which manages the datetime and datetime-span. It is similar to COleDateTime and COleDateTimeSpan.

2018-08-27 1.0版本.

日期时间类 和 日期时间跨度类.

接口类似于OLE的COleDateTime类和COleDateTimeSpan类.

CLeeDateTime: 日期时间类. windows中能表示1601/01/01以来的日期, linux中能表示的日期没有限制. 可精确到1毫秒. 
可以与 time_t, struct tm, SYSTEMTIME(windows), timeval(linux), date/double (windows OLE) 等时间类型相互转换, 可解析表示日期时间的字符串, 并可按指定格式格式化为字符串.

CLeeDateTimeSpan: 日期时间跨度类. 可精确到1毫秒. 用于CLeeDateTime 的日期时间计算.

