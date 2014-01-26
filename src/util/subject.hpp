#ifndef HOBO_SUBJECT
#define HOBO_SUBJECT

#include <memory>
#include <string> 
#include <unordered_map>
#include <list>
#include <algorithm>

namespace hoboquest {
  template <class Source>
  class Subject {
    public:
      typedef std::string EventId;
      typedef std::function<bool(std::shared_ptr<Source>)> Observer;

      void observe(const EventId &event, Observer&& observer) {
        _observers[event].push_front(std::forward<Observer>(observer));
      }

      virtual void notify(const EventId &event, std::shared_ptr<Source> source) {
        if (!_observers.count(event))
          return;
        auto &list = _observers.at(event);
        auto new_end = std::remove_if(list.begin(), list.end(), [&source](const Observer &obs) {
          return !obs(source);
        });
        list.erase(new_end, list.end());

        // The following should work, but will result in duplicate calls when an observer is removed
        // _observers.at(event).remove_if([&source](const Observer &obs) {
          // std::cout << "notifying an observer\n";
          // return !obs(source);
        // });
      }

    protected:
      std::unordered_map<EventId, std::list<Observer>> _observers;
  };
} /* hoboquest */ 

#endif
