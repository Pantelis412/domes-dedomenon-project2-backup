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

void test_set_from_vector(void) {
	Vector vec_test= vector_create(0, NULL);
	vector_insert_last(vec_test, create_int(2));
	vector_insert_last(vec_test, create_int(1));
	vector_insert_last(vec_test, create_int(3));
	vector_insert_last(vec_test, create_int(0));
	Set test_set= set_from_vector(vec_test, compare_ints);
	TEST_ASSERT(test_set != NULL);
	TEST_ASSERT(set_size(test_set)==4);
	vector_insert_last(vec_test, create_int(0));
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



}

void test_set_traverse(void) {

}

void test_set_merge(void) {

}

void test_set_find_k_smallest(void) {

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
