/*
 * HashMap.h
 *
 *  Created on: Apr 7, 2017
 *      Author: dbondin
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

template<class K, class V>
class HashMap {

private:

	struct Entry {
		K key;
		V value;
		Entry * next;
	};

public:

	class HashMapEntry {
	public:
		HashMapEntry();
		HashMapEntry(const K & _key, const V & _value);
		K key;
		V value;
	};

	class HashMapIterator {
	public:
		HashMapIterator(const HashMap * _hm);
		bool hasNext() const;
		const HashMapEntry & next();
	private:
		int index;
		Entry * pe;
		const HashMap * hm;
		HashMapEntry e;
	};

	static const int DEFAULT_SIZE = 16;

	HashMap(int _size = DEFAULT_SIZE);
	virtual ~HashMap();

	virtual void put(const K & key, const V & value);
	virtual const V & get(const K & key) const;
	virtual HashMapIterator & iterator() const;

private:

	int size;
	Entry ** table;

	unsigned int hash(const K & key) const;
};

#include "HashMap.hpp"

#endif /* HASHMAP_H_ */
