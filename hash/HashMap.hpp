#include <exception>
#include <stdexcept>

template<class K, class V>
HashMap<K, V>::HashMap(int _size /* = DEFAULT_SIZE */) :
		size(_size) {
	table = new Entry*[size];
	for (int i = 0; i < size; ++i) {
		table[i] = NULL;
	}
}

template<class K, class V>
HashMap<K, V>::~HashMap() {
	for (int i = 0; i < size; ++i) {
		Entry * pe = table[i];
		while (pe != NULL) {
			Entry * next = pe->next;
			delete pe;
			pe = next;
		}
	}
	delete[] table;
}

template<class K, class V>
void HashMap<K, V>::put(const K & key, const V & value) {
	unsigned int index = hash(key) % size;
	Entry * pe = table[index];
	while (pe != NULL) {
		if (pe->key == key) {
			break;
		}
		pe = pe->next;
	}

	if (pe != NULL) {
		pe->value = value;
	} else {
		pe = new Entry;
		pe->key = key;
		pe->value = value;
		pe->next = table[index];
		table[index] = pe;
	}
}

template<class K, class V>
unsigned int HashMap<K, V>::hash(const K & key) const {

	const unsigned char * p = (const unsigned char *) &key;
	int a = 0;
	int keySize = sizeof(K);

	for (int i = 0; i < keySize; ++i, ++p) {
		a ^= *p;
	}

	return a;
}

template<class K, class V>
const V &
HashMap<K, V>::get(const K & key) const {
	unsigned int index = hash(key) % size;
	Entry * pe = table[index];
	while (pe != NULL) {
		if (pe->key == key) {
			break;
		}
		pe = pe->next;
	}

	if (pe == NULL) {
		throw std::runtime_error("No element found in map");
	}

	return pe->value;
}

template<class K, class V>
HashMap<K, V>::HashMapEntry::HashMapEntry(const K & _key, const V & _value): key(_key), value(_value) {
};

template<class K, class V>
HashMap<K, V>::HashMapEntry::HashMapEntry() {
};

template<class K, class V>
bool
HashMap<K, V>::HashMapIterator::hasNext() const {
	if(pe == NULL) {
		for(int i=0; i<hm->size; ++i) {
			if(hm->table[i] != NULL) {
				return true;
			}
		}
	}
	else {
		if(pe->next != NULL) {
			return true;
		}
		for(int i=index+1; i<hm->size; ++i) {
			if(hm->table[i] != NULL) {
				return true;
			}
		}
	}
	return false;
}

template<class K, class V>
const typename HashMap<K, V>::HashMapEntry &
HashMap<K, V>::HashMapIterator::next() {
	if(pe == NULL) {
		for(int i=0; i<hm->size; ++i) {
			if(hm->table[i] != NULL) {
				index = i;
				pe = hm->table[i];
				e.key = pe->key;
				e.value = pe->value;
				return e;
			}
		}
	}
	else {
		if(pe->next != NULL) {
			pe = pe->next;
			e.key = pe->key;
			e.value = pe->value;
			return e;
		}
		for(int i=index+1; i<hm->size; ++i) {
			if(hm->table[i] != NULL) {
				index = i;
				pe = hm->table[i];
				e.key = pe->key;
				e.value = pe->value;
				return e;
			}
		}
	}
	throw std::runtime_error("No next element can be reached");
	return e;
}

template<class K, class V>
HashMap<K, V>::HashMapIterator::HashMapIterator(const HashMap * _hm) {
	this->index = -1;
	this->pe = NULL;
	this->hm = _hm;
}
;

template<class K, class V>
typename HashMap<K, V>::HashMapIterator &
HashMap<K, V>::iterator() const {
	HashMapIterator * iter = new HashMapIterator(this);
	return *iter;
}
