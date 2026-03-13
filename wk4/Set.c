#include "Set.h"

struct set {
    int *arr;
    int numElems;
    int capacity;
};

#define INITIAL_CAPACITY 8

// Creates a new empty set
Set SetNew(void) {
    Set s = malloc(sizeof(struct set));
    s->arr = malloc(INITIAL_CAPACITY * sizeof(int));
    s->numElems = 0;
    s->capacity = INITIAL_CAPACITY;
    return s;
}

// Frees memory allocated to the set
void SetFree(Set s) {
    free(s->arr);
    free(s);
}

// Amortized time complexity = O(1)

// on any single call to this function, the worst case time complexity is O(n)
// on a span of many calls
//  O(1), O(1), O(1), .... n times, O(n); O(1), O(1), ... n*2, O(2n), ... etc.

// Inserts an element into the set
void SetInsert(Set s, int elem) {
    // if (SetContains(s, elem)) return;

    // if we double every time,
    // we only run this code, once every n insertions, guaranteed
    if (s->numElems == s->capacity) {
        s->arr = realloc(s->arr, 2 * s->capacity * sizeof(int));
        s->capacity *= 2;
    }

    s->arr[s->numElems] = elem;
    s->numElems++;
}

// Deletes an element from the set
void SetDelete(Set s, int elem) {
    if (!SetContains(s, elem)) return;

    bool startShifting = false;
    for (int i = 0; i < s->numElems; i++) {
        if (startShifting) {
            s[i - 1] = s[i];
        }

        if (s->arr[i] == elem) {
            startShifting = true;
        }
    }

    s->numElems--;
}

// Returns true if the given element is in the set, and false otherwise
bool SetContains(Set s, int elem) {
    for (int i = 0; i < s->numElems; i++) {
        if (s->arr[i] == elem) return true;
    }
    return false;
}

// Returns the number of elements in the set
int SetSize(Set s) {
    return s->numElems;
}