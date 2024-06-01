//////////////////////////////////////////////////////////////////
//
// Unit tests για το set_utils.
// Οποιαδήποτε υλοποίηση οφείλει να περνάει όλα τα tests.
//
//////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing
#include "set_utils.h"

int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

// Επιστρέφει έναν ακέραιο σε νέα μνήμη με τιμή value
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int sum=0;
void f(Set set, Pointer value){
		sum+=*(int*)value;
		}

void test_set_from_vector(void) {
	Vector vec_test= vector_create(0, NULL);
	vector_insert_last(vec_test, create_int(2));
	vector_insert_last(vec_test, create_int(1));
	vector_insert_last(vec_test, create_int(3));
	vector_insert_last(vec_test, create_int(0));
	vector_insert_last(vec_test, create_int(0));
	Set test_set= set_from_vector(vec_test, compare_ints);
	TEST_ASSERT(test_set != NULL);
	TEST_ASSERT(set_size(test_set)==4);
	TEST_ASSERT(*(int*)set_node_value(test_set, set_first(test_set))==0);// τσεκάρω για διάταξη
	vector_destroy(vec_test);
	set_destroy(test_set);

}

void test_set_to_vector(void) {
	//Δημιουργώ vector και βαζω τα στοιχεία του στο set με τυχαία σειρά
	Vector vec_test= vector_create(0, NULL);
	vector_insert_last(vec_test, create_int(2));
	vector_insert_last(vec_test, create_int(1));
	vector_insert_last(vec_test, create_int(3));
	vector_insert_last(vec_test, create_int(0));
	Set test_set= set_from_vector(vec_test, compare_ints);
	vector_destroy(vec_test);
	// Βάζω τα στοιχεία του set ταξινομημένα σε καινούριο vector
	Vector vec_new = set_to_vector(test_set);
	set_destroy(test_set);
	TEST_ASSERT(vec_new != NULL);
	TEST_ASSERT(vector_size(vec_new) == 4);
	vector_destroy(vec_new);
}

void test_set_traverse(void) {
	Set set= set_create(compare_ints, free);
	set_insert(set, create_int(1));
	set_insert(set, create_int(4));
	set_insert(set, create_int(9));
	set_insert(set, create_int(12));
	set_traverse(set, f);
	TEST_ASSERT(sum==26);
	set_destroy(set);
}

void test_set_merge(void) {
	Set set1= set_create(compare_ints, free);
	set_insert(set1, create_int(1));
	set_insert(set1, create_int(4));
	set_insert(set1, create_int(9));
	set_insert(set1, create_int(12));

	Set set2= set_create(compare_ints, free);
	set_insert(set2, create_int(3));
	set_insert(set2, create_int(5));
	set_insert(set2, create_int(9));
	set_insert(set2, create_int(14));
	Set set = set_merge(set1, set2, compare_ints);
	TEST_ASSERT(set != NULL);
	TEST_ASSERT(set_size(set)==7);
	TEST_ASSERT(*(int*)set_node_value(set, set_first(set))==1);// τσεκάρω για διάταξη
	set_destroy(set1);
	set_destroy(set2);
	set_destroy(set);
}

void test_set_find_k_smallest(void) {
	Set set= set_create(compare_ints, free);
	set_insert(set, create_int(1));
	set_insert(set, create_int(9));
	set_insert(set, create_int(4));
	set_insert(set, create_int(12));
	Pointer test_pointer=set_find_k_smallest(set, 3);
	TEST_ASSERT(*(int*)test_pointer==9);
	set_destroy(set);
}


// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "test_set_import_from_vector",	test_set_from_vector },
	{ "test_set_export_to_vector",		test_set_to_vector },
	{ "test_set_traverse",				test_set_traverse },
	{ "test_set_merge",					test_set_merge },
	{ "test_set_find_k_smallest",		test_set_find_k_smallest },

	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
}; 
