#include "EventEmitter.h"
#include <stdexcept>
#include <unordered_map>

EventEmitter* EventEmitter::on(string name, function<void(void)> callback)
{
	if (name.length() < 1) return this;
	events[name] = callback;
	return this;
}

EventEmitter* EventEmitter::off(const string name)
{
	if (name.length() < 1) return this;
	events.erase(name);
	return this;
}

EventEmitter* EventEmitter::emit(string name)
{
	if (isKey<string, function<void(void)>>(&events, name))
	{
		function<void(void)> callback = events[name];
		callback();
	}
	return this;
}

template<typename K, typename V>
bool isKey(unordered_map<K, V>* _map, K key)
{
	try
	{
		V val = _map->at(key);
	}
	catch (std::out_of_range& error)
	{
		return false;
	}
	return true;
}



