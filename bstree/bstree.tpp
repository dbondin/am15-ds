/*
 * bstree.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: dbondin
 */

#include "bstree.h"

template<class K, class V>
bstree<K, V>::bstree() {
	root_node = NULL;
	count = 0;
}

template<class K, class V>
bstree<K, V>::~bstree() {
}

template<class K, class V>
void
bstree<K, V>::add(const K & key, const V & value) {
	if(root_node == NULL) {
		root_node = new bstree<K, V>::node();
		root_node->key = key;
		root_node->value = value;
		root_node->left = NULL;
		root_node->right = NULL;
		++count;
	}
	else {
		bstree<K, V>::node * n = find_or_create(root_node, NULL, key);
		n->value = value;
	}
}

template<class K, class V>
void
bstree<K, V>::del(const K & key) {
	
}

template<class K, class V>
bool
bstree<K, V>::find(const K & key, V & value) {
	bstree<K, V>::node * n = find_node(root_node, key);
	if(n != NULL) {
		value = n->value;
		return true;
	}
	return false;
}

template<class K, class V>
typename bstree<K, V>::node *
bstree<K, V>::find_node(node * n, const K & key) {
	if(n == NULL) {
		return NULL;
	}
	else if(n->key < key) {
		return find_node(n->right, key);
	}
	else if(key < n->key) {
		return find_node(n->left, key);
	}
	return n;
}

template<class K, class V>
typename bstree<K, V>::node *
bstree<K, V>::find_or_create(node * n, node * parent, const K & key) {
	if(n == NULL) {
		bstree<K, V>::node * new_node = new bstree<K, V>::node();
		new_node->key = key;
		new_node->left = NULL;
		new_node->right = NULL;
		++count;
		
		if(parent != NULL) {
			if(key < parent->key) {
				parent->left = new_node;
			}
			else if(parent->key < key) {
				parent->right = new_node;
			}
			else {
				// TODO: Fix this WTF
				throw "Wrong way !!!";
			}
		}
		
		return new_node;
	}
	else {
		if(key < n->key) {
			return find_or_create(n->left, n, key);
		}
		else if(n->key < key) {
			return find_or_create(n->right, n, key);
		}
		return n;
	}
}

template<class K, class V>
bool
bstree<K, V>::is_equal(const K & key1, const K & key2)
{
	return !((key1 < key2) || (key2 < key1));
}

template<class K, class V>
K *
bstree<K, V>::get_keys() {
	K * result = new K[get_count()];
	int index = 0;
	fill_keys(root_node, result, index);
	return result;
}

template<class K, class V>
void 
bstree<K, V>::fill_keys(node * n, K * keys, int & index) {
	if(n != NULL) {
		keys[index] = n->key;
		++index;
		fill_keys(n->left, keys, index);
		fill_keys(n->right, keys, index);
	}
}


template<class K, class V>
int
bstree<K, V>::get_count() {
	return count;
}