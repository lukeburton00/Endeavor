    #include "Subject.hpp"
    
    void Subject::addObserver(std::shared_ptr<Observer> observer)
    {
        mObservers.push_back(observer);
    }
    void Subject::removeObserver(std::shared_ptr<Observer> observer)
    {
        mObservers.erase(remove(mObservers.begin(), mObservers.end(), observer));
    }

    void Subject::notify(void* data)
    {
        for (int i = 0; i < mObservers.size(); i++)
        {
            mObservers[i]->onNotify(data);
        }
    }