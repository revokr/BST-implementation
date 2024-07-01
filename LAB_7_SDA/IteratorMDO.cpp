#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	prim();
}

void IteratorMDO::prim() {
	if (dict.rel(5, 4) == true) {
		while (!stiva.empty())
			stiva.pop();
		curent = dict.rad;
		while (curent != nullptr) {
			stiva.push(curent);
			curent = curent->dr;
		}
		if (!stiva.empty()) {
			curent = stiva.top();
		}
		else {
			curent = nullptr;
		}
	}
	else if (dict.rel(4, 5) == true) {
		while (!stiva.empty())
			stiva.pop();
		curent = dict.rad;
		while (curent != nullptr) {
			stiva.push(curent);
			curent = curent->st;
		}
		if (!stiva.empty()) {
			curent = stiva.top();
		}
		else {
			curent = nullptr;
		}
	}
}

void IteratorMDO::urmator() {
	if (dict.rel(5, 4) == true) {
		if (!valid())
			return;
		Nod* nod = stiva.top();
		stiva.pop();

		if (nod->st != nullptr) {
			nod = nod->st;
			while (nod != nullptr) {
				stiva.push(nod);
				nod = nod->dr;
			}
		}

		if (!stiva.empty())
			curent = stiva.top();
		else
			curent = nullptr;
	}
	else if (dict.rel(4, 5) == true){
		if (!valid())
			return;
		Nod* nod = stiva.top();
		stiva.pop();

		if (nod->dr != nullptr) {
			nod = nod->dr;
			while (nod != nullptr) {
				stiva.push(nod);
				nod = nod->st;
			}
		}

		if (!stiva.empty())
			curent = stiva.top();
		else
			curent = nullptr;
	}

}

bool IteratorMDO::valid() const {
	return curent != nullptr;
}

TElem IteratorMDO::element() const {
	return { curent->k, curent->v };
}


