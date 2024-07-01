#include <iostream>
#include "MDO.h"
#include "IteratorMDO.h"
#include "TestScurt.h"
#include "TestExtins.h"

void afisare(IteratorMDO& it) {
    while(it.valid()) {
        std::cout << it.element().first << " -- ";
        for (auto i : it.element().second) {
            std::cout << i << " ";
        }
        std::cout << "\n";
        it.urmator();
    }
}

bool relatie2(TCheie cheie1, TCheie cheie2) {
    if (cheie1 < cheie2) {
        return true;
    }
    else {
        return false;
    }
}

TCheie cea_mai_freq_cheie(MDO& mdo) {
    IteratorMDO it = mdo.iterator();
    int max = 0;
    TCheie maxim;
    while (it.valid()) {
        TElem el = it.element();
        std::vector<TValoare> vals = mdo.cauta(el.first);
        if (vals.size() > max) {
            max = vals.size();
            maxim = el.first;
        }
        it.urmator();
    }
    return maxim;

}


int main() {
    testAll();
    testAllExtins();


    MDO dictOrd = MDO(relatie2);
    dictOrd.adauga(1, 2);
    dictOrd.adauga(55, 1);
    dictOrd.adauga(5, 1);
    dictOrd.adauga(1, 1);
    dictOrd.adauga(2, 1);
    dictOrd.adauga(3, 1);
    dictOrd.adauga(3, 2);
    dictOrd.adauga(3, 4);
    IteratorMDO it = dictOrd.iterator();
    it.prim();
    //afisare(it);
    TCheie ch = cea_mai_freq_cheie(dictOrd);

    std::cout << "Cea mai frecventa cheie este : " << ch << '\n';

    std::cout << "Finished Tests!" << std::endl;
}
