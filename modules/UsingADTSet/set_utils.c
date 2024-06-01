///////////////////////////////////////////////////////////
//
// Υλοποίηση του set_utils με γενικό τρόπο, χρησιμοποιώντας
// μια οποιαδήποτε υλοποίηση του ADT Set.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>

#include "set_utils.h"


Set set_from_vector(Vector vec, CompareFunc compare) {
	Set set = set_create(compare, free);
	for(int i=0; i<vector_size(vec); i++){
		set_insert(set, vector_get_at(vec, i));
	}
	return set;
}

Vector set_to_vector(Set set) {
	Vector vector = vector_create(0, NULL);
	SetNode setnode= set_first(set);
	for(int i=0; i<set_size(set); i++){
		vector_insert_last(vector, set_node_value(set, setnode));
		setnode=set_next(set, setnode);		
	}
	return vector;
}

void set_traverse(Set set, TraverseFunc f) {
	for( SetNode node=set_first(set); node!= SET_EOF; node= set_next(set, node)){
		f(set, set_node_value(set, node));
	}
}

Set set_merge(Set set1, Set set2, CompareFunc compare) {
	return NULL;
}

Pointer set_find_k_smallest(Set set, int k) {
	return NULL;
}