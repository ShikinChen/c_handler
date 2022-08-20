//
// Created by Shiki on 2022/8/20.
//
#include "looper.h"


#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


void FreeMessageQueue(MessageQueue *queue) {
  FreeProxy(queue->msg_);
  if (queue->next_ != NULL) {
	FreeMessageQueue(queue->next_);
  }
  free(queue);
}

void StartLooper(Looper *looper) {
  for(;;) {
	MessageQueue *next = NextMessage(looper);
	long wait = -1;
	if (next != NULL) {
	  struct timeval tv;
	  gettimeofday(&tv, NULL);
	  long now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	  if (now >= next->msg_->time_) {
		if (next->msg_->run_ != NULL) {
		  next->msg_->run_();
		}
		if (next->msg_->target_ != NULL) {
		  next->msg_->target_(next->msg_->msg_);
		}
		FreeMessageQueue(next);
		continue;
	  } else {
		pthread_mutex_lock(looper->lock_);
		next->next_ = looper->queue_;
		looper->queue_ = next;
		pthread_mutex_unlock(looper->lock_);
		wait = next->msg_->time_ - now;
	  }
	}
	if (looper->quit_) {
	  FreeLooper(looper);
	  break;
	}
	if (wait != -1) {
	  struct timeval now;
	  struct timespec outime;
	  gettimeofday(&now, NULL);
	  long sec = wait / 1000;
	  long msec = wait % 1000;
	  long usec = now.tv_usec + msec * 1000;
	  outime.tv_sec = now.tv_sec + sec + (usec / 1000000);
	  usec = usec % 1000000;
	  outime.tv_nsec = usec * 1000;
	  pthread_mutex_lock(looper->lock_);
	  pthread_cond_timedwait(looper->wait_, looper->lock_, &outime);
	  pthread_mutex_unlock(looper->lock_);
	} else {
	  pthread_mutex_lock(looper->lock_);
	  pthread_cond_wait(looper->wait_, looper->lock_);
	  pthread_mutex_unlock(looper->lock_);
	}
  }
}

void AddMessage(Looper *looper, MessageProxy *msg) {
  pthread_mutex_lock(looper->lock_);
  int size = sizeof(MessageQueue);
  MessageQueue *queue = (MessageQueue*)malloc(size);
  memset(queue, 0x0, size);
  queue->msg_ = msg;
  if (looper->queue_ == NULL) {
	looper->queue_ = queue;
  } else {
	MessageQueue *prev = looper->queue_;
	if (prev->msg_->time_ > queue->msg_->time_) {
	  queue->next_ = prev;
	  looper->queue_ = queue;
	} else {
	  while(prev->next_ != NULL) {
		if (prev->next_->msg_->time_ > queue->msg_->time_) {
		  queue->next_ = prev->next_;
		  break;
		}
		prev = prev->next_;
	  }
	  prev->next_ = queue;
	}
  }
  pthread_mutex_unlock(looper->lock_);
  pthread_cond_signal(looper->wait_);
}

MessageQueue* NextMessage(Looper *looper) {
  MessageQueue *next = NULL;
  pthread_mutex_lock(looper->lock_);
  if (looper->queue_ != NULL) {
	next = looper->queue_;
	looper->queue_ = looper->queue_->next_;
	next->next_ = NULL;
  }
  pthread_mutex_unlock(looper->lock_);
  return next;
}

void QuitLooper(Looper *looper) {
  pthread_mutex_lock(looper->lock_);
  FreeMessageQueue(looper->queue_);
  looper->queue_ = NULL;
  looper->quit_;
  pthread_mutex_unlock(looper->lock_);
  pthread_cond_signal(looper->wait_);
}

void FreeLooper(Looper *looper) {
  free(looper->name_);
  pthread_condattr_destroy(looper->waitattr_);
  free(looper->waitattr_);
  pthread_cond_destroy(looper->wait_);
  free(looper->wait_);
  pthread_mutex_destroy(looper->lock_);
  free(looper->lock_);
  free(looper);
}