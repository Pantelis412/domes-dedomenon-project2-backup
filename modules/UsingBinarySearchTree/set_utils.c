///////////////////////////////////////////////////////////
//
// Υλοποίηση του set_utils για Sets βασισμένα σε Binary Search Tree.
//
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "set_utils.h"



// Χρησιμοποιούμε τη συγκεκριμένη υλοποίηση του UsingBinarySearchTree/ADTSet.c,
// οπότε γνωρίζουμε την ακριβή δομή για την αναπαράσταση των δεδομένων.
// Αντιγράφουμε εδώ τον ορισμό των structs ώστε να μπορούμε να προσπελάσουμε
// τα περιεχόμενά τους.

struct set {
	SetNode root;				// η ρίζα, NULL αν είναι κενό δέντρο
	int size;					// μέγεθος, ώστε η set_size να είναι Ο(1)
	CompareFunc compare;		// η διάταξη
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο του set
};

struct set_node {
	SetNode left, right;		// Παιδιά
	Pointer value;
};

void traverse_BST_insert_vector(Vector vector, SetNode node){
	if (node != NULL){
		traverse_BST_insert_vector(vector, node->left);
		vector_insert_last(vector, node->value);
		traverse_BST_insert_vector(vector, node->right);
	}
	return;
}

void traverse_BST_for_f(Set set, SetNode node, TraverseFunc f){
	if (node != NULL){
		traverse_BST_for_f(set, node->left, f);
		f(set, node->value);
		traverse_BST_for_f(set, node->right, f);
	}
	return;
}

Set set_from_vector(Vector vec, CompareFunc compare) {
	Vector sorted=vector_create(0, NULL), unsorted=vector_create(0, NULL);
	vector_insert_last(sorted, vector_node_value(vec, vector_first(vec)));
	for(VectorNode node =vector_next(vec, vector_first(vec)); node != VECTOR_EOF; node=vector_next(vec, node)){
		if(vector_node_value(vec, node) >= vector_node_value((sorted), vector_last(sorted)))
			vector_insert_last(sorted, vector_node_value(vec, node));
		else
			vector_insert_last(unsorted, vector_node_value(vec, node));
	}
	//Set set= set_create(compare, free);
	return NULL;
}

Vector set_to_vector(Set set) {
	Vector vector= vector_create(0,NULL);
	traverse_BST_insert_vector(vector, set->root);
	return vector;
}

void set_traverse(Set set, TraverseFunc f) {
	traverse_BST_for_f(set, set->root, f);
}

Set set_merge(Set set1, Set set2, CompareFunc compare) {
	return NULL;
}

Pointer set_find_k_smallest(Set set, int k) {
	return NULL;
}