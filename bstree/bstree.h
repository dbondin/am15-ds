/*
 * bstree.h
 *
 *  Created on: Mar 24, 2017
 *      Author: dbondin
 */

#ifndef BSTREE_H_
#define BSTREE_H_

template<class K, class V>
class bstree {
public:
	bstree();
	virtual ~bstree();
	virtual void add(const K & key, const V & value);
	virtual void del(const K & key);
	virtual bool find(const K & key, V & value);
	/**
	 * Caller MUST free the memory with delete [] after using this result
	 */
	virtual K * get_keys();
	virtual int get_count();
private:
	struct node {
		K key;
		V value;
		node * left;
		node * right;
	};
	node * root_node;
	node * find_or_create(node * n, node * parent, const K & key);
	bool is_equal(const K & key1, const K & key2);
	node * find_node(node * n, const K & key);
	int count;
	void fill_keys(node * n, K * keys, int & index);
};

#include "bstree.tpp"

#endif /* BSTREE_H_ */
