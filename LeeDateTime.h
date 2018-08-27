#pragma once
#include <ctime>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <sys/time.h>
#endif

using std::string;

class CLeeDateTime;

//����ʱ������
class CLeeDateTimeSpan {
	friend class CLeeDateTime;//��Ԫ
public:
	CLeeDateTimeSpan() : m_span(0.0){ }
	CLeeDateTimeSpan(int days, int hours, int minutes, int seconds, int milliseconds = 0) 
		: m_span(days + hours / 24.0 + minutes / 60.0 / 24.0 
			+ seconds / 3600.0 / 24.0 + milliseconds / 1000.0 / 3600.0 / 24.0){ }
	CLeeDateTimeSpan(double span) : m_span(span){ }
	CLeeDateTimeSpan& operator=(const CLeeDateTimeSpan&rhs)  {
		if (this == &rhs) {
			return *this;
		}
		m_span = rhs.m_span;
		return *this;
	}
	operator double() const  { return m_span; }//����ת������,ת��Ϊdouble
	void SetDateTimeSpan(int days, int hours, int minutes, int seconds, int milliseconds = 0)  {
		m_span = days + hours / 24.0 + minutes / 60.0 / 24.0 
			+ seconds / 3600.0 / 24.0 + milliseconds / 1000.0 / 3600.0 / 24.0;
	}
	bool operator==(const CLeeDateTimeSpan& rhs) const {
		return m_span - rhs.m_span < THREE_MILLISECOND &&
			rhs.m_span - m_span < THREE_MILLISECOND;
	}
	bool operator!=(const CLeeDateTimeSpan& rhs) const { return !(*this == rhs); }
	bool operator>(const CLeeDateTimeSpan& rhs) const {
		return m_span - rhs.m_span >= THREE_MILLISECOND;
	}
	bool operator<(const CLeeDateTimeSpan& rhs) const {
		return  rhs.m_span - m_span >= THREE_MILLISECOND;
	}
	bool operator>=(const CLeeDateTimeSpan& rhs) const {
		return  !(*this < rhs);
	}
	bool operator<=(const CLeeDateTimeSpan& rhs) const {
		return  !(*this > rhs);
	}
	CLeeDateTimeSpan operator+(const CLeeDateTimeSpan& rhs) const {
		return CLeeDateTimeSpan(m_span + rhs.m_span);
	}
	CLeeDateTimeSpan operator-(const CLeeDateTimeSpan& rhs) const {
		return CLeeDateTimeSpan(m_span - rhs.m_span);
	}
	CLeeDateTimeSpan& operator+=(const CLeeDateTimeSpan& rhs) {
		m_span += rhs.m_span;
		return *this;
	}
	CLeeDateTimeSpan& operator-=(const CLeeDateTimeSpan& rhs) {
		m_span -= rhs.m_span;
		return *this;
	}
	double GetTotalDays() const  { return m_span; }//�õ�������
	double GetTotalHours() const  { return m_span * 24.0; }//�õ���Сʱ��
	double GetTotalMinutes() const  { return m_span * (24.0 * 60.0); }//�õ��ܷ�����
	double GetTotalSeconds() const  { return m_span * (24.0 * 60.0 * 60.0); }//�õ�������
	double GetTotalMilliseconds() const  { return m_span * (24.0 * 60.0 * 60.0 * 1000.0); }//�õ��ܺ�����

private:
	double m_span;//�������ֱ�ʾ����, С�����ֱ�ʾһ���е�ʱ��. ���� 2��3Сʱ��Ӧ��2.125.
	constexpr static double THREE_MILLISECOND = 3 / 1000.0 / 3600.0 / 24.0;//������. ������CLeeDateTimeSpan֮���ڴ�֮��ʱ,����Ϊ�������.
};

