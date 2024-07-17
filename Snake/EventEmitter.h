#pragma once
#include<functional>
#include<string>
#include<unordered_map>

using namespace std;

class EventEmitter
{
private:
	unordered_map<string, function<void(void)>> events;
public:
	EventEmitter* on(const string name, function<void(void)> callback);
	EventEmitter* off(const string name);
	EventEmitter* emit(const string name);
};


template <typename K, typename V>
bool isKey(unordered_map<K, V>* map, K key);

