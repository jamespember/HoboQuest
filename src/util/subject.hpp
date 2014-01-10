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
      typedef std::function<bool(Source&)> Observer;

      void observe(const EventId &event, Observer&& observer) {
        _observers[event].push_back(std::forward<Observer>(observer));
      }

      virtual void notify(const EventId &event, Source &source) {
        std::list<Observer> &observers = _observers.at(event);
        observers.remove_if([&source](const Observer &obs) {
          return !obs(source);
        });
      }

    protected:
      std::unordered_map<EventId, std::list<Observer>> _observers;
  };
} /* hoboquest */ 

#endif
