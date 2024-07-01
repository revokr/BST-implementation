#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;
typedef std::vector<TValoare> TList;

#include <utility>
typedef std::pair<TCheie, std::vector<TValoare>> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

//typedef struct Nod {
//	TCheie k;
//	vector<TValoare> v;
//	Nod* st, * dr;
//}Nod;

struct Nod {
	TCheie k;
	std::vector<TValoare> v;
	Nod* st;
	Nod* dr;

	Nod(TCheie c, TValoare v) : k(c), v({ v }), st(nullptr), dr(nullptr) {}
};



class MDO {
	friend class IteratorMDO;
private:
	Nod* rad;
	Relatie rel;
	int size;

	Nod* minim(Nod* p) {
		while (p->st != nullptr)
			p = p->st;
		return p;
	}


	Nod* adauga_rec(Nod* p, TCheie c, TValoare v) {
		if (p == nullptr) {
			p = new Nod(c, v);
			return p;
		}
		if (p->k == c)
			p->v.push_back(v);
		else if (c < p->k) {
			p->st = adauga_rec(p->st, c, v);
		}
		else if (c > p->k) {
			p->dr = adauga_rec(p->dr, c, v);
		}
		
		return p;
	}

	Nod* sterge_rec(Nod* rad, TCheie c, TValoare v) {
		if (rad == nullptr) {
			return rad;
		}
		if (c < rad->k) {
			rad->st = sterge_rec(rad->st, c, v);
		}
		else if (c > rad->k) {
			rad->dr = sterge_rec(rad->dr, c, v);
		}
		else {
			auto it = std::find(rad->v.begin(), rad->v.end(), v);
			if (it != rad->v.end()) {
				rad->v.erase(it);
				size--;
				if (rad->v.empty()) {
					if (rad->st == nullptr) {
						Nod* temp = rad->dr;
						delete rad;
						return temp;
					}
					else if (rad->dr == nullptr) {
						Nod* temp = rad->st;
						delete rad;
						return temp;
					}
					else {
						Nod* temp = minim(rad->dr);
						rad->k = temp->k;
						rad->v = temp->v;
						rad->dr = sterge_rec(rad->dr, temp->k, temp->v[0]);
					}
				}
			}
		}
		return rad;
	}

	vector<TValoare> cauta_rec(Nod* p, TCheie c) const{
		if (p == nullptr) {
			vector<TValoare> gf;
			return gf;
		}
		if (c < p->k) {
			return cauta_rec(p->st, c);
		}
		else if (c > p->k)
				return cauta_rec(p->dr, c);
		else
			return p->v;
		
	}
public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

};