//����ʱ����,windows���ܱ�ʾ1601/01/01����������,linux���ܱ�ʾ������û������.
class CLeeDateTime {
public:
	CLeeDateTime() : m_dt(0.0) { }
	CLeeDateTime(double d) : m_dt(d) { }
	CLeeDateTime(time_t t) : m_dt(CLeeDateTime::time_t_to_double(t)) { }
	CLeeDateTime(const struct tm& s) ;
#ifdef _WIN32
	CLeeDateTime(const ::SYSTEMTIME& st) ;//�Ὣ������Ҳ����
#endif
#ifdef __linux__
	CLeeDateTime(const timeval& st) ;//�Ὣ΢����Ҳ����,��ʧ���ȱ�ɺ���.
#endif
	CLeeDateTime(int year, int month, int day, 
		int hour = 0, int minute = 0, int second = 0, int millisecond = 0) ;
	CLeeDateTime(const string& str) ;
	CLeeDateTime(const CLeeDateTime& c) : m_dt(c.m_dt) { }//�������캯��
	CLeeDateTime& operator=(const CLeeDateTime& rhs);//��ֵ����

	string Format(const string& format = "%Y-%m-%d %H:%M:%S") const;//��ʽ�����ʱ��(��Ϊ����ֵ,��������),������ʽ�����strftime����.
	string FormatWithMillisecond(const string& format = "%Y-%m-%d %H:%M:%S") const;//��ʽ�����ʱ��, �õ���������ַ���

	void SetDateTime(int year, int month, int day,
		int hour = 0, int minute = 0, int second = 0, int millisecond = 0) ;//��������ʱ��
	void ParseDateTime(const string& str) ;//���ַ����н�������ʱ��

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	int GetMillisecond() const;//����
	int GetDayOfWeek() const;//һ�ܵĵڼ���. ����Ϊ0, ����Ϊ6.
#ifdef _WIN32
	::SYSTEMTIME Get_SYSTEMTIME() const;//תΪSYSTEMTIME
#endif
#ifdef __linux__
	::timeval Get_timeval() const;//תΪtimeval
#endif
    struct tm Get_tm() const;//תΪstruct tm(��Ϊ����ֵ,��������).
	struct tm Get_GMT_tm() const;//תΪstruct tm(��Ϊ����ֵ,��������).���ص���GMTʱ���tm.
	time_t Get_time_t() const;//תΪtime_t(��Ϊ����ֵ,��������)

	bool IsLeapYear() const;//�Ƿ�������
	operator double() const { return m_dt; }//����ת������,ת��Ϊdouble
	
	bool operator==(const CLeeDateTime& rhs) const;
	bool operator!=(const CLeeDateTime& rhs) const;
	bool operator>(const CLeeDateTime& rhs) const;
	bool operator<(const CLeeDateTime& rhs) const;
	bool operator>=(const CLeeDateTime& rhs) const;
	bool operator<=(const CLeeDateTime& rhs) const;

	CLeeDateTime operator+(const CLeeDateTimeSpan& span) const ;
	CLeeDateTime& operator+=(const CLeeDateTimeSpan& span) ;
	CLeeDateTime operator-(const CLeeDateTimeSpan& span) const ;
	CLeeDateTime& operator-=(const CLeeDateTimeSpan& span) ;

	CLeeDateTimeSpan operator-(const CLeeDateTime& rhs) const ;//��������ʱ�������

	static CLeeDateTime GetCurrentTime();//�õ���ǰʱ��
	static bool IsLeapYear(int year);//ĳ���Ƿ�������
	static int GetDays(int year, int month);//�õ�ĳ��ĳ�µ�����
	static int GetTimeZone();//�õ�����ʱ��						 
	static double time_t_to_double(time_t t);//��time_t����ʱ��ת��Ϊdouble����
	static time_t double_to_time_t(double d);//��double����ʱ��ת��Ϊtime_t����(Ϊ����ֵ,��������).��time_tΪ32λ,��������.
    
private:
	double m_dt;//��1899-12-30 00:00:00��ʼ��ʱ��, �������ֱ�ʾ����, С�����ֱ�ʾһ���е�ʱ��. ����1899-12-31 06:00:00 ��ӦΪ1.25. 
	constexpr static double HALF_SECOND = 0.5 / 3600.0 / 24.0;//����
	constexpr static double THREE_MILLISECOND = 3 / 1000.0 / 3600.0 / 24.0;//������. ������CLeeDateTime֮���ڴ�֮��ʱ,����Ϊ�������.
};
