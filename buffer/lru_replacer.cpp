//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {
    head = new ListNode(-1);
    tail = new ListNode(-1);
    head->next = tail;
    head->pre = tail;
    tail->pre = head;
    tail->next = head;
    max_cap = num_pages;
    size = 0;
}

LRUReplacer::~LRUReplacer(){
    temp = head;
    while(head != tail){
        head = head->next;
        delete temp;
        temp = head;
    }
    delete tail;
};

bool LRUReplacer::Victim(frame_id_t *frame_id) {
    latchs.lock();
    if(size == 0){
        latchs.unlock();
        return false;
    }
    *frame_id = tail->pre->frame_id;

    LRUReplacer::removenumber(tail->pre);
    rec.erase(*frame_id);
    size--;
    latchs.unlock();
    return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
    latchs.lock();
    if(rec.find(frame_id) == rec.end()){
        latchs.unlock();
        return ;
    }
    LRUReplacer::removenumber(rec[frame_id]);
    rec.erase(frame_id);
    size--;
    latchs.unlock();
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
    latchs.lock();
    if(rec.find(frame_id) == rec.end()){
        if(size >= max_cap){
            rec.erase(tail->pre->frame_id);
            LRUReplacer::removenumber(tail->pre);
            size--;
        }
        temp = new ListNode(frame_id);
        LRUReplacer::movetohead(temp);
        rec[frame_id] = head->next;
        size++;
    }
    latchs.unlock();
}

size_t LRUReplacer::Size() { 
    return size;
}

void LRUReplacer::movetohead(ListNode* node){
    node->next = head->next;
    head->next = node;
    node->next->pre = node;
    node->pre = head;
}

void LRUReplacer::removenumber(ListNode* node){
    node->next->pre = node->pre;
    node->pre->next = node->next;
}

}  // namespace bustub
