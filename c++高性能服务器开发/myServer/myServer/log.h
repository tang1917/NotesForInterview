#ifndef __MYSERVER_LOG_H__
#define __MYSERVER_LOG_H__
#include<string>
#include<stdint.h>
#include<memory>
#include<list>
#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
#include<tuple>
namespace myserver {
	//��־�¼�
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr;
		LogEvent();

	private:
		const char* m_file = nullptr;	//�ļ���
		int32_t m_line = 0;				//�к�
		uint32_t m_elapse = 0;			//����������ʼ�����ڵĺ�����
		uint32_t m_thread = 0;			//�߳�id
		uint32_t m_fiberId = 0;			//Э��id
		uint64_t m_time;				//ʱ���
		std::string m_content;

	};
	//��־����
	class LogLevel {
	public:
		enum Level {
			DEBUG = 1,
			INFO = 2,
			WARN = 3,
			ERROR = 4,
			FATAL = 5
		};
	};
	//��־��ʽ��
	class LogFormatter
	{
	public:

		typedef std::shared_ptr<LogFormatter> ptr;
		std::string format(LogEvent::ptr event);
		void init();
	private:
		class FormatItem {
		public:
			typedef std::shared_ptr<FormatItem> ptr;
			virtual ~FormatItem(){}
			virtual void format(std::ostream& os,LogEvent::ptr event) = 0;
		};
	private:
		std::string m_pattern;
		std::vector<FormatItem::ptr> m_items;

	};

	//��־�����
	class LogAppender
	{
	public:
		typedef std::shared_ptr<LogAppender> ptr;
		virtual ~LogAppender() {}
		virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
		void setFormatter(LogFormatter::ptr val) { m_formatter = val; }
		LogFormatter::ptr getFormatter() const { return m_formatter; }

	protected:									//������Ҫʹ�ø����m_level
		LogLevel::Level m_level;
		LogFormatter::ptr m_formatter;
	};


	//��־��
	class Logger {
	public:
		typedef std::shared_ptr<Logger> ptr;
		Logger(const std::string&name = "root");
		void log(LogLevel::Level level, LogEvent::ptr event);

		void debug(LogEvent::ptr event);
		void info(LogEvent::ptr event);
		void warn(LogEvent::ptr event);
		void error(LogEvent::ptr event);
		void fatal(LogEvent::ptr event);

		void addAppender(LogAppender::ptr appender);
		void delAppender(LogAppender::ptr appender);
		LogLevel::Level getLevel() const { return m_level; }
		void selLevel(LogLevel::Level val) { m_level = val; }

	private:
		std::string m_name;							//��־����
		LogLevel::Level m_level;					//��־����
		std::list<LogAppender::ptr>	m_appenders		//Appender����

	};

	//���������̨��Appender
	class StdoutLogAppender :public LogAppender
	{
	public:
		typedef std::shared_ptr<StdoutLogAppender> ptr;
		void log(LogLevel::Level level, LogEvent::ptr event) override;
	};

	//����������ļ���Appender
	class FileLogAppender :public LogAppender {
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;
		FileLogAppender(const std::string& filename);
		void log(LogLevel::Level level, LogEvent::ptr event) override;

		//���´��ļ�,�ļ��򿪳ɹ�����true
		bool reopen();
	private:
		std::string m_filename;
		std::ofstream m_filestream;
	};
}
#endif // !__MYSERVER_LOG_H__

