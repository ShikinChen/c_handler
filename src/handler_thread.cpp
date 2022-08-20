//
// Created by Shiki on 2022/8/20.
//

#include "handler_thread.h"

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include "looper.h"


HandlerThread* CreateThread(char *name) {
  int thr_len = sizeof(thr_len);
  HandlerThread *thread = (HandlerThread*)malloc(thr_len);
  memset(thread, 0x0, thr_len);
  int len = strlen(name);
  char *thr_name = (char*)malloc(len + 1);
  memset(thr_name, 0x0, len + 1);
  sprintf(thr_name, "%s", name);
  thread->name_ = thr_name;
  int loo_len = sizeof(Looper);
  Looper *looper = (Looper*)malloc(loo_len);
  memset(looper, 0x0, loo_len);
  char *loo_name = (char*)malloc(len + 1);
  memset(loo_name, 0x0, len + 1);
  sprintf(loo_name, "%s", name);
  looper->name_ = loo_name;
  int loc_len = sizeof(pthread_mutex_t);
  looper->lock_ = (pthread_mutex_t*)malloc(loc_len);
  memset(looper->lock_, 0x0, loc_len);
  pthread_mutex_init(looper->lock_, NULL);
  int attr_len = sizeof(pthread_condattr_t);
  looper->waitattr_ = (pthread_condattr_t*)malloc(attr_len);
  memset(looper->waitattr_, 0x0, attr_len);
  pthread_condattr_init(looper->waitattr_);
  int con_len = sizeof(pthread_cond_t);
  looper->wait_ = (pthread_cond_t*)malloc(con_len);
  memset(looper->wait_, 0x0, con_len);
  pthread_cond_init(looper->wait_, looper->waitattr_);
  looper->queue_ = NULL;
  looper->quit_ = false;
  thread->looper_ = looper;
  return thread;
}


void StartThread(HandlerThread *thread) {
  thread->status_ = pthread_create(&thread->tid_, NULL, (void *(*)(void*))&StartLooper, thread->looper_);
}

void ThreadJoin(HandlerThread *thread) {
  if (thread->status_ == 0) {
	pthread_join(thread->tid_, NULL);
  }
}

void QuitThread(HandlerThread *thread) {
  QuitLooper(thread->looper_);
}