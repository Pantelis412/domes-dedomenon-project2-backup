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

Vector vector_bubble_sort(Vector vector){
	Pointer temp;
	for(int i=1; i<=vector_size(vector)-1; i++){
		for(int j=vector_size(vector) -1; j>=i; j--){
			if(*(int*)vector_get_at(vector, j-1)>*(int*)vector_get_at(vector, j)){
				temp=vector_get_at(vector, j);
				vector_set_at(vector, j, vector_get_at(vector, j-1));
				vector_set_at(vector, j-1, temp);
			}
		}
	}
	return vector;
}

Vector two_vector_merge(Vector vector1, Vector vector2){
	Vector vector= vector_create(0, NULL);
	int i=0, j=0;
	while(i<vector_size(vector1) && j<vector_size(vector2)){
		if(*(int*)vector_get_at(vector1, i) <= *(int*)vector_get_at(vector2, j)){
			vector_insert_last(vector, vector_get_at(vector1, i));
			i++;
		}
		else{
			vector_insert_last(vector, vector_get_at(vector2, j));
			j++;
		}
	}
	if(i==vector_size(vector1)){
		while(j<vector_size(vector2)){
			vector_insert_last(vector, vector_get_at(vector2, j));
			j++;
		}
	}
	else{
		while(i<vector_size(vector1)){
			vector_insert_last(vector, vector_get_at(vector1, i));
			i++;
		}
	}
	return vector;
}

Set create_tree_set(Set set, Vector vector, int first, int last){
	int mid=(first+last)/2;
	set_insert(set,vector_get_at(vector, mid));
	if(first<last){
		create_tree_set(set, vector, first, mid-1);
		create_tree_set(set, vector, mid+1, last);
	}
	return set;
}

Set set_from_vector(Vector vec, CompareFunc compare) {
	//Διαχωρίζουμε το vector σε 2: ταξινομημένο και μη ταξινομημένο
	Vector sorted=vector_create(0, NULL), unsorted=vector_create(0, NULL);
	vector_insert_last(sorted, vector_node_value(vec, vector_first(vec)));
	for(VectorNode node =vector_next(vec, vector_first(vec)); node != VECTOR_EOF; node=vector_next(vec, node)){
		if(*(int*)vector_node_value(vec, node) >= *(int*)vector_node_value((sorted), vector_last(sorted)))
			vector_insert_last(sorted, vector_node_value(vec, node));
		else
			vector_insert_last(unsorted, vector_node_value(vec, node));
	}
	//Ταξινομώ το vector
	unsorted= vector_bubble_sort(unsorted);

	//Συγχωνεύω τα δύο vectors
	Vector vector=vector_create(0, NULL);
	vector= two_vector_merge(sorted, unsorted);
	
	//Δημιουργώ το set από το vector
	Set set= set_create(compare, NULL);
	int left=0;
	int right=vector_size(vector)-1;
	set = create_tree_set(set, vector, left, right);
	return set;
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
	Vector vector1=set_to_vector(set1);
	Vector vector2=set_to_vector(set2);
	Vector vector=two_vector_merge(vector1, vector2);
	int left=0;
	int right=vector_size(vector)-1;
	Set set=set_create(compare, NULL);
	set = create_tree_set(set, vector, left, right);
	return set;
}

Pointer set_find_k_smallest(Set set, int k) {
	return NULL;
}