//
//  OperationQueue.cpp
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#include "OperationQueue.h"

namespace mural
{
    OperationQueue::OperationQueue():
        done(false),
        currentBmqIdx(1)
    {
        this->thd = std::unique_ptr<std::thread>(new std::thread([this] {
            this->doUnblockOperations();
        }));
    }
    OperationQueue::~OperationQueue()
    {
        this->addOperation([&]{
            done = true;
        });
        this->thd->join();

        // TODO: complete all block operations
    }
    void OperationQueue::addOperation(Operation m)
    {
        this->mq.push(m);
    }
    void OperationQueue::addBlockOperation(Operation m)
    {
        if (this->currentBmqIdx == 1) {
            this->bmq.push(m);
        }
        else {
            this->bmq2.push(m);
        }
    }
    void OperationQueue::doBlockOperations()
    {
        if (this->currentBmqIdx == 1) {
            // Swap queue
            this->currentBmqIdx = 2;

            while (this->bmq.size() > 0) {
                Operation msg = this->bmq.front();
                bmq.pop();
                msg();
            }
        }
        else {
            // Swap queue
            this->currentBmqIdx = 1;

            while (this->bmq2.size() > 0) {
                Operation msg = this->bmq2.front();
                bmq2.pop();
                msg();
            }
        }
    }
    void OperationQueue::doUnblockOperations()
    {
        while (!done) {
            if (this->mq.size() > 0) {
                Operation msg = this->mq.front();
                mq.pop();
                msg();
            }
        } // note: last message sets done to true
    }
}
