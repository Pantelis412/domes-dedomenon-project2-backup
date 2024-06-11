///////////////////////////////////////////////////////////
//
// Υλοποίηση του set_utils με γενικό τρόπο, χρησιμοποιώντας
// μια οποιαδήποτε υλοποίηση του ADT Set.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>

#include "set_utils.h"

//Βοηθητική συνάρτηση

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
	Vector vector1=set_to_vector(set1);
	Vector vector2=set_to_vector(set2);
	Vector vector=two_vector_merge(vector1, vector2);
	Set set=set_from_vector(vector, compare);
	vector_destroy(vector1);
	vector_destroy(vector2);
	vector_destroy(vector);
	return set;
}

Pointer set_find_k_smallest(Set set, int k) {
	SetNode node=set_first(set);
	for(int i=0; i< k; i++){
		node=set_next(set, node);
	}
	return set_node_value(set, node);
}