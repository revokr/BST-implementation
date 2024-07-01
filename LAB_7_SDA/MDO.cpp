#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	rel = r;
	rad = nullptr;
	size = 0;
}


void MDO::adauga(TCheie c, TValoare v) {
	rad = adauga_rec(rad, c, v);
	size++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
	return cauta_rec(rad, c);
}

bool MDO::sterge(TCheie c, TValoare v) {
	int init = dim();
	rad = sterge_rec(rad, c, v);
	return dim() < init;
}

int MDO::dim() const {
	return size;
}

bool MDO::vid() const {
	return rad == nullptr;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	/* de adaugat */
}
