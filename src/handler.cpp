//
// Created by Shiki on 2022/8/20.
//

#include "handler.h"
#include <memory>
#include <sys/time.h>

Handler* CreateHandler(Looper *looper, HandlerMessage handler) {
  int size = sizeof(Handler);
  Handler *hand = (Handler*)malloc(size);
  memset(hand, 0x0, size);
  hand->looper_ = looper;
  hand->target_ = handler;
  return hand;
}

void SendMessage(Handler *handler, Message *msg) {
  MessageProxy *proxy = CreateProxy(msg, handler->target_);
  proxy->time_ = 0;
  AddMessage(handler->looper_, proxy);
}

void SendMessage(Handler *handler, Message *msg, long delay) {
  MessageProxy *proxy = CreateProxy(msg, handler->target_);
  struct timeval tv;
  gettimeofday(&tv, NULL);
  long now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  proxy->time_ = now + delay;
  AddMessage(handler->looper_, proxy);
}

void PostCallback(Handler *handler, Runnable callback) {
  MessageProxy *proxy = CreateProxy(callback);
  proxy->time_ = 0;
  AddMessage(handler->looper_, proxy);
}

void PostCallback(Handler *handler, Runnable callback, long delay) {
  MessageProxy *proxy = CreateProxy(callback);
  struct timeval tv;
  gettimeofday(&tv, NULL);
  long now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  proxy->time_ = now + delay;
  AddMessage(handler->looper_, proxy);
}

void FreeHandler(Handler *handler) {
  free(handler);
}