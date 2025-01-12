/*
* Copyright (c) 2017-2018 Snowflake Computing, Inc. All rights reserved.
*/

#ifndef SNOWFLAKE_PLATFORM_H
#define SNOWFLAKE_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _WIN32
// Windows
#define STDCALL __stdcall
#include <windows.h>
#include <direct.h>
#include <time.h>

typedef HANDLE SF_THREAD_HANDLE;
typedef CONDITION_VARIABLE SF_CONDITION_HANDLE;
typedef CRITICAL_SECTION SF_CRITICAL_SECTION_HANDLE;
typedef SRWLOCK SF_RWLOCK_HANDLE;
typedef HANDLE SF_MUTEX_HANDLE;

#define PATH_SEP '\\'

#else
#define STDCALL
// Get uname output for Linux and MacOSX
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <pthread.h>

typedef pthread_t SF_THREAD_HANDLE;
typedef pthread_cond_t SF_CONDITION_HANDLE;
typedef pthread_mutex_t SF_CRITICAL_SECTION_HANDLE;
typedef pthread_rwlock_t SF_RWLOCK_HANDLE;
typedef pthread_mutex_t SF_MUTEX_HANDLE;

#define PATH_SEP '/'

#endif

struct tm *STDCALL sf_gmtime(const time_t *timep, struct tm *result);

struct tm *STDCALL sf_localtime(const time_t *timep, struct tm *result);

void STDCALL sf_tzset(void);

int STDCALL sf_setenv(const char *name, const char *value);

char *STDCALL sf_getenv(const char *name);

int STDCALL sf_unsetenv(const char *name);

int STDCALL sf_mkdir(const char *path);


int STDCALL
_thread_init(SF_THREAD_HANDLE *thread, void *(*proc)(void *), void *arg);

int STDCALL _thread_join(SF_THREAD_HANDLE thread);

void STDCALL _thread_exit();

int STDCALL _cond_init(SF_CONDITION_HANDLE *cond);

int STDCALL _cond_broadcast(SF_CONDITION_HANDLE *cond);

int STDCALL _cond_signal(SF_CONDITION_HANDLE *cond);

int STDCALL
_cond_wait(SF_CONDITION_HANDLE *cond, SF_CRITICAL_SECTION_HANDLE *lock);

int STDCALL _cond_term(SF_CONDITION_HANDLE *cond);

int STDCALL _critical_section_init(SF_CRITICAL_SECTION_HANDLE *lock);

int STDCALL _critical_section_lock(SF_CRITICAL_SECTION_HANDLE *lock);

int STDCALL _critical_section_unlock(SF_CRITICAL_SECTION_HANDLE *lock);

int STDCALL _critical_section_term(SF_CRITICAL_SECTION_HANDLE *lock);

int STDCALL _rwlock_init(SF_RWLOCK_HANDLE *lock);

int STDCALL _rwlock_rdlock(SF_RWLOCK_HANDLE *lock);

int STDCALL _rwlock_rdunlock(SF_RWLOCK_HANDLE *lock);

int STDCALL _rwlock_wrlock(SF_RWLOCK_HANDLE *lock);

int STDCALL _rwlock_wrunlock(SF_RWLOCK_HANDLE *lock);

int STDCALL _rwlock_term(SF_RWLOCK_HANDLE *lock);

int STDCALL _mutex_init(SF_MUTEX_HANDLE *lock);

int STDCALL _mutex_lock(SF_MUTEX_HANDLE *lock);

int STDCALL _mutex_unlock(SF_MUTEX_HANDLE *lock);

int STDCALL _mutex_term(SF_MUTEX_HANDLE *lock);

const char *STDCALL sf_os_name();

void STDCALL sf_os_version(char *ret);

int STDCALL sf_strncasecmp(const char *s1, const char *s2, size_t n);

char *STDCALL sf_filename_from_path(const char *path);

void STDCALL sf_log_timestamp(char* tsbuf, size_t tsbufsize);

int STDCALL sf_create_directory_if_not_exists(const char * directoryName);

int STDCALL sf_delete_directory_if_exists(const char * directoryName);

void STDCALL sf_get_tmp_dir(char * tmpDir);

#ifdef __cplusplus
}
#endif

#endif