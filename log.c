#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

static int st_loglevel = LOG_ERROR_LEVEL;

void set_log_level(int level)
{
	if (level >= LOG_CRIT_LEVEL && level <= LOG_TRACE_LEVEL) {
		st_loglevel = level;
	}
}

void log_debug(int level, const char* file, int lineno, const char* fmt, ...)
{
    va_list ap;
    if (level > st_loglevel) {
        return;
    }

    if (st_loglevel >= LOG_DEBUG_LEVEL){
    	fprintf(stderr, "[%s:%d] ", file, lineno);	
    }
    
    if (fmt != NULL) {
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, "\n");
    }
    fflush(stderr);
    return;
}

void log_buffer_debug(int level, const char* file, int lineno, void* pbuf, int size, const char* fmt, ...)
{
    va_list ap;
    unsigned char* ptr = (unsigned char*)pbuf;
    unsigned char* plast = ptr;
    int i;
    if (level > st_loglevel) {
        return;
    }
    if (st_loglevel >= LOG_DEBUG_LEVEL){
    	fprintf(stderr, "[%s:%d] ", file, lineno);	
    }
    if (fmt != NULL) {
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, " ");
    }
    fprintf(stderr, "ptr[0x%p] size[%d:0x%x]", ptr, size, size);
    for (i = 0; i < size; i++) {
        if ((i % 16) == 0) {
            if (i > 0) {
                fprintf(stderr, "    ");
                while (plast != ptr) {
                    if (*plast >= ' ' && *plast <= '~') {
                        fprintf(stderr, "%c", *plast);
                    } else {
                        fprintf(stderr, ".");
                    }
                    plast ++;
                }                
            }
            fprintf(stderr,"\n0x%08x:",i);
        }
        fprintf(stderr," 0x%02x",*ptr);
        ptr ++;
    }
    if (plast != ptr) {
        while ((i % 16) != 0) {
            fprintf(stderr, "     ");
            i ++;
        }
        fprintf(stderr, "    ");
        while (plast != ptr) {
            if (*plast >= ' ' && *plast <= '~') {
                fprintf(stderr, "%c", *plast);
            } else {
                fprintf(stderr, ".");
            }
            plast ++;
        }
        fprintf(stderr, "\n");
    }
    fflush(stderr);
    return;
}