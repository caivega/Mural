//
//  OperationQueue.h
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#ifndef __CinderCanvas__OperationQueue__
#define __CinderCanvas__OperationQueue__

#include <queue>
#include <thread>

namespace mural
{
    typedef std::function<void()> Operation;

    class OperationQueue
    {
        bool done;
        std::queue<Operation> mq;

        std::queue<Operation> bmq;
        std::queue<Operation> bmq2;
        int currentBmqIdx;

        std::unique_ptr<std::thread> thd;

    public:
        OperationQueue();
        ~OperationQueue();

        /* Operations run on a separate thread */
        void addOperation(Operation m);
        /* Operations run on a main thread (for OpenGL...) */
        void addBlockOperation(Operation m);

        static OperationQueue& defaultQueue()
        {
            static OperationQueue instance;
            return instance;
        }

        void doBlockOperations();

    private:
        // No copy
        OperationQueue(const OperationQueue&) {}
        void operator=(const OperationQueue&) {}
        
        void doUnblockOperations();
    };
    
}

#endif /* defined(__CinderCanvas__OperationQueue__) */
