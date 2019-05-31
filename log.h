#ifndef __LOG_H_815C5D14DD3DF470C62478FA2B1315DE__
#define __LOG_H_815C5D14DD3DF470C62478FA2B1315DE__

void log_debug(int level,const char* file, int lineno,const char* fmt,...);
void log_buffer_debug(int level,const char* file, int lineno,void* pbuf,int size,const char* fmt,...);
void set_log_level(int level);

#define LOG_CRIT_LEVEL          0
#define LOG_ERROR_LEVEL         1
#define LOG_WARN_LEVEL          2
#define LOG_INFO_LEVEL          3
#define LOG_DEBUG_LEVEL         4
#define LOG_TRACE_LEVEL         5

#define LOG_CRIT(...)    do{log_debug(LOG_CRIT_LEVEL,__FILE__,__LINE__,__VA_ARGS__);}while(0)
#define LOG_ERROR(...)   do{log_debug(LOG_ERROR_LEVEL,__FILE__,__LINE__,__VA_ARGS__);}while(0)
#define LOG_WARN(...)    do{log_debug(LOG_WARN_LEVEL,__FILE__,__LINE__,__VA_ARGS__);}while(0)
#define LOG_INFO(...)    do{log_debug(LOG_INFO_LEVEL,__FILE__,__LINE__,__VA_ARGS__);}while(0)
#define LOG_DEBUG(...)   do{log_debug(LOG_DEBUG_LEVEL,__FILE__,__LINE__,__VA_ARGS__);}while(0)
#define LOG_TRACE(...)   do{log_debug(LOG_TRACE_LEVEL,__FILE__,__LINE__,__VA_ARGS__);}while(0)


#define LOG_BUFFER_CRIT(ptr,size,...)    do{log_buffer_debug(LOG_CRIT_LEVEL,__FILE__,__LINE__,((void*)(ptr)),((int)(size)),__VA_ARGS__);}while(0)
#define LOG_BUFFER_ERROR(ptr,size,...)   do{log_buffer_debug(LOG_ERROR_LEVEL,__FILE__,__LINE__,((void*)(ptr)),((int)(size)),__VA_ARGS__);}while(0)
#define LOG_BUFFER_WARN(ptr,size,...)    do{log_buffer_debug(LOG_WARN_LEVEL,__FILE__,__LINE__,((void*)(ptr)),((int)(size)),__VA_ARGS__);}while(0)
#define LOG_BUFFER_INFO(ptr,size,...)    do{log_buffer_debug(LOG_INFO_LEVEL,__FILE__,__LINE__,((void*)(ptr)),((int)(size)),__VA_ARGS__);}while(0)
#define LOG_BUFFER_DEBUG(ptr,size,...)   do{log_buffer_debug(LOG_DEBUG_LEVEL,__FILE__,__LINE__,((void*)(ptr)),((int)(size)),__VA_ARGS__);}while(0)
#define LOG_BUFFER_TRACE(ptr,size,...)   do{log_buffer_debug(LOG_TRACE_LEVEL,__FILE__,__LINE__,((void*)(ptr)),((int)(size)),__VA_ARGS__);}while(0)


#endif /* __LOG_H_815C5D14DD3DF470C62478FA2B1315DE__ */
