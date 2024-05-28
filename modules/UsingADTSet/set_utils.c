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
	return NULL;
}

void set_traverse(Set set, TraverseFunc f) {

}

Set set_merge(Set set1, Set set2, CompareFunc compare) {
	return NULL;
}

Pointer set_find_k_smallest(Set set, int k) {
	return NULL;
}