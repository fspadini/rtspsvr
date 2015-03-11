#pragma once

#include "connection.h"

enum{from_net = 0, from_app, from_timer};
enum{app_shared, app_monopoly};
struct app_msg
{
	void* ptr;     //消息节点
	int from;  
	int src;       //src_app_id
	int event;      //消息
	int length;     //消息长度 
	char* content;  //消息内容
};

class app
{
public:

	virtual int on_net(connection *n, int event, char* content, int length) = 0;	
	virtual int on_app(int event, char* content, int length, int src) = 0;
	virtual int on_timer(int event, void * ptr) = 0;
	virtual int on_unpack(char * data, int len, char *&packet) = 0;
	
	app();
	
	virtual ~app();
	
	int create(int appid, int msg_cout, const char * app_name, int app_mode = app_shared);
	
	int push(app_msg * msg);
	
	int increase_drop_msg();
	
	const char * name();
	
	int get_appid();

	int get_app_mode();
		
	int add_timer(int id, int interval, void * context = NULL);

	int post_connect(const char * ip, short port, int delay, void * context = NULL);
	
	int post_app_msg(int dst, int event, void * content = NULL, int length = 0, int src = -1);
	
	static int log_out(int lev, const char * format,...);
	
private:

	static void * app_run(void* param);
	
	int run();
		
private:	
	ring_buffer m_ring_buf;
	char m_name[max_app_name + 1];
	bool m_brun;
	int m_drop_msg;
	int m_appid;
	int m_mode;
};