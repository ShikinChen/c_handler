//
// Created by Shiki on 2022/8/20.
//

#ifndef C_HANDLER_SRC_HANDLER_THREAD_H_
#define C_HANDLER_SRC_HANDLER_THREAD_H_

#include <pthread.h>
#include "looper.h"

typedef struct handler_thread {

  pthread_t tid_;

  int status_;

  char *name_;

  Looper *looper_;

} HandlerThread;

HandlerThread *CreateThread(char *name);

void StartThread(HandlerThread *thread);

void ThreadJoin(HandlerThread *thread);

void QuitThread(HandlerThread *thread);
#endif //C_HANDLER_SRC_HANDLER_THREAD_H_
